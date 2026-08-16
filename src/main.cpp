#include "core/App.hpp"
#include "core/Logger.hpp"
#include <iostream>
#include <cstdlib>
#include <csignal>

static core::App* g_app = nullptr;

static void signalHandler(int signal) {
    if (g_app) {
        g_app->shutdown();
    }
    std::exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    core::App app;
    g_app = &app;

    if (!app.init(argc, argv)) {
        std::cerr << "Failed to initialize application." << std::endl;
        return EXIT_FAILURE;
    }

    return app.run();
}
