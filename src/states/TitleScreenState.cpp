#include "TitleScreenState.h"

#include "../images/Images.h"
#include "../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;

constexpr const static uint8_t UPLOAD_DELAY = 16;




// ----------------------------------------------------------------------------
//  Initialise state ..
//
void TitleScreenState::activate() {

    this->counter = 20;
    
}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
GameStateType TitleScreenState::update(GameStateType currentState, GameCookie *cookie) {


	// Handle player input ..

    if (PC::buttons.pressed(BTN_UP) && cookie->level > 0)   cookie->level--;
    if (PC::buttons.pressed(BTN_DOWN) && cookie->level < 2) cookie->level++;

	if (PC::buttons.pressed(BTN_A)) {
	    
        currentState = GameStateType::PlayGame_Activate; 

	}

	if (PC::buttons.pressed(BTN_B)) {
	    
	    cookie->setLastMoves(9999);
        currentState = GameStateType::HighScore_Activate; 

	}

    return currentState;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void TitleScreenState::render(GameCookie *cookie) {

    const uint8_t xOffset[] = {30, 44, 30};
    PD::clear();
    PD::setColor(6);

    PD::drawBitmap(0, -2, Images::Title_Background_Full);
    PD::drawBitmap(69, 166, Images::LevelTexts[cookie->level]);

    if (cookie->level == 0) {
        PD::drawBitmap(110 + xOffset[cookie->level], 166, Images::Arrow_Up_Dark);
    }
    else {
        PD::drawBitmap(110 + xOffset[cookie->level], 166, Images::Arrow_Up);
    }

    if (cookie->level == 2) {
        PD::drawBitmap(110 + xOffset[cookie->level], 172, Images::Arrow_Down_Dark);
    }
    else {
        PD::drawBitmap(110 + xOffset[cookie->level], 172, Images::Arrow_Down);
    }
    
}



