#ifndef OTHELLO_COMPUTER_MOVE1_H
#define OTHELLO_COMPUTER_MOVE1_H

#include "othello_declarations.h"
#include "othello_AI.h"

int computer_move_practice ( int player_sign, SDL_Surface *Screen )
{
	int move = -2, temp, score = -1;
	int computer_sign = ( player_sign == white_tile ) ? black_tile : white_tile;
	for ( int i=0; i<8; i++ )
	{
		for ( int j=0; j<8; j++ )
		{
			temp = isValidMove ( computer_sign, i, j );
			if(temp == 0 ) continue ;
			if ( temp != 0 && isCorner ( i, j ))
			{
				place ( computer, computer_sign, i, j, Screen , true) ;
				return 0;
			}
			if ( temp > score )
			{
				score = temp;
				move = MAT ( i,j );
			}
		}
	}
	if ( move == -2 ) return 0;
	place ( computer, computer_sign, move/8, move%8, Screen , true) ;
	return 0;
}

/*int minimax ( int player_sign, SDL_Surface *Screen )
{
	int BackUpBoard [64];
	int winner = check();
	if ( winner != 0)
		return winner * player_sign;
	int move = -1;
	int score = -2;
	for ( int i =0; i<8; i++)
	{
		for ( int j=0; j<8; j++ )
		{
			if ( isValidMove ( player_sign, i, j) )
			{
				for ( int i=0; i<64; i++ )
					BackUpBoard [i] = mat [i];
				place ( player, player_sign, i, j, Screen, false );
				int thisScore = -minimax (player_sign*(-1), Screen);
				if ( thisScore > score )
				{
					score = thisScore;
					if ( score == 1 ) return 1;
					move = i;
				}
				for ( int i=0; i<64; i++ )
					mat [i] = BackUpBoard [i];
			}
		}
	}
	if(  move == -1 ) return 0;
	return score;
}

void computer_move_challenge ( int player_sign, SDL_Surface *Screen )
{
	int move = -1;
	int score = -2;

	int computer_sign;
	computer_sign = ( player_sign == white_tile ) ? black_tile : white_tile ;

	for ( int i=0; i<8; i++)
	{
		for ( int j=0; j<8; j++ )
		{
			if ( isValidMove ( player_sign, i, j) )
			{
				int BackUpBoard [64];
				for ( int i=0; i<64; i++ )
					BackUpBoard [i] = mat [i];
				place ( computer, computer_sign, i, j, Screen, false );
				int temp_score = -minimax ( player_sign , Screen);
				for ( int i=0; i<64; i++ )
					mat [i] = BackUpBoard [i];
				if ( temp_score > score )
				{
					score = temp_score;
					move = MAT(i,j);
				}
			}
		}
	}
	place ( computer, computer_sign, move/8, move%8, Screen, false );
}*/

void computer_move ( int player_sign, SDL_Surface * Screen )
{
	if( game_state ) computer_move_practice ( player_sign , Screen);
	else computer_move_challenge ( player_sign , Screen);
	display ( 65, computer, getScore ( player_sign ), Screen );
}


#endif

