#include "game_app.h"

void prepareSettings(GameApp::Settings* settings) {
    settings->setResizable(false);
}

//This line is a macro that expands into an "int main()" function.
CINDER_APP(GameApp, ci::app::RendererGl, prepareSettings);
