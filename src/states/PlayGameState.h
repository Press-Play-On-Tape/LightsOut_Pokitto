#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"
#include "src/utils/GameCookie.h"

class PlayGameState {

	private:

		void toggleCell(uint8_t level, Point cell, bool automated);
		void clearPuzzle(uint8_t level);
		void resetPuzzle(uint8_t level);
		void createPuzzle(uint8_t level);
		void renderGrid(uint8_t level);
		void renderCursor(uint8_t level, Point cursor);
        bool isComplete(uint8_t level);

	public:

		void activate(GameCookie *cookie);
		GameStateType update(GameStateType currentState, GameCookie *cookie);
		void render();

	private:

		uint8_t grid[11][11];
		uint8_t orig[11][11];
		uint8_t create[11][11];
		uint16_t moves = 0;
		uint8_t level = 0;

		Point cursor;
		Point lastMove;
		MenuOption menuOption = MenuOption::NewGame;
		ControlMode controlMode = ControlMode::Game;


};