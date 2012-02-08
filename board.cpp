#include "board.h"

namespace sdlpong {

    board::board(char *level) {
        load_level_from_file(level);
    }

    int
        board::getVal(int y, int x) {
            return gameboard[y][x];
        }

    void
        board::modVal(int y, int x, int mod) {
            gameboard[y][x] += mod;
        }
    void
        board::load_level_from_file(char *lvl_name) {
            FILE *fp;
            char ch;

            if ((fp = fopen(lvl_name, "r")) == NULL) {
                printf("error loading level\n");
                exit(1);
            }

            int * board_ptr = gameboard[0];

            while (!feof(fp)) {
                ch = fgetc(fp);

                if (ch == ' ' || ch == '\n') {
                    /*if (ch == '\n')
                      printf("\n");*/
                } else if (isdigit(ch)){
                    *board_ptr = ch - '0';
                    //printf("%c ", ch);
                    board_ptr++;
                }
            }

            fclose(fp);
        }

    void
        board::draw(SDL_Surface *view)
        {
            int i, k;
            int brick_width;
            int brick_height;
            struct brick one;

            brick_width = MAX_X / 10;
            brick_height= 0.33 * MAX_Y / 5;

            one.width = brick_width;
            one.height= brick_height;

            Slock(view);
            for (i = 0; i < 5; i++)
                for (k = 0; k < 10; k++)
                {

                    if (gameboard[i][k] > 0)
                    {
                        switch(gameboard[i][k]) {
                            case 1:
                                one.color = SDL_MapRGB(view->format, 0, 255, 255);
                                break;
                            case 2:
                                one.color = SDL_MapRGB(view->format, 0, 0, 255);
                                break;
                            case 3:
                                one.color = SDL_MapRGB(view->format, 0, 255, 0);
                                break;
                        }
                        one.x = k*brick_width;
                        one.y = i*brick_height;
                        draw_rect(view, one);
                    }
                }
            Sunlock(view);
        }

    void 
        board::draw_rect(SDL_Surface *t, struct brick l)
        {
            int a, b;

            for (a = l.x + 1; a < (l.x + l.width)-1; a++)
                for (b = l.y+1; b < (l.y + l.height)-1; b++)
                    SDL_putPixel(t, a, b, l.color);
        }
};
