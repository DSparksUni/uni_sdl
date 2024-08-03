#pragma once

#include <memory>

#include "SDL/SDL.h"

namespace uni {
    struct UniqueSDLDeleter {
        void operator()(SDL_Window* window);
        void operator()(SDL_Renderer* render);
    };

    using unique_window = std::unique_ptr<SDL_Window, UniqueSDLDeleter>;
    using unique_renderer = std::unique_ptr<SDL_Renderer, UniqueSDLDeleter>;
}
