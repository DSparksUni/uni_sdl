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

#include "uni_util.hpp"

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

        UNI_NODISCARD RenderInfo info() const noexcept;
        UNI_NODISCARD SDL_Renderer* render() const noexcept;
        UNI_NODISCARD int width() const noexcept;
        UNI_NODISCARD int height() const noexcept;
        UNI_NODISCARD int view_width() const noexcept;
        UNI_NODISCARD int view_height() const noexcept;

        void set_draw_color(int color) noexcept;
        void clear(int color) noexcept;
        void update() noexcept;
    };

#if defined(UNI_IMPL) && !defined(UNI_WINDOW_IMPL_)
#define UNI_WINDOW_IMPL_
    inline Window::Window(int width, int height, const char* title):
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
    inline Window::~Window() {
        SDL_DestroyRenderer(this->m_render);
        SDL_DestroyWindow(this->m_window);
    }

    UNI_NODISCARD inline RenderInfo Window::info() const noexcept {
        return {this->m_render, this->c_width, this->c_height};
    }
    UNI_NODISCARD inline SDL_Renderer* Window::render() const noexcept {
        return this->m_render;
    }
    UNI_NODISCARD inline int Window::width() const noexcept {
        return this->c_width;
    }
    UNI_NODISCARD inline int Window::height() const noexcept {
        return this->c_height;
    }
    UNI_NODISCARD inline int Window::view_width() const noexcept {
        return this->m_view_width;
    }
    UNI_NODISCARD inline int Window::view_height() const noexcept {
        return this->m_view_height;
    }

    inline void Window::set_draw_color(int color) noexcept {
        SDL_SetRenderDrawColor(this->m_render, UNI_UNPACK_COLOR((unsigned)color));
    }

    inline void Window::clear(int color) noexcept {
        this->set_draw_color(color);
        SDL_RenderClear(this->m_render);
    }

    inline void Window::update() noexcept {
        SDL_SetRenderTarget(this->m_render, nullptr);
        SDL_RenderCopy(this->m_render, this->m_canvas, nullptr, nullptr);
        SDL_SetRenderTarget(this->m_render, this->m_canvas);

        SDL_RenderPresent(this->m_render);
    }
#endif  //UNI_WINDOW_IMPL_
}
