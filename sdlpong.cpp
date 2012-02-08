#include <SDL.h>
#include <iostream>
#include <vector>

#include "SDL_prim.h"
#include "stars.h"
#include "defs.h"
#include "ball.h"
#include "stick.h"
#include "collision.h"
#include "VirtScreen.h"
#include "FileFactory.h"
#include "led_panel.h"

using namespace sdlpong;
using namespace std;

int 
main(void)
{
	SDL_Surface *window;
	//SDL_Surface *blend_temp;
	SDL_Event event;
	int end = 0;

	int x, y;
	int rel_x, cur_x;	// game - x pad place
    long long cycle, led_cycle; //timers
	int i;
    FileFactory *fFactory = FileFactory::getFactoryInstance();
    VirtScreen virtScreen;
    stick st;
    board gmboard("levels/level2");
    stars stfield(N);
   
    /* ball init */
    ball playball;
    playball.setVisible(true);
    playball.setSpeed(2);
    playball.setA(1);
    playball.setB(1);

    led_panel leds(27, 5, MAX_X);
    leds.set_offset(10, 10);
    leds.set_text("spadaj beju");

    /* load resource files */
    fFactory->registerObject("data/led_on.png", "led_on.png");
    fFactory->registerObject("data/led_off.png", "led_off.png");

	/* starting subsystems */
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_SetVideoMode(MAX_X, MAX_Y+160, 0, 0);
	SDL_WM_SetCaption("sdl pong", NULL);
	SDL_ShowCursor(SDL_DISABLE);

    /* fade in / fade out impl */
    virtScreen.addScreen("draw_temp", getSurface(window, MAX_X, MAX_Y), NULL);
	virtScreen.addScreen("blend_temp", getSurface(window, MAX_X, MAX_Y), NULL);
   
    vector<string> drawable;
    virtScreen.addScreen("main", getSurface(window, MAX_X, MAX_Y), getFrameRect(MAX_X, MAX_Y, 0, 160));
    drawable.push_back("main");

    virtScreen.addScreen("led", getSurface(window, MAX_X, 160), getFrameRect(MAX_X, 160, 0, 0));
    drawable.push_back("led");

#ifdef __FreeBSD__
    srandomdev();
#endif
	
	/* set timer */
	cycle = SDL_GetTicks();
	led_cycle = SDL_GetTicks();
	/* first position for the ball and pad */
    st.setCords(-1, 0);
    st.draw(virtScreen.getScreen("draw_temp"));

	cur_x = MAX_X / 2;
	rel_x = cur_x;
	
	int tmp_x_pos = MAX_X/2;
	playball.setCords(tmp_x_pos, playball.getA()*tmp_x_pos);
    playball.draw(virtScreen.getScreen("draw_temp"));

	gmboard.draw(virtScreen.getScreen("draw_temp"));

	/* Fade in */

/*	for (i = 0; i<256;)
	{
		if ( cycle+1 < SDL_GetTicks())
		{
			cycle = SDL_GetTicks();
			blend_image(virtScreen.getScreen("main"), virtScreen.getScreen("blend_temp"), virtScreen.getScreen("draw_temp"), i, 0);
            virtScreen.draw(window, drawable);
            SDL_Flip(window);
			i+=5;
		}
	}
*/	

	SDL_Flip(window);

	while (end == 0)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
			end = 1;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				end = 1;
		}
		
		SDL_GetMouseState(&x, &y);
	
		SDL_FillRect(virtScreen.getScreen("main"), NULL, SDL_MapRGB((virtScreen.getScreen("main"))->format, 0,0,0));

		if (x > MAX_X/2)
		{
		    st.setCords(cur_x + (x - MAX_X/2), 0);
			rel_x = cur_x + (x-MAX_X/2);
		}
		else if (x < MAX_X/2)
		{
			st.setCords( cur_x - (MAX_X/2 - x), 0);
			rel_x = cur_x - (MAX_X/2 - x);			
		}

		/* background sky effect */
		stfield.draw(virtScreen.getScreen("main"));
		
		/* redraw board */
		gmboard.draw(virtScreen.getScreen("main"));
        
        /* playball draw */
        playball.draw(virtScreen.getScreen("main"));
           
        /* paddle draw */
        st.draw(virtScreen.getScreen("main"));

		/* move ball almost every 10 clicks */
		if (cycle+10 < SDL_GetTicks())
		{
		    stfield.iterate_sky();
			//detect_collision(&gmboard, x_pos, y_pos, &b, &a);
        
            int x_pos = playball.getX();
            int y_pos = playball.getY();
            
            detect_collision(&gmboard, &playball);

			if (x_pos > MAX_X || x_pos < 0)
                playball.setB(-1*playball.getB());
			else if (y_pos > MAX_Y)
			{
                playball.setA(1);
                playball.setB(1);
                playball.setCords(x_pos, y_pos);
                playball.setVisible(false);
				playball.draw(virtScreen.getScreen("main"));

				tmp_x_pos = MAX_X/2;
	            playball.setCords(tmp_x_pos, playball.getA()*tmp_x_pos);
                x_pos = playball.getX();
                y_pos = playball.getY();
			}
/*			else if (x_pos < 0)
				b = -1*b;*/
			else if (y_pos < 0)
				playball.setA(-1*playball.getA());
			/* if ball hits the pad */
			else if (y_pos > MAX_Y-40 && y_pos < MAX_Y-35 && 
					(x_pos >= rel_x - PAD_WIDTH &&
					x_pos <= rel_x + PAD_WIDTH))
			{
				if (x_pos >= rel_x - PAD_WIDTH/4 &&
					x_pos <= rel_x + PAD_WIDTH/4)
				{
					if (playball.getA() >= 0)
						playball.setA(-1*playball.getA());
				}
				else
				{
					if (playball.getA() == -1)
						playball.setA((-1)*random() % 3);
					else
						playball.setA((-1)*random() % 3);
				}
			}
			cycle = SDL_GetTicks();
			x_pos += playball.getB()*playball.getSpeed();
			y_pos += playball.getA()*playball.getSpeed();
//			printf("x == %d y == %d\n", x_pos, y_pos);
			playball.setCords(x_pos, y_pos);
            playball.setVisible(true);
		}

        if (led_cycle + 150 < SDL_GetTicks()) {
            led_cycle = SDL_GetTicks();
            if (leds.get_done()) {
                leds.set_text("za");
                std::cout << "juz\n";
            }
            leds.all_off();
            leds.scroll();

            zero_surface(virtScreen.getScreen("led"));
            leds.draw(virtScreen.getScreen("led"));
        }

        virtScreen.draw(window, drawable);
		SDL_Flip(window);
		
	}
  
    leds.all_off();
    leds.set_mode("static");
    leds.set_text("end");
    leds.scroll();
    leds.draw(virtScreen.getScreen("led"));
    virtScreen.draw(window, drawable);

    /* Fade out */
    SDL_BlitSurface(virtScreen.getScreen("main"), NULL, virtScreen.getScreen("blend_temp"), NULL);
    //zero_surface(virtScreen.getScreen("draw_temp"));
	for (i = 0; i<256;)
	{
		if ( cycle+1 < SDL_GetTicks())
		{
			cycle = SDL_GetTicks();
			blend_image(virtScreen.getScreen("main"), virtScreen.getScreen("blend_temp"), virtScreen.getScreen("draw_temp"), i, 1);
            virtScreen.draw(window, drawable);
			SDL_Flip(window);
			i+=5;
		}
	}

	return 0;
}


