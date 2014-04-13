#ifndef OTHELLO_ARTIFICIAL_INTELLIGENCE_H
#define OTHELLO_ARTIFICIAL_INTELLIGENCE_H

#include "othello_declarations.h"

struct StateVariable
{
	int ComputerStaticPieces;
	int PlayerStaticPieces;
	int ComputerMobility;
	int PlayerMobility;
	int ComputerPieces;
	int PlayerPieces;
	int ComputerCorner;
	int PlayerCorner;

	StateVariable ()
	{
		ComputerStaticPieces = 0;
		PlayerStaticPieces = 0;
		ComputerMobility = 0;
		PlayerMobility = 0;
		ComputerPieces = 0;
		PlayerPieces = 0;
		PlayerCorner = 0;
		ComputerCorner = 0;
	}
};

bool isStatic ( int X, int Y, int tile )
{
	int x,y, score = 0;
	bool Static [8] ;
	for ( int i=0; i<8; i++ )
	{
		x = X;
		y = Y;
		while ( true )
		{
			x += direction [i] [0];
			y += direction [i] [1];

			if ( !isOnBoard ( x,y ) )
			{
				score ++;
				Static [i] = true;
				break;
			}
			if ( mat [ MAT (x,y) ] != tile )
			{
				Static [i] = false ;
				break;
			}
		}
	}
	for ( int i=0; i<7; i++ )
	{
		for ( int j=i+1; j<8; j++ )
		{
			if ( Static [i] && Static [j] )
				if ( direction [i][0] + direction [j][0] == 0 && direction [i][1] + direction [j][1] == 0 )
					score -- ;
		}
	}
	if ( score >= 4 ) return true;
	return false;
}

StateVariable evaluate ( int player_sign )
{
	StateVariable result;
	int computer_sign = ( player_sign == white_tile ) ? black_tile : white_tile ;
	for ( int i=0; i<64; i++ )
	{
		if ( mat [i] == player_sign )
		{
			result.PlayerPieces ++;
			if ( isStatic ( i/8, i%8, player_sign )) result.PlayerStaticPieces ++ ;
			if ( isCorner ( i/8, i%8 )) result.PlayerCorner ++ ;
		}
		if ( mat [i] == computer_sign )
		{
			result.ComputerPieces ++ ;
			if ( isStatic ( i/8, i%8, computer_sign )) result.ComputerStaticPieces ++ ;
			if ( isCorner ( i/8, i%8 )) result.ComputerCorner ++ ;
		}
		if ( isValidMove ( player_sign, i/8, i%8 )) result.PlayerMobility ++ ;
		if ( isValidMove ( computer_sign, i/8, i%8 )) result.ComputerMobility ++ ;
	}
	return result;
}

long double EvalScore ( StateVariable S, int tile )
{
	if ( tile == computer )
		return (long double) ( S.ComputerCorner * 9999999 + S.ComputerStaticPieces * 1000 + S.ComputerPieces ) / S.PlayerMobility ;
	if ( tile == player )
		return (long double) ( S.PlayerCorner * 9999999 + S.PlayerStaticPieces * 1000 + S.PlayerPieces) / S.ComputerMobility ;
}

bool isRunning ()
{
	for ( int i =0; i<64; i++ )
		if ( isValidMove ( white_tile, i/8, i%8 ) || isValidMove ( black_tile, i/8, i%8 ))
			return true;
	return false;
}

const int MAX_DEPTH = 50000;
int depth ;

long double MiniMax ( int turn, int player_sign, SDL_Surface *Screen, bool start = false )
{

    //static int depth;
	if ( start ) depth = 0;
	//else depth ++;
	long double score = -99999999;
	int computer_sign = ( player_sign == white_tile) ? black_tile : white_tile ;
	int next_turn = ( turn == player ) ? computer : player ;
	int sign = ( turn == player ) ? player_sign : computer_sign;

	if ( depth == MAX_DEPTH || ( ! isRunning ()))
	{
		score = EvalScore ( evaluate ( player_sign ), next_turn );
		return score;
	}
	else
	{
		depth = depth + 1 ;
		int temp_board [64];
		for ( int i=0; i<64; i++ )
		{
			if ( isValidMove ( sign, i/8, i%8 ))
			{
				if ( isCorner ( i/8, i%8 ) )
					return EvalScore ( evaluate ( player_sign ), turn );
				for ( int k=0; k<64; k++ )
					temp_board [k] = mat [k] ;

				place ( turn, sign, i/8, i%8, Screen, false );
				float temp = -MiniMax ( next_turn, player_sign, Screen, false );

				if ( temp > score )
					score = temp;
				for ( int k=0; k<64; k++ )
					mat [k] = temp_board [k] ;
			}
		}
		return score;
	}
}

int computer_move_challenge ( int player_sign, SDL_Surface *Screen )
{
	int move = -2, temp;
	long double score = 9999999;
	int temp_board [64];
	int computer_sign = ( player_sign == white_tile ) ? black_tile : white_tile;
	for ( int i=0; i<8; i++ )
	{
		for ( int j=0; j<8; j++ )
		{

			if ( isValidMove ( computer_sign, i, j ))
			{
				if ( isCorner ( i, j ))
				{
					place ( computer, computer_sign, i, j, Screen , true) ;
					return 0;
				}
				for ( int k=0; k<64; k++ )
					temp_board [k] = mat [k] ;
				place ( computer, computer_sign, i, j, Screen , false) ;
				//depth = 0;
				temp = MiniMax ( player, player_sign, Screen, true );
				for ( int k=0; k<64; k++ )
					mat [k] = temp_board [k] ;
				if ( temp < score )
				{
					score = temp;
					move = MAT (i,j);
				}
			}
		}
	}
	if ( move == -2 ) return 0;
	place ( computer, computer_sign, move/8, move%8, Screen , true) ;
	return 0;
}

//this block of code describing AI of the game has been rejected due to lack of an efficient depth control mechanism.


/*int computer_move_challenge ( int player_sign, SDL_Surface *Screen )
{
	int move = -2, mv = -2;
	long double score = -9999999, value = -9999999, value1=-9999999,  temp, temp1, temp2, temp3, temp4;
	int temp_board [3][64];
	bool end_move = true ;
	bool flag = false;
	bool end_move_1 = true ;
	int computer_sign = ( player_sign == white_tile ) ? black_tile : white_tile;
	for ( int i=0; i<8; i++ )
	{
		for ( int j=0; j<8; j++ )
		{
			if ( isValidMove ( computer_sign, i, j ))
			{
				if ( isCorner ( i, j ))
				{
					place ( computer, computer_sign, i, j, Screen , true) ;
					return 0;
				}
				for ( int k=0; k<64; k++ )
					temp_board [0][k] = mat [k] ;
				value = -999999;
				place ( computer, computer_sign, i, j, Screen, false );
				for ( int index=0; index<64; index ++ )
				{
					if ( isValidMove ( player_sign, index/8, index%8 ) )
					{
						for ( int index2=0; index2 <64; index2 ++ )
							temp_board [1] [index2] = mat [index2] ;
						place ( player, player_sign, index/8, index%8, Screen, false );
						value1 = -9999999;
						for ( int index3=0; index3<64; index3 ++ )
						{
							if ( isValidMove ( computer_sign, index3/8, index3%8 ))
							{
								for ( int index4=0; index4 < 64; index4 ++ )
									temp_board [2][index4] = mat [index4] ;
								place ( computer, computer_sign, index3/8, index3%8, Screen, false );
								temp3 = EvalScore ( evaluate ( player_sign ), player );
								for ( int index5 = 0; index5 < 64; index5 ++ )
									if ( isValidMove ( player_sign, index5/8, index5%8 ) && isCorner ( index5/8, index5%8 ))
										temp3 = -99999;
								if ( temp3 > value1 ) value1 = temp3 ;
								for ( int index4=0; index4 < 64; index4 ++ )
									mat [index4] = temp_board [2][index4]  ;
								end_move_1 = false ;
							}
						}

						temp4 = value1 ;
						if ( end_move_1 )	//temp4 = 1;
							temp4 = ( check () == computer_sign ) ? 9999999 : 1;
						temp1 = EvalScore ( evaluate ( player_sign ), player );
						//if ( mat [0] == player_sign || mat [7] == player_sign || mat [63] == player_sign || mat [56] == player_sign )
						//{
						//	temp1 == 9999999;
						//	flag = true;
						//}
						temp1 /= ( temp4 * 100000 ) ;

						if ( temp1 > value )
						{
							value = temp1;
							mv = index;
						}
						for ( int index2=0; index2 <64; index2 ++ )
							mat [index2] = temp_board [1] [index2];
						end_move = false ;
					}
				}
				temp = value;
				if ( end_move ) //temp = 1 ;
					temp = ( check () == player_sign ) ? 9999999 : 1;
				temp2 = EvalScore ( evaluate ( player_sign ),computer) ;
				temp = ( temp2 ) / ( temp * 100000 ) ;

				//temp = MiniMax ( player_sign, Screen, true );
				if ( temp > score )
				{
					score = temp;
					move = MAT ( i,j );
				}
				for ( int k=0; k<64; k++ )
					mat [k] = temp_board [0][k] ;
			}
		}
	}
	if ( move == -2 ) return 0;
	place ( computer, computer_sign, move/8, move%8, Screen , true) ;
	return 0;
} */

#endif


