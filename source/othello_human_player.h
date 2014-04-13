#ifndef OTHELLO_HUMAN_PLAYER1_H
#define OTHELLO_HUMAN_PLAYER1_H

#include "othello_declarations.h"

int player_move( int player_sign , SDL_Surface * Screen)
{
	int x,y,sqr = 65, valid = 0;

	for ( int i =0; i < 64; i++ )
		valid += isValidMove ( player_sign, i/8, i%8 );
	if ( !valid ) return 0;

	SDL_Event e;
	bool loop = true ;

	while ( loop )
	{
		while ( SDL_PollEvent ( &e ) )
		{
			SDL_GetMouseState ( &x, &y );
			if ( x >= 238 && y >= 78 && x <= 600 && y <= 440 )
			{
				x = x - 238;
				y = y - 78;
				sqr = MAT ( (x-2)/45, (y-2)/45 );
				if ( sqr >=0 && sqr < 64 ) display ( sqr, player, getScore ( player_sign ), Screen );
			}
			if ( e.type == SDL_QUIT ) exit(0);
			if ( e.type == SDL_MOUSEBUTTONUP )
			{
				/*flag = place ( sqr, player_sign );
				if ( flag == 1 ){ loop = false ; break; }*/

				if ( x >= 160 && y >= 450 && x <= 480 && y <= 480 )
				{
					reset();
					display ( sqr, player, getScore ( player_sign ), Screen );
					if ( player_sign == black_tile ) loop = false;
					break;
				}
				//if ( x >= 238 && y >= 78 && x <= 600 && y <= 440 )
				//{
					//x = x - 238;
					//y = y - 78;
					if ( isValidMove ( player_sign, (x-2)/45, (y-2)/45 ))
					{
						place ( player, player_sign, (x-2)/45, (y-2)/45, Screen, true );
						loop = false;
						break;
					}
				//}
			}
			if ( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_h )
				show_hints = !show_hints ;
		}
	}
	return 0;
}

#endif



