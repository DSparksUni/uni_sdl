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

#include "uni_window.hpp"

namespace uni {
    Window::Window(int width, int height, const char* title):
        m_view_width(width), m_view_height(height)
    {
        this->m_window = SDL_CreateWindow(
            title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
        );
        if(!this->m_window) throw WindowError::SDL_WINDOW_ERROR;

        this->m_render = SDL_CreateRenderer(
            this->m_window, -1, SDL_RENDERER_ACCELERATED
        );
        if(!this->m_render) throw WindowError::SDL_RENDERER_ERROR;

        this->m_canvas = SDL_CreateTexture(
            this->m_render, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,
            this->c_width, this->c_height
        );
        if(!this->m_canvas) throw WindowError::SDL_TEXTURE_ERROR;

        SDL_SetRenderTarget(this->m_render, this->m_canvas);
    }
    Window::~Window() {
        SDL_DestroyRenderer(this->m_render);
        SDL_DestroyWindow(this->m_window);
    }

    UNI_NODISCARD SDL_Renderer* Window::render() const noexcept {
        return this->m_render;
    }
    UNI_NODISCARD int Window::width() const noexcept {
        return this->c_width;
    }
    UNI_NODISCARD int Window::height() const noexcept {
        return this->c_height;
    }
    UNI_NODISCARD int Window::view_width() const noexcept {
        return this->m_view_width;
    }
    UNI_NODISCARD int Window::view_height() const noexcept {
        return this->m_view_height;
    }

    void Window::set_draw_color(int color) noexcept {
        SDL_SetRenderDrawColor(this->m_render, UNI_UNPACK_COLOR(color));
    }

    void Window::clear(int color) noexcept {
        this->set_draw_color(color);
        SDL_RenderClear(this->m_render);
    }

    void Window::update() noexcept {
        SDL_SetRenderTarget(this->m_render, nullptr);
        SDL_RenderCopy(this->m_render, this->m_canvas, nullptr, nullptr);
        SDL_SetRenderTarget(this->m_render, this->m_canvas);

        SDL_RenderPresent(this->m_render);
    }
}
