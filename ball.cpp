#include "ball.h"

namespace sdlpong {
    ball::ball() {

    }

    ball::ball(int x, int y, bool v) {
        _x_ball = x;
        _y_ball = y;
        _visibility = v;
    }

    void
        ball::draw(SDL_Surface *view)
        {
            Slock(view);
            if (_visibility)
                SDL_drawCircle_TG(view, _x_ball, _y_ball, 5, SDL_MapRGB(view->format, 255, 100, 100), 255, SDL_TG_ALPHA | SDL_TG_FILL);
            else
                SDL_drawCircle_TG(view, _x_ball, _y_ball, 5, SDL_MapRGB(view->format, 0, 0, 0), 255, SDL_TG_ALPHA | SDL_TG_FILL);
            Sunlock(view);
        }
    void 
        ball::setVisible(bool val) {
            _visibility = val;
        }

    void
        ball::setCords(int x, int y) {
            _x_ball = x;
            _y_ball = y;
        }

    void
        ball::setSpeed(int s) {
            _speed = s;
        }
    
    void 
        ball::setA(int pa) {
            _a = pa;
        }

    void
        ball::setB(int pb) {
            _b = pb;
        }

    int
        ball::getA() {
            return _a;
        }

    int 
        ball::getB() {
            return _b; 
        }

    int 
        ball::getSpeed() {
            return _speed;
        }

    int 
        ball::getX() {
            return _x_ball;
        }

    int 
        ball::getY() {
            return _y_ball;
        }
};
