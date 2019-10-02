#include <iostream>

#include <gfx\environment\engine.h>
#include <gfx\environment\window.h>
#include <gfx\io\file-system.h>
#include <gfx\primitives\mesh.h>
#include <gfx\primitives\vertex-definition.h>
#include <gfx\shaders\shader-set.h>
#include <gfx\materials\texture.h>

using namespace synonms::gfx::enumerators;
using namespace synonms::gfx::environment;
using namespace synonms::gfx::io;
using namespace synonms::gfx::materials;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;

int main()
{
    // SYSTEM ********************
    std::cout << "Initialising system..." << std::endl;

    Engine engine;

    std::cout << "System initialised" << std::endl;

    // WINDOW *******************
    std::cout << "Creating window..." << std::endl;

    Window window(1024, 1024, "GLOOP");
    window.MakeContextCurrent();

    std::cout << "Window created" << std::endl;

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

    ShaderSet shaderSet(vertexShaderSource, fragmentShaderSource);
    shaderSet.Use();
    shaderSet.SetUniform("u_colour", 0.8f, 0.3f, 0.8f, 1.0f);
    shaderSet.SetUniform("u_textureSlot", 0);

    std::cout << "Shaders created" << std::endl;
    std::cout << shaderSet.ToString() << std::endl;


    // MESH **************************
    std::cout << "Creating mesh..." << std::endl;

    float vertexData[] = {
        // x      y     u     v
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };

    unsigned int indexData[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexDefinition vertexDefinition({
        { AttributeType::Position, DataType::Float, 2, sizeof(float), false },
        { AttributeType::Texture, DataType::Float, 2, sizeof(float), false }
        });

    Mesh mesh(vertexDefinition, vertexData, 4 * 4 * sizeof(float), indexData, 3 * 2 * sizeof(unsigned int));

    std::cout << "Mesh created" << std::endl;
    std::cout << mesh.ToString() << std::endl;

    std::cout << "Entering event loop..." << std::endl;

    /* Loop until the user closes the window */
    while (!window.ShouldClose())
    {
        window.Clear();

        mesh.Draw();

        window.SwapBuffers();

        engine.PollEvents();
    }

    std::cout << "Event loop ended" << std::endl;

    std::cout << "Press a key to quit..." << std::endl;	
    std::cin.get();

    return 0;
}