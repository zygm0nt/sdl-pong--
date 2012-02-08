#include "led_panel.h"
#include "letters.h"

namespace sdlpong {

    using namespace std;

    led_panel::led_panel() {
        this->panel = NULL;
        mode = "scroll";
        text_bin = NULL;
    }

    led_panel::led_panel(int x, int y, int width) {

        this->width = width;
        this->x = x;
        this->y = y;

        this->off_x = 0;
        this->off_y = 0;

        panel = new led* [y];
        for (int i = 0; i < y; i++) {
            panel[i] = new led[x];
        }
        mode = "scroll";
        text_bin = NULL;
    }

    led_panel::~led_panel(void) {

        for (int i=0; i < this->y; i++)
            delete panel[i];
        delete panel;

    }

    void
        led_panel::set_offset(int ox, int oy) {
            this->off_x = ox;
            this->off_y = oy;
        }

    void 
        led_panel::print(void) {
            for (int i =0; i < this->y; i++) {
                for (int j = 0; j < this->x; j++)
                    cout << panel[i][j].getState() << " ";
                cout << endl;
            }
        }

    void
        led_panel::all_on(void) {
            if (this->panel == NULL)
                return;

            for (int i = 0; i < this->y; i++)
                for (int j = 0; j < this->x; j++)
                    panel[i][j].setState(true);
        }

    void 
        led_panel::all_off(void) {
            if (this->panel == NULL)
                return;

            for (int i = 0; i < this->y; i++)
                for (int j = 0; j < this->x; j++)
                    panel[i][j].setState(false);
        }

    vector<draw_container> 
        led_panel::getDrawable(void) {

            vector<draw_container> tmp;

            int mult = width/x;

            for (int i = 0; i < this->y; i++)
                for (int j = 0; j < this->x; j++) {
                    led t;

                    if (panel[i][j].getState() == true) {
                        t.type = OBJ_LED_ON;
                    } else 
                        t.type = OBJ_LED_OFF;

                    t.x = j*mult + this->off_x;
                    t.y = i*mult + this->off_y;

                    tmp.push_back(t);
                }

            return tmp;
        }

    void
        led_panel::draw(SDL_Surface *screen) {

            int mult = width/x;

            for (int i = 0; i < this->y; i++)
                for (int j = 0; j < this->x; j++) {
                    led t;

                    if (panel[i][j].getState() == true) {
                        t.type = OBJ_LED_ON;
                    } else 
                        t.type = OBJ_LED_OFF;
                    
                    panel[i][j].setCords(j*mult + this->off_x, i*mult + this->off_y);
                    panel[i][j].draw(screen);
                }

        }

    void
        led_panel::set_text(char *txt) {
            this->cur_text.erase();
            this->cur_text = txt;

            /* 5 rows for a letter */
            if (text_bin != NULL) {
                for (int i = 0; i < this->y; i++) 
                    delete text_bin[i];
                delete text_bin;
                text_bin = NULL;
            }
            text_bin = new int*[5];

            for (int i = 0; i < this->y; i++) 
                /* 4 cols for a letter + 1 for a spacing */
                text_bin[i] = new int[this->cur_text.length()*5];

            /* reset */
            for (int i =0; i < this->y; i++) {
                for (unsigned int j = 0; j < this->cur_text.length()*5; j++)
                    text_bin[i][j] = 0;
            }

            string::iterator str_iter;
            int num = 0;
            for (str_iter = this->cur_text.begin(); str_iter != this->cur_text.end();
                    str_iter++) {
                for (int i = 0; i < 5; i++) { 
                    if (*str_iter == ' ') {
                        this->int2bin(alphabet[DEF_SPACE].val[i], 
                                &(text_bin[i][num*5+3]));
                    } else
                        this->int2bin(alphabet[(*str_iter)-'a'].val[i],
                                &(text_bin[i][num*5+3]));
                }
                num++;
            }

            if (mode == "scroll") 
                this->act_offset = -this->x;
            else if (mode == "static")
                this->act_offset = 0;
            this->done = false;
        }

    void 
        led_panel::print_bin(void) {
            for (int i =0; i < this->y; i++) {
                for (unsigned int j = 0; j < this->cur_text.length()*5; j++)
                    cout << text_bin[i][j] << " ";
                cout << endl;
            }
        }

    void
        led_panel::int2bin(int w, int *t) {
            for (int i = 0; i < 4; w>>=1, i++) {
                *t = w & 1;
                t--;
                //cout << (w & 1);
            }
            //cout << endl;
        }

    int 
        led_panel::lightup_text(int pos) {

            //cout << pos + (int)this->cur_text.length()*5 << endl;
            /*
               if (pos + (int)this->cur_text.length()*5 <= 0)
               return 1;

               for (int i = 0; i < this->y; i++) {
               for (int j = 0; j < this->x && j+pos < (int)this->cur_text.length()*5; j++) {
               if (j+pos >= 0 && j+pos < this->x) {
            //cout << "rysuje (" << j << ", " << pos << ")\n";
            panel[i][j+pos].state = (bool)text_bin[i][j];
            } else if (pos < 0) {
            cout << "j == " << j << " pos == " << pos << endl;
            panel[i][(j-pos)%this->x].state = (bool)text_bin[i][j];
            }
            }

            }*/

            for (int i = 0; i < this->y; i++) {
                for (int j = 0; j < this->x; j++) {
                    if (pos+j >= 0 && pos+j < (int)this->cur_text.length()*5)
                        panel[i][j].setState(text_bin[i][pos+j]);
                }
            }

            return 0;
        }

    /* return 0 until whole text scrolls
     * then return 1
     */
    int 
        led_panel::scroll(void) {
            int retVal = 0;
            if (mode == "scroll") {
                this->lightup_text(this->act_offset);

                this->act_offset++;

                //cout << "offset: " <<  this->act_offset << " " << this->cur_text.length()*5 << endl;
                if (this->act_offset == (int)this->cur_text.length()*5) {
                    this->done = true;
                    retVal = 1;
                } else
                    retVal = 0;
            } else if (mode == "static") {
                this->lightup_text(this->act_offset);
                retVal = 0;
                //std::cout << this->act_offset << std::endl;
            }
            return retVal;
        }

    bool
        led_panel::get_done(void) {
            return this->done;
        }

    void
        led_panel::set_mode(string x) {
            this->mode = x;
        }
};
