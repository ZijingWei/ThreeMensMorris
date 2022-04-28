#include "../include/node.h"

State::State() {
    color_ = 1;
    code_ = 0;
    score_ = 0;
    code_color_ = pair<int, int>(0,1);
    next_ = new std::set<State *>();
}

State::State(int code, int color) { //input always in 10nary

    code_ = code;
    color_ = color;
    score_ = 0;
    int nextColor = 0;
    if (color == 1) {
        nextColor = 2;
    } else {
        nextColor = 1;
    }
    code_color_ = pair<int, int>(code,color);
    next_ = new std::set<State *>();

}

State::State(const State& other) {
    code_ = other.GetCode();
    color_ = other.GetColor();
    score_ = other.GetScore();
    int nextColor = 0;
    if (color_ == 1) {
        nextColor = 2;
    } else {
        nextColor = 1;
    }
    code_color_ = pair<int, int>(other.GetCode(),other.GetColor());
}

State::~State() {
    for (std::set<State *>::iterator it=next_->begin(); it!=next_->end(); ++it) {
        if (*it != NULL) {
            delete *it;
        }
    }
    delete next_;
}


int State::GetCode() const{
    return code_;
}

int State::GetColor() const {
    return color_;
}

int State::GetScore() const {
    return score_;
}



void State::SetScore(int score){
    this->score_ = score;
}
void State::SetColor(int color) {
    this->color_ = color;
}
void State::SetCode(int code) {
    this->code_ = code;
}




