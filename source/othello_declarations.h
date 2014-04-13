#ifndef OTHELLO_DECLARATIONS_INCLUDED_H
#define OTHELLO_DECLARATIONS_INCLUDED_H

#include "othello_def.h"

SDL_Surface *page = NULL;
SDL_Rect pageRect;
SDL_Surface *Board = NULL;
SDL_Rect boardRect;
SDL_Surface *Board_base = NULL;
SDL_Rect boardBaseRect;
SDL_Surface *score_board = NULL;
SDL_Rect scoreRect;
SDL_Surface *ResetButton = NULL;
SDL_Rect ResetRect;
SDL_Surface *header = NULL;

int player_tile_color = white_tile;

inline bool isOnBoard ( int x, int y )
{
	return x<8 && x>=0 && y<8 && y>=0;
}

void initialise ( )
{
	Board_base = SDL_LoadBMP("Images/board.bmp");
	for ( int i=0; i < 8; i++ )
		for ( int j=0; j < 8; j++ )
			boxRGBA ( Board_base, i*45+2, j*45+2, (i+1)*45, (j+1)*45, 120, 150, 165, 255 );
	boardBaseRect.x = 0;
	boardBaseRect.y = 0;
}

int isValidMove ( int tile, int X, int Y )
{
	if ( mat[ MAT( X,Y )] != empty_space ) return 0;
	if (!isOnBoard(X,Y) ) return 0;
	int other_tile;
	if ( tile == white_tile ) other_tile = black_tile;
	else other_tile = white_tile;
	mat[ MAT(X,Y) ] = tile ;
	int tiles_to_flip = 0;
	for( int i=0; i<8; i++ )
	{
		int x=X, y=Y;
		x += direction[i][0];
		y += direction[i][1];
		if ( isOnBoard (x,y) && mat[ MAT(x,y) ] == other_tile )
		{
			x += direction[i][0];
			y += direction[i][1];
			if ( !isOnBoard (x,y) ) continue;
			while ( mat [ MAT(x,y) ] == other_tile )
			{
				x += direction[i][0];
				y += direction[i][1];
				if ( !isOnBoard (x,y) ) break;
			}
			if ( !isOnBoard (x,y) ) continue;
			if ( mat[ MAT(x,y) ] == tile )
			{
				while ( true )
				{
					x -= direction[i][0];
					y -= direction[i][1];
					if ( x == X && y == Y ) break;
					tiles_to_flip ++;
				}
			}
		}
	}
	mat[ MAT(X,Y) ] = empty_space;
	return tiles_to_flip;
}

void Free ()
{
	SDL_FreeSurface ( surf1 );
	SDL_FreeSurface ( surf2 );
	SDL_FreeSurface ( surf3 );
	SDL_FreeSurface ( surf4 );
	SDL_FreeSurface ( surf5 );
	SDL_FreeSurface ( surf6 );
	SDL_FreeSurface ( surf7 );
	SDL_FreeSurface ( D1 );
	SDL_FreeSurface ( D2 );
	SDL_FreeSurface ( page );
	SDL_FreeSurface ( Board );
	SDL_FreeSurface ( score_board );
	SDL_FreeSurface ( ResetButton );
	SDL_FreeSurface ( header );
}


void display(int selected, char turn, int score, SDL_Surface *Screen)
{
	int i,j;
	page = SDL_LoadBMP("Images/back_ground.bmp");
    pageRect.x = 0;
    pageRect.y = 0;
	Board = SDL_LoadBMP("Images/board.bmp");
	SDL_BlitSurface ( Board_base, 0, Board, &boardBaseRect );
    boardRect.x = 238;
    boardRect.y = 78;
	for ( i=0; i<8; i++ )
	{
		for ( j=0; j<8; j++ )
		{
			if ( show_hints && turn == player && isValidMove ( player_tile_color, i, j) )
				boxRGBA ( Board, i*45+2, j*45+2, (i+1)*45, (j+1)*45, 221, 141, 205, 200 );
		
			if ( MAT(i,j) == selected )
				boxRGBA ( Board, i*45+2, j*45+2, (i+1)*45, (j+1)*45, 0, 180, 255, 255 );

			if( mat[MAT(i,j)] == white_tile )
				filledCircleRGBA ( Board, i*45+22, j*45+22, 15, WHITE_ );

			if( mat[MAT(i,j)] == black_tile )
				filledCircleRGBA ( Board, i*45+22, j*45+22, 15, BLACK_ );
		}
	}
	SDL_BlitSurface ( Board, 0, page, &boardRect );

	score_board = SDL_LoadBMP ( "Images/score_board.bmp" );
	ResetButton = SDL_LoadBMP ( "Images/reset.bmp" );

	showScore ( turn, score, score_board );
	scoreRect.x = 40;
	scoreRect.y = 78;
	SDL_BlitSurface ( score_board, 0, page, &scoreRect );

	ResetRect.x = 160;
	ResetRect.y = 450;
	SDL_BlitSurface ( ResetButton, 0, page, &ResetRect );
	putImage ( header, "Images/header.bmp", 0, 0, page );

	SDL_BlitSurface ( page, 0, Screen, &pageRect );

	//SDL_LockSurface ( Screen );
	SDL_Flip ( Screen );
	Free () ;
	//SDL_UnlockSurface ( Screen );
}

inline bool isCorner ( int x, int y )
{
	return ( x == 0 || x == 7 ) && ( y == 0 || y == 7 ) ;
}

int getScore ( int player_sign )
{
	int score, cmp_score = 0, ply_score = 0;
	int cmp_sign;
	if ( player_sign == black_tile ) cmp_sign = white_tile;
	else cmp_sign = black_tile;

	for ( int i=0; i<64; i++ )
	{
		if ( mat [i] == player_sign ) ply_score++;
		if ( mat [i] == cmp_sign ) cmp_score ++;
	}
	score = cmp_score * 100 + ply_score ;
	return score;
}

void place ( char turn, int tile, int X, int Y, SDL_Surface *Screen , bool validity = false)
{
	mat [ MAT (X,Y) ] = tile;
	int other_tile = ( tile == white_tile ) ? black_tile : white_tile;
	int player_sign = ( turn == player ) ? tile : other_tile ;

	for( int i=0; i<8; i++ )
	{
		int x=X, y=Y;
		x += direction[i][0];
		y += direction[i][1];
		if ( isOnBoard (x,y) && mat[ MAT(x,y) ] == other_tile )
		{
			x += direction[i][0];
			y += direction[i][1];
			if ( !isOnBoard (x,y) ) continue;
			while ( mat [ MAT(x,y) ] == other_tile )
			{
				x += direction[i][0];
				y += direction[i][1];
				if ( !isOnBoard (x,y) ) break;
			}
			if ( !isOnBoard (x,y) ) continue;
			if ( mat[ MAT(x,y) ] == tile )
			{
				while ( true )
				{
					if( validity ) SDL_Delay ( 166 );
					x -= direction[i][0];
					y -= direction[i][1];
					if ( x == X && y == Y ) break;
					mat [ MAT (x,y) ] = tile;
					if ( validity ) display ( 65, turn, getScore ( player_sign ), Screen );
					if ( validity ) SDL_Delay ( 167 );
				}
			}
		}
	}
}

int check()
{
	int wht=0, blk=0, emp=0, valid = 0;
	for ( int i =0; i < 64; i++ )
	{
		valid += isValidMove ( white_tile, i/8, i%8 );
		valid += isValidMove ( black_tile, i/8, i%8 );
	}
	for ( int i=0; i<64; i++ )
	{
		if ( mat[i] == white_tile ) wht++;
		if ( mat[i] == black_tile ) blk++;
		if ( mat[i] == empty_space ) emp++;
	}
	if ( ! valid ) emp = 0;

	if ( emp != 0 && wht ==0 ) return black_tile;
	if ( emp != 0 && blk ==0 ) return white_tile;
	if ( emp == 0 )
	{
		if ( wht > blk ) return white_tile ;
		else if ( wht == blk ) return empty_space;
		else return black_tile ;
	}
	return 0;
}


#endif

