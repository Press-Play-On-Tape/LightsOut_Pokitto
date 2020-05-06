#include "PlayGameState.h"
#include "Pokitto.h"
#include "src/utils/Enums.h"
#include "src/images/Images.h"
#include "src/sounds/Sounds.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PS=Pokitto::Sound;


const uint8_t cellSize[] =  { 24, 16, 12 };
const uint8_t offsetX[] =   { 44, 45, 44 };
const uint8_t offsetY[] =   { 14, 15, 14 };
const uint8_t offsetYHand[] = { 11, 10, 8};
const uint8_t initMoves[] = { 7, 11, 17 };
//const uint8_t initMoves[] = { 1, 1, 1 };


void PlayGameState::toggleCell(uint8_t level, Point cell, bool automated) {
        
    uint8_t gridSize = size[level];
    
    this->grid[cell.Y][cell.X] = !grid[cell.Y][cell.X];
    
    if (cell.X > 0)                   this->grid[cell.Y][cell.X - 1] = !this->grid[cell.Y][cell.X - 1];
    if (cell.X < (gridSize - 1))      this->grid[cell.Y][cell.X + 1] = !this->grid[cell.Y][cell.X + 1];
    if (cell.Y > 0)                   this->grid[cell.Y - 1][cell.X] = !this->grid[cell.Y - 1][cell.X];
    if (cell.Y < (gridSize - 1))      this->grid[cell.Y + 1][cell.X] = !this->grid[cell.Y + 1][cell.X];

    if (cell.X == lastMove.X && cell.Y == lastMove.Y) {
        this->moves--;
        this->lastMove.X = -1;
        this->lastMove.Y = -1;
    }
    else {
        this->moves++;
        this->lastMove.X = cell.X;
        this->lastMove.Y = cell.Y;
    }

    if (!automated) {

        if (isComplete(level)) {

            PS::playMusicStream("music/lights2.raw", 0);
            
        }
        else {

            PS::playSFX(Sounds::sfx_Switch, Sounds::sfx_Switch_length);

        } 

    }
            
}

void PlayGameState::clearPuzzle(uint8_t level) {
    
    uint8_t gridSize = size[level];

    for (uint8_t y = 0; y < gridSize; y++) {

        for (uint8_t x = 0; x < gridSize; x++) {
            
            this->grid[y][x] = 0;
            this->orig[y][x] = 0;
            this->create[y][x] = 0;
            
        }
        
    }

}

void PlayGameState::resetPuzzle(uint8_t level) {
    
    uint8_t gridSize = size[level];
    
    for (uint8_t y = 0; y < gridSize; y++) {

        for (uint8_t x = 0; x < gridSize; x++) {
            
            this->grid[y][x] = this->orig[y][x];

        }
        
    }

}

void PlayGameState::createPuzzle(uint8_t level) {

    uint8_t moves = initMoves[level];
    uint8_t gridSize = size[level];
    
    for (uint8_t x = 0; x < moves; x++) {
        
        while (true) {
    
            uint8_t r = random(0, gridSize * gridSize);
        
            if (this->create[r / gridSize][r % gridSize] == 0) {

                Point cell = { r % gridSize, r / gridSize };
                
                toggleCell(gridSize, cell, true);
                this->create[r / gridSize][r % gridSize] = 1;
                break;
                
            }
        
        }
        
    }
    
    // Copy to orig grid ..
    
    for (uint8_t y = 0; y < gridSize; y++) {

        for (uint8_t x = 0; x < gridSize; x++) {
            
            this->orig[y][x] = this->grid[y][x];

        }
        
    }

    this->moves = 0;
    this->lastMove.X = -1;
    this->lastMove.Y = -1;

}


void PlayGameState::renderGrid(uint8_t level) {
        
    uint8_t gridSize = size[level];
    
    for (uint8_t y = 0; y < gridSize; y++) {

        for (uint8_t x = 0; x < gridSize; x++) {
            
            PD::drawBitmap(offsetX[level] + (x * (cellSize[level] + 3)), offsetY[level] + (y * (cellSize[level] + 3)), Images::Tiles[(level * 2) + this->grid[y][x]]);

        }
        
    }
    
}

void PlayGameState::renderCursor(uint8_t level, Point cursor) {
        
    uint8_t gridSize = size[level];

    if (this->controlMode == ControlMode::Game) {

        PD::drawBitmap(offsetX[level] + (cursor.X * (cellSize[level] + 3)) + (cellSize[level] / 2) - 7, offsetY[level] + (cursor.Y * (cellSize[level] + 3)) + cellSize[level] - offsetYHand[level], Images::Hand_Vert);

    }
    else {

        PD::drawBitmap(135, 65 + (static_cast<uint8_t>(this->menuOption) * 15), Images::Menu_Options[static_cast<uint8_t>(this->menuOption)]);
        
    }
    
} 

bool PlayGameState::isComplete(uint8_t level) {
        
    uint8_t gridSize = size[level];

    bool isComplete = true;

    for (uint8_t y = 0; y < gridSize; y++) {

        for (uint8_t x = 0; x < gridSize; x++) {
            
            if (this->grid[y][x]) {

                isComplete = false;
                break;

            }

        }
        
    }

    return isComplete;

}


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void PlayGameState::activate(GameCookie *cookie) {

	this->moves = 0;
	this->level = cookie->level;
    this->menuOption = MenuOption::NewGame;
    this->controlMode = ControlMode::Game;
    this->cursor.X = 0;
    this->cursor.Y = 0;
    this->lastMove.X = -2;
    this->lastMove.Y = -2;

    clearPuzzle(this->level);
    createPuzzle(this->level);

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
GameStateType PlayGameState::update(GameStateType currentState, GameCookie *cookie) {
        
    uint8_t gridSize = size[level];
    

    // Handle player movement ..

    if (!isComplete(this->level)) {

        if (this->controlMode == ControlMode::Game) {   
            
            if (PC::buttons.pressed(BTN_LEFT) && cursor.X > 0)                  this->cursor.X--;
            if (PC::buttons.pressed(BTN_RIGHT) && cursor.X < (gridSize - 1))    this->cursor.X++;
            if (PC::buttons.pressed(BTN_UP) && cursor.Y > 0)                    this->cursor.Y--;
            if (PC::buttons.pressed(BTN_DOWN) && cursor.Y < (gridSize - 1))     this->cursor.Y++;
            if (PC::buttons.pressed(BTN_A))                                     toggleCell(this->level, this->cursor, false);
            if (PC::buttons.pressed(BTN_C))                                     this->controlMode = ControlMode::Menu;
            
        }
        else {
            
            if (PC::buttons.pressed(BTN_C))                                     this->controlMode = ControlMode::Game;
            if (PC::buttons.pressed(BTN_UP))                                    this->menuOption--;
            if (PC::buttons.pressed(BTN_DOWN))                                  this->menuOption++;

            if (PC::buttons.pressed(BTN_A)) {
                
                switch (menuOption) {
                    
                    case MenuOption::NewGame:
                        clearPuzzle(this->level);
                        createPuzzle(this->level);
                        this->lastMove.X = -1;
                        this->lastMove.Y = -1;
                        this->moves = 0;
                        break;
                        
                    case MenuOption::Reset:
                        resetPuzzle(this->level);
                        this->moves = 0;
                        break;
                        
                    case MenuOption::MainMenu:
                        currentState = GameStateType::TitleScreen_Activate;
                        break;
                        
                }
                
            }

        }

    }
    else {

        if (PC::buttons.pressed(BTN_A)) {

            cookie->setLastMoves(this->moves);
            currentState = GameStateType::HighScore_Activate;
        }

    }

    return currentState;

}

void PlayGameState::render() {

    PD::drawBitmap(0, 0, Images::Background);
    
    PD::setCursor(81, 160);
    PD::print("Moves: ");
    if (this->moves < 100)  PD::print("0");
    if (this->moves < 10)   PD::print("0");
    PD::print(moves, 10);

    renderGrid(this->level);

    if (this->controlMode == ControlMode::Menu) {

        PD::drawBitmap(130, 60, Images::Menu);

    }

    renderCursor(this->level, this->cursor);

    if (isComplete(this->level)) {

        PD::drawBitmap(26, 63, Images::Congratulations);
        PD::drawBitmap(34, 76, Images::Char_C);
        PD::drawBitmap(44, 76, Images::Char_O);
        PD::drawBitmap(54, 76, Images::Char_N);
        PD::drawBitmap(64, 76, Images::Char_G);
        PD::drawBitmap(74, 76, Images::Char_R);
        PD::drawBitmap(84, 76, Images::Char_A);
        PD::drawBitmap(94, 76, Images::Char_T);
        PD::drawBitmap(104, 76, Images::Char_U);
        PD::drawBitmap(114, 76, Images::Char_L);
        PD::drawBitmap(124, 76, Images::Char_A);
        PD::drawBitmap(134, 76, Images::Char_T);
        PD::drawBitmap(144, 76, Images::Char_I);
        PD::drawBitmap(154, 76, Images::Char_O);
        PD::drawBitmap(164, 76, Images::Char_N);
        PD::drawBitmap(174, 76, Images::Char_S);
        PD::drawBitmap(184, 76, Images::Char_Ex);

    }

}