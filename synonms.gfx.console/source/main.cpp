#include <iostream>

#include <vendor\glm\glm.hpp>
#include <vendor\glm\gtc\matrix_transform.hpp>

#include <gfx\environment\camera.h>
#include <gfx\environment\engine.h>
#include <gfx\environment\light.h>
#include <gfx\environment\perspective-view.h>
#include <gfx\environment\window.h>
#include <gfx\gui\gui-helper.h>
#include <gfx\io\file-system.h>
#include <gfx\materials\texture.h>
#include <gfx\materials\material.h>
#include <gfx\mathematics\linear\matrix4x4.h>
#include <gfx\mathematics\maths-helper.h>
#include <gfx\primitives\mesh.h>
#include <gfx\primitives\mesh-instance.h>
#include <gfx\primitives\primitive-factory.h>
#include <gfx\primitives\vertex-definition.h>
#include <gfx\shaders\phong-shader-set.h>

using namespace synonms::gfx::enumerators;
using namespace synonms::gfx::environment;
using namespace synonms::gfx::gui;
using namespace synonms::gfx::io;
using namespace synonms::gfx::materials;
using namespace synonms::gfx::mathematics;
using namespace synonms::gfx::mathematics::linear;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;

//static void glfw_error_callback(int error, const char* description)
//{
//    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//}

int main(int, char**)
{
    // Setup window
//    glfwSetErrorCallback(glfw_error_callback);

    // SYSTEM ********************
    std::cout << "Initialising system..." << std::endl;

    Engine engine;

    std::cout << "System initialised" << std::endl;

    // WINDOW *******************
    std::cout << "Creating window..." << std::endl;

    Window window(2048, 1024, "GLOOP");
    window.MakeContextCurrent();
    window.EnableVsync();

    std::cout << "Window created" << std::endl;

    // VIEW *******************
    std::cout << "Creating view..." << std::endl;

    PerspectiveView view(60.0f, 2048.0f / 1024.0f, 0.1f, 100.0f);

    std::cout << "View created" << std::endl;

    // CAMERA *******************
    std::cout << "Creating camera..." << std::endl;

    Camera camera;
    camera.position.y = 50.0f;
    camera.position.z = 50.0f;
    camera.rotationDegrees.pitch = 45.0f;

    std::cout << "Camera created" << std::endl;

    // GLEW EXTENSIONS
    std::cout << "Initialising extensions..." << std::endl;

    engine.InitialiseExtensions();

    std::cout << "Extensions initialised" << std::endl;

    // MATERIALS ***********************
    auto checkerboardDiffuseTexture = std::make_shared<Texture>("resources/textures/UVCheckerBoard-2048x2048.png");
    auto checkerboardSpecularTexture = std::make_shared<Texture>("resources/textures/UVCheckerBoard-specular-2048x2048.png");

    auto checkerboardMaterial = Material::Create()
        .WithTexture(Material::TextureSlot::Diffuse, checkerboardDiffuseTexture)
        .WithTexture(Material::TextureSlot::Specular, checkerboardSpecularTexture);

    auto metalMaterial = Material::Create()
        .WithDiffuseColour({ 0.5f, 0.5f, 0.5f, 1.0f })
        .WithShininess(100.0f);

    auto lightMaterial = Material::Create()
        .WithDiffuseColour({ 1.0f, 1.0f, 1.0f, 1.0f })
        .WithEmissiveColour({ 1.0f, 1.0f, 1.0f });

    // SHADERS ***********************
    std::cout << "Creating shaders..." << std::endl;

    FileSystem fileSystem;

    std::string vertexShaderSource = fileSystem.ReadFile("resources/shaders/phong.vertex.glsl");
    std::string fragmentShaderSource = fileSystem.ReadFile("resources/shaders/phong.fragment.glsl");

    PhongShaderSet shaderSet(vertexShaderSource, fragmentShaderSource);

    std::cout << "Shaders created" << std::endl;
    std::cout << shaderSet.ToString() << std::endl;

    // MESH **************************
    std::cout << "Creating mesh..." << std::endl;

    auto boxMesh = PrimitiveFactory::CreateBox(1.0f, 1.0f, 1.0f);
    auto planeMesh = PrimitiveFactory::CreatePlane(1.0f, 1.0f);

    MeshInstance planeInstance(planeMesh, checkerboardMaterial);
    planeInstance.SetUniformScale(100.0f);
    planeInstance.rotationDegrees.x = -90.0f;

    MeshInstance boxInstance(boxMesh, metalMaterial);
    boxInstance.SetUniformScale(20.0f);

    MeshInstance lightInstance(boxMesh, lightMaterial);
    lightInstance.SetUniformScale(5.0f);

    std::cout << "Meshes created" << std::endl;
    std::cout << boxMesh.ToString() << std::endl;

    // LIGHT **********************************
    std::cout << "Creating light..." << std::endl;

    Light light;
    light.ambientColour = Vector4<float>({ 0.1f, 0.1f, 0.1f, 1.0f });
    light.diffuseColour = Vector4<float>({ 1.0f, 1.0f, 1.0f, 1.0f });
    light.specularColour = Vector4<float>({ 0.5f, 0.5f, 0.5f, 0.5f });
    light.intensityMultiplier = 1.0f;
    light.position.y = 20.0f;
    light.position.z = 20.0f;
    light.isEnabled = true;

    std::cout << "Light created" << std::endl;

    // IMGUI **********************************
    std::cout << "Initialising IMGUI..." << std::endl;

    auto imguiContext = GuiHelper::Initialise(window.GetContext(), "#version 330 core");
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

        window.Clear();
        window.SetViewport(0, 0, currentWindowSize.width, currentWindowSize.height);

        GuiHelper::NewFrame();

        auto projectionMatrix = view.GetProjectionMatrix();
        auto viewMatrix = camera.GetViewMatrix();

        {
            auto modelMatrix = planeInstance.GetModelMatrix();
            auto normalMatrix = planeInstance.GetNormalMatrix();

            shaderSet.Render(PhongShaderUniforms(projectionMatrix, viewMatrix, modelMatrix, normalMatrix, planeInstance.GetMaterial(), light, sceneAmbientColour), planeInstance.GetMesh());
        }

        {
            auto modelMatrix = boxInstance.GetModelMatrix();
            auto normalMatrix = boxInstance.GetNormalMatrix();

            shaderSet.Render(PhongShaderUniforms(projectionMatrix, viewMatrix, modelMatrix, normalMatrix, boxInstance.GetMaterial(), light, sceneAmbientColour), boxInstance.GetMesh());
        }

        {
            lightInstance.position = light.position;

            auto modelMatrix = lightInstance.GetModelMatrix();
            auto normalMatrix = lightInstance.GetNormalMatrix();

            shaderSet.Render(PhongShaderUniforms(projectionMatrix, viewMatrix, modelMatrix, normalMatrix, lightInstance.GetMaterial(), light, sceneAmbientColour), lightInstance.GetMesh());
        }

        GuiHelper::PushWindow("gfx", 100.0f, 100.0f, 400.0f, 400.0f);

        GuiHelper::CollapsingHeader("Box");
        GuiHelper::SliderFloat3("Translation", &boxInstance.position.x, -200.0f, 200.0f);
        GuiHelper::SliderFloat3("Scale", &boxInstance.scale.x, 1.0f, 100.0f);
        GuiHelper::SliderFloat3("Rotation", &boxInstance.rotationDegrees.pitch, -180.0f, 180.0f);

        GuiHelper::CollapsingHeader("Light");
        GuiHelper::SliderFloat3("Position", &light.position.x, -100.0f, 100.0f);
        GuiHelper::ColourEdit3("Ambient", &light.ambientColour.red);
        GuiHelper::ColourEdit3("Diffuse", &light.diffuseColour.red);
        GuiHelper::ColourEdit3("Specular", &light.specularColour.red);

        auto planeVertex1Normal = Vector3<float>(0.0f, 0.0f, 1.0f);
        auto vertexNormalDirection = planeInstance.GetNormalMatrix().Transform(planeVertex1Normal);
        vertexNormalDirection.Normalise();

        auto planeVertex1Position = Vector3<float>(-0.5f, -0.5f, 0.0f);
        auto planeVertex1PositionWorld = planeInstance.GetModelMatrix().Transform(planeVertex1Position);
        auto vertexToLightDirection = light.position - planeVertex1PositionWorld;
        vertexToLightDirection.Normalise();

        auto diffuseDot = MathsHelper::Maximum(vertexNormalDirection.Dot(vertexToLightDirection), 0.0f);
        auto diffuseResult = checkerboardMaterial.diffuseColour * light.diffuseColour * diffuseDot;
        diffuseResult.red = MathsHelper::Clamp(diffuseResult.red, 0.0f, 1.0f);
        diffuseResult.green = MathsHelper::Clamp(diffuseResult.green, 0.0f, 1.0f);
        diffuseResult.blue = MathsHelper::Clamp(diffuseResult.blue, 0.0f, 1.0f);

        GuiHelper::CollapsingHeader("Debug");
        GuiHelper::Text("Plane V1 Nml: (" + std::to_string(vertexNormalDirection.x) + "," + std::to_string(vertexNormalDirection.y) + "," + std::to_string(vertexNormalDirection.z) + ")");
        GuiHelper::Text("Plane V1 Pos: (" + std::to_string(planeVertex1PositionWorld.x) + "," + std::to_string(planeVertex1PositionWorld.y) + "," + std::to_string(planeVertex1PositionWorld.z) + ")");
        GuiHelper::Text("Light Pos: (" + std::to_string(light.position.x) + "," + std::to_string(light.position.y) + "," + std::to_string(light.position.z) + ")");
        GuiHelper::Text("Plane V1 -> Light: (" + std::to_string(vertexToLightDirection.x) + "," + std::to_string(vertexToLightDirection.y) + "," + std::to_string(vertexToLightDirection.z) + ")");

        GuiHelper::Text("DiffuseDot: " + std::to_string(diffuseDot));
        GuiHelper::Text("DiffuseResult: (" + std::to_string(diffuseResult.red) + "," + std::to_string(diffuseResult.green) + "," + std::to_string(diffuseResult.blue) + "," + std::to_string(diffuseResult.alpha) + ")");

        GuiHelper::PopWindow();

        GuiHelper::Render();

        window.SwapBuffers();

        engine.PollEvents();
    }

    GuiHelper::Shutdown();

    std::cout << "Event loop ended" << std::endl;

    std::cout << "Press a key to quit..." << std::endl;	
    std::cin.get();

    return 0;
}

