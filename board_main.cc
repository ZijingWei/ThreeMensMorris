//
// Created by 28741 on 2022/4/11.
//
#include "include/node.h"
#include "include/analysis.h"

int main() {
    std::cout << "Here" << std::endl;
    std::cout << StateSpace::IntToString9(110220) << std::endl;
    StateSpace::DrawBoard(StateSpace::TerToDec(110220));
}