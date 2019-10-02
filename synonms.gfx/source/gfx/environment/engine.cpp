#include "engine.h"

#include <iostream>

#include <glproxy\system.h>

using namespace synonms::gfx::environment;

Engine::Engine()
{
    std::cout << "Initialising system..." << std::endl;

    if (!proxies::opengl::System::Initialise())
    {
        throw std::exception("Failed to intialise system");
    }

    proxies::opengl::System::SetBlendFunction(proxies::opengl::enumerators::BlendFactor::SourceAlpha, proxies::opengl::enumerators::BlendFactor::OneMinusSourceAlpha);
    proxies::opengl::System::EnableBlending();

    std::cout << "System initialised" << std::endl;
}

Engine::~Engine()
{
    std::cout << "Terminating..." << std::endl;

    proxies::opengl::System::Terminate();

    std::cout << "Terminated" << std::endl;
}

void Engine::InitialiseExtensions()
{
    std::cout << "Initialising system extensions..." << std::endl;

    if (!proxies::opengl::System::InitialiseExtensions())
    {
        throw std::exception("Failed to intialise system extensions");
    }

    std::cout << "System extensions initialised" << std::endl;
}

void Engine::PollEvents()
{
    proxies::opengl::System::PollEvents();
}