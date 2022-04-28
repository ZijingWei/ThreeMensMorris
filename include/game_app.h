#pragma once
#include "node.h"
#include "analysis.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <cinder/Color.h>
#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/audio/Voice.h>
#include <string>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using std::string;
using std::to_string;
using cinder::app::KeyEvent;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace ci;
using namespace ci::app;



class GameApp: public cinder::app::App {
    public:

        const int kWindowSize = 1000;
        const char* kWin = "Game Over!";
        const float kFontSize = 60;
        const string kColorBlack = "black";
        const int kStartBoardCode = 0;
        const int kStartColor = 2;
        const int kStartNextColor = 1;
        const int kAiColor = 2;
        const int kDefaultWin = 0;
        const int kDefaultBackgroundRed = 255;
        const int kDefaultBackgroundGreen = 246;
        const int kDefaultBackgroundBlue = 148;
        const float kBoundOne = 0;
        const float kBoundTwo = 1000;
        const int kSelectBound = 60;
        const float kCenter = 500;
        const int kDrawWinX = 200;
        const int kDrawWinY = 120;
        const string kBoardName = "3by3board.png";
        const int kSelect = 1;
        
        const char* kFont = "helvetica";
        const glm::vec2 kWinPosition = glm::vec2(500 - 150,500-40);
        const float kBoardSize = 3;
        const float kRadius = 22;
        const float kSingleBoardSize = 1000/3;
        const float kBoardBounds = float(getWindowBounds().getHeight());
        
        GameApp();
    
//        void setup() override;
//    
//        void update() override;
//    
        void draw() override;
//    
        void mouseDown(cinder::app::MouseEvent) override;
//    
//        void mouseMove(cinder::app::MouseEvent) override;
    
    private:
        
        State board_state_;
        int next_color_;
        pair<int, int> select_move_;
        int win_;
        cinder::gl::Texture2dRef background_;
        
        /**
         * Draw the Board include background image and colors
         */
        void DrawBoard();

        /**
         * Draw single board
         */
        void DrawSingeBoard();

        /**
         * Draw single board
         * @param a color
         * @param pos position
         */
        void DrawPoint(int a, vec2 pos);

        /**
         * Draw a rectangle to the selected point
         */
        void DrawSelect();

        /**
         * Draw a box to say who wins the game
         */
        void DrawWin();

        /**
         * Update color of current player
         */
        void UpDateColor();
        
        
        

};

