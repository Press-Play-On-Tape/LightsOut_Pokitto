#include "Pokitto.h"
#include "PokittoCookie.h"
#include "src/Game.h"

#include "src/images/Images.h"
#include "src/utils/Constants.h"
#include "src/utils/Utils.h"
#include "src/utils/Enums.h"


using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


Game game;
GameCookie cookie;

int main() {


    // Initialise pokitto ..

    cookie.begin("LIGHTS", sizeof(cookie), (char*)&cookie);

    PC::begin();
    PD::loadRGBPalette(palettePico);   
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(14);
    PC::setFrameRate(30);
    PD::setFont(font5x7);


    // Kick off the random number generator ..
    
    srand(time(0));



    // Has the cookie been initialised?

    if (cookie.initialised != COOKIE_INITIALISED) {

        cookie.initialise();

    }


    // Play game!

    game.setup(&cookie);

    while (PC::isRunning()) {
    
    if (!PC::update()) continue;
    
        PC::sound.updateStream();
        game.loop();
    
    }
    
    return 0;

}

    