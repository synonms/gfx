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
    camera.SetPosition({ 0.0f, 0.0f, 50.0f });
    camera.SetRotation({ 0.0f, 0.0f, 0.0f });

    std::cout << "Camera created" << std::endl;

    // GLEW EXTENSIONS
    std::cout << "Initialising extensions..." << std::endl;

    engine.InitialiseExtensions();

    std::cout << "Extensions initialised" << std::endl;

    // MATERIALS ***********************
    auto checkerboardDiffuseTexture = std::make_shared<Texture>("resources/textures/UVCheckerBoard-2048x2048.png");

    auto checkerboardMaterial = Material::Create()
        .WithDiffuseColour({0.8f, 0.6f, 0.4f})
        .WithTexture(0, checkerboardDiffuseTexture)
        .WithShininess(0.8f);

    auto lightMaterial = Material::Create()
        .WithAmbientColour({ 1.0f, 1.0f, 1.0f })
        .WithDiffuseColour({ 1.0f, 1.0f, 1.0f })
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

    auto mesh = PrimitiveFactory::CreateBox(1.0f, 1.0f, 1.0f);
    MeshInstance objectInstance(mesh, checkerboardMaterial);
    objectInstance.SetPosition({ 0.0f, 0.0f, 0.0f });
    objectInstance.SetScale({ 20.0f, 20.0f, 20.0f });
    objectInstance.SetRotation({ 0.0f, 0.0f, 0.0f });

    MeshInstance lightInstance(mesh, lightMaterial);
    lightInstance.SetScale({5.0f, 5.0f, 5.0f});

    std::cout << "Meshes created" << std::endl;
    std::cout << mesh.ToString() << std::endl;

    // LIGHT **********************************
    std::cout << "Creating light..." << std::endl;

    Light light;
    light.SetPosition({ 0.0f, 20.0f, 20.0f });
    light.IsEnabled = true;

    std::cout << "Light created" << std::endl;

    std::cout << "Entering event loop..." << std::endl;

    auto imguiContext = GuiHelper::Initialise(window.GetContext(), "#version 330 core");
    GuiHelper::ApplyDarkStyle();

    while (!window.ShouldClose())
    {
        const auto currentWindowSize = window.GetSize();

        window.Clear();
        window.SetViewport(0, 0, currentWindowSize.width, currentWindowSize.height);

        GuiHelper::NewFrame();

        auto projectionMatrix = view.GetProjectionMatrix();
        auto viewMatrix = camera.GetViewMatrix();

        {
            auto modelMatrix = objectInstance.GetModelMatrix();
            auto normalMatrix = objectInstance.GetNormalMatrix();

            shaderSet.Render(PhongShaderUniforms(projectionMatrix, viewMatrix, modelMatrix, normalMatrix, objectInstance.GetMaterial(), light), objectInstance.GetMesh());
        }

        {
            lightInstance.SetPosition(light.GetPosition());

            auto modelMatrix = lightInstance.GetModelMatrix();
            auto normalMatrix = lightInstance.GetNormalMatrix();

            shaderSet.Render(PhongShaderUniforms(projectionMatrix, viewMatrix, modelMatrix, normalMatrix, lightInstance.GetMaterial(), light), lightInstance.GetMesh());
        }

        GuiHelper::PushWindow("Transform");
        GuiHelper::SliderFloat3("Translation", objectInstance.GetPositionData(), -200.0f, 200.0f);
        GuiHelper::SliderFloat3("Scale", objectInstance.GetScaleData(), 1.0f, 100.0f);
        GuiHelper::SliderFloat3("Rotation", objectInstance.GetRotationData(), -180.0f, 180.0f);
        GuiHelper::SliderFloat3("Light Position", light.GetPositionData(), -100.0f, 100.0f);
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

