#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../images/Images.h"
#include "../utils/GameCookie.h"

class TitleScreenState {
    
    private:

        uint8_t counter = 0;

    public:	
        
        void activate();
        GameStateType update(GameStateType currentState, GameCookie *cookie);
        void render(GameCookie *cookie);

};

