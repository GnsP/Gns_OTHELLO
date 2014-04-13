#ifndef OTHELLO_DEFINITIONS_INCLUDED_H
#define OTHELLO_DEFINITIONS_INCLUDED_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>

const int white_tile = 1;
const int black_tile = -1;
const int empty_space = 0;
const char computer = 'c';
const char player = 'p';

int direction[8][2] 	= {	{0,1},
							{1,1},
							{1,0},
							{1,-1},
							{0,-1},
							{-1,-1},
							{-1,0},
							{-1,1}	};

int game_state = 1;
int mat[64];

bool show_hints = false;

inline int MAT ( int i, int j )
{
	return i*8+j;
}

SDL_Color WHITE = {255,255,255};
SDL_Color BLACK = {16,35,44};

#define WHITE_ 255,255,255,255
#define BLACK_ 16,35,44,255

void reset()
{
	for ( int i=0; i<8; i++ )
		for ( int j=0; j<8; j++ )
			mat[ MAT (i,j) ] = empty_space;
	mat[ MAT (3,3) ] = white_tile;
	mat[ MAT (4,4) ] = white_tile;
	mat[ MAT (3,4) ] = black_tile;
	mat[ MAT (4,3) ] = black_tile;
}

void putImage ( SDL_Surface *child, char *fileName, int X, int Y, SDL_Surface *base )
{
	child = SDL_LoadBMP ( fileName );
	SDL_Rect temp;
	temp.x = X;
	temp.y = Y;
	SDL_BlitSurface ( child, 0, base, &temp );
}

SDL_Surface *surf1 = NULL, *surf2 = NULL, *surf3 = NULL, *surf4 = NULL, *surf5 = NULL, *surf6 = NULL, *surf7 = NULL, *D1 = NULL, *D2 = NULL ;

void writeDigits ( SDL_Surface *area, int d1, int d2 )
{
	switch( d1 )
	{
		case 0:
		{
			putImage ( D1, "Images/0.bmp", 5, 5, area );
			break;
		}
		case 1:
		{
			putImage ( D1, "Images/1.bmp", 5, 5, area );
			break;
		}
		case 2:
		{
			putImage ( D1, "Images/2.bmp", 5, 5, area );
			break;
		}
		case 3:
		{
			putImage ( D1, "Images/3.bmp", 5, 5, area );
			break;
		}
		case 4:
		{
			putImage ( D1, "Images/4.bmp", 5, 5, area );
			break;
		}
		case 5:
		{
			putImage ( D1, "Images/5.bmp", 5, 5, area );
			break;
		}
		case 6:
		{
			putImage ( D1, "Images/6.bmp", 5, 5, area );
			break;
		}
		case 7:
		{
			putImage ( D1, "Images/7.bmp", 5, 5, area );
			break;
		}
		case 8:
		{
			putImage ( D1, "Images/8.bmp", 5, 5, area );
			break;
		}
		case 9:
		{
			putImage ( D1, "Images/9.bmp", 5, 5, area );
			break;
		}
		default:
		{
			putImage ( D1, "Images/blank.bmp", 5, 5, area );
			break;
		}
	}
	switch( d2 )
	{
		case 0:
		{
			putImage ( D2, "Images/0.bmp", 35, 5, area );
			break;
		}
		case 1:
		{
			putImage ( D2, "Images/1.bmp", 35, 5, area );
			break;
		}
		case 2:
		{
			putImage ( D2, "Images/2.bmp", 35, 5, area );
			break;
		}
		case 3:
		{
			putImage ( D2, "Images/3.bmp", 35, 5, area );
			break;
		}
		case 4:
		{
			putImage ( D2, "Images/4.bmp", 35, 5, area );
			break;
		}
		case 5:
		{
			putImage ( D2, "Images/5.bmp", 35, 5, area );
			break;
		}
		case 6:
		{
			putImage ( D2, "Images/6.bmp", 35, 5, area );
			break;
		}
		case 7:
		{
			putImage ( D2, "Images/7.bmp", 35, 5, area );
			break;
		}
		case 8:
		{
			putImage ( D2, "Images/8.bmp", 35, 5, area );
			break;
		}
		case 9:
		{
			putImage ( D2, "Images/9.bmp", 35, 5, area );
			break;
		}
		default:
		{
			putImage ( D2, "Images/blank.bmp", 35, 5, area );
			break;
		}
	}
}

void showScore ( char turn, int score, SDL_Surface *base )
{
	int digit [4];
	int i = 0 ;
	while ( i < 4 )
	{
		digit [ i++ ] = score % 10;
		score /= 10;
	}

	putImage ( surf1, "Images/score.bmp", 48, 10, base );
	putImage ( surf2, "Images/computer_score.bmp", 10, 69, base );
	putImage ( surf3, "Images/player_score.bmp", 10, 135, base );
	putImage ( surf4, "Images/turn.bmp", 48, 200, base );
	if ( turn == 'c' )
		putImage ( surf5, "Images/computer.bmp", 48, 260, base );
	else
		putImage ( surf5, "Images/human.bmp", 48, 260, base );

	surf6 = SDL_LoadBMP ( "Images/score_area.bmp" );
	surf7 = SDL_LoadBMP ( "Images/score_area.bmp" );
	writeDigits ( surf6, digit[3], digit[2] );
	writeDigits ( surf7, digit[1], digit[0] );
	SDL_Rect Rect6, Rect7;
	Rect6.x = 115;
	Rect6.y = 60;
	Rect7.x = 115;
	Rect7.y = 130;
	SDL_BlitSurface ( surf6, 0, base, &Rect6 );
	SDL_BlitSurface ( surf7, 0, base, &Rect7 );
}


#endif