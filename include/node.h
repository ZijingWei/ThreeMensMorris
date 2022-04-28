#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <set>

using namespace std;

class State {

public:
    State();
    State(int code, int color);
    State(const State& other);
    ~State();

    
    int GetCode() const;
    int GetColor() const;
    
    int GetScore() const;
    void SetScore(int score);
    void SetColor(int color);
    void SetCode(int code);


private:
    int code_;
    int score_;
    int color_; //1 black 2white
    pair<int, int> code_color_;
    std::set<State *> * next_;
}; 