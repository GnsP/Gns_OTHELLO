#ifndef OTHELLO_GAME_CORE1_H
#define OTHELLO_GAME_CORE1_H

#include "othello_human_player.h"
#include "othello_computer_move.h"


int play( SDL_Surface *Screen)
{
	int player_sign,winner,flag,res = 0;
	char p;

	SDL_Surface *page_1 = SDL_LoadBMP ( "Images/back_ground.bmp" );
	SDL_Rect page1_Rect;
	page1_Rect.x=0;
	page1_Rect.y=0;

	//------------------------------

	TTF_Font *f = TTF_OpenFont("Fonts/arial.ttf",30);
	SDL_Surface * Surf1 = TTF_RenderText_Blended(f, "Select Game Mode :", WHITE);
	SDL_Surface * Surf2 = SDL_LoadBMP ( "Images/practice.bmp");
	SDL_Surface * Surf3 = SDL_LoadBMP ( "Images/challenge.bmp");


	SDL_Rect R1,R2,R3;
	R1.x = 50;
	R1.y = 100;
	R2.x = 140;
	R2.y = 350;
	R3.x = 350;
	R3.y = 350;

	SDL_BlitSurface ( Surf1, 0, page_1, &R1 );
	SDL_BlitSurface ( Surf2, 0, page_1, &R2 );
	SDL_BlitSurface ( Surf3, 0, page_1, &R3 );

	SDL_BlitSurface ( page_1, 0, Screen, &page1_Rect );
	SDL_Flip ( Screen );

    bool pageRunning = true;
    SDL_Event e;
    int x,y;
	while ( pageRunning )
	{
		while ( SDL_PollEvent ( &e ))
		{
			SDL_GetMouseState ( &x, &y );

			if ( e.type == SDL_QUIT )
				exit (0);
			if ( e.type == SDL_MOUSEBUTTONUP )
			{
				if ( x > 140 && y > 350 && x < 340 && y < 470 )
				{
					pageRunning = false;
					game_state = 1;
					break;
				}

				if ( x > 350 && y > 350 && x < 550 && y < 470 )
				{
					pageRunning = false;
					game_state = 0 ;
					break;
				}
			}
		}
	}

	//------------------------------

	page_1 = SDL_LoadBMP ( "Images/back_ground.bmp" );

	f = TTF_OpenFont("Fonts/arial.ttf",40);
	Surf1 = TTF_RenderText_Blended(f, "What will you take ?", WHITE);
	Surf2 = SDL_LoadBMP ( "Images/white.bmp");
	Surf3 = SDL_LoadBMP ( "Images/black.bmp");

	R1.x = 50;
	R1.y = 100;
	R2.x = 140;
	R2.y = 350;
	R3.x = 350;
	R3.y = 350;

	SDL_BlitSurface ( Surf1, 0, page_1, &R1 );
	SDL_BlitSurface ( Surf2, 0, page_1, &R2 );
	SDL_BlitSurface ( Surf3, 0, page_1, &R3 );

	SDL_BlitSurface ( page_1, 0, Screen, &page1_Rect );
	SDL_Flip ( Screen );

    pageRunning = true;
	while ( pageRunning )
	{
		while ( SDL_PollEvent ( &e ))
		{
			SDL_GetMouseState ( &x, &y );

			if ( e.type == SDL_QUIT )
				exit (0);
			if ( e.type == SDL_MOUSEBUTTONUP )
			{
				if ( x > 140 && y > 350 && x < 340 && y < 470 )
				{
					pageRunning = false;
					p = 'P';
					player_sign = white_tile;
					break;
				}

				if ( x > 350 && y > 350 && x < 550 && y < 470 )
				{
					pageRunning = false;
					p = 'C';
					player_sign = black_tile;
					break;
				}
			}
		}
	}
	
	show_hints = false ;
	
	player_tile_color = player_sign;
	display (65, player, getScore(player_sign),Screen) ;
	if(p=='P')
	{
		player_move(white_tile, Screen);
		flag=1;
	}
	else
	{
		computer_move(black_tile,Screen);
		flag=1;
	}
	winner=check();
	while(winner==0)
	{
		if(flag%2==0)
		{
			if(p=='P') player_move(player_sign, Screen);
			else computer_move(player_sign,Screen);
		}
		else
		{
			if(p=='P') computer_move(player_sign,Screen);
			else player_move(player_sign, Screen);
		}
		winner=check();
		flag++;
		/*if(flag==64)
		{
			winner=empty_space;
			break;
		}*/
	}
	display (65, player, getScore(player_sign),Screen) ;
	
	/*free ( surf1 );
	free ( surf2 );
	free ( surf3 );
	free ( surf4 );
	free ( surf5 );
	free ( surf6 );
	free ( surf7 );
	free ( D1 );
	free ( D2 );
	free ( page );
	free ( Board );
	free ( score_board );
	free ( ResetButton );
	free ( header );*/
	

	page_1 = SDL_LoadBMP ( "Images/back_ground.bmp" );
	page1_Rect.x=0;
	page1_Rect.y=0;
	f = TTF_OpenFont("Fonts/arial.ttf",25);

	if(winner==player_sign)
		Surf1 = TTF_RenderText_Blended(f, "CONGRATS ! YOU WON !!!", WHITE);
	else if(winner==empty_space)
		Surf1 = TTF_RenderText_Blended(f, "OOPS ... GAME DRAW !!!", WHITE);
	else
		Surf1 = TTF_RenderText_Blended(f, "SORRY ! COMPUTER WINS !", WHITE);
	R1.x = 50;
	R1.y = 220;

	Surf2 = SDL_LoadBMP ( "Images/play_again.bmp" );
	R2.x = 170;
	R2.y = 300;

	SDL_BlitSurface ( Surf1, 0, page_1, &R1 );
	SDL_BlitSurface ( Surf2, 0, page_1, &R2 );

	SDL_BlitSurface ( page_1, 0, Screen, &page1_Rect );
	SDL_Flip ( Screen );

	pageRunning = true;
	while ( pageRunning )
	{
		while ( SDL_PollEvent ( &e ))
		{
			SDL_GetMouseState ( &x, &y );

			if ( e.type == SDL_QUIT )
				exit (0);
			if ( e.type == SDL_MOUSEBUTTONUP )
			{
				if ( x > 170 && y > 300 && x < 470 && y < 420 )
				{
					res = 27;
					pageRunning = false;
					break;
				}
			}
		}
	}
	SDL_FreeSurface ( Surf1 );
	SDL_FreeSurface ( Surf2 );
	SDL_FreeSurface ( Surf3 );
	return res;
}


#endif

