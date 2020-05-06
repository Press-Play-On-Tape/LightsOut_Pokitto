#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Constants.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		uint16_t moves[3][5] = { 50, 60, 70, 80, 90 };
		uint8_t initials[3][5][3] = { 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5 };
		uint32_t lastMoves = 0;
		uint32_t lastMovesIndex = 0;
		uint8_t level = 0;

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;


			for (uint8_t l = 0; l < 3; l++) {

                this->moves[l][0] = 210;
                this->moves[l][1] = 220;
                this->moves[l][2] = 230;
                this->moves[l][3] = 240;
                this->moves[l][4] = 250;

				for (uint8_t x = 0; x < 5; x++) {

					for (uint8_t y = 0; y < 3; y++) {

						this->initials[l][x][y] = x + 1;

					}

				}
                
			}

			this->lastMoves = 0;
			this->lastMovesIndex = 0;
			this->level = 0;
			this->saveCookie();

		}
		

		uint32_t getLastMovesIndex() {

			return lastMovesIndex;

		}


		uint32_t setLastMoves(uint16_t numberOfMoves) {

            uint32_t index = NO_SCORE;
            
			for (uint32_t x = 0; x < 5; x++) {

				if (numberOfMoves <= this->moves[this->level][x]) {
				    
				    index = x;
				    break;
				    
				}

			}

			if (index != NO_SCORE) {

			    for (int32_t x = 3; x >= index; x--) {
			        
			        this->moves[this->level][x + 1] = this->moves[this->level][x];
			        this->initials[this->level][x + 1][0] = this->initials[this->level][x][0];
			        this->initials[this->level][x + 1][1] = this->initials[this->level][x][1];
			        this->initials[this->level][x + 1][2] = this->initials[this->level][x][2];
			        
			    }

				this->moves[this->level][index] = numberOfMoves;
				this->initials[this->level][index][0] = 0;
				this->initials[this->level][index][1] = 0;
				this->initials[this->level][index][2] = 0;

			}

			this->lastMoves = numberOfMoves;
			this->lastMovesIndex = index;

			return index;

		}

};