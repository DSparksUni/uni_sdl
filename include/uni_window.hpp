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

#include <iostream>

#include "SDL/SDL.h"

#define UNI_NODISCARD [[nodiscard]]
#define UNI_UNPACK_COLOR(c) (c>>24), (c>>16)&0xFF, (c>>8)&0xFF, c&0xFF

namespace uni {
    enum WindowError {
        SDL_WINDOW_ERROR,
        SDL_RENDERER_ERROR,
        SDL_TEXTURE_ERROR
    };

    class Window {
    private:
        SDL_Renderer* m_render;
        SDL_Texture* m_canvas;
        SDL_Window* m_window;

        const int c_width = 1280;
        const int c_height = 720;
        int m_view_width, m_view_height;

    public:
        Window(int width, int height, const char* title);
        ~Window();

        UNI_NODISCARD SDL_Renderer* render() const noexcept;
        UNI_NODISCARD int width() const noexcept;
        UNI_NODISCARD int height() const noexcept;
        UNI_NODISCARD int view_width() const noexcept;
        UNI_NODISCARD int view_height() const noexcept;

        void set_draw_color(int color) noexcept;
        void clear(int color) noexcept;
        void update() noexcept;
    };
}
