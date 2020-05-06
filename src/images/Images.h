#pragma once

namespace Images {

    #include "Arrow_Up.h"
    #include "Arrow_Up_Dark.h"
    #include "Arrow_Down.h"
    #include "Arrow_Down_Dark.h"
    #include "Hand_Vert.h"
    #include "Hand_Horiz.h"

    #include "LevelText_00.h"
    #include "LevelText_01.h"
    #include "LevelText_02.h"

    #include "title/Title_Background.h"
    #include "title/Title_Beam.h"
    #include "title/Title_Background_Full.h"

    #include "background/Background.h"
    #include "background/Menu.h"
    #include "background/Menu_00.h"
    #include "background/Menu_01.h"
    #include "background/Menu_02.h"
    #include "background/Congratulations.h"

    #include "tiles/TileDown0.h"
    #include "tiles/TileUp0.h"
    #include "tiles/TileDown1.h"
    #include "tiles/TileUp1.h"
    #include "tiles/TileDown2.h"
    #include "tiles/TileUp2.h"

    #include "ppot/Ppot_00.h"
    #include "ppot/Ppot_01.h"
    #include "ppot/Ppot_02.h"
    #include "ppot/Ppot_03.h"
    #include "ppot/Ppot_Full.h"
    #include "ppot/Ppot_Arrow.h"

    #include "highscore/Top5Scores.h"
    #include "highscore/LightsOut.h"
    #include "highscore/Char_Underscore.h"
    #include "highscore/Char_A.h"
    #include "highscore/Char_B.h"
    #include "highscore/Char_C.h"
    #include "highscore/Char_D.h"
    #include "highscore/Char_E.h"
    #include "highscore/Char_F.h"
    #include "highscore/Char_G.h"
    #include "highscore/Char_H.h"
    #include "highscore/Char_I.h"
    #include "highscore/Char_J.h"
    #include "highscore/Char_K.h"
    #include "highscore/Char_L.h"
    #include "highscore/Char_M.h"
    #include "highscore/Char_N.h"
    #include "highscore/Char_O.h"
    #include "highscore/Char_P.h"
    #include "highscore/Char_Q.h"
    #include "highscore/Char_R.h"
    #include "highscore/Char_S.h"
    #include "highscore/Char_T.h"
    #include "highscore/Char_U.h"
    #include "highscore/Char_V.h"
    #include "highscore/Char_W.h"
    #include "highscore/Char_X.h"
    #include "highscore/Char_Y.h"
    #include "highscore/Char_Z.h"
    #include "highscore/Char_0.h"
    #include "highscore/Char_1.h"
    #include "highscore/Char_2.h"
    #include "highscore/Char_3.h"
    #include "highscore/Char_4.h"
    #include "highscore/Char_5.h"
    #include "highscore/Char_6.h"
    #include "highscore/Char_7.h"
    #include "highscore/Char_8.h"
    #include "highscore/Char_9.h"
    #include "highscore/Char_Dot.h"
    #include "highscore/Char_Space.h"
    #include "highscore/Char_Ex.h"
    
    #include "highscore/HS_Highlight.h"
       
    const uint8_t * const Tiles[] = { 
        
        TileDown0, TileUp0, TileDown1, TileUp1, TileDown2, TileUp2,
        
    }; 

    const uint8_t * const Ppot[] = { 
        
        Ppot_00, Ppot_01, Ppot_02, Ppot_03,
        
    };
    
    const uint8_t * const HS_Font[] = { 
        
        Char_Underscore, Char_A, Char_B, Char_C, Char_D, Char_E, Char_F, Char_G, Char_H, Char_I, Char_J, Char_K, Char_L, Char_M, 
        Char_N, Char_O, Char_P, Char_Q, Char_R, Char_S, Char_T, Char_U, Char_V, Char_W, Char_X, Char_Y, Char_Z, Char_0, Char_1,
        Char_2, Char_3, Char_4, Char_5, Char_6, Char_7, Char_8, Char_9, Char_Dot, Char_Space, 
        
    };
    
    const uint8_t * const Menu_Options[] = { 
        
        Menu_00, Menu_01, Menu_02,
        
    };
    
    const uint8_t * const LevelTexts[] = { 
        
        LevelText_00, LevelText_01, LevelText_02,
        
    };

};