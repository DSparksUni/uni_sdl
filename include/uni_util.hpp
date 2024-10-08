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

    struct RenderInfo {
        SDL_Renderer* render;
        int width, height;
    };

#if defined(UNI_IMPL) && !defined(UNI_UTIL_IMPL_)
    inline void UniqueSDLDeleter::operator()(SDL_Window* window) {
        SDL_DestroyWindow(window);
    }
    inline void UniqueSDLDeleter::operator()(SDL_Renderer* render) {
        SDL_DestroyRenderer(render);
    }
#endif  //UNI_IMPL
}
