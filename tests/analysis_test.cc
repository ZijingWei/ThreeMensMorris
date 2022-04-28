#include <catch2/catch.hpp>
#include "../include/node.h"
#include "../include/analysis.h"
#include <iostream>
#include <set>


TEST_CASE("Ternary to Decimal") {
    StateSpace::DrawBoard(11340);
    SECTION("Without Zero In Front") {
        REQUIRE(11340 == StateSpace::TerToDec(120120000));
        REQUIRE(9207 == StateSpace::TerToDec(110122000));
        REQUIRE(15444 == StateSpace::TerToDec(210012000));
        REQUIRE(6561 == StateSpace::TerToDec(100000000));
        REQUIRE(13122 == StateSpace::TerToDec(200000000));
    }

    SECTION("With Zero In Front") {
        REQUIRE(4779 == StateSpace::TerToDec(20120000));
        REQUIRE(2646 == StateSpace::TerToDec(10122000));
        REQUIRE(2322 == StateSpace::TerToDec(10012000));
        REQUIRE(0 == StateSpace::TerToDec(000000000));
        REQUIRE(4374 == StateSpace::TerToDec(20000000));
    }


}

TEST_CASE("Decimal to Ternary") {
    SECTION("Without Zero In Front") {
        REQUIRE(120120000 == StateSpace::DecToTer(11340));
        REQUIRE(110122000 == StateSpace::DecToTer(9207));
        REQUIRE(210012000 == StateSpace::DecToTer(15444));
        REQUIRE(100000000 == StateSpace::DecToTer(6561));
        REQUIRE(200000000 == StateSpace::DecToTer(13122));
    }

    SECTION("With Zero In Front") {
        REQUIRE(20120000 == StateSpace::DecToTer(4779));
        REQUIRE(10122000 == StateSpace::DecToTer(2646));
        REQUIRE(10012000 == StateSpace::DecToTer(2322));
        REQUIRE(0 == StateSpace::DecToTer(0));
        REQUIRE(20000000 == StateSpace::DecToTer(4374));
    }


}

TEST_CASE("Test Get Board") {
    SECTION("Empty Board") {
        int** expect = new int*[3];
        for (int i = 0; i < 3; ++i) {
            expect[i] = new int[3];
            for (int j = 0; j < 3; j ++) {
                expect[i][j] = 0;
            }
        }
        int** board = StateSpace::GetBoard(StateSpace::TerToDec(000000000));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; j++) {
                REQUIRE(expect[i][j] == board[i][j]);
            }
            
        }
        StateSpace::DeleteBroad(expect);
        StateSpace::DeleteBroad(board);
    }

    SECTION("Without Zero In Front") {
        int** expect = new int*[3];
        for (int i = 0; i < 3; ++i) {
            expect[i] = new int[3];
        }
        expect[0][0] = 1;
        expect[0][1] = 2;
        expect[0][2] = 0;
        expect[1][0] = 1;
        expect[1][1] = 2;
        expect[1][2] = 0;
        expect[2][0] = 0;
        expect[2][1] = 0;
        expect[2][2] = 0;
        
        int** board = StateSpace::GetBoard(StateSpace::TerToDec(120120000));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; j++) {
                REQUIRE(expect[i][j] == board[i][j]);
            }
        }
        StateSpace::DeleteBroad(expect);
        StateSpace::DeleteBroad(board);
    }

    SECTION("With Zero In Front") {
        int** expect = new int*[3];
        for (int i = 0; i < 3; ++i) {
            expect[i] = new int[3];
        }
        expect[0][0] = 0;
        expect[0][1] = 0;
        expect[0][2] = 0;
        expect[1][0] = 1;
        expect[1][1] = 1;
        expect[1][2] = 0;
        expect[2][0] = 2;
        expect[2][1] = 2;
        expect[2][2] = 0;

        int** board = StateSpace::GetBoard(StateSpace::TerToDec(110220));
        //StateSpace::DrawBoard(StateSpace::TerToDec(000110220));
        StateSpace::DrawBoard(StateSpace::TerToDec(110220));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; j++) {
                REQUIRE(expect[i][j] == board[i][j]);
            }
        }
        StateSpace::DeleteBroad(expect);
        StateSpace::DeleteBroad(board);
    }


}

TEST_CASE("Test Is Position Valid for Input") {

    SECTION("Invalid - Out of Bound") {
        REQUIRE(false == StateSpace::IsPositionValid(StateSpace::TerToDec(110002200), 2, 3));
    }

    SECTION("Invalid - position not empty") {
        REQUIRE(false == StateSpace::IsPositionValid(StateSpace::TerToDec(110002200), 0, 0));
    }

    SECTION("All Good") {
        REQUIRE(false == StateSpace::IsPositionValid(StateSpace::TerToDec(110002200), 0, 2));
    }
}

TEST_CASE("Check Game Ended") {

    SECTION("1 Win") {
        REQUIRE(1 == StateSpace::CheckEndGame(StateSpace::TerToDec(111002200)));
        REQUIRE(1 == StateSpace::CheckEndGame(StateSpace::TerToDec(100012201)));
        REQUIRE(1 == StateSpace::CheckEndGame(StateSpace::TerToDec(100122102)));
    }

    SECTION("2 Win") {
        REQUIRE(-1 == StateSpace::CheckEndGame(StateSpace::TerToDec(222011100)));
        REQUIRE(-1 == StateSpace::CheckEndGame(StateSpace::TerToDec(200021102)));
        REQUIRE(-1 == StateSpace::CheckEndGame(StateSpace::TerToDec(200211201)));
    }

    SECTION("No Winner") {
        REQUIRE(0 == StateSpace::CheckEndGame(StateSpace::TerToDec(000000000)));
        REQUIRE(0 == StateSpace::CheckEndGame(StateSpace::TerToDec(1)));
        REQUIRE(0 == StateSpace::CheckEndGame(StateSpace::TerToDec(2)));
        REQUIRE(0 == StateSpace::CheckEndGame(StateSpace::TerToDec(121000000)));
        REQUIRE(0 == StateSpace::CheckEndGame(StateSpace::TerToDec(121002100)));
        REQUIRE(0 == StateSpace::CheckEndGame(StateSpace::TerToDec(221002101)));
        REQUIRE(0 == StateSpace::CheckEndGame(StateSpace::TerToDec(212001120)));
    }
}


TEST_CASE("Test Move Phase") {
    SECTION("Empty Board") {
        REQUIRE(false == StateSpace::IsMovePhase(StateSpace::TerToDec(0)));
    }
    
    SECTION("Not Move Phase Board") {
        REQUIRE(false == StateSpace::IsMovePhase(StateSpace::TerToDec(100020100)));
    }
    
    SECTION("Move Phase Board") {
        REQUIRE(true == StateSpace::IsMovePhase(StateSpace::TerToDec(110102220)));
    }
    
}

TEST_CASE("Test Get All Valid Move Node") {
    SECTION("Color 1") {
        std::set<pair<int, int> > * nodes = StateSpace::GetAllValidMoveNode(StateSpace::TerToDec(110102220), 1);
        set<pair<int, int> >* expect = new set<pair<int, int> >;
        expect->insert(std::make_pair(0,0));
        expect->insert(std::make_pair(0,1));
        expect->insert(std::make_pair(1,0));
        for (std::set<pair<int, int> >::iterator it=nodes->begin(); it!=nodes->end(); ++it) {
            set< pair<int, int> >::iterator it2 = expect->find((*it));
            REQUIRE(it2 != expect->end());
        }
        delete nodes;
    }

    SECTION("Color 2") {
        std::set<pair<int, int> > * nodes = StateSpace::GetAllValidMoveNode(StateSpace::TerToDec(220201110), 2);
        set<pair<int, int> >* expect = new set<pair<int, int> >;
        expect->insert(std::make_pair(0,0));
        expect->insert(std::make_pair(0,1));
        expect->insert(std::make_pair(1,0));
        for (std::set<pair<int, int> >::iterator it=nodes->begin(); it!=nodes->end(); ++it) {
            set< pair<int, int> >::iterator it2 = expect->find((*it));
            REQUIRE(it2 != expect->end());
        }
        delete nodes;
    }
    
}

TEST_CASE("Test Get All Valid Empty Node") {
    std::set<pair<int, int> > * nodes = StateSpace::GetAllEmptyPosition(StateSpace::TerToDec(110002200));
    set<pair<int, int> >* expect = new set<pair<int, int> >;
    expect->insert(std::make_pair(0,2));
    expect->insert(std::make_pair(1,0));
    expect->insert(std::make_pair(1,1));
    expect->insert(std::make_pair(2,1));
    expect->insert(std::make_pair(2,2));
    for (std::set<pair<int, int> >::iterator it=nodes->begin(); it!=nodes->end(); ++it) {
        set< pair<int, int> >::iterator it2 = expect->find((*it));
        REQUIRE(it2 != expect->end());
    }
    delete nodes;

}

TEST_CASE("Test Get All Valid Next Move") {
    SECTION("Move for Color 1") {
        std::set<pair<int, int> > * nodes = StateSpace::GetAllValidNextMove(StateSpace::TerToDec(110102220), 0, 0);
        set<pair<int, int> >* expect = new set<pair<int, int> >;
        expect->insert(std::make_pair(1,1));

        for (std::set<pair<int, int> >::iterator it=nodes->begin(); it!=nodes->end(); ++it) {
            set< pair<int, int> >::iterator it2 = expect->find((*it));
            REQUIRE(it2 != expect->end());
        }
        delete nodes;
    }

    SECTION("Move for Color 2") {
        std::set<pair<int, int> > * nodes = StateSpace::GetAllValidNextMove(StateSpace::TerToDec(220201110), 0, 0);
        set<pair<int, int> >* expect = new set<pair<int, int> >;
        expect->insert(std::make_pair(1,1));

        for (std::set<pair<int, int> >::iterator it=nodes->begin(); it!=nodes->end(); ++it) {
            set< pair<int, int> >::iterator it2 = expect->find((*it));
            REQUIRE(it2 != expect->end());
        }
        delete nodes;
    }
}

TEST_CASE("Test Get All Next Steps") {
    SECTION("In Add Step") {
        std::set<int > * nodes = StateSpace::GetNextSteps(StateSpace::TerToDec(110002200), 1);
        set<int >* expect = new set<int >;
        expect->insert(8821);
        expect->insert(8823);
        expect->insert(8901);
        expect->insert(9063);
        expect->insert(9549);

        for (std::set<int >::iterator it=nodes->begin(); it!=nodes->end(); ++it) {
            set< int >::iterator it2 = expect->find((*it));
            REQUIRE(it2 != expect->end());
        }
        delete nodes;
    }

    SECTION("In Move Step") {
        std::set<int > * nodes = StateSpace::GetNextSteps(StateSpace::TerToDec(110102202), 1);
        set<int >* expect = new set<int >;
        expect->insert(2585);
        expect->insert(6959);
        expect->insert(7607);
        expect->insert(8903);
        for (std::set<int >::iterator it=nodes->begin(); it!=nodes->end(); ++it) {
            set< int >::iterator it2 = expect->find((*it));
            REQUIRE(it2 != expect->end());
        }
        delete nodes;
    }
}

