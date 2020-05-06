#include "SplashScreenState.h"
#include "../images/Images.h"
#include "../utils/Utils.h"
#include "../sounds/Sounds.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void SplashScreenState::activate() {

    PS::playMusicStream("music/lights1.raw", 0);

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
GameStateType SplashScreenState::update(GameStateType currentState, GameCookie *cookie) { 
    

    // If level is not 5, 7 or 9 then make it so ..

    if (cookie->level < 0 || cookie->level > 2) {

        cookie->level = 0;

    }


    // Handle player actions ..

    auto justPressed = PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C);

    if (justPressed > 0) {

        currentState = GameStateType::TitleScreen_Activate; 

    }
    
    if (Utils::isFrameCount(12)) {
     
        this->counter++;
        
        if (this->counter == 4) {
            
            this->counter = 0;
            
        }
        
    }
    
    return currentState;
}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void SplashScreenState::render() {

    PD::drawBitmap(44, 54, Images::Ppot_Full);
    PD::drawBitmap(64, 76, Images::Ppot[counter]);

    if (counter < 2) PD::drawBitmap(163, 72, Images::Ppot_Arrow);

}
