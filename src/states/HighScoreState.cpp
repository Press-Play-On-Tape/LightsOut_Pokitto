#include "HighScoreState.h"
#include "../images/Images.h"
#include "../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

constexpr const static uint8_t UPLOAD_DELAY = 16;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void HighScoreState::activate() {
	
	this->cursor = 0;
}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
GameStateType HighScoreState::update(GameStateType currentState, GameCookie *cookie) {
	
    bool flash = Utils::getFrameCountHalf(48);
    uint32_t index = cookie->getLastMovesIndex();
    uint8_t level = cookie->level;


	// Handle other input ..

    if (index != NO_SCORE) {

        if (PC::buttons.pressed(BTN_LEFT) && this->cursor > 0) {
            this->cursor--;
        }

        if (PC::buttons.pressed(BTN_RIGHT) && this->cursor < 2) {
            this->cursor++;
        }

        if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 16)) {

            uint32_t val = cookie->initials[level][index][this->cursor];
            val++;
            if (val > 38) val = 0;
            cookie->initials[level][index][this->cursor] = val;
            
        }

        if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 16)) {

            uint32_t val = cookie->initials[level][index][this->cursor];
            if (val == 0) val = 38;
            val--;
            cookie->initials[level][index][this->cursor] = val;
            
        }

        if (PC::buttons.pressed(BTN_A) && cookie->initials[level][index][0] != 0 && cookie->initials[level][index][1] != 0 && cookie->initials[level][index][2] != 0) {

            cookie->saveCookie();
            cookie->setLastMoves(9999);
            
        }

    }
    else {
     
        if (PC::buttons.pressed(BTN_A)) {
        	currentState = GameStateType::TitleScreen_Activate; 
        }
   
    }

    return currentState;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void HighScoreState::render(GameCookie *cookie) {
	
    bool flash = Utils::getFrameCountHalf(32);
    uint32_t index = cookie->getLastMovesIndex();
    uint8_t level = cookie->level;
    
    PD::fillScreen(1);
    PD::setColor(7);
    PD::drawLine(0, 15, 219, 15);
    PD::drawLine(0, 63, 219, 63);
    PD::setColor(6);
    PD::drawLine(0, 16, 219, 16);
    PD::drawLine(0, 50, 219, 50);
    PD::drawLine(0, 64, 219, 64);
    PD::drawLine(0, 155, 219, 155);
    PD::setColor(5);
    PD::fillRect(0, 51, 220, 2);
    PD::fillRect(0, 156, 220, 2);
    PD::setColor(0);
    PD::fillRect(0, 17, 220, 31);
    PD::fillRect(0, 65, 220, 89);

    PD::drawBitmap(14, 80, Images::LightsOut);


    // Has a new High Score been set ?
        
    if (index != NO_SCORE) {
    
        PD::drawBitmap(63, 23, Images::Char_E);
        PD::drawBitmap(73, 23, Images::Char_N);
        PD::drawBitmap(83, 23, Images::Char_T);
        PD::drawBitmap(93, 23, Images::Char_E);
        PD::drawBitmap(103, 23, Images::Char_R);

        PD::drawBitmap(118, 23, Images::Char_Y);
        PD::drawBitmap(128, 23, Images::Char_O);
        PD::drawBitmap(138, 23, Images::Char_U);
        PD::drawBitmap(148, 23, Images::Char_R);

        PD::drawBitmap(70, 37, Images::Char_I);
        PD::drawBitmap(80, 37, Images::Char_N);
        PD::drawBitmap(90, 37, Images::Char_I);
        PD::drawBitmap(100, 37, Images::Char_T);
        PD::drawBitmap(110, 37, Images::Char_I);
        PD::drawBitmap(120, 37, Images::Char_A);
        PD::drawBitmap(130, 37, Images::Char_L);
        PD::drawBitmap(140, 37, Images::Char_S);

        uint8_t digits[4] = {};
        Utils::extractDigits(digits, cookie->lastMoves);


        // Render Highlights ..
        
        PD::drawBitmap(108, 90 + (index * 12), Images::HS_Highlight);
        PD::drawBitmap(210, 90 + (index * 12), Images::HS_Highlight);



        // Render score and name entry ..
        
        for (uint8_t j = 4; j > 0; --j) {
        
            PD::drawBitmap(155 - (j * 10), 90 + (index * 12), Images::HS_Font[digits[j - 1] + 27]);
        
        }

        for (uint32_t x = 0; x < 3; x++) {
            
            if ((this->cursor == x && flash) || this->cursor != x) {
            
                PD::drawBitmap(178 + (x * 10), 90 + (index * 12), Images::HS_Font[cookie->initials[level][index][x]]);
                
            }

        }

    }
    else {

        PD::drawBitmap(69, 21, Images::LevelTexts[cookie->level]);  
        PD::drawBitmap(56, 38, Images::Top5Scores);

    }
        


    // Render remaining scores ..
    
    PD::drawBitmap(110, 74, Images::Char_M);
    PD::drawBitmap(120, 74, Images::Char_O);
    PD::drawBitmap(130, 74, Images::Char_V);
    PD::drawBitmap(140, 74, Images::Char_E);
    PD::drawBitmap(150, 74, Images::Char_S);

    PD::drawBitmap(173, 74, Images::Char_N);
    PD::drawBitmap(183, 74, Images::Char_A);
    PD::drawBitmap(193, 74, Images::Char_M);
    PD::drawBitmap(203, 74, Images::Char_E);

    for (uint32_t y = 0; y < 5; y++) {
    
        //Score

        uint8_t digits[4] = {};
        Utils::extractDigits(digits, cookie->moves[level][y]);
        
        if (index != y) {

            for (uint8_t j = 4; j > 0; --j) {
            
                PD::drawBitmap(155 - (j * 10), 90 + (y * 12), Images::HS_Font[digits[j - 1] + 27]);
            
            }

            for (uint32_t x = 0; x < 3; x++) {
                
                PD::drawBitmap(178 + (x * 10), 90 + (y * 12), Images::HS_Font[cookie->initials[level][y][x]]);

            }

        }
        
    }

}
