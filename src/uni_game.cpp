/*
    Copyright (c) 2024 Dylan Sparks

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

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
