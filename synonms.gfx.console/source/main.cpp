#include <iostream>

#include <gfx\environment\camera.h>
#include <gfx\environment\light.h>
#include <gfx\environment\perspective-view.h>
#include <gfx\environment\orthographic-view.h>
#include <gfx\gui\gui-helper.h>
#include <gfx\io\file-system.h>
#include <gfx\io\image.h>
#include <gfx\materials\pbr-material.h>
#include <gfx\materials\material.h>
#include <gfx\materials\texture-factory.h>
#include <gfx\transforms\matrix4x4.h>
#include <gfx\mathematics\maths-helper.h>
#include <gfx\output\pane.h>
#include <gfx\primitives\mesh.h>
#include <gfx\primitives\mesh-instance.h>
#include <gfx\primitives\primitive-factory.h>
#include <gfx\shaders\buffer-shader.h>
#include <gfx\shaders\phong-shader.h>
#include <gfx\shaders\shadowmap-shader.h>
#include <gfx\shaders\normal-shader.h>
#include <gfx\shaders\pbr-shader.h>
#include <gfx\shaders\deferred-gbuffer-shader.h>
#include <gfx\shaders\deferred-lighting-shader.h>

#include <opengl\state-manager.h>
#include <opengl\system.h>
#include <opengl\window.h>
#include <opengl\factories\frame-buffer-factory.h>
#include <opengl\factories\render-buffer-factory.h>

using namespace synonms::gfx::environment;
using namespace synonms::gfx::gui;
using namespace synonms::gfx::io;
using namespace synonms::gfx::materials;
using namespace synonms::gfx::mathematics;
using namespace synonms::gfx::transforms;
using namespace synonms::gfx::geometry;
using namespace synonms::gfx::output;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;

using namespace synonms::gfx::api;

/*
RENDERER (Implementation agnostic)
-----------------------------------
2D/3D renderer (forward/deferred)
Scene Graph
Sorting
Culling
Materials
LOD
Animation
Camera
VFX
PostFX
Reflections/AO etc.

RENDER API (implementation specific)
--------------------------------------
Render Context
Swap Chain
Framebuffer
Vertex Buffer
Index Buffer
Texture
Shader
States
Pipelines
Render Passes
*/


//static void glfw_error_callback(int error, const char* description)
//{
//    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//}

int main(int, char**)
{
    // Setup window
//    glfwSetErrorCallback(glfw_error_callback);
    auto windowWidth = 2048;
    auto windowHeight = 1024;
    auto debugWindowWidth = windowWidth / 4;
    auto debugWindowHeight = windowHeight / 4;
    auto shadowMapSize = 1024;
    

    // SYSTEM ********************
    if (!opengl::System::Initialise())
    {
        throw std::exception("Failed to intialise system");
    }

//    opengl::StateManager::SetBlendFunction(opengl::enumerators::BlendFactor::SourceAlpha, opengl::enumerators::BlendFactor::OneMinusSourceAlpha);
//    opengl::StateManager::EnableBlending();


    // WINDOW *******************
    opengl::Window::SetOpenGlContextVersion(3, 3);
    opengl::Window::SetOpenGlProfile(opengl::enumerators::OpenGlProfile::Core);
    opengl::Window::SetSwapInterval(1);

    opengl::Window window(windowWidth, windowHeight, "GFX");
    window.MakeCurrent();


    // GLEW EXTENSIONS **************
    opengl::System::InitialiseExtensions();


    // PANES **********************
    std::cout << "Creating panes..." << std::endl;

    Pane mainPane(0, 0, windowWidth, windowHeight);
    Pane debugPane1((windowWidth / 4) * 3, (windowHeight / 4) * 3, debugWindowWidth, debugWindowHeight);
    Pane debugPane2((windowWidth / 4) * 3,  windowHeight / 2,      debugWindowWidth, debugWindowHeight);
    Pane debugPane3((windowWidth / 4) * 3, (windowHeight / 4),     debugWindowWidth, debugWindowHeight);
    Pane debugPane4((windowWidth / 4) * 3,  0,                     debugWindowWidth, debugWindowHeight);

    std::cout << "Panes created" << std::endl;


    // VIEW *******************
    PerspectiveView view(60.0f, static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 50.0f);
//    OrthographicView view(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 50.0f);


    // CAMERA *******************
    Camera camera;
    camera.position = Point3<float>{ 0.0f, 10.0f, 10.0f };
    camera.rotationDegrees = Vector3<float>{ 45.0f, 0.0f, 0.0f };


    // MATERIALS ***********************
    FileSystem fileSystem;


    Image planeAlbedoImage("D:\\Nick\\pictures\\textures\\floor\\PavingStones36_col.jpg");
    Image planeNormalImage("D:\\Nick\\pictures\\textures\\floor\\PavingStones36_nrm.jpg");
    Image planeRoughnessImage("D:\\Nick\\pictures\\textures\\floor\\PavingStones36_rgh.jpg");
    Image planeAOImage("D:\\Nick\\pictures\\textures\\floor\\PavingStones36_AO.jpg");
    // TODO
    Image planeDisplacementImage("D:\\Nick\\pictures\\textures\\floor\\PavingStones36_disp.jpg");

    PBRMaterial pavingStonesMaterial;
    pavingStonesMaterial.Albedo = TextureFactory::CreateColour(planeAlbedoImage);
    pavingStonesMaterial.Normal = TextureFactory::CreateColour(planeNormalImage);
    pavingStonesMaterial.Roughness = TextureFactory::CreateColour(planeRoughnessImage);
    pavingStonesMaterial.AmbientOcclusion = TextureFactory::CreateColour(planeAOImage);
    pavingStonesMaterial.SpecularColourF0 = Vector3<float>(0.04f, 0.04f, 0.04f);

    Image metalAlbedoImage("D:\\Nick\\pictures\\textures\\metals\\Metal03_col.jpg");
    Image metalNormalImage("D:\\Nick\\pictures\\textures\\metals\\Metal03_nrm.jpg");
    Image metalRoughnessImage("D:\\Nick\\pictures\\textures\\metals\\Metal03_rgh.jpg");
    Image metalMetallicImage("D:\\Nick\\pictures\\textures\\metals\\Metal03_met.jpg");
    // TODO
    Image metalDisplacementImage("D:\\Nick\\pictures\\textures\\metals\\Metal03_disp.jpg");

    PBRMaterial metalMaterial;
    metalMaterial.Albedo = TextureFactory::CreateColour(metalAlbedoImage);
    metalMaterial.Normal = TextureFactory::CreateColour(metalNormalImage);
    metalMaterial.Roughness = TextureFactory::CreateColour(metalRoughnessImage);
    metalMaterial.Metallic = TextureFactory::CreateColour(metalMetallicImage);
    metalMaterial.SpecularColourF0 = Vector3<float>(0.56f, 0.57f, 0.58f);


    auto lightMaterial = Material::Create()
        .WithDiffuseColour({ 1.0f, 1.0f, 1.0f, 1.0f })
        .WithEmissiveColour({ 1.0f, 1.0f, 1.0f });


    // SHADERS ***********************
    std::string phongVertexShaderSource = fileSystem.ReadFile("resources/shaders/phong.vertex.glsl");
    std::string phongFragmentShaderSource = fileSystem.ReadFile("resources/shaders/phong.fragment.glsl");

    PhongShader phongShader(phongVertexShaderSource, phongFragmentShaderSource);

    std::string shadowmapVertexShaderSource = fileSystem.ReadFile("resources/shaders/shadowmap.vertex.glsl");
    std::string shadowmapFragmentShaderSource = fileSystem.ReadFile("resources/shaders/shadowmap.fragment.glsl");

    ShadowmapShader shadowmapShader(shadowmapVertexShaderSource, shadowmapFragmentShaderSource);

    std::string bufferVertexShaderSource = fileSystem.ReadFile("resources/shaders/buffer.vertex.glsl");
    std::string bufferFragmentShaderSource = fileSystem.ReadFile("resources/shaders/buffer.fragment.glsl");

    BufferShader bufferShader(bufferVertexShaderSource, bufferFragmentShaderSource);

    std::string normalVertexShaderSource = fileSystem.ReadFile("resources/shaders/normal.vertex.glsl");
    std::string normalFragmentShaderSource = fileSystem.ReadFile("resources/shaders/normal.fragment.glsl");
    std::string normalGeometryShaderSource = fileSystem.ReadFile("resources/shaders/normal.geometry.glsl");

    NormalShader normalShader(normalVertexShaderSource, normalFragmentShaderSource, normalGeometryShaderSource);

    std::string pbrVertexShaderSource = fileSystem.ReadFile("resources/shaders/pbr.vertex.glsl");
    std::string pbrFragmentShaderSource = fileSystem.ReadFile("resources/shaders/pbr.fragment.glsl");

    PBRShader pbrShader(pbrVertexShaderSource, pbrFragmentShaderSource);

    std::string deferredGBufferVertexShaderSource = fileSystem.ReadFile("resources/shaders/deferred.gbuffer.vertex.glsl");
    std::string deferredGBufferFragmentShaderSource = fileSystem.ReadFile("resources/shaders/deferred.gbuffer.fragment.glsl");

    DeferredGBufferShader deferredGBufferShader(deferredGBufferVertexShaderSource, deferredGBufferFragmentShaderSource);

    std::string deferredLightingVertexShaderSource = fileSystem.ReadFile("resources/shaders/deferred.lighting.vertex.glsl");
    std::string deferredLightingFragmentShaderSource = fileSystem.ReadFile("resources/shaders/deferred.lighting.fragment.glsl");

    DeferredLightingShader deferredLightingShader(deferredLightingVertexShaderSource, deferredLightingFragmentShaderSource);

    // MESH **************************
    auto boxMesh = PrimitiveFactory::CreateBox(1.0f, 1.0f, 1.0f);
    auto planeMesh = PrimitiveFactory::CreatePlane(1.0f, 1.0f);
    auto screenQuad = PrimitiveFactory::CreatePlane(2.0f, 2.0f);

    MeshInstance planeInstance(*planeMesh.get());
    planeInstance.SetUniformScale(10.0f);
    planeInstance.rotationDegrees.x = -90.0f;

    MeshInstance boxInstance(*boxMesh.get());
    boxInstance.SetUniformScale(5.0f);
    boxInstance.position = Point3<float>(0.0f, 2.5f, 0.0f);

    MeshInstance lightInstance(*boxMesh.get());
    lightInstance.SetUniformScale(1.0f);

    std::cout << "Meshes created" << std::endl;
    std::cout << boxMesh->ToString() << std::endl;

    
    // BUFFERS **********************************
    auto offscreenColourTexture = TextureFactory::CreateColour(windowWidth, windowHeight);
    auto offscreenDepthStencilBuffer = opengl::factories::RenderBufferFactory::CreateDepthStencilBuffer(windowWidth, windowHeight);
    auto offscreenFrameBuffer = opengl::factories::FrameBufferFactory::CreateOffscreenBuffer(windowWidth, windowHeight, offscreenColourTexture->GetTextureId(), offscreenDepthStencilBuffer->GetRenderBufferId());

    auto shadowMapColourTexture = TextureFactory::CreateColour(shadowMapSize, shadowMapSize);
    auto shadowMapDepthTexture = TextureFactory::CreateDepth(shadowMapSize, shadowMapSize);
    auto shadowMapFrameBuffer = opengl::factories::FrameBufferFactory::CreateShadowmapBuffer(shadowMapSize, shadowMapSize, shadowMapDepthTexture->GetTextureId(), shadowMapColourTexture->GetTextureId());

    auto gBufferPositionTexture = TextureFactory::CreateGBufferPosition(windowWidth, windowHeight);
    auto gBufferNormalTexture = TextureFactory::CreateGBufferNormal(windowWidth, windowHeight);
    auto gBufferAlbedoSpecTexture = TextureFactory::CreateGBufferAlbedoWithSpecular(windowWidth, windowHeight);
    auto gBufferDepthStencilBuffer = opengl::factories::RenderBufferFactory::CreateDepthStencilBuffer(windowWidth, windowHeight);
    auto deferredRendererFrameBuffer = opengl::factories::FrameBufferFactory::CreateGBuffer(windowWidth, windowHeight, gBufferPositionTexture->GetTextureId(), gBufferNormalTexture->GetTextureId(), gBufferAlbedoSpecTexture->GetTextureId(), gBufferDepthStencilBuffer->GetRenderBufferId());


    // LIGHT **********************************
    Light sunLight(Light::LightType::Directional);
    sunLight.ambientColour = Vector4<float>(0.1f, 0.1f, 0.1f, 1.0f);
    sunLight.diffuseColour = Vector4<float>(1.0f, 1.0f, 1.0f, 1.0f);// , 1.0f);23.47f, 21.31f, 20.79f
    sunLight.specularColour = Vector4<float>(0.5f, 0.5f, 0.5f, 0.5f);
    sunLight.intensityMultiplier = 1.0f;
    sunLight.target = Point3<float>(0.0f, 0.0f, 0.0f);
    sunLight.position = Point3<float>(0.0f, 10.0f, 10.0f);
    sunLight.isEnabled = true;
    sunLight.radiance = Vector3<float>(23.47f, 21.31f, 20.79f);
    // TODO - figure out how to size this
    sunLight.shadowMapProjectionMatrix = OrthographicView(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 50.0f).GetProjectionMatrix();
    sunLight.shadowMapDepthTexture = shadowMapDepthTexture;


    // IMGUI **********************************
    auto imguiContext = GuiHelper::Initialise(window.GetWindow(), "#version 330 core");
    GuiHelper::ApplyDarkStyle();

    auto displaySize = GuiHelper::GetDisplaySize();
    auto displayFramebufferScale = GuiHelper::GetDisplayFramebufferScale();

    std::cout << "Initialisation complete" << std::endl;
    std::cout << "GUI displaySize: " << displaySize.x << "x" << displaySize.y << std::endl;
    std::cout << "GUI displayFramebufferScale: " << displayFramebufferScale.x << "x" << displayFramebufferScale.y << std::endl;

    std::cout << "Entering event loop..." << std::endl;

    Vector4<float> sceneAmbientColour(0.0f, 0.0f, 0.0f, 1.0f);

    while (!window.ShouldClose())
    {
        const auto currentWindowSize = window.GetSize();
        const auto currentWindowWidth = std::get<0>(currentWindowSize);
        const auto currentWindowHeight = std::get<1>(currentWindowSize);

        GuiHelper::NewFrame();

        auto projectionMatrix = view.GetProjectionMatrix();
        auto viewMatrix = camera.GetViewMatrix();

        // Draw Sun shadowmap
        {
            opengl::Window::SetViewport(0, 0, shadowMapSize, shadowMapSize);

            shadowMapFrameBuffer->Bind(opengl::enumerators::FramebufferTarget::Framebuffer);
            opengl::FrameBuffer::ClearColour(0.0f, 0.0f, 0.0f, 1.0f);
            opengl::FrameBuffer::Clear(opengl::enumerators::AttributeBit::ColourBuffer | opengl::enumerators::AttributeBit::DepthBuffer);
            opengl::StateManager::EnableDepthTesting();

            auto sunViewProjectionMatrix = sunLight.shadowMapProjectionMatrix * sunLight.GetViewMatrix();

            shadowmapShader.RenderOrthographic(sunViewProjectionMatrix, planeInstance.GetModelMatrix(), planeInstance.GetMesh());
            shadowmapShader.RenderOrthographic(sunViewProjectionMatrix, boxInstance.GetModelMatrix(), boxInstance.GetMesh());
        }

        mainPane.SetAsViewport();
        opengl::Window::SetViewport(0, 0, currentWindowWidth, currentWindowHeight);

        // Use GBuffer FBO
//        deferredRendererFrameBuffer->Bind(opengl::enumerators::FramebufferTarget::Framebuffer);
//        opengl::FrameBuffer::ClearColour(0.0f, 0.0f, 0.0f, 1.0f);
//        opengl::FrameBuffer::Clear(opengl::enumerators::AttributeBit::ColourBuffer | opengl::enumerators::AttributeBit::DepthBuffer);
//        opengl::StateManager::EnableDepthTesting();
//
//        // Geometry pass
//        {
//            lightInstance.position = sunLight.position;
//
//            auto planeModelMatrix = planeInstance.GetModelMatrix(); auto planeNormalMatrix = Matrix4x4::CreateNormalFrom(planeModelMatrix);
//            auto boxModelMatrix = boxInstance.GetModelMatrix(); auto boxNormalMatrix = Matrix4x4::CreateNormalFrom(boxModelMatrix);
//            auto lightModelMatrix = lightInstance.GetModelMatrix(); auto lightNormalMatrix = Matrix4x4::CreateNormalFrom(lightModelMatrix);
//
//            deferredGBufferShader.Render(DeferredGBufferShaderUniforms(projectionMatrix, viewMatrix, planeModelMatrix, planeNormalMatrix, pavingStonesMaterial), planeInstance.GetMesh());
//            deferredGBufferShader.Render(DeferredGBufferShaderUniforms(projectionMatrix, viewMatrix, boxModelMatrix, boxNormalMatrix, metalMaterial), boxInstance.GetMesh());
//            deferredGBufferShader.Render(DeferredGBufferShaderUniforms(projectionMatrix, viewMatrix, lightModelMatrix, lightNormalMatrix, metalMaterial), lightInstance.GetMesh());
//        }

        // Use Offscreen FBO
        offscreenFrameBuffer->Bind(opengl::enumerators::FramebufferTarget::Framebuffer);
        opengl::StateManager::EnableDepthTesting();
        opengl::FrameBuffer::ClearColour(0.0f, 0.0f, 0.0f, 1.0f);
        opengl::FrameBuffer::Clear(opengl::enumerators::AttributeBit::ColourBuffer | opengl::enumerators::AttributeBit::DepthBuffer | opengl::enumerators::AttributeBit::StencilBuffer);

        // Lighting pass
//        {
//            deferredLightingShader.Render(DeferredLightingShaderUniforms(camera.position, *gBufferPositionTexture, *gBufferNormalTexture, *gBufferAlbedoSpecTexture, sunLight), planeInstance.GetMesh());
//        }

        {
            lightInstance.position = sunLight.position;

            auto planeModelMatrix = planeInstance.GetModelMatrix(); auto planeNormalMatrix = Matrix4x4::CreateNormalFrom(planeModelMatrix);
            auto boxModelMatrix = boxInstance.GetModelMatrix(); auto boxNormalMatrix = Matrix4x4::CreateNormalFrom(boxModelMatrix);
//            auto lightModelMatrix = lightInstance.GetModelMatrix(); auto lightNormalMatrix = Matrix4x4::CreateNormalFrom(lightModelMatrix);

            pbrShader.Render(PBRShaderData(projectionMatrix, viewMatrix, planeModelMatrix, planeNormalMatrix, pavingStonesMaterial, camera, sunLight), planeInstance.GetMesh());
            pbrShader.Render(PBRShaderData(projectionMatrix, viewMatrix, boxModelMatrix, boxNormalMatrix, metalMaterial, camera, sunLight), boxInstance.GetMesh());
//            pbrShader.Render(PBRShaderData(projectionMatrix, viewMatrix, lightModelMatrix, lightNormalMatrix, metalMaterial, camera, sunLight), lightInstance.GetMesh());
        }

        // Revert to default buffer
        opengl::FrameBuffer::BindDefault(opengl::enumerators::FramebufferTarget::Framebuffer);

        opengl::StateManager::DisableDepthTesting();
        opengl::FrameBuffer::Clear(opengl::enumerators::AttributeBit::ColourBuffer | opengl::enumerators::AttributeBit::DepthBuffer | opengl::enumerators::AttributeBit::StencilBuffer);

        {
            // Draw buffers to panes
            opengl::Texture::ActivateSlot(0);

            offscreenColourTexture->Bind();
            mainPane.SetAsViewport();
            bufferShader.Render(0, *screenQuad.get());

//            gBufferPositionTexture->Bind();
//            debugPane1.SetAsViewport();
//            bufferShader.Render(0, *screenQuad.get());
//
//            gBufferNormalTexture->Bind();
//            debugPane2.SetAsViewport();
//            bufferShader.Render(0, *screenQuad.get());
//
//            gBufferAlbedoSpecTexture->Bind();
//            debugPane3.SetAsViewport();
//            bufferShader.Render(0, *screenQuad.get());

            shadowMapColourTexture->Bind();
            debugPane4.SetAsViewport();
            bufferShader.Render(0, *screenQuad.get());
        }

        GuiHelper::PushWindow("gfx", 100.0f, 100.0f, 400.0f, 400.0f);

        GuiHelper::CollapsingHeader("Box");
        GuiHelper::SliderFloat3("Translation", &boxInstance.position.x, -20.0f, 20.0f);
        GuiHelper::SliderFloat3("Scale", &boxInstance.scale.x, 1.0f, 20.0f);
        GuiHelper::SliderFloat3("Rotation", &boxInstance.rotationDegrees.pitch, -180.0f, 180.0f);

        GuiHelper::CollapsingHeader("Light");
        GuiHelper::SliderFloat3("Position", &sunLight.position.x, -20.0f, 20.0f);
        GuiHelper::SliderFloat3("Target", &sunLight.target.x, -20.0f, 20.0f);
        GuiHelper::SliderFloat3("Radiance", &sunLight.radiance.red, 0.0f, 20.0f);

        GuiHelper::CollapsingHeader("Debug");

        GuiHelper::Text("DEBUG STUFF HERE");

        GuiHelper::PopWindow();

        GuiHelper::Render();

        window.SwapBuffers();

        opengl::System::PollEvents();
    }

    GuiHelper::Shutdown();

    std::cout << "Event loop ended" << std::endl;

    std::cout << "Press a key to quit..." << std::endl;	
    std::cin.get();

    return 0;
}

