#include "uni_util.hpp"

namespace uni {
    void UniqueSDLDeleter::operator()(SDL_Window* window) {
        SDL_DestroyWindow(window);
    }
    void UniqueSDLDeleter::operator()(SDL_Renderer* render) {
        SDL_DestroyRenderer(render);
    }
}
