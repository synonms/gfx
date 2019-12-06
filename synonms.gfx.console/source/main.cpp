#include <iostream>

#include <vendor\glm\glm.hpp>
#include <vendor\glm\gtc\matrix_transform.hpp>

#include <gfx\enumerators\texture-slot.h>
#include <gfx\environment\camera.h>
#include <gfx\environment\light.h>
#include <gfx\environment\perspective-view.h>
#include <gfx\gui\gui-helper.h>
#include <gfx\io\file-system.h>
#include <gfx\materials\material.h>
#include <gfx\mathematics\linear\matrix4x4.h>
#include <gfx\mathematics\maths-helper.h>
#include <gfx\output\pane.h>
#include <gfx\primitives\mesh.h>
#include <gfx\primitives\mesh-instance.h>
#include <gfx\primitives\primitive-factory.h>
#include <gfx\shaders\buffer-shader.h>
#include <gfx\shaders\phong-shader.h>
#include <gfx\shaders\shadowmap-shader.h>

#include <opengl\state-manager.h>
#include <opengl\system.h>
#include <opengl\window.h>
#include <opengl\factories\frame-buffer-factory.h>
#include <opengl\factories\render-buffer-factory.h>
#include <opengl\factories\texture-factory.h>

using namespace synonms::gfx::enumerators;
using namespace synonms::gfx::environment;
using namespace synonms::gfx::gui;
using namespace synonms::gfx::io;
using namespace synonms::gfx::materials;
using namespace synonms::gfx::mathematics;
using namespace synonms::gfx::mathematics::linear;
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

Vector4<float> CalculateAmbient(const Light& light, const Material& material)
{
    GuiHelper::Text("** AMBIENT **************");

    auto result = material.diffuseColour * light.ambientColour * light.intensityMultiplier;
    GuiHelper::Text("AmbientResult: " + result.ToString());

    result.Clamp(0.0f, 1.0f);
    GuiHelper::Text("AmbientResult (C): " + result.ToString());

    return result;
}

Vector4<float> CalculateDiffuse(const Light& light, const Material& material, const Vector3<float>& vertexPosition, const Vector3<float>& vertexNormal, const MeshInstance& meshInstance)
{
    GuiHelper::Text("** DIFFUSE **************");

    auto vertexPositionWorld = meshInstance.GetModelMatrix().Transform(vertexPosition);
    GuiHelper::Text("V Position: " + vertexPosition.ToString());

    auto vertexNormalDirection = meshInstance.GetNormalMatrix().Transform(vertexNormal);
    vertexNormalDirection.Normalise();
    GuiHelper::Text("V Normal: " + vertexNormalDirection.ToString());

    auto vertexToLightDirection = light.position - vertexPositionWorld;
    GuiHelper::Text("Vertex -> Light: " + vertexToLightDirection.ToString());
    vertexToLightDirection.Normalise();
    GuiHelper::Text("Vertex -> Light (N): " + vertexToLightDirection.ToString());

    auto diffuseDot = MathsHelper::Maximum(vertexNormalDirection.Dot(vertexToLightDirection), 0.0f);
    GuiHelper::Text("DiffuseDot: " + std::to_string(diffuseDot));

    auto result = material.diffuseColour * light.diffuseColour * diffuseDot * light.intensityMultiplier;
    GuiHelper::Text("DiffuseResult: " + result.ToString());

    result.Clamp(0.0f, 1.0f);
    GuiHelper::Text("DiffuseResult (C): " + result.ToString());

    return result;
}

Vector4<float> CalculateSpecular(const Light& light, const Material& material, const Vector3<float>& vertexPosition, const Vector3<float>& vertexNormal, const MeshInstance& meshInstance, const Vector3<float>& cameraPosition)
{
    GuiHelper::Text("** SPECULAR **************");

    auto vertexPositionWorld = meshInstance.GetModelMatrix().Transform(vertexPosition);
    GuiHelper::Text("V Position: " + vertexPosition.ToString());

    auto vertexNormalDirection = meshInstance.GetNormalMatrix().Transform(vertexNormal);
    vertexNormalDirection.Normalise();
    GuiHelper::Text("V Normal: " + vertexNormalDirection.ToString());

    auto vertexToLightDirection = light.position - vertexPositionWorld;
    GuiHelper::Text("Vertex -> Light: " + vertexToLightDirection.ToString());

    auto lightReflectionDirection = Vector3<float>::CreateReflectioneOf(Vector3<float>::CreateInverseOf(vertexToLightDirection), vertexNormalDirection);
    GuiHelper::Text("Reflection: " + lightReflectionDirection.ToString());
    lightReflectionDirection.Normalise();
    GuiHelper::Text("Reflection (N): " + lightReflectionDirection.ToString());

    // TODO - probably wrong
    auto vertexToCameraDirection = cameraPosition - vertexPositionWorld;
    GuiHelper::Text("Vertex -> Camera: " + vertexToCameraDirection.ToString());
    vertexToCameraDirection.Normalise();
    GuiHelper::Text("Vertex -> Camera (N): " + vertexToCameraDirection.ToString());

    auto specularDot = MathsHelper::Maximum(lightReflectionDirection.Dot(vertexToCameraDirection), 0.0f);
    GuiHelper::Text("SpecularDot: " + std::to_string(specularDot));

    auto result = material.specularColour * light.specularColour * MathsHelper::Power(specularDot, 0.3 * material.shininess) * light.intensityMultiplier;
    GuiHelper::Text("SpecularResult: " + result.ToString());

    result.Clamp(0.0f, 1.0f);
    GuiHelper::Text("SpecularResult (C): " + result.ToString());

    return result;
}

int main(int, char**)
{
    // Setup window
//    glfwSetErrorCallback(glfw_error_callback);
    auto windowWidth = 2048;
    auto windowHeight = 1024;

    // SYSTEM ********************
    std::cout << "Initialising system..." << std::endl;

    if (!opengl::System::Initialise())
    {
        throw std::exception("Failed to intialise system");
    }

    opengl::StateManager::SetBlendFunction(opengl::enumerators::BlendFactor::SourceAlpha, opengl::enumerators::BlendFactor::OneMinusSourceAlpha);
    opengl::StateManager::EnableBlending();

    std::cout << "System initialised" << std::endl;

    // WINDOW *******************
    std::cout << "Creating window..." << std::endl;

    opengl::Window::SetOpenGlContextVersion(3, 3);
    opengl::Window::SetOpenGlProfile(opengl::enumerators::OpenGlProfile::Core);
    opengl::Window::SetSwapInterval(1);

    opengl::Window window(windowWidth, windowHeight, "GFX");
    window.MakeCurrent();

    std::cout << "Window created" << std::endl;

    // GLEW EXTENSIONS **************
    std::cout << "Initialising extensions..." << std::endl;

    opengl::System::InitialiseExtensions();

    std::cout << "Extensions initialised" << std::endl;

    // PANES **********************
    std::cout << "Creating panes..." << std::endl;

    Pane mainPane(-1.0f, -1.0f, 2.0f, 2.0f);
    Pane debugPane1(0.5f, 0.0f, 0.5f, 0.5f);
    Pane debugPane2(0.5f, 0.5f, 0.5f, 0.5f);

    std::cout << "Panes created" << std::endl;

    // VIEW *******************
    std::cout << "Creating view..." << std::endl;

    PerspectiveView view(60.0f, static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 50.0f);

    std::cout << "View created" << std::endl;

    // CAMERA *******************
    std::cout << "Creating camera..." << std::endl;

    Camera camera;
    camera.position.y = 10.0f;
    camera.position.z = 10.0f;
    camera.rotationDegrees.pitch = 45.0f;

    std::cout << "Camera created" << std::endl;

    // MATERIALS ***********************
    FileSystem fileSystem;

    std::shared_ptr<opengl::Texture> checkerboardDiffuseTexture;
    std::shared_ptr<opengl::Texture> checkerboardSpecularTexture;
    std::shared_ptr<opengl::Texture> cubemapDiffuseTexture;

    {
        auto checkerboardImage = fileSystem.ReadImage("resources/textures/UVCheckerBoard-2048x2048.png");
        checkerboardDiffuseTexture = opengl::factories::TextureFactory::CreateColour(checkerboardImage.width, checkerboardImage.height, checkerboardImage.data);
    }

    {
        auto checkerboardSpecularImage = fileSystem.ReadImage("resources/textures/UVCheckerBoard-specular-2048x2048.png");
        checkerboardSpecularTexture = opengl::factories::TextureFactory::CreateColour(checkerboardSpecularImage.width, checkerboardSpecularImage.height, checkerboardSpecularImage.data);
    }

    {
        auto cubemapImage = fileSystem.ReadImage("resources/textures/UVCubemap-2048x1536.png");
        cubemapDiffuseTexture = opengl::factories::TextureFactory::CreateColour(cubemapImage.width, cubemapImage.height, cubemapImage.data);
    }

    auto checkerboardMaterial = Material::Create()
        .WithTexture(TextureSlot::Colour, checkerboardDiffuseTexture)
        .WithTexture(TextureSlot::Specular, checkerboardSpecularTexture);

    auto cubeMaterial = Material::Create()
        .WithTexture(TextureSlot::Colour, cubemapDiffuseTexture);

    auto lightMaterial = Material::Create()
        .WithDiffuseColour({ 1.0f, 1.0f, 1.0f, 1.0f })
        .WithEmissiveColour({ 1.0f, 1.0f, 1.0f });

    // SHADERS ***********************
    std::cout << "Creating shaders..." << std::endl;

    std::string phongVertexShaderSource = fileSystem.ReadFile("resources/shaders/phong.vertex.glsl");
    std::string phongFragmentShaderSource = fileSystem.ReadFile("resources/shaders/phong.fragment.glsl");

    PhongShader phongShaderSet(phongVertexShaderSource, phongFragmentShaderSource);

    std::string shadowmapVertexShaderSource = fileSystem.ReadFile("resources/shaders/shadowmap.vertex.glsl");
    std::string shadowmapFragmentShaderSource = fileSystem.ReadFile("resources/shaders/shadowmap.fragment.glsl");

    ShadowmapShader shadowmapShaderSet(shadowmapVertexShaderSource, shadowmapFragmentShaderSource);

    std::string bufferVertexShaderSource = fileSystem.ReadFile("resources/shaders/buffer.vertex.glsl");
    std::string bufferFragmentShaderSource = fileSystem.ReadFile("resources/shaders/buffer.fragment.glsl");

    BufferShader bufferShaderSet(bufferVertexShaderSource, bufferFragmentShaderSource);

    std::cout << "Shaders created" << std::endl;

    // MESH **************************
    std::cout << "Creating mesh..." << std::endl;

    auto boxMesh = PrimitiveFactory::CreateBox(1.0f, 1.0f, 1.0f);
    auto planeMesh = PrimitiveFactory::CreatePlane(1.0f, 1.0f);

    MeshInstance planeInstance(*planeMesh.get(), checkerboardMaterial);
    planeInstance.SetUniformScale(10.0f);
    planeInstance.rotationDegrees.x = -90.0f;

    MeshInstance boxInstance(*boxMesh.get(), cubeMaterial);
    boxInstance.SetUniformScale(5.0f);

    MeshInstance lightInstance(*boxMesh.get(), lightMaterial);
    lightInstance.SetUniformScale(1.0f);

    std::cout << "Meshes created" << std::endl;
    std::cout << boxMesh->ToString() << std::endl;

    // LIGHT **********************************
    std::cout << "Creating light..." << std::endl;

    Light light;
    light.ambientColour = Vector4<float>({ 0.1f, 0.1f, 0.1f, 1.0f });
    light.diffuseColour = Vector4<float>({ 1.0f, 1.0f, 1.0f, 1.0f });
    light.specularColour = Vector4<float>({ 0.5f, 0.5f, 0.5f, 0.5f });
    light.intensityMultiplier = 1.0f;
    light.position.x = -5.0f;
    light.position.y = 5.0f;
    light.position.z = 5.0f;
    light.isEnabled = true;

    std::cout << "Light created" << std::endl;

    // BUFFERS **********************************
    std::cout << "Creating buffers..." << std::endl;

    auto offscreenColourTexture = opengl::factories::TextureFactory::CreateColour(windowWidth, windowHeight);
    auto offscreenDepthStencilBuffer = opengl::factories::RenderBufferFactory::CreateDepthStencilBuffer(windowWidth, windowHeight);
    auto offscreenFrameBuffer = opengl::factories::FrameBufferFactory::CreateOffscreenBuffer(windowWidth, windowHeight, offscreenColourTexture->GetTextureId(), offscreenDepthStencilBuffer->GetRenderBufferId());

    std::cout << "Buffers created" << std::endl;

    // IMGUI **********************************
    std::cout << "Initialising IMGUI..." << std::endl;

    auto imguiContext = GuiHelper::Initialise(window.GetWindow(), "#version 330 core");
    GuiHelper::ApplyDarkStyle();

    auto displaySize = GuiHelper::GetDisplaySize();
    auto displayFramebufferScale = GuiHelper::GetDisplayFramebufferScale();

    std::cout << "displaySize: " << displaySize.x << "x" << displaySize.y << std::endl;
    std::cout << "displayFramebufferScale: " << displayFramebufferScale.x << "x" << displayFramebufferScale.y << std::endl;

    std::cout << "IMGUI initialised" << std::endl;

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

        // Draw box to offline buffer
        offscreenFrameBuffer->Bind(opengl::enumerators::FramebufferTarget::Framebuffer);

        opengl::Window::SetViewport(0, 0, currentWindowWidth, currentWindowHeight);

        opengl::StateManager::EnableDepthTesting();
        opengl::FrameBuffer::ClearColour(0.0f, 0.0f, 0.0f, 1.0f);
        opengl::FrameBuffer::Clear(opengl::enumerators::AttributeBit::ColourBuffer | opengl::enumerators::AttributeBit::DepthBuffer | opengl::enumerators::AttributeBit::StencilBuffer);

        {
            auto modelMatrix = planeInstance.GetModelMatrix();
            auto normalMatrix = planeInstance.GetNormalMatrix();

            phongShaderSet.Render(PhongShaderUniforms(projectionMatrix, viewMatrix, modelMatrix, normalMatrix, planeInstance.GetMaterial(), light, sceneAmbientColour), planeInstance.GetMesh());
        }

        {
            auto modelMatrix = boxInstance.GetModelMatrix();
            auto normalMatrix = boxInstance.GetNormalMatrix();

            phongShaderSet.Render(PhongShaderUniforms(projectionMatrix, viewMatrix, modelMatrix, normalMatrix, boxInstance.GetMaterial(), light, sceneAmbientColour), boxInstance.GetMesh());
        }

        {
            lightInstance.position = light.position;

            auto modelMatrix = lightInstance.GetModelMatrix();
            auto normalMatrix = lightInstance.GetNormalMatrix();

            phongShaderSet.Render(PhongShaderUniforms(projectionMatrix, viewMatrix, modelMatrix, normalMatrix, lightInstance.GetMaterial(), light, sceneAmbientColour), lightInstance.GetMesh());
        }

        // Revert to default buffer
        opengl::FrameBuffer::BindDefault(opengl::enumerators::FramebufferTarget::Framebuffer);

        opengl::Window::SetViewport(0, 0, currentWindowWidth, currentWindowHeight);

        opengl::StateManager::DisableDepthTesting();
        opengl::FrameBuffer::Clear(opengl::enumerators::AttributeBit::ColourBuffer | opengl::enumerators::AttributeBit::DepthBuffer | opengl::enumerators::AttributeBit::StencilBuffer);

        {
            // Draw buffers to panes
            opengl::Texture::ActivateSlot(0);
            offscreenColourTexture->Bind();
            bufferShaderSet.Render(0, mainPane.GetMesh());
//            bufferShaderSet.Render(0, debugPane1.GetMesh());
//            depthBuffer->Bind();
//            bufferShaderSet.Render(0, debugPane2.GetMesh());
        }

        GuiHelper::PushWindow("gfx", 100.0f, 100.0f, 400.0f, 400.0f);

        GuiHelper::CollapsingHeader("Box");
        GuiHelper::SliderFloat3("Translation", &boxInstance.position.x, -20.0f, 20.0f);
        GuiHelper::SliderFloat3("Scale", &boxInstance.scale.x, 1.0f, 20.0f);
        GuiHelper::SliderFloat3("Rotation", &boxInstance.rotationDegrees.pitch, -180.0f, 180.0f);

        GuiHelper::CollapsingHeader("Light");
        GuiHelper::SliderFloat3("Position", &light.position.x, -20.0f, 20.0f);
        GuiHelper::ColourEdit3("Ambient", &light.ambientColour.red);
        GuiHelper::ColourEdit3("Diffuse", &light.diffuseColour.red);
        GuiHelper::ColourEdit3("Specular", &light.specularColour.red);
        GuiHelper::SliderFloat("Intensity", light.intensityMultiplier, 0.0f, 20.0f);

        GuiHelper::CollapsingHeader("Debug");

        auto ambient = CalculateAmbient(light, checkerboardMaterial);
        auto diffuse = CalculateDiffuse(light, checkerboardMaterial, Vector3<float>(-0.5f, -0.5f, 0.0f), Vector3<float>(0.0f, 0.0f, 1.0f), planeInstance);
        auto specular = CalculateSpecular(light, checkerboardMaterial, Vector3<float>(-0.5f, -0.5f, 0.0f), Vector3<float>(0.0f, 0.0f, 1.0f), planeInstance, camera.position);

        GuiHelper::Text("** RESULT **************");

        auto vertexPositionWorld = planeInstance.GetModelMatrix().Transform(Vector3<float>(-0.5f, -0.5f, 0.0f));
        auto vertexToLightDirection = light.position - vertexPositionWorld;
        auto vertexToLightDistance = vertexToLightDirection.Length();
        GuiHelper::Text("V -> L Dist: " + std::to_string(vertexToLightDistance));

        auto attenuation = 1.0f / (light.constantAttenuation +
            (light.linearAttenuation * vertexToLightDistance) +
            (light.quadraticAttenuation * vertexToLightDistance * vertexToLightDistance));

        GuiHelper::Text("Attenuation: " + std::to_string(attenuation));

        auto lightContribution = ambient + (diffuse * attenuation) + (specular * attenuation);
        GuiHelper::Text("Light Contribution: " + lightContribution.ToString());

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

