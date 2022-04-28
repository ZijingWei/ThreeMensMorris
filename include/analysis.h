#pragma once
#include "../include/node.h"
#include <iostream>
#include <utility>
#include <vector>
#include <set>

using namespace std;

class StateSpace {

public:
    static const int kOne = 1;
    static const int kTwo= 2;
    static const int kZero = 0;
    static const int kBoardSize = 3;
    
    StateSpace();

    /**
     * A helper function that convert string to int
     * @param str 
     * @return int number
     */
    static int StringToInt(string str);
    
    /**
     * A helper function that convert int to string
     * @param value
     * @return the string
     */
    static std::string IntToString(int value);

    /**
     * A helper function that convert int to string with exactly 9 digits, 001002001 instead of 1002001
     * @param value
     * @return the string
     */
    static std::string IntToString9(int value);
    
    /**
     * A helper function that convert decimal number to ternary number
     * @param n 
     * @return ternary
     */
    static int DecToTer(int n);
    
    /**
     * A helper function that convert ternary number to decimal number
     * @param s 
     * @return decimal
     */
    static int TerToDec(int s);
    
    /**
     * Get the 2-d board of the game
     * @param code 
     * @return 2-d board
     */
    static int** GetBoard(int code);
    
    /**
     * delete the board
     * @param a 
     */
    static void DeleteBroad(int** a);
    
    /**
     * Draw board in console
     * @param code 
     */
    static void DrawBoard(int code);
    
    /**
     * convert int point to a char, 1 to 'X', 2 to 'O', 0 to '_'
     * @param num 
     * @return string with one char
     */
    static string DrawPoint(int num);

    /**
     * Check if the game is ended
     * @param code 
     * @return bool
     */
    static int CheckEndGame(int code);
    
    /**
     * Check if it's on the move phase
     * @param code 
     * @return 
     */
    static bool IsMovePhase(int code);
    /**
     * Get all valid move nodes in a board
     * @param code the board code
     * @param color color of the player 
     * @return 
     */
    static std::set<pair<int, int> > * GetAllValidMoveNode(int code, int color);
    
    /**
     * Check if the point we want to add is in bound
     * @param x 
     * @param y 
     * @return bool
     */
    static bool IsInTheBound(int x, int y);
    
    /**
     * Check the position is not out of bound and is empty
     * @param code 
     * @param x 
     * @param y 
     * @return bool
     */
    static bool IsPositionValid(int code, int x, int y);
    
    /**
     * Get all valid next Move position for a state
     * @param code 
     * @param x 
     * @param y 
     * @return a set with all valid move position
     */
    static std::set<pair<int, int> > * GetAllValidNextMove(int code, int x, int y);
    
    /**
     * Get all valid next Add position for a state
     * @param code 
     * @param x 
     * @param y 
     * @return a set with all valid add position
     */
    static std::set<pair<int, int> >* GetAllEmptyPosition(int code);
    
    /**
     * Add One step from an add state
     * @param code 
     * @param x 
     * @param y 
     * @param color 
     * @return a new state
     */
    static int AddOneStepADD(int code, int x, int y, int color);
    
    /**
     * Add One step from a move state
     * @param code 
     * @param from 
     * @param to 
     * @return a new state
     */
    static int AddOneStepMOVE(int code, pair<int, int> from, pair<int, int> to);
    
    /**
     * Get all next steps from a state
     * @param code 
     * @param color 
     * @return set of steps
     */
    static std::set<int> * GetNextSteps(int code, int color);

    /**
     * Check if the color is the move color
     * @param code
     * @param x
     * @param y
     * @param nextColor
     * @return bool
     */
    static bool CheckMoveColor(int code, int x, int y, int nextColor);
    
    /**
     * Get the best next move
     * @param code
     * @param color
     * @return best board for the next step
     */
    static int GetBestMove(int code, int color);

    /**
     * The minimax algorithm
     * @param state a pair of code and score
     * @param mycolor color
     * @param depth pepth
     * @param alpha the alpha score
     * @param beta the beta score
     * @return the score of current state
     */
    static int Minimax(pair<int, int> state, int mycolor, int depth,int alpha,int beta);

    /**
     * Check if the this state plus one ADD step would led to win
     * @param code
     * @param color
     * @return if it is, then return the coor the would led to win, if it is not, return pair (-1,-1)
     */
    static pair<int, int> IsAddCritical(int code, int color);
    
private:
    
    
}; 