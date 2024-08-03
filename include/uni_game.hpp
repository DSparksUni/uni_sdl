#pragma once

#include "uni_window.hpp"

namespace uni {
    class Game {
    protected:
        Window* window;

        double delta_time;

    private:
        bool running;

        int window_width, window_height;
        const char* window_title;

        size_t performance_frequency;
        size_t last_time;
    public:
        Game(int window_width, int window_height, const char* window_title);
        virtual ~Game() = default;

        virtual bool init();
        virtual bool loop();
        virtual void destroy();

        void run();
    };
}

