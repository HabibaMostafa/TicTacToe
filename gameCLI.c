/************************** Tic Tac Toe ************************************
Student Name: Habiba Mostafa                    
Date: November 28th, 2018                              Course Name: CIS 1500

****************************************************************************
The user is prompted for 11 different inputs before the output
is generated.
*****************************************************************************/

#include "gameCLI.h"
int main()
{

  int  userRow, userCol, computerRow, computerCol;
  int taken;
  char board[N][N];
  char winner = 'N';

  srand(time(NULL));

  printf("This tic-tac-toe board is of size %d by %d\n", N, N);

  printf("Player symbol: X \nComputer symbol: O\n\n");

  printf("Here is the board - spaces are indicated by a ?\n");

  createInitialBoard(board); // create a 3 X 3 board with '?' in each cell

  while ((winner != 'Y') && !(isBoardFull(board))) // while there is no winner and the board is not full
  {
    taken = 0;

    while (!(taken)) // loop used to accept valid row and col values from the user
    {
      readUserMove(&userRow, &userCol); //get user's move
      printf("You chose row %d and column %d \n", userRow, userCol);

      while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N)) // validate user's move
      {
        printf("That's is an invalid row or column number - try again\n");
        readUserMove(&userRow, &userCol);
        printf("You chose row %d and column %d \n", userRow, userCol);
      }

      if (board[userRow - 1][userCol - 1] == '?') // if cell is unoccupied
      {
        board[userRow - 1][userCol - 1] = 'X'; // store an X there
        taken = 1;
      }
      else
      {
        taken = 0; // otherwise inform the user to enter values again
        printf("That spot is taken - please try another one\n");
      }
    } //end of while (!taken)

    if (gameWon(board, 'X')) // check if the user wins - game will end if the user does win
    {
      printf("YOU WIN!\n");
      winner = 'Y';
    }

    else if (!(isBoardFull(board))) //check if the board is already full
    {
      taken = 0;

      while (!(taken))
      {
        getComputerMove(board, &computerRow, &computerCol, userRow - 1, userCol - 1); // get computer's row and col

        if (board[computerRow][computerCol] == '?') // check if the cell is unoccupied
        {
          board[computerRow][computerCol] = 'O';
          taken = 1;
        }
        else
        {
          taken = 0; //That spot is taken - computer - try another one
        }
      }

      printf("Computer chose row %d and column %d \n", computerRow + 1, computerCol + 1);

      if (gameWon(board, 'O')) // check if the computer wins - game must end if it does
      {
        printf("THE COMPUTER WON! HARD LUCK!\n");
        winner = 'Y';
      }
    }

    printCurrentBoard(board);

    printf("\nPress enter to continue \n");
    getchar();

  } //end of while

  if (winner != 'Y')
    printf("IT'S A TIE!\n\n");


  return 0;
}

int getComputerMove(char board[N][N], int *computerRow, int *computerCol, int userRow, int userCol)
{
  /*
  This function determines computer's move in terms of row (computerRow) and column (computerCol)
  and outputs them to main. The computer first tries to find a winning spot for itself; if it doesn't
  find one, then it calls function computerPlaysRandom in its attempt to place its symbol in
  the same row or column as the user (userRow, userCol)
*/

  int winningSpot = 0;
  int blocked = 1;           // this declaration is required if you attempt the bonus part

  winningSpot = computerPlaysToWin(board, computerRow, computerCol);

  if (!winningSpot) // if computer does find a winning spot, then it plays to block the user
  {
    computerPlaysRandom(computerRow, computerCol, userRow, userCol);

//	   If you attempt the bonus part, then uncomment the code below and use it to first try and block user move
//	   If unsuccessful, then it pick row and col (pseudo) randomly


	   blocked = computerPlaysToBlock(board, computerRow, computerCol);
	   if (blocked == 0)
		   computerPlaysRandom(computerRow, computerCol, userRow, userCol);

  }


  return winningSpot;
}


int isInputValid(int entered, int minimum, int maximum)
{

  //This function tests the number enetered by the user for the condition to see whether it is equal to
  //or lies between the minimum and maximum values specified or not - (1 and 3)
  //It returns 1 if number matches conditions and returns 0 otherwise.

  if ((entered >= minimum) && (entered <= maximum))
  {
    return 1;
  }

  return 0;
}

int isBoardFull(char board[N][N])
{

  int i;
  int j;

  //This function checks whether spots within the board are full or available. It checks whether
  //board array elements are occupied or not. In case the board is full, 1 is returned. In case of
  //the availability of spots, 0 is returned.

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      if (board[i][j] == '?')
      {
        return 0;
      }
    }
  }

  return 1;
}

void createInitialBoard(char board[N][N])
{

  int i;
  int j;

  //This function creates an empty board, it is defined by a 2 Dimensional array of size [N][N] or [3][3].
  //Each cell is assigned a '?' to represent empty spots. The board is also printed by this function in a
  //row column format with appropriate lines in between.

  printf("\n\n");

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      board[i][j] = '?';
      printf(" %c ", board[i][j]);
      if (j != 2)
      {
        printf("|");
      }
      else if (i != 2)
      {
        printf("\n");
        printf("-----------\n");
      }
    }
  }
  printf("\n");

  return;
}

void readUserMove(int *userRow, int *userCol)
{

  //This function asks the user for their choice of position of 'X'. They are asked for their
  //chosen row and their chosen column number.

  printf("\n\n");
  printf("Enter your chosen row number: ");
  scanf("%d", userRow);
  printf("Enter your chosen column number: ");
  scanf("%d", userCol);
  printf("\n\n");
}

void printCurrentBoard(char board[N][N])
{

  int i;
  int j;

  //This function simply prints the board at the current game round according to the user's move
  //and the computer's.

  printf("\n");
  printf("Your current board is: \n");
  printf("\n");

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      printf(" %c ", board[i][j]);
      if (j != 2)
      {
        printf("|");
      }
      else if (i != 2)
      {
        printf("\n");
        printf("-----------\n");
      }
    }
  }
  printf("\n");

  return;
}

int gameWon(char board[N][N], char symbol)
{

  //Declared Variables can be found below

  int sumR[N], sumC[N];
  int sumLD, sumRD;

  //Function call for the sumAllDimensions function to pass through the values required for the winning test.

  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);


  //The function memberOf is called to test whether the sum of rows, columns or diagonals is equal to 12
  //which consequently means that the computer won and 1 is returned. Otherwise, returns 0.

  if((memberOf(12, sumR)) || (memberOf(12, sumC)) || (memberOf(3, sumR)) || (memberOf(3, sumC)) ||
     (sumLD == 3) || (sumRD == 3) || (sumLD == 12) || (sumRD == 12))
  {
    return 1;
  }

  return 0;
}

int computerPlaysToWin(char board[N][N], int *cRow, int *cCol)
{

  //Declaring variables required for this function

  int i = 0;
  int j = 0;
  int sumR[N], sumC[N];
  int sumLD, sumRD;
  int sumRDColIndex;

  //This is a function call for sumAllDimensions to check if the computer has a chance to win according to the sum of
  //each row, column and diagonal.

  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);


  //Checking rows for a sum of 8

  for(i = 0; i < N; i++)
  {
    if(sumR[i] == 8)
    {
      for(j = 0; j < N; j++)
      {
        if(board[i][j] == '?')
        {
          *cRow = i;
          *cCol = j;
          return 1;
        }
      }
    }
  }


  //Checking columns for a sum of 8

  for(j = 0; j < N; j++)
  {
    if(sumC[i] == 8)
    {
      for(i = 0; i < N; i++)
      {
        if(board[i][j] == '?')
        {
          *cRow = i;
          *cCol = j;
          return 1;
        }
      }
    }
  }


  //Checking left diagonal for a sum of 8

  if(sumLD == 8)
  {
    for(i = 0; i < N; i ++)
    {
      if(board[i][i] == '?')
      {
        *cRow = i;
        *cCol = i;
        return 1;
      }
    }
  }


  //Checking right diagonal for a sum of 8

  if(sumRD == 8)
  {
    sumRDColIndex = 2;
    for(i = 0; i < N; i ++)
    {
      if(board[i][sumRDColIndex] == '?')
      {
        *cRow = i;
        *cCol = sumRDColIndex;
        return 1;
      }
      sumRDColIndex --;
    }
  }

  return 0;
}

void computerPlaysRandom(int *cRow, int *cCol, int uRow, int uCol)
{

  int randomNumber, randomNumber2;

  //Program generates a random number to choose the computer's next move. If 0, computer will shoose a spot in the same row
  //as the user. If 1, computer will choose a spot in the same column as the user. If 2, the same diagonals are chosen.

  //If the computer will choose the same row as the user
  randomNumber = rand() % 3;

  do{
  if(randomNumber == 0)
  {
    *cRow = uRow;
    *cCol = rand() % 3;
  }

  //If the computer will choose the same column as the user
  else if(randomNumber == 1)
  {
    *cCol = uCol;
    *cRow = rand() % 3;
  }

  //If the computer will choose the same diagonal
  else if(randomNumber == 2)
  {
    if((uRow == 0) && (uCol == 0))
    {
      randomNumber2 = rand() % 2;
      switch(randomNumber2)
      {
        case 0: *cRow = 2;
                *cCol = 2;
                break;
        case 1: *cRow = 1;
                *cCol = 1;
                break;
      }
    }
    else if((uRow == 0) && (uCol == 2))
    {
      randomNumber2 = rand() % 2;
      switch(randomNumber2)
      {
        case 0: *cRow = 1;
                *cCol = 1;
                break;
        case 1: *cRow = 2;
                *cCol = 0;
                break;
      }
    }
    else if((uRow == 2) && (uCol == 0))
    {
      randomNumber2 = rand() % 2;
      switch(randomNumber2)
      {
        case 0: *cRow = 1;
                *cCol = 1;
                break;
        case 1: *cRow = 0;
                *cCol = 2;
                break;
      }
    }
    else if((uRow == 2) && (uCol == 2))
    {
      randomNumber2 = rand() % 2;
      switch(randomNumber2)
      {
        case 0: *cRow = 1;
                *cCol = 1;
                break;
        case 1: *cRow = 0;
                *cCol = 0;
                break;
      }
    }
    else if((uRow == 1) && (uCol == 1))
    {
      randomNumber2 = rand() % 2;
      switch(randomNumber2)
      {
        case 0: *cRow = 0;
                *cCol = 0;
                break;
        case 1: *cRow = 0;
                *cCol = 2;
                break;
        case 2: *cRow = 2;
                *cCol = 0;
                break;
        case 3: *cRow = 2;
                *cCol = 2;
                break;
      }
    }
  }
  }while(*cRow == uRow && * cCol == uCol);

  return;
}

void sumAllDimensions(char board[N][N], int sumR[N], int sumC[N], int *sumLD, int *sumRD)
{

  int i;
  int j;

  //Initializing the sum of rows and columns arrays to zero

  for(i = 0; i < N; i++)
  {
    sumR[i] = 0;
    sumC[i] = 0;
  }

  //Initializing the sum of left and right diagonals

  *sumLD = 0;
  *sumRD = 0;

  //Calculating the sum of the rows

  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      if(board[i][j] == 'X')
      {
        sumR[i] = sumR[i] + 1;
      }
      else if(board[i][j] == 'O')
      {
        sumR[i] = sumR[i] + 4;
      }
    }
  }


  //Calculating the sum of the columns

  for(j = 0; j < N; j++)
  {
    for(i = 0; i < N; i++)
    {
      if(board[i][j] == 'X')
      {
        sumC[j] = sumC[j] + 1;
      }
      else if(board[i][j] == 'O')
      {
        sumC[j] = sumC[j] + 4;
      }
    }
  }


  //Calculating the sum of the left diagonals

  if(board[0][0] == 'X')
  {
    *sumLD = *sumLD + 1;
  }
  else if(board[0][0] == 'O')
  {
    *sumLD = *sumLD + 4;
  }

  if(board[1][1] == 'X')
  {
    *sumLD = *sumLD + 1;
  }
  else if(board[1][1] == 'O')
  {
    *sumLD = *sumLD + 4;
  }

  if(board[2][2] == 'X')
  {
    *sumLD = *sumLD + 1;
  }
  else if(board[2][2] == 'O')
  {
    *sumLD = *sumLD + 4;
  }


  //Calculating the sum of the right diagonals

  if(board[0][2] == 'X')
  {
    *sumRD = *sumRD + 1;
  }
  else if(board[0][2] == 'O')
  {
    *sumRD = *sumRD + 4;
  }

  if(board[1][1] == 'X')
  {
    *sumRD = *sumRD + 1;
  }
  else if(board[1][1] == 'O')
  {
    *sumRD = *sumRD + 4;
  }

  if(board[2][0] == 'X')
  {
    *sumRD = *sumRD + 1;
  }
  else if(board[2][0] == 'O')
  {
    *sumRD = *sumRD + 4;
  }

  return;
}

int memberOf(int aNum, int someArray[N])
{

  int i;

  //This function checks to see whether a number (usually a sum) is present in an element of an array (sumR or sumC).
  //If yes, 1 is returned. If no, 0 is returned.

  for(i = 0; i < N; i ++)
  {
    if(aNum == someArray[i])
    {
      return 1;
    }
  }

  return 0;
}


int computerPlaysToBlock(char board[N][N], int * cRow, int * cCol)
{

  int i = 0;
  int j = 0;
  int sumR[N], sumC[N];
  int sumLD, sumRD;
  int sumRDColIndex;

  //This is a function call for sumAllDimensions to check if the computer can win.

  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);


  //Checking rows for a sum of 2

  for(i = 0; i < N; i++)
  {
    if(sumR[i] == 2)
    {
      for(j = 0; j < N; j++)
      {
        if(board[i][j] == '?')
        {
          *cRow = i;
          *cCol = j;
          return 1;
        }
      }
    }
  }


  //Checking columns for a sum of 2

  for(j = 0; j < N; j++)
  {
    if(sumC[i] == 2)
    {
      for(i = 0; i < N; i++)
      {
        if(board[i][j] == '?')
        {
          *cRow = i;
          *cCol = j;
          return 1;
        }
      }
    }
  }


  //Checking left diagonal for a sum of 2

  if(sumLD == 2)
  {
    for(i = 0; i < N; i ++)
    {
      if(board[i][i] == '?')
      {
        *cRow = i;
        *cCol = i;
        return 1;
      }
    }
  }


  //Checking right diagonal for a sum of 2

  if(sumRD == 2)
  {
    sumRDColIndex = 2;
    for(i = 0; i < N; i ++)
    {
      if(board[i][sumRDColIndex] == '?')
      {
        *cRow = i;
        *cCol = sumRDColIndex;
        return 1;
      }
      sumRDColIndex --;
    }
  }

  return 0;

}

