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
