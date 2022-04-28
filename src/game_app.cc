
#include "game_app.h"

 GameApp::GameApp() : board_state_(StateSpace::TerToDec(kStartBoardCode), kStartColor), 
                        select_move_(std::make_pair(-1*kSelect, -1*kSelect)) {
    
    ci::app::setWindowSize(kWindowSize, kWindowSize);
    background_ = gl::Texture2d::create(loadImage
                                                 (loadAsset(kBoardName)));
    next_color_ = kStartNextColor;
    win_ = kDefaultWin;
    
}

void GameApp::draw() {
    DrawBoard();
}

void GameApp::DrawBoard() {
    
    ci::Color8u background_color(kDefaultBackgroundRed, kDefaultBackgroundGreen, 
                                 kDefaultBackgroundBlue);
    ci::gl::clear(background_color);
    const Rectf board_bounds(kBoundOne, kBoundOne, kBoundTwo, kBoundTwo);
    gl::draw(background_, board_bounds);
    DrawSingeBoard();
    DrawWin();
    //DrawSelect();
}

void GameApp::DrawSelect() {
    
    if (select_move_.first > -1 * kSelect) {
        float xPos = select_move_.first * kSingleBoardSize + kSingleBoardSize/2;
        float yPos = select_move_.second * kSingleBoardSize + kSingleBoardSize/2;
        const Rectf rect(xPos-kSelectBound, yPos-kSelectBound,
                         xPos+kSelectBound, yPos+kSelectBound);
        gl::drawStrokedRect(rect);
    }

}

void GameApp::DrawSingeBoard() {
    int** board = StateSpace::GetBoard(board_state_.GetCode());
    
    for (size_t i = 0; i < kBoardSize; i++) {
        for (size_t j = 0; j < kBoardSize; j++) {
            float xPos = i * kSingleBoardSize + kSingleBoardSize/2;
            float yPos = j * kSingleBoardSize + kSingleBoardSize/2;
            vec2 pos(xPos, yPos);
            DrawPoint(board[i][j], pos);
        }
    }

    StateSpace::DeleteBroad(board);
    DrawSelect();
}

void GameApp::DrawPoint(int color, vec2 pos) {
    if (color == 1) {
        gl::color(Color(1,1,1)); // white
        gl::drawSolidCircle( pos, kRadius);
    } else if (color == 2) {
        gl::color(Color(0,0,0)); // black
        gl::drawSolidCircle( pos, kRadius);
    }
}

void GameApp::mouseDown(cinder::app::MouseEvent event) {
    if (StateSpace::CheckEndGame(board_state_.GetCode())  != kDefaultWin) {
        //restart
        
        board_state_.SetCode(kStartBoardCode);
        next_color_ = kStartNextColor;
        win_ = kDefaultWin;
        
    } else {
        //check if AI step
        if (next_color_ == kAiColor) {
            int best_move = StateSpace::GetBestMove(board_state_.GetCode(), board_state_.GetColor());
            board_state_.SetCode(best_move);
            UpDateColor();
            win_ = StateSpace::CheckEndGame(board_state_.GetCode());
        } else {
            int x_tile_coordinate_ = event.getX();
            int y_tile_coordinate_ = event.getY();
            x_tile_coordinate_ = int(x_tile_coordinate_ / kSingleBoardSize);
            y_tile_coordinate_ = int(y_tile_coordinate_ / kSingleBoardSize);
            //check if it is move phase
            if (StateSpace::IsMovePhase(board_state_.GetCode())) {
                //select a point to move
                if (select_move_.first == -1) {
                    if (StateSpace::CheckMoveColor(board_state_.GetCode(),
                                                   x_tile_coordinate_,
                                                   y_tile_coordinate_,
                                                   next_color_)) {
                        select_move_.first = x_tile_coordinate_;
                        select_move_.second = y_tile_coordinate_;
                    }
                    //else please select again

                } else {
                    //move the point to another position
                    //check if the select position is valid
                    std::set<pair<int, int> > * validNextPoint =
                            StateSpace::GetAllValidNextMove(board_state_.GetCode(), select_move_.first,
                                                            select_move_.second);
                    //store new next states
                    for (std::set<pair<int, int> >::iterator it2=validNextPoint->begin()
                            ; it2!=validNextPoint->end(); ++it2) {

                        if (x_tile_coordinate_ == it2->first && y_tile_coordinate_ == it2->second) {
                            //change board_state
                            board_state_.SetCode(StateSpace::AddOneStepMOVE(board_state_.GetCode(),
                                                                            select_move_,
                                                                            make_pair(it2->first,
                                                                                      it2->second)));
                            select_move_ = std::make_pair(-1,-1);
                            UpDateColor();
                            win_ = StateSpace::CheckEndGame(board_state_.GetCode());

                        }
                    }
                    delete validNextPoint;
                    if (select_move_.first != -1) {
                        if (StateSpace::CheckMoveColor(board_state_.GetCode(), x_tile_coordinate_,
                                                       y_tile_coordinate_, next_color_)) {
                            select_move_.first = x_tile_coordinate_;
                            select_move_.second = y_tile_coordinate_;
                        } else {
                            //invalid position, please select again
                        }

                    }

                }
            } else {

                if (StateSpace::IsPositionValid(board_state_.GetCode(), x_tile_coordinate_,
                                                y_tile_coordinate_)) {
                    int next = StateSpace::AddOneStepADD(board_state_.GetCode(),
                                                         x_tile_coordinate_,
                                                         y_tile_coordinate_,
                                                         next_color_);
                    UpDateColor();
                    board_state_.SetCode(next);
                    win_ = StateSpace::CheckEndGame(board_state_.GetCode());
                }
            }
        }
        
    }
}

void GameApp::UpDateColor() {
    int temp = next_color_;
    next_color_ = board_state_.GetColor();
    board_state_.SetColor(temp);
}

void GameApp::DrawWin() {
    if (win_ != kDefaultWin) {
        float xPos = kCenter;
        float yPos = kCenter;
        const Rectf rect(xPos-kDrawWinX, yPos-kDrawWinY, xPos+kDrawWinX, yPos+kDrawWinY);
        gl::color(255, 229, 204);
        gl::drawSolidRect(rect);
        ci::gl::drawString(kWin
                , kWinPosition
                , ci::Color("black")
                , ci::Font(kFont, kFontSize));
    }
    
}
