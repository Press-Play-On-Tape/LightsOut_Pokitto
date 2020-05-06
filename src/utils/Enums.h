#pragma once

const uint8_t size[] = {5, 7, 9};

enum class GameStateType : uint32_t {
	SplashScreen_Activate,
	SplashScreen,
	TitleScreen_Activate,
	TitleScreen,
	PlayGame_Activate,
	PlayGame,
	HighScore_Activate,
	HighScore
};

enum class ControlMode : uint8_t {
    Game,
    Menu,
};


enum class MenuOption : uint8_t {
    NewGame,
    Reset,
    MainMenu
};

inline MenuOption &operator++(MenuOption &c ) {
    c = (c == MenuOption::MainMenu ? MenuOption::MainMenu : static_cast<MenuOption>( static_cast<uint8_t>(c) + 1 ));
    return c;
}

inline MenuOption operator++(MenuOption &c, int ) {
    MenuOption result = c;
    ++c;
    return result;
}

inline MenuOption &operator--(MenuOption &c ) {
    c = (c == MenuOption::NewGame ? MenuOption::NewGame : static_cast<MenuOption>( static_cast<uint8_t>(c) - 1 ));
    return c;
}

inline MenuOption operator--(MenuOption &c, int ) {
    MenuOption result = c;
    --c;
    return result;
}