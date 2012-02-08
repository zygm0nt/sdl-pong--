#ifndef _BALL_H_
#define _BALL_H_

#include <SDL.h>
extern "C" {
#include "SDL_prim.h"
}
#include "utils.h"

namespace sdlpong {

    class ball {
        private:
        int _x_ball, _y_ball;
        int _a, _b;
        bool _visibility;
        int _speed;
        public:
        ball();
        ball(int x, int y, bool v);
        void draw(SDL_Surface *view);
        void setVisible(bool);
        void setCords(int, int);
        void setA(int );
        void setB(int);
        void setSpeed(int);

        int getA();
        int getB();
        int getSpeed();
        int getX();
        int getY();
    };
};

#endif
