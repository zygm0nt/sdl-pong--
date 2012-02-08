#ifndef DRAW_CONTAINER_H
#define DRAW_CONTAINER_H

#include <SDL.h>

/* object types */
#define OBJ_LED_ON	1
#define OBJ_LED_OFF	0

namespace sdlpong {

    class draw_container {
        public:
            int type;
            int x, y;
    };
};
#endif
