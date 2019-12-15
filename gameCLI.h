/************************** Tic Tac Toe ************************************
Student Name: Habiba Mostafa                    
Date: November 28th, 2018                           Course Name: CIS 1500 */

#ifndef GAMECLI
#define GAMECLI

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int isInputValid(int, int, int);
int isBoardFull(char[N][N]);
void createInitialBoard(char[N][N]);
void readUserMove(int *, int *);
void printCurrentBoard(char[N][N]);
int getComputerMove(char[N][N], int *, int *, int, int);
int gameWon(char[N][N], char);
int computerPlaysToWin(char[N][N], int *, int *);
void computerPlaysRandom(int *, int *, int, int);
void sumAllDimensions(char[N][N], int[N], int[N], int *, int *);
int memberOf(int, int[N]);
int computerPlaysToBlock(char [N][N], int * , int * );


#endif
