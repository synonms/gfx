#include <iostream>

#include <vendor\glm\glm.hpp>
#include <vendor\glm\gtc\matrix_transform.hpp>

#include <gfx\environment\camera.h>
#include <gfx\environment\engine.h>
#include <gfx\environment\orthographic-view.h>
#include <gfx\environment\window.h>
#include <gfx\gui\gui-helper.h>
#include <gfx\io\file-system.h>
#include <gfx\mathematics\linear\matrix4x4.h>
#include <gfx\primitives\mesh.h>
#include <gfx\primitives\mesh-instance.h>
#include <gfx\primitives\vertex-definition.h>
#include <gfx\shaders\shader-set.h>
#include <gfx\materials\texture.h>

using namespace synonms::gfx::enumerators;
using namespace synonms::gfx::environment;
using namespace synonms::gfx::gui;
using namespace synonms::gfx::io;
using namespace synonms::gfx::materials;
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

    OrthographicView view(0.0f, 2048.0f, 0.0f, 1024.0f, -1.0f, 1.0f);

    std::cout << "View created" << std::endl;

    // CAMERA *******************
    std::cout << "Creating camera..." << std::endl;

    Camera camera;

    std::cout << "Camera created" << std::endl;

    // GLEW EXTENSIONS
    std::cout << "Initialising extensions..." << std::endl;

    engine.InitialiseExtensions();

    std::cout << "Extensions initialised" << std::endl;

    // TEXTURE ***********************
    Texture texture("resources/textures/UVCheckerBoard-2048x2048.png");
    texture.Bind(0);

    // SHADERS ***********************
    std::cout << "Creating shaders..." << std::endl;

    FileSystem fileSystem;

    std::string vertexShaderSource = fileSystem.ReadFile("resources/shaders/default-vertex-shader.glsl");
    std::string fragmentShaderSource = fileSystem.ReadFile("resources/shaders/default-fragment-shader.glsl");

    // Projection matrix converts the positions to screen (viewport) space
    auto projectionMatrix = view.GetProjectionMatrix();
    // View matrix represents eye position
    // Transformation is simulated by performing the reverse operation on the geometry
    // i.e. to move the "camera" left, instead move all the geometry right
    auto viewMatrix = camera.GetViewMatrix();
    // Model matrix is the transform of the geometry (i.e. moves it into world space)
//    auto modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -500.0f, 0.0f));
    // OpenGL is right to left multiplication
//    auto modelViewProjection = projectionMatrix * viewMatrix * modelMatrix;

    ShaderSet shaderSet(vertexShaderSource, fragmentShaderSource);
    shaderSet.Use();
    shaderSet.SetUniform("u_colour", 0.8f, 0.3f, 0.8f, 1.0f);
    shaderSet.SetUniform("u_textureSlot", 0);

    std::cout << "Shaders created" << std::endl;
    std::cout << shaderSet.ToString() << std::endl;

    // MESH **************************
    std::cout << "Creating mesh..." << std::endl;

    float vertexData[] = {
        // x      y       u     v
         0.0f,   0.0f, 0.0f, 0.0f,
       500.0f,   0.0f, 1.0f, 0.0f,
       500.0f, 500.0f, 1.0f, 1.0f,
         0.0f, 500.0f, 0.0f, 1.0f
    };

    unsigned int indexData[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexDefinition vertexDefinition({
        { AttributeType::Position, DataType::Float, 2, sizeof(float), false },
        { AttributeType::TextureCoordinates, DataType::Float, 2, sizeof(float), false }
        });

    Mesh mesh(vertexDefinition, vertexData, 4 * 4, indexData, 3 * 2);
    MeshInstance meshInstance1(mesh);
    MeshInstance meshInstance2(mesh);

    std::cout << "Meshes created" << std::endl;
    std::cout << mesh.ToString() << std::endl;

    std::cout << "Entering event loop..." << std::endl;

    auto imguiContext = GuiHelper::Initialise(window.GetContext(), "#version 330 core");
    GuiHelper::ApplyDarkStyle();

    auto translation1 = Vector3<float>(0.0f, 0.0f, 0.0f);
    auto translation2 = Vector3<float>(0.0f, 0.0f, 0.0f);

    while (!window.ShouldClose())
    {
        window.Clear();

        GuiHelper::NewFrame();

        {
            meshInstance1.GetTransform().SetPosition(translation1);

            auto modelViewProjection = projectionMatrix * viewMatrix * meshInstance1.GetTransform().GetTranslationMatrix();

            shaderSet.Use();
            shaderSet.SetUniformMatrix("u_modelViewProjection", modelViewProjection.Data());

            mesh.Draw();
        }

        {
            meshInstance2.GetTransform().SetPosition(translation2);

            auto modelViewProjection = projectionMatrix * viewMatrix * meshInstance2.GetTransform().GetTranslationMatrix();

            shaderSet.Use();
            shaderSet.SetUniformMatrix("u_modelViewProjection", modelViewProjection.Data());

            mesh.Draw();
        }

        GuiHelper::PushWindow("Transform");
        GuiHelper::SliderFloat3("Translation 1", &translation1.x, 0.0f, 2048.0f);
        GuiHelper::SliderFloat3("Translation 2", &translation2.x, 0.0f, 2048.0f);
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

