//**********************************************************************
//*                                                                    *
//* Program Name: Gobble 'Em Up                                        *
//* Author:       Lacy Tesdall                                         *
//* Date Written: July 14, 2018                                        *
//*                                                                    *
//**********************************************************************

//**********************************************************************
//*                                                                    *
//* This program allows the user to play the classic game of           *
//* Tic-Tac-Toe but with an added twist. Different sized playing       *
//* pieces are used to add an extra dimension on winning by being      *
//* placed on the board, or by gobbling the other player's pieces.     *
//*                                                                    *
//**********************************************************************
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
class computer;
class player;

//**********************************************************************
//*                         Symbolic Constants                         *
//**********************************************************************
#define ROW         5       // Max row size of the playing board
#define COL         8       // Max columnn size of the playing board
#define PLAYER      88      // Player's symbol X
#define COMPUTER    79      // Computer's symbol O
#define USER_WINS   1       // Value for the user win
#define COMP_WINS   2       // Value for the computer win
#define CAT         3       // Value for no win
#define SMALL_PIECE 'S'     // Small playing piece 'S'
#define MED_PIECE   'M'     // Medium playing piece 'M'
#define LARGE_PIECE 'L'     // Large playing piece 'L'

//**********************************************************************
//*                         Class Definitions                          *
//**********************************************************************
// The playing board
class board
{
   char playingBoard[5][8] = { '1', ' ', '|', '2', ' ', '|', '3', ' ',
                               '-', '-', '+', '-', '-', '+', '-', '-',
                               '4', ' ', '|', '5', ' ', '|', '6', ' ',
                               '-', '-', '+', '-', '-', '+', '-', '-',
                               '7', ' ', '|', '8', ' ', '|', '9', ' ',
                             };
public:
   // Display the playing board
   void show_board();
   // Check to see if the user won
   int checkUserWinner();
   // Check to see if the computer won
   int checkCompWinner();
   // Check to see if there's a cat
   int checkCat();
   // Computer's turn
   friend void computerTurn(board *game, computer *comp);
   // Player's turn
   friend void playerTurn  (board *game, player *play);
};

// Computer's play and pieces
class computer
{
   int small  = 2, // Small playing pieces allowed 
       medium = 2, // Medium playing pieces allowed
       large  = 2; // Large playing pieces allowed
public:
   // Computer's turn
   friend void computerTurn(board *game, computer *comp);
};

// Player's play and pieces
class player
{
   int small  = 2, // Small playing pieces allowed
       medium = 2, // Medium playing pieces allowed
       large  = 2; // Large playing pieces allowed
public:
   // Player's turn
   friend void playerTurn(board *game, player *play);
   char checkPiece();
};

//**********************************************************************
//*                   Display the playing board                        *
//**********************************************************************
void board::show_board()
{
   int i,
       v;

   for (i = 0; i < ROW; i++)
   {
      cout << "\n";
      for (v = 0; v < COL; v++)
         cout << playingBoard[i][v];
   }
   cout << "\n\n";
   return;
}

//**********************************************************************
//*                   Check to see if the user won                     *
//**********************************************************************
int board::checkUserWinner()
{
   int result = 0;

   // Horizontal wins
   if ((playingBoard[0][0] == PLAYER) && (playingBoard[0][3] == PLAYER) && (playingBoard[0][6] == PLAYER))
      result = USER_WINS;
   else if ((playingBoard[2][0] == PLAYER) && (playingBoard[2][3] == PLAYER) && (playingBoard[2][6] == PLAYER))
      result = USER_WINS;
   else if ((playingBoard[4][0] == PLAYER) && (playingBoard[4][3] == PLAYER) && (playingBoard[4][6] == PLAYER))
      result = USER_WINS;

   // Vertical wins
   else if ((playingBoard[0][0] == PLAYER) && (playingBoard[2][0] == PLAYER) && (playingBoard[4][0] == PLAYER))
      result = USER_WINS;
   else if ((playingBoard[0][3] == PLAYER) && (playingBoard[2][3] == PLAYER) && (playingBoard[4][3] == PLAYER))
      result = USER_WINS;
   else if ((playingBoard[0][6] == PLAYER) && (playingBoard[2][6] == PLAYER) && (playingBoard[4][6] == PLAYER))
      result = USER_WINS;

   // Diagonal wins
   else if ((playingBoard[0][0] == PLAYER) && (playingBoard[2][3] == PLAYER) && (playingBoard[4][6] == PLAYER))
      result = USER_WINS;
   else if ((playingBoard[0][6] == PLAYER) && (playingBoard[2][3] == PLAYER) && (playingBoard[4][0] == PLAYER))
      result = USER_WINS;

   return result;
}

//**********************************************************************
//*                 Check to see if the computer won                   *
//**********************************************************************
int board::checkCompWinner()
{
   int result = 0;

   // Horizontal wins
   if ((playingBoard[0][0] == COMPUTER) && (playingBoard[0][3] == COMPUTER) && (playingBoard[0][6] == COMPUTER))
      result = COMP_WINS;
   else if ((playingBoard[2][0] == COMPUTER) && (playingBoard[2][3] == COMPUTER) && (playingBoard[2][6] == COMPUTER))
      result = COMP_WINS;
   else if ((playingBoard[4][0] == COMPUTER) && (playingBoard[4][3] == COMPUTER) && (playingBoard[4][6] == COMPUTER))
      result = COMP_WINS;

   // Vertical wins
   else if ((playingBoard[0][0] == COMPUTER) && (playingBoard[2][0] == COMPUTER) && (playingBoard[4][0] == COMPUTER))
      result = COMP_WINS;
   else if ((playingBoard[0][3] == COMPUTER) && (playingBoard[2][3] == COMPUTER) && (playingBoard[4][3] == COMPUTER))
      result = COMP_WINS;
   else if ((playingBoard[0][6] == COMPUTER) && (playingBoard[2][6] == COMPUTER) && (playingBoard[4][6] == COMPUTER))
      result = COMP_WINS;

   // Diagonal wins
   else if ((playingBoard[0][0] == COMPUTER) && (playingBoard[2][3] == COMPUTER) && (playingBoard[4][6] == COMPUTER))
      result = COMP_WINS;
   else if ((playingBoard[0][6] == COMPUTER) && (playingBoard[2][3] == COMPUTER) && (playingBoard[4][0] == COMPUTER))
      result = COMP_WINS;

   return result;
}

//**********************************************************************
//*                  Check to see if there's a cat                     *
//**********************************************************************
int board::checkCat()
{
   int result = CAT,
       i,
       v;

   for (i = 0; i < ROW; i += 2)
   {
      for (v = 0; v < COL; v += 3)
      {
         if ((playingBoard[i][v] != PLAYER) && (playingBoard[i][v] != COMPUTER))
            result = 0;
      }
   }

   return result;
}

//**********************************************************************
//*                         Computer's turn                            *
//**********************************************************************
void computerTurn(board *game, computer *comp)
{
   int invalid = 1,
       random;

   cout << "\n\nComputer's Turn:";
   cout <<   "\n----------------";
   cout <<   "\n";
   do
   {
      random = ((rand() % 9) + 1);
      switch (random)
      {
      case 1:
         if (game->playingBoard[0][1] != LARGE_PIECE)
         {
            game->playingBoard[0][0] = COMPUTER;
            if (game->playingBoard[0][1] == ' ')
               game->playingBoard[0][1] = SMALL_PIECE;
            else if (game->playingBoard[0][1] == SMALL_PIECE)
               game->playingBoard[0][1] = MED_PIECE;
            else
               game->playingBoard[0][1] = LARGE_PIECE;

            invalid = 0;
         }
         break;
      case 2:
         if (game->playingBoard[0][4] != LARGE_PIECE)
         {
            game->playingBoard[0][3] = COMPUTER;
            if (game->playingBoard[0][4] == ' ')
               game->playingBoard[0][4] = SMALL_PIECE;
            else if (game->playingBoard[0][4] == SMALL_PIECE)
               game->playingBoard[0][4] = MED_PIECE;
            else
               game->playingBoard[0][4] = LARGE_PIECE;

            invalid = 0;
         }
         break;
      case 3:
         if (game->playingBoard[0][7] != LARGE_PIECE)
         {
            game->playingBoard[0][6] = COMPUTER;
            if (game->playingBoard[0][7] == ' ')
               game->playingBoard[0][7] = SMALL_PIECE;
            else if (game->playingBoard[0][7] == SMALL_PIECE)
               game->playingBoard[0][7] = MED_PIECE;
            else
               game->playingBoard[0][7] = LARGE_PIECE;

            invalid = 0;
         }
         break;
      case 4:
         if (game->playingBoard[2][1] != LARGE_PIECE)
         {
            game->playingBoard[2][0] = COMPUTER;
            if (game->playingBoard[2][1] == ' ')
               game->playingBoard[2][1] = SMALL_PIECE;
            else if (game->playingBoard[2][1] == SMALL_PIECE)
               game->playingBoard[2][1] = MED_PIECE;
            else
               game->playingBoard[2][1] = LARGE_PIECE;

            invalid = 0;
         }
         break;
      case 5:
         if (game->playingBoard[2][4] != LARGE_PIECE)
         {
            game->playingBoard[2][3] = COMPUTER;
            if (game->playingBoard[2][4] == ' ')
               game->playingBoard[2][4] = SMALL_PIECE;
            else if (game->playingBoard[2][4] == SMALL_PIECE)
               game->playingBoard[2][4] = MED_PIECE;
            else
               game->playingBoard[2][4] = LARGE_PIECE;

            invalid = 0;
         }
         break;
      case 6:
         if (game->playingBoard[2][7] != LARGE_PIECE)
         {
            game->playingBoard[2][6] = COMPUTER;
            if (game->playingBoard[2][7] == ' ')
               game->playingBoard[2][7] = SMALL_PIECE;
            else if (game->playingBoard[2][7] == SMALL_PIECE)
               game->playingBoard[2][7] = MED_PIECE;
            else
               game->playingBoard[2][7] = LARGE_PIECE;

            invalid = 0;
         }
         break;
      case 7:
         if (game->playingBoard[4][1] != LARGE_PIECE)
         {
            game->playingBoard[4][0] = COMPUTER;
            if (game->playingBoard[4][1] == ' ')
               game->playingBoard[4][1] = SMALL_PIECE;
            else if (game->playingBoard[4][1] == SMALL_PIECE)
               game->playingBoard[4][1] = MED_PIECE;
            else
               game->playingBoard[4][1] = LARGE_PIECE;

            invalid = 0;
         }
         break;
      case 8:
         if (game->playingBoard[4][4] != LARGE_PIECE)
         {
            game->playingBoard[4][3] = COMPUTER;
            if (game->playingBoard[4][4] == ' ')
               game->playingBoard[4][4] = SMALL_PIECE;
            else if (game->playingBoard[4][4] == SMALL_PIECE)
               game->playingBoard[4][4] = MED_PIECE;
            else
               game->playingBoard[4][4] = LARGE_PIECE;

            invalid = 0;
         }
         break;
      case 9:
         if (game->playingBoard[4][7] != LARGE_PIECE)
         {
            game->playingBoard[4][6] = COMPUTER;
            if (game->playingBoard[4][7] == ' ')
               game->playingBoard[4][7] = SMALL_PIECE;
            else if (game->playingBoard[4][7] == SMALL_PIECE)
               game->playingBoard[4][7] = MED_PIECE;
            else
               game->playingBoard[4][7] = LARGE_PIECE;

            invalid = 0;
         }
         break;
      default:
         cout << "\nInvalid play. I'm sorry, you've lost";
         exit(1);
         break;
      }
   } while (invalid == 1);

   return;
}

//**********************************************************************
//*             Check the validity the player's location               *
//**********************************************************************
char player::checkPiece()
{
   char piece;

   cout << "Pick the piece you'd like to play: ";
   cin  >> piece;
   piece = toupper(piece);

   while ((piece != SMALL_PIECE) && (piece != MED_PIECE) && (piece != LARGE_PIECE))
   {
      cout << "\nInvalid input. Please try again: ";
      cin >> piece;
      piece = toupper(piece);
   }
   
   return piece;
}

//**********************************************************************
//*                         Player's Turn                              *
//**********************************************************************
void playerTurn(board *game, player *play)
{
   int  location,
        invalid = 1,
        valid   = 0;
   char piece;

   cout << "\nYour move.";
   cout << "\nSelect your location to play: ";
   cin  >> location;
   while ((location < 1) || (location > 9))
   {
      cout << "\nNot a valid selection. Please try again: ";
      cin  >> location;
   }

   do
   {
      switch (location)
      {
         case 1:
            if (game->playingBoard[0][1] != LARGE_PIECE)
            {
               piece = play->checkPiece();
               do
               {
                  switch (piece)
                  {
                     case SMALL_PIECE:
                        if (play->small > 0)
                        {
                           game->playingBoard[0][1] = SMALL_PIECE;
                           play->small--;
                           valid = 1;
                        }
                        else
                        {
                           cout << "\nYou have no more small pieces.";
                           piece = play->checkPiece();
                        }
                        break;
                     case MED_PIECE:
                        if (play->medium > 0)
                        {
                           game->playingBoard[0][1] = MED_PIECE;
                           play->medium--;
                           valid = 1;
                        }
                        else
                        {
                           cout << "\nYou have no more medium pieces.";
                           piece = play->checkPiece();
                        }
                        break;
                     case LARGE_PIECE:
                        if (play->large > 0)
                        {
                           game->playingBoard[0][1] = LARGE_PIECE;
                           play->large--;
                           valid = 1;
                        }
                        else
                        {
                           cout << "\nYou have no more large pieces.";
                           piece = play->checkPiece();
                        }
                        break;
                     default:
                        cout << "\nError occurred. Program is aborting";
                        exit(1);
                        break;
                  }
               } while (valid == 0);
               game->playingBoard[0][0] = PLAYER;
               invalid = 0;
            }
            break;
         case 2:
            if (game->playingBoard[0][4] != LARGE_PIECE)
            {
               piece = play->checkPiece();
               do
               {
                  switch (piece)
                  {
                  case SMALL_PIECE:
                     if (play->small > 0)
                     {
                        game->playingBoard[0][4] = SMALL_PIECE;
                        play->small--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more small pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case MED_PIECE:
                     if (play->medium > 0)
                     {
                        game->playingBoard[0][4] = MED_PIECE;
                        play->medium--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more medium pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case LARGE_PIECE:
                     if (play->large > 0)
                     {
                        game->playingBoard[0][4] = LARGE_PIECE;
                        play->large--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more large pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  default:
                     cout << "\nError occurred. Program is aborting";
                     exit(2);
                     break;
                  }
               } while (valid == 0);
               game->playingBoard[0][3] = PLAYER;
               invalid = 0;
            }
            break;
         case 3:
            if (game->playingBoard[0][7] != LARGE_PIECE)
            {
               piece = play->checkPiece();
               do
               {
                  switch (piece)
                  {
                  case SMALL_PIECE:
                     if (play->small > 0)
                     {
                        game->playingBoard[0][7] = SMALL_PIECE;
                        play->small--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more small pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case MED_PIECE:
                     if (play->medium > 0)
                     {
                        game->playingBoard[0][7] = MED_PIECE;
                        play->medium--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more medium pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case LARGE_PIECE:
                     if (play->large > 0)
                     {
                        game->playingBoard[0][7] = LARGE_PIECE;
                        play->large--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more large pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  default:
                     cout << "\nError occurred. Program is aborting";
                     exit(3);
                     break;
                  }
               } while (valid == 0);
               game->playingBoard[0][6] = PLAYER;
               invalid = 0;
            }
            break;
         case 4:
            if (game->playingBoard[2][1] != LARGE_PIECE)
            {
               piece = play->checkPiece();
               do
               {
                  switch (piece)
                  {
                  case SMALL_PIECE:
                     if (play->small > 0)
                     {
                        game->playingBoard[2][1] = SMALL_PIECE;
                        play->small--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more small pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case MED_PIECE:
                     if (play->medium > 0)
                     {
                        game->playingBoard[2][1] = MED_PIECE;
                        play->medium--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more medium pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case LARGE_PIECE:
                     if (play->large > 0)
                     {
                        game->playingBoard[2][1] = LARGE_PIECE;
                        play->large--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more large pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  default:
                     cout << "\nError occurred. Program is aborting.";
                     exit(4);
                     break;
                  }
               } while (valid == 0);
               game->playingBoard[2][0] = PLAYER;
               invalid = 0;
            }
            break;
         case 5:
            if (game->playingBoard[2][4] != LARGE_PIECE)
            {
               piece = play->checkPiece();
               do
               {
                  switch (piece)
                  {
                  case SMALL_PIECE:
                     if (play->small > 0)
                     {
                        game->playingBoard[2][4] = SMALL_PIECE;
                        play->small--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more small pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case MED_PIECE:
                     if (play->medium > 0)
                     {
                        game->playingBoard[2][4] = MED_PIECE;
                        play->medium--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more medium pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case LARGE_PIECE:
                     if (play->large > 0)
                     {
                        game->playingBoard[2][4] = LARGE_PIECE;
                        play->large--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more large pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  default:
                     cout << "\nError occurred. Program is aborting";
                     exit(5);
                     break;
                  }
               } while (valid == 0);
               game->playingBoard[2][3] = PLAYER;
               invalid = 0;
            }
            break;
         case 6:
            if (game->playingBoard[2][7] != LARGE_PIECE)
            {
               piece = play->checkPiece();
               do
               {
                  switch (piece)
                  {
                  case SMALL_PIECE:
                     if (play->small > 0)
                     {
                        game->playingBoard[2][7] = SMALL_PIECE;
                        play->small--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more small pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case MED_PIECE:
                     if (play->medium > 0)
                     {
                        game->playingBoard[2][7] = MED_PIECE;
                        play->medium--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more medium pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case LARGE_PIECE:
                     if (play->large > 0)
                     {
                        game->playingBoard[2][7] = LARGE_PIECE;
                        play->large--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more large pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  default:
                     cout << "\nError occured. Program is aborting.";
                     exit(6);
                     break;
                  }
               } while (valid == 0);
               game->playingBoard[2][6] = PLAYER;
               invalid = 0;
            }
            break;
         case 7:
            if (game->playingBoard[4][1] != LARGE_PIECE)
            {
               piece = play->checkPiece();
               do
               {
                  switch (piece)
                  {
                  case SMALL_PIECE:
                     if (play->small > 0)
                     {
                        game->playingBoard[4][1] = SMALL_PIECE;
                        play->small--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more small pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case MED_PIECE:
                     if (play->medium > 0)
                     {
                        game->playingBoard[4][1] = MED_PIECE;
                        play->medium--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more medium pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case LARGE_PIECE:
                     if (play->large > 0)
                     {
                        game->playingBoard[4][1] = LARGE_PIECE;
                        play->large--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more large pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  default:
                     cout << "\nError occurred. Program is aborting.";
                     exit(7);
                     break;
                  }
               } while (valid == 0);
               game->playingBoard[4][0] = PLAYER;
               invalid = 0;
            }
            break;
         case 8:
            if (game->playingBoard[4][4] != LARGE_PIECE)
            {
               piece = play->checkPiece();
               do
               {
                  switch (piece)
                  {
                  case SMALL_PIECE:
                     if (play->small > 0)
                     {
                        game->playingBoard[4][4] = SMALL_PIECE;
                        play->small--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more small pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case MED_PIECE:
                     if (play->medium > 0)
                     {
                        game->playingBoard[4][4] = MED_PIECE;
                        play->medium--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more medium pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case LARGE_PIECE:
                     if (play->large > 0)
                     {
                        game->playingBoard[4][4] = LARGE_PIECE;
                        play->large--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more large pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  default:
                     cout << "\nError Occurred. Program aborting.";
                     exit(8);
                     break;
                  }
               } while (valid == 0);
               game->playingBoard[4][3] = PLAYER;
               invalid = 0;
            }
            break;
         case 9:
            if (game->playingBoard[4][7] != LARGE_PIECE)
            {
               piece = play->checkPiece();
               do
               {
                  switch (piece)
                  {
                  case SMALL_PIECE:
                     if (play->small > 0)
                     {
                        game->playingBoard[4][7] = SMALL_PIECE;
                        play->small--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more small pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case MED_PIECE:
                     if (play->medium > 0)
                     {
                        game->playingBoard[4][7] = MED_PIECE;
                        play->medium--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more medium pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  case LARGE_PIECE:
                     if (play->large > 0)
                     {
                        game->playingBoard[4][7] = LARGE_PIECE;
                        play->large--;
                        valid = 1;
                     }
                     else
                     {
                        cout << "\nYou have no more large pieces.";
                        piece = play->checkPiece();
                     }
                     break;
                  default:
                     cout << "\nError occurred. Program is aborting.";
                     exit(9);
                     break;
                  }
               } while (valid == 0);
               game->playingBoard[4][6] = PLAYER;
               invalid = 0;
            }
            break;
         default:
            cout << "\nInvalid play. I'm sorry, you've lost";
            exit(1);
            break;
      }
      if (invalid == 1)
      {
         cout << "\nInvalid move.";
         cout << "\nPlease pick your location.";
         cin >> location;
      }
   } while (invalid == 1);
   return;
}

//**********************************************************************
//*                         Function Prototypes                        *
//**********************************************************************
void print_heading();
// Print the program heading and instructions
void get_player_name(char *playerName);
// Get the player's name

//**********************************************************************
//*                           Main Function                            *
//**********************************************************************
int main()
{
   char     playerName[20]; // Player's name
   int      winner = 0;     // Keep track of whether someone wins or not
   board    game;           // Playing board game
   computer compTurn;       // Computer turn
   player   playTurn;       // Player turn

   // Randomizer for the computer's turn
   srand((unsigned int) time(NULL));

   // Print the program heading and instructions
   print_heading();

   // Get the player's name
   get_player_name(playerName);

   cout << "\nHere's the playing board:";
   while (winner == 0)
   {
      // Show the playing board
      game.show_board();

      // Player's turn
      if ((game.checkUserWinner() == 0) && (game.checkCompWinner() == 0) && (game.checkCat() == 0))
         playerTurn(&game, &playTurn);
      else
         winner = 1;

      // Show the playing board
      game.show_board();

      // Computer's turn
      if ((game.checkUserWinner() == 0) && (game.checkCompWinner() == 0) && (game.checkCat() == 0))
         computerTurn(&game, &compTurn);
      else
         winner = 1;
   }

   // Check to see who won
   if (game.checkUserWinner() == USER_WINS)
      cout << "\n" << playerName << " has gobbled up Toby. Congrats!";
   else if (game.checkCompWinner() == COMP_WINS)
      cout << "\nLooks like you've been gobbled up... Toby wins!";
   else
      cout << "\nHm, it seems that both of us have escaped gobilization.";

   // Say goodbye and terminate the program
   cout << "\n\n\nThanks for playing.";
   cout << "\n\n\n\n\n\n";
   return 0;
}

//**********************************************************************
//*           Print the program heading and instructions               *
//**********************************************************************
void print_heading()
{
   cout << "\n\n\n\n\n\n=======================================================";
   cout << "\n  Hello! My name is Toby, and welcome to the classic";
   cout << "\n  game of Tic-Tac-Toe with an added twist. The rules";
   cout << "\n  are simple: be the first to get three in row.";
   cout << "\n  But did I mention that you could get eaten?";
   cout << "\n  Here are the rules:";
   cout << "\n  -------------------";
   cout << "\n  Each player has 6 pieces: 2 small, 2 medium, 2 large.";
   cout << "\n  Any piece can be played on an empty space; however,";
   cout << "\n  a medium piece can be played on top of a small piece,";
   cout << "\n  and a large piece can be played on top of either a";
   cout << "\n  small or medium sized piece.";
   cout << "\n  First, choose a location. Any location as long as it's available.";
   cout << "\n  Choose the size piece to play.";
   cout << "\n  Be the first to get 3 in a row.";
   cout << "\n\n  Now let's play!";
   cout << "\n=======================================================";
   return;
}

//**********************************************************************
//*                     Get the player's name                          *
//**********************************************************************
void get_player_name(char *playerName)
{
   char answer[2];

   do
   {
      cout << "\nPlease enter your name: ";
      cin >> playerName;
      cout << "\nIs your name " << playerName << "? Enter 'Y' or 'N'";
      cin >> answer;
      *answer = toupper(*answer);
      while ((*answer != 'Y') && (*answer != 'N'))
      {
         cout << "\nInvalid entry. Please enter 'Y' or 'N'";
         cin >> answer;
         *answer = toupper(*answer);
      }
   } while (*answer == 'N');

   return;
}