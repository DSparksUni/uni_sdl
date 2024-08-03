#include "uni_game.hpp"
#include "SDL/SDL.h"

namespace uni {
    Game::Game(int wwidth, int wheight, const char* wtitle):
        window(nullptr), delta_time(0.0), running(true), window_width(wwidth), window_height(wheight),
        window_title(wtitle), performance_frequency(0), last_time(0)
    {}

    bool Game::init() {
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            fprintf(stderr, "[ERROR] Failed to initialize SDL...\n");
            return false;
    }

        try {
            window = new Window(window_width, window_height, window_title);
        } catch(WindowError error) {
            switch(error) {
                case uni::WindowError::SDL_WINDOW_ERROR: {
                    fprintf(stderr, "[ERROR] Failed to create SDL Window...\n");
                } break;
                case uni::WindowError::SDL_RENDERER_ERROR: {
                    fprintf(stderr, "[ERROR] Failed to create SDL Renderer...\n");
                } break;
                case uni::WindowError::SDL_TEXTURE_ERROR: {
                    fprintf(stderr, "[ERROR] Failed to create window canvas...\n");
                } break;
            }

            return false;
        }

        performance_frequency = SDL_GetPerformanceFrequency(); 

        return true;
    }

    bool Game::loop() {
        const size_t begin_time = SDL_GetPerformanceCounter();
        const size_t elapsed = begin_time - last_time;
        delta_time = static_cast<double>(elapsed) / static_cast<double>(performance_frequency);

        return true;
    }

    void Game::destroy() {
        if(window) delete window;

        SDL_Quit();
    }

    void Game::run() {
        running = this->init();
        while(running) running = this->loop();
        this->destroy();
    }
}
