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
#include <gfx\shaders\shader-set.h>

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
    camera.GetTransform().SetPosition({ 0.0f, 0.0f, 30.0f });
    camera.GetTransform().SetViewDirection({ 0.0f, 0.0f, -1.0f });

    std::cout << "Camera created" << std::endl;

    // GLEW EXTENSIONS
    std::cout << "Initialising extensions..." << std::endl;

    engine.InitialiseExtensions();

    std::cout << "Extensions initialised" << std::endl;

    // MATERIALS ***********************
    auto checkerboardDiffuseTexture = std::make_shared<Texture>("resources/textures/UVCheckerBoard-2048x2048.png");

    auto material = Material::Create()
        .WithDiffuseColour({0.8f, 0.6f, 0.4f, 1.0f})
        .WithTexture(0, checkerboardDiffuseTexture);


    // SHADERS ***********************
    std::cout << "Creating shaders..." << std::endl;

    FileSystem fileSystem;

    std::string vertexShaderSource = fileSystem.ReadFile("resources/shaders/phong.vertex.glsl");
    std::string fragmentShaderSource = fileSystem.ReadFile("resources/shaders/phong.fragment.glsl");

    // Projection matrix converts the positions to screen (viewport) space
    auto projectionMatrix = view.GetProjectionMatrix();
    // View matrix represents eye position
    // Transformation is simulated by performing the reverse operation on the geometry
    // i.e. to move the "camera" left, instead move all the geometry right
    auto viewMatrix = camera.GetTransform().GetViewpointTransformationMatrix();
    // Model matrix is the transform of the geometry (i.e. moves it into world space)
//    auto modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -500.0f, 0.0f));
    // OpenGL is right to left multiplication
//    auto modelViewProjection = projectionMatrix * viewMatrix * modelMatrix;

    ShaderSet shaderSet(vertexShaderSource, fragmentShaderSource);
    shaderSet.Use();

    std::cout << "Shaders created" << std::endl;
    std::cout << shaderSet.ToString() << std::endl;

    // MESH **************************
    std::cout << "Creating mesh..." << std::endl;

    auto mesh = PrimitiveFactory::CreateBox(1.0f, 1.0f, 1.0f);
    MeshInstance meshInstance(mesh);

    std::cout << "Meshes created" << std::endl;
    std::cout << mesh.ToString() << std::endl;

    // LIGHT **********************************
    std::cout << "Creating light..." << std::endl;

    Light light;
    light.AmbientColour.red = 1.0f;
    light.AmbientColour.green = 1.0f;
    light.AmbientColour.blue = 1.0f;
    light.AmbientIntensityMultiplier = 0.2f;
    light.DiffuseColour.red = 1.0f;
    light.DiffuseColour.green = 1.0f;
    light.DiffuseColour.blue = 1.0f;
    light.WorldTransform.SetPosition(0.0f, 20.0f, 20.0f);
    light.IsEnabled = true;

    std::cout << "Light created" << std::endl;

    std::cout << "Entering event loop..." << std::endl;

    auto imguiContext = GuiHelper::Initialise(window.GetContext(), "#version 330 core");
    GuiHelper::ApplyDarkStyle();

    auto translation = Vector3<float>(0.0f, 0.0f, 0.0f);
    auto scale = Vector3<float>(20.0f, 20.0f, 20.0f);
    auto rotation = Vector3<float>(0.0f, 0.0f, 0.0f);
    auto lightPosition = Vector3<float>(0.0f, 20.0f, 20.0f);

    while (!window.ShouldClose())
    {
        const auto currentWindowSize = window.GetSize();

        window.Clear();
        window.SetViewport(0, 0, currentWindowSize.width, currentWindowSize.height);

        GuiHelper::NewFrame();

        {
            meshInstance.GetTransform().SetPosition(translation);
            meshInstance.GetTransform().SetScale(scale);
            meshInstance.GetTransform().SetRotation(Matrix4x4<float>::CreateFromRotationPitchYawRoll(MathsHelper::DegreesToRadians(rotation.x), MathsHelper::DegreesToRadians(rotation.y), MathsHelper::DegreesToRadians(rotation.z)));
            light.WorldTransform.SetPosition(lightPosition);

            auto modelMatrix = meshInstance.GetTransform().GetTransformationMatrix();
//            auto modelViewProjection = projectionMatrix * viewMatrix * modelMatrix;

            auto sisisi = sizeof(modelMatrix.xAxis);

            shaderSet.Use();
            shaderSet.SetUniform("vu_modelMatrix", modelMatrix);
            shaderSet.SetUniform("vu_viewMatrix", viewMatrix);
            shaderSet.SetUniform("vu_projectionMatrix", projectionMatrix);
            shaderSet.SetUniform("vu_normalMatrix", Matrix4x4<float>::CreateInverseTranspose3x3From(modelMatrix));

            shaderSet.SetUniform("vu_isLightEnabled", light.IsEnabled);
            shaderSet.SetUniform("vu_lightPosition", light.WorldTransform.GetPosition());

            shaderSet.SetUniform("fu_materialAmbientColour", material.GetAmbientColour());
            shaderSet.SetUniform("fu_materialDiffuseColour", material.GetDiffuseColour());
            shaderSet.SetUniform("fu_materialSpecularColour", material.GetSpecularColour());
            shaderSet.SetUniform("fu_materialEmissiveColour", material.GetEmissiveColour());
            shaderSet.SetUniform("fu_materialShininess", material.GetShininess());
            shaderSet.SetUniform("fu_isTextureEnabled", true);
            shaderSet.SetUniform("fu_textureSlot", 0);

            shaderSet.SetUniform("fu_isLightEnabled", light.IsEnabled);
            shaderSet.SetUniform("fu_lightPosition", light.WorldTransform.GetPosition());
            shaderSet.SetUniform("fu_lightAmbientColour", light.AmbientColour);
            shaderSet.SetUniform("fu_lightDiffuseColour", light.DiffuseColour);
            shaderSet.SetUniform("fu_lightSpecularColour", light.SpecularColour);
            shaderSet.SetUniform("fu_ambientIntensityMultiplier", light.AmbientIntensityMultiplier);

            mesh.Draw();
        }

        GuiHelper::PushWindow("Transform");
        GuiHelper::SliderFloat3("Translation", &translation.x, -200.0f, 200.0f);
        GuiHelper::SliderFloat3("Scale", &scale.x, 1.0f, 100.0f);
        GuiHelper::SliderFloat3("Rotation", &rotation.x, -180.0f, 180.0f);
        GuiHelper::SliderFloat3("Light Position", &lightPosition.x, -100.0f, 100.0f);
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

