#ifndef OTHELLO_USER_INTERFACE1_H
#define OTHELLO_USER_INTERFACE1_H

#include "othello_game_core.h"

void start_screen(SDL_Surface *Screen)
{
	static int cnt;
	if(cnt==0)
	{
		SDL_Surface * page = SDL_LoadBMP ("Images/back_ground.bmp");
		SDL_Rect pageRect;
		pageRect.x=0;
		pageRect.y=0;

		TTF_Font *f = TTF_OpenFont("Fonts/arial.ttf",40);
		TTF_Font *f1 = TTF_OpenFont("Fonts/LCD.ttf",30);
		SDL_Surface * Surf1 = TTF_RenderText_Blended(f, "OTHELLO", WHITE);
		SDL_Surface * Surf2 = TTF_RenderText_Blended(f, "by Ganesh Prasad", WHITE);
		SDL_Surface * Surf3 = TTF_RenderText_Blended(f1, "[ CLICK TO CONTINUE ]", WHITE);

		SDL_Rect R1,R2,R3;
		R1.x = 100;
		R1.y = 100;
		R2.x = 100;
		R2.y = 250;
		R3.x = 150;
		R3.y = 420;

		SDL_BlitSurface ( Surf1, 0, page, &R1 );
		SDL_BlitSurface ( Surf2, 0, page, &R2 );
		SDL_BlitSurface ( Surf3, 0, page, &R3 );

		SDL_BlitSurface ( page, 0, Screen, &pageRect );
		SDL_Flip ( Screen );
	}
	cnt++;
}

void game()
{
	int p;
	static int count;

	SDL_Init ( SDL_INIT_EVERYTHING );
	atexit ( SDL_Quit );

	SDL_Surface *Screen = SDL_SetVideoMode ( 640, 480, 0, SDL_HWSURFACE|SDL_DOUBLEBUF );
	SDL_WM_SetCaption ( "Gns OTHELLO -- v.01.00", 0 );
	TTF_Init();
	initialise () ;

	if(count==0)
	{
		start_screen(Screen);
		bool running = true;
		SDL_Event e;
		while ( running )
		{
			while(SDL_PollEvent(&e))
			{
				if ( e.type == SDL_QUIT )
					exit( 0 );
				if ( e.type == SDL_KEYUP || e.type == SDL_MOUSEBUTTONUP )
				{	running = false; break; }
			}
		}
	}
	p = 27 ;
	while(p==27)
	{
		reset();
		p = play ( Screen );
	}
	SDL_FreeSurface ( Screen );
}


#endif
