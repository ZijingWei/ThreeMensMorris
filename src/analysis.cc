#include <../include/analysis.h>
#include <utility>
#include <set>
#include <map>
#include <unordered_set>
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include<iomanip>
using namespace std;

int** StateSpace::GetBoard(int code) { //DELETE after use
    //decimal to ternary number 
    //and then ternary to board
    int** a = new int*[kBoardSize];
    for (int i = 0; i < kBoardSize; ++i) {
        a[i] = new int[kBoardSize];
    }
    int one = DecToTer(code);
    string code_str = IntToString9(one);
    for (int j = 0; j < kBoardSize; j++) {
        for (int k = 0; k < kBoardSize; k++) {
            a[j][k] = StringToInt(code_str.substr(0,kOne));
            code_str = code_str.substr(kOne);
        }
    }
    return a;
}

void StateSpace::DrawBoard(int code) {
    int** a = GetBoard(code);
    cout <<"1)  " << DrawPoint(a[0][0]) << " " << DrawPoint(a[0][1]) << " "<< DrawPoint(a[0][2]) << " " << endl;
    cout << "2)  "<<DrawPoint(a[1][0]) << " " <<DrawPoint(a[1][1]) << " "<< DrawPoint(a[1][2]) << " " << endl;
    cout << "3)  "<<DrawPoint(a[2][0]) << " " << DrawPoint(a[2][1]) << " "<<DrawPoint( a[2][2]) << " " << endl;
    DeleteBroad(a);
}

string StateSpace::DrawPoint(int num) {
    if (num == 1) {
        return "O";
    } else if (num == 0) {
        return "_";
    } else {
        return "X";
    }
}

int StateSpace::StringToInt(string str) {
    int num;
    stringstream ss;
    ss << str;
    ss >> num;
    return num;
}

std::string StateSpace::IntToString(int value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

std::string StateSpace::IntToString9(int value) { //This ensures that I have 9 digit. 001002001, instead of 1002001
    std::ostringstream os;
    os << setw(9) << setfill('0') << value << setw(9) << setfill('0');
    return os.str();
}

int StateSpace::DecToTer(int n) {
    //std::string str_ret;
    if (n==0) return 0;
    if (n<0) n = 0 - n;
    int ret=0;
    int mul=1;
    while(n>0)
    {
        int digitofternary=n%kBoardSize;
        n/=kBoardSize;
        ret += mul * digitofternary;
        mul *= 10;

    }
    return ret;
}

int StateSpace::TerToDec(int s) {
    int multiplier=1, result=0;
    if (s == 0) {
        return 0;
    }
    if (s<0) s = 0 - s;
    while(s>0)
    {
        result=result+s%10*multiplier;
        multiplier=multiplier*kBoardSize;
        s=s/10;
    }
    return result;
}



void StateSpace::DeleteBroad(int** a) {
    for (int i = 0; i < kBoardSize; i++) {
        delete[] a[i];
    }
    delete[] a;
}

bool StateSpace::IsInTheBound(int x_coor, int y_coor) {
    if (x_coor < kZero || x_coor > kTwo ||y_coor < kZero || y_coor > kTwo) {
        return false;
    }
    return true;
}

bool StateSpace::CheckMoveColor(int code, int x, int y, int nextColor) {
    int** a = GetBoard(code);
    if (a[x][y] == nextColor) {
        DeleteBroad(a);
        return true;
    } else {
        DeleteBroad(a);
        return false;
    }
    
    
}

std::set<pair<int, int> > * StateSpace::GetAllValidMoveNode(int code, int color) { //DELETE After use
    set<pair<int, int> >* theSet = new set<pair<int, int> >;
    int** a = StateSpace::GetBoard(code);
    for (int i = 0; i < kBoardSize; i++) {
        for (int j = 0; j < kBoardSize; j++) {
            if (a[i][j] == color) {
                theSet->insert(make_pair(i, j));
            }
        }
    }
    StateSpace::DeleteBroad(a);
    return theSet;
}

std::set<pair<int, int> >* StateSpace::GetAllEmptyPosition(int code) { //DELETE After use
    set<pair<int, int> > * emptyPos = new set<pair<int, int> >;
    int** a = GetBoard(code);
    for (int i = 0; i < kBoardSize; i++) {
        for (int j = 0; j < kBoardSize; j++) {
            if (a[i][j] == kZero) {
                emptyPos->insert(make_pair(i, j));
            }
        }
    }
    DeleteBroad(a);
    return emptyPos;
}

bool StateSpace::IsMovePhase(int code) {
    int count = 0;
    int ternary_code = StateSpace::DecToTer(code);
    string code_str = StateSpace::IntToString9(ternary_code);
    for (std::string::size_type i = 0; i < code_str.size(); ++i) {
        if (code_str[i] == '0') {
            count++;
        }
    }
    if (count == kBoardSize) {
        return true;
    } else {
        return false;
    }
}

bool StateSpace::IsPositionValid(int code, int x_coor, int y_coor) {
    if (!IsInTheBound(x_coor, y_coor)) {
        return false;
    }
    int ternary_code = StateSpace::DecToTer(code);
    string code_str = StateSpace::IntToString9(ternary_code);
    if (code_str.at(x_coor * kBoardSize + y_coor) != '0') {
        return false;
    }
    return true;
}

std::set<pair<int, int> > * StateSpace::GetAllValidNextMove(int code, int x, int y) { //DELETE After use
    set<pair<int, int> > * neighbors = new set<pair<int, int> >;
    if (((x == kOne && y == kOne) || (x == kTwo && y == kTwo)) && IsPositionValid(code, x - kOne, y - kOne)) {
        neighbors->insert( pair<int,int>(x - kOne, y - kOne));
    }
    if (IsPositionValid(code, x - kOne, y)) {
        neighbors->insert(pair<int,int>(x - kOne, y));
    }
    if (((x == kOne && y == kOne) || (x == kTwo && y == kZero)) && IsPositionValid(code, x - kOne, y + kOne)) {
        neighbors->insert( pair<int,int>(x - kOne, y + kOne));
    }
    if (IsPositionValid(code, x, y - kOne)) {
        neighbors->insert( pair<int,int>(x, y - kOne));
    }
    if (IsPositionValid(code, x, y + kOne)) {
        neighbors->insert( pair<int,int>(x, y + kOne));
    }
    if (((x == kOne && y == kOne) || (x == kZero && y == kTwo)) && IsPositionValid(code, x + kOne, y - kOne)) {
        neighbors->insert( pair<int,int>(x + kOne, y - kOne));
    }
    if (IsPositionValid(code, x + kOne, y)) {
        neighbors->insert( pair<int,int>(x + kOne, y));
    }
    if (((x == kOne && y == kOne) || (x == kZero && y == kZero)) && IsPositionValid(code, x + kOne, y + kOne)) {
        neighbors->insert( pair<int,int>(x + kOne, y + kOne));
    }
    return neighbors;
}

int StateSpace::CheckEndGame(int code) {
    int** _board = StateSpace::GetBoard(code);
    int end_flag = kZero;
    for (int i = kZero; i < kBoardSize; i++) {
        int y0 = _board[i][kZero];
        int y1 = _board[i][kOne];
        int y2 = _board[i][kTwo];
        if (y0 == y1 && y1 == y2 && y0 != kZero) {
            //end_flag = y0;
            if (y0 == kOne) end_flag = kOne;
            if (y0 == kTwo) end_flag = -1*kOne;
            DeleteBroad(_board);
            return end_flag;
        }

        int x0 = _board[kZero][i];
        int x1 = _board[kOne][i];
        int x2 = _board[kTwo][i];

        if (x0 == x1 && x1 == x2 && x0 != kZero) {
            //end_flag = x0;
            if (x0 == kOne) end_flag = kOne;
            if (x0 == kTwo) end_flag = -1* kOne;
            DeleteBroad(_board);
            return end_flag;
        }
    }

    // check cross
    int c00 = _board[kZero][kZero];
    int c22 = _board[kTwo][kTwo];
    int c11 = _board[kOne][kOne];

    int c20 = _board[kTwo][kZero];
    int c02 = _board[kZero][kTwo];
    if (c00 == c11 && c11 == c22 && c00 != kZero) {
        if (c00 == kOne) end_flag = kOne;
        if (c00 == kTwo) end_flag = -1*kOne;
        DeleteBroad(_board);
        //end_flag = c00;
        return end_flag;
    }
    if (c20 == c11 && c11 == c02 && c20 != kZero) {
        //end_flag = c20;
        if (c20 == kOne) end_flag = kOne;
        if (c20 == kTwo) end_flag = -1*kOne;
        DeleteBroad(_board);
        return end_flag;
    }


    DeleteBroad(_board);
    return kZero;
}

int StateSpace::AddOneStepADD(int code, int x_coor, int y_coor, int color) {
    if (x_coor < kZero || x_coor > kTwo ||y_coor < kZero || y_coor > kTwo) {
        //std::cout << "invalid position - out of bound" << endl;
        return code;
    }
    string new_code;
    if (StateSpace::CheckEndGame(code) == kZero) {
        int tre = StateSpace::DecToTer(code);
        string code_str = StateSpace::IntToString9(tre);
        int position = x_coor *kBoardSize + y_coor;

        if (code_str.at(position) == '0') {
            new_code.append(code_str.substr(kZero, position));
            new_code.append(IntToString(color));
            new_code.append(code_str.substr(position+kOne));
        } else {
            //std::cout << "invalid postion - already have node here" << std::endl;
            return code;
        }

    } else {
        //std::cout << "Game already over!" << std::endl;
        return code;
    }
    return StateSpace::TerToDec(StateSpace::StringToInt(new_code));
}

int StateSpace::AddOneStepMOVE(int code, pair<int, int> from, pair<int, int> to) {
    int tre = StateSpace::DecToTer(code);
    string code_str = StateSpace::IntToString9(tre);
    int position = from.first *kBoardSize + from.second;
    string this_color;
    this_color.push_back(code_str.at(position));
    int color = StringToInt(this_color);
    string new_code;
    new_code.append(code_str.substr(kZero, position));
    new_code.append("0");
    new_code.append(code_str.substr(position+kOne));
    int newcode = StateSpace::TerToDec(StringToInt(new_code));
    return StateSpace::AddOneStepADD(newcode, to.first, to.second, color);

}

std::set<int> * StateSpace::GetNextSteps(int code, int color) { //DELETE After use
    set<int> * nextStep = new set<int>; //toreturn
    if (IsMovePhase(code)){ //if it is in move phase
        //find all possible node that can move
        set<pair<int, int> > * move_nodes = StateSpace::GetAllValidMoveNode(code, color);
        //for every node find all next position that it can move
        for (std::set<pair<int, int> >::iterator it=move_nodes->begin(); it!=move_nodes->end(); ++it) {
            pair<int, int> from = make_pair(it->first, it->second);
            std::set<pair<int, int> > * validNextPoint = StateSpace::GetAllValidNextMove(code, it->first, it->second);
            //store new next states
            for (std::set<pair<int, int> >::iterator it2=validNextPoint->begin(); it2!=validNextPoint->end(); ++it2) {
                nextStep->insert(AddOneStepMOVE(code, from, make_pair(it2->first, it2->second)));
            }
            delete validNextPoint;
        }
        delete move_nodes;
    } else { //if it is in add phase
        set<pair<int, int> > * add_nodes = StateSpace::GetAllEmptyPosition(code); //find all empty position
        //store new next states
        for (std::set<pair<int, int> >::iterator it=add_nodes->begin(); it!=add_nodes->end(); ++it) {
            nextStep->insert(StateSpace::AddOneStepADD(code, it->first, it->second, color));
        }
        delete add_nodes;
    }
    return nextStep;

}
int StateSpace::Minimax(pair<int, int> state, int mycolor, int depth,int alpha ,int beta) {
    int othercolor = kZero;
    if (mycolor == kOne) {
        othercolor = kTwo;
    } else {
        othercolor = kOne;
    }

    if (CheckEndGame(state.first) == othercolor) {
        return -1000;
    } else if (CheckEndGame(state.first) == mycolor) {
        return 1000;
    } else if (depth == 0) {
        return 0;
    } else {
        if (state.second == othercolor) { 
            int bestVal = -10000;
            std::set<int> * possibleSet = StateSpace::GetNextSteps(state.first, state.second);
            for (std::set<int>::iterator it=possibleSet->begin(); it!=possibleSet->end(); ++it) {
                bestVal = std::max(bestVal, Minimax(pair<int, int>(*it, mycolor), mycolor, depth-1, alpha, beta));
                alpha = std::max(alpha, bestVal);
                if (beta <= alpha) {
                    break;
                }
            }
            delete possibleSet;
            return bestVal;
        } else { 
            int bestVal = 10000;
            std::set<int> * possibleSet = StateSpace::GetNextSteps(state.first, othercolor);
            for (std::set<int>::iterator it=possibleSet->begin(); it!=possibleSet->end(); ++it) {
                bestVal = std::min(bestVal, Minimax(pair<int, int>(*it, othercolor), mycolor, depth-1, alpha, beta));
                beta = std::min(beta, bestVal);
                if (beta <= alpha) {
                    break;
                }
            }
            delete possibleSet;
            return bestVal;
        }

    }
}

int StateSpace::GetBestMove(int code, int color) {
    int mycolor = kZero;
    if (color == kOne) {
        mycolor = kTwo;
    } else {
        mycolor = kOne;
    }

    if (!IsMovePhase(code)) {
        cout << "check phase " << code << " with " << color << endl;
        pair<int, int> possAddCritical = IsAddCritical(code, color);
        cout << possAddCritical.first << " and " << possAddCritical.second << endl;
        if (possAddCritical.first != -1) {
            return AddOneStepADD(code, possAddCritical.first, possAddCritical.second, mycolor);
        }
    }
    pair<int, int> bestmove = pair<int, int>(-1,-10000);
    std::set<int> * possibleSet = StateSpace::GetNextSteps(code, mycolor);
    for (std::set<int>::iterator it=possibleSet->begin(); it!=possibleSet->end(); ++it) {
        int move = Minimax(pair<int, int>(*it, mycolor), mycolor, 7, -10000, 10000);
        if (move > bestmove.second) {
            bestmove.first = *it;
            bestmove.second = move;
        }
    }
    return bestmove.first;
}

pair<int, int> StateSpace::IsAddCritical(int code, int color) {
    int** _board = StateSpace::GetBoard(code);

    int other = kZero;
    if (color == kOne) {
        other = kTwo;
    } else {
        other = kOne;
    }
    pair< pair<int, int>, int> numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),kZero);
    //vertical
    for (int i = 0; i < kBoardSize; i++) {
        numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),kZero);
        int num1 = 0;
        int num2 = 0;
        for (int j = 0; j < kBoardSize; j++) {
            if (_board[j][i] == 0) {
                numEmpty.first = pair<int, int>(j,i);
                numEmpty.second += 1;
            } else if (_board[j][i] == color) {
                num1++;
            } else {
                num2++;
            }
        }


        if (num1 == kTwo && numEmpty.second == kOne) {
            DeleteBroad(_board);
            return numEmpty.first;
        }
    }

    //horizontal check
    for (int i = 0; i < kBoardSize; i++) {
        numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),0);
        int num1 = 0;
        int num2 = 0;
        for (int j = 0; j < kBoardSize; j++) {
            if (_board[i][j] == kZero) {
                numEmpty.first = pair<int, int>(i,j);
                numEmpty.second += kOne;
            } else if (_board[i][j] == color) {
                num1++;
            } else {
                num2++;
            }
        }

        if (num1 == kTwo && numEmpty.second == kOne) {
            DeleteBroad(_board);
            return numEmpty.first;

        }
    }

    //diag
    numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),kZero);
    int num1 = 0;
    int num2 = 0;
    for (int i = 0; i < kBoardSize; i++) {
        if (_board[i][i] == kZero) {
            numEmpty.first = pair<int, int>(i,i);
            numEmpty.second += kOne;
        } else if (_board[i][i] == color) {
            num1++;
        } else {
            num2++;
        }

    }
    if (num1 == kTwo && numEmpty.second == kOne) {
        DeleteBroad(_board);
        return numEmpty.first;

    }

    numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),kZero);
    num1 = 0;
    num2 = 0;
    for (int i = kTwo; i >= 0; i--) {
        if (_board[i][kTwo - i] == kZero) {
            numEmpty.first = pair<int, int>(i,kTwo - i);
            numEmpty.second += kOne;
        } else if (_board[i][kTwo - i] == color) {
            num1++;
        } else {
            num2++;
        }

    }
    if (num1 == kTwo && numEmpty.second == kOne) {
        DeleteBroad(_board);
        return numEmpty.first;

    }
    numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),kZero);

    DeleteBroad(_board);
    return numEmpty.first;
}