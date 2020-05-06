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
    
    PD::clear();

    PD::drawBitmap(0, 0, Images::Background);


    // Has a new High Score been set ?
        
    if (index != NO_SCORE) {
    
        PD::drawBitmap(63, 25, Images::Char_E);
        PD::drawBitmap(73, 25, Images::Char_N);
        PD::drawBitmap(83, 25, Images::Char_T);
        PD::drawBitmap(93, 25, Images::Char_E);
        PD::drawBitmap(103, 25, Images::Char_R);

        PD::drawBitmap(118, 25, Images::Char_Y);
        PD::drawBitmap(128, 25, Images::Char_O);
        PD::drawBitmap(138, 25, Images::Char_U);
        PD::drawBitmap(148, 25, Images::Char_R);

        PD::drawBitmap(70, 45, Images::Char_I);
        PD::drawBitmap(80, 45, Images::Char_N);
        PD::drawBitmap(90, 45, Images::Char_I);
        PD::drawBitmap(100, 45, Images::Char_T);
        PD::drawBitmap(110, 45, Images::Char_I);
        PD::drawBitmap(120, 45, Images::Char_A);
        PD::drawBitmap(130, 45, Images::Char_L);
        PD::drawBitmap(140, 45, Images::Char_S);

        uint8_t digits[4] = {};
        Utils::extractDigits(digits, cookie->lastMoves);


        // Render Highlights ..
        
        PD::drawBitmap(49, 85 + (index * 12), Images::HS_Highlight);
        PD::drawBitmap(169, 85 + (index * 12), Images::HS_Highlight);



        // Render score and name entry ..
        
        for (uint8_t j = 4; j > 0; --j) {
        
            PD::drawBitmap(96 - (j * 10), 86 + (index * 12), Images::HS_Font[digits[j - 1] + 27]);
        
        }

        for (uint32_t x = 0; x < 3; x++) {
            
            if ((this->cursor == x && flash) || this->cursor != x) {
            
                PD::drawBitmap(137 + (x * 10), 86 + (index * 12), Images::HS_Font[cookie->initials[level][index][x]]);
                
            }

        }

    }
    else {

        PD::drawBitmap(69, 20, Images::LevelTexts[cookie->level]);  

        PD::drawBitmap(55, 45, Images::Char_T);
        PD::drawBitmap(65, 45, Images::Char_O);
        PD::drawBitmap(75, 45, Images::Char_P);

        PD::drawBitmap(90, 45, Images::Char_5);

        PD::drawBitmap(105, 45, Images::Char_S);
        PD::drawBitmap(115, 45, Images::Char_C);
        PD::drawBitmap(125, 45, Images::Char_O);
        PD::drawBitmap(135, 45, Images::Char_R);
        PD::drawBitmap(145, 45, Images::Char_E);
        PD::drawBitmap(155, 45, Images::Char_S);

    }
        


    // Render remaining scores ..
    
    PD::drawBitmap(51, 69, Images::Char_M);
    PD::drawBitmap(61, 69, Images::Char_O);
    PD::drawBitmap(71, 69, Images::Char_V);
    PD::drawBitmap(81, 69, Images::Char_E);
    PD::drawBitmap(91, 69, Images::Char_S);

    PD::drawBitmap(131, 69, Images::Char_N);
    PD::drawBitmap(141, 69, Images::Char_A);
    PD::drawBitmap(151, 69, Images::Char_M);
    PD::drawBitmap(161, 69, Images::Char_E);

    for (uint32_t y = 0; y < 5; y++) {
    
        //Score

        uint8_t digits[4] = {};
        Utils::extractDigits(digits, cookie->moves[level][y]);
        
        if (index != y) {

            for (uint8_t j = 4; j > 0; --j) {
            
                PD::drawBitmap(96 - (j * 10), 86 + (y * 12), Images::HS_Font[digits[j - 1] + 27]);
            
            }

            for (uint32_t x = 0; x < 3; x++) {
                
                PD::drawBitmap(137 + (x * 10), 86 + (y * 12), Images::HS_Font[cookie->initials[level][y][x]]);

            }

        }
        
    }

}
