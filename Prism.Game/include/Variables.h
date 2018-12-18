#pragma once

#include <string>

namespace Variables {
    namespace Resources {
        typedef const char* ResourcePath;
        constexpr ResourcePath LEVELS = "levels";
        constexpr ResourcePath SAVES = "saves";
        constexpr ResourcePath SPRITES = "img";
        constexpr ResourcePath LEVEL_EXTENSION = ".json";

        namespace Sprites {
            typedef ResourcePath SpritePath;
            // TODO: Kijk of dit niet geconcatinate kunnen worden
            constexpr SpritePath PLAIN_BLACK = "img/Black.png";
            constexpr SpritePath PLAIN_WHITE = "img/White.png";
            constexpr SpritePath WHITE_BORDERED = "img/White_Bordered.png";
            constexpr SpritePath GAME_OVER = "img/gameover.png";
            constexpr SpritePath NEW_GAME = "img/NewGameButton.png";

	        constexpr SpritePath SELECT_LEVEL = "img/menus/normal/select_level.png";
	        constexpr SpritePath BACK = "img/menus/normal/Back.png";
	        constexpr SpritePath LEVEL_SLOT_FILLED = "img/menus/normal/LoadLevelButton_Filled.png";
	        constexpr SpritePath LEVEL_SLOT_EMPTY = "img/menus/normal/LoadLevelButton_Empty.png";
	        constexpr SpritePath PREVIOUS_BUTTON = "img/menus/normal/PreviousPageButton.png";
	        constexpr SpritePath PREVIOUS_BUTTON_DISABLED = "img/menus/normal/PreviousPageButton_Disabled.png";
	        constexpr SpritePath NEXT_BUTTON = "img/menus/normal/NextPageButton.png";
	        constexpr SpritePath NEXT_BUTTON_DISABLED = "img/menus/normal/NextPageButton_Disabled.png";
	        constexpr SpritePath BTN_NIGHTMARE_MODE = "img/menus/normal/nightmare_mode.png";

            namespace NightMare {
	            constexpr SpritePath SELECT_LEVEL = "img/menus/nightmare/select_level.png";
	            constexpr SpritePath BACK = "img/menus/nightmare/Back.png";
	            constexpr SpritePath BTN_NIGHTMARE_MODE = "img/menus/nightmare/nightmare_mode.png";
	            constexpr SpritePath LEVEL_SLOT_FILLED = "img/menus/nightmare/LoadLevelButton_Filled.png";
	            constexpr SpritePath LEVEL_SLOT_EMPTY = "img/menus/nightmare/LoadLevelButton_Empty.png";
	            constexpr SpritePath PREVIOUS_BUTTON = "img/menus/nightmare/PreviousPageButton.png";
	            constexpr SpritePath PREVIOUS_BUTTON_DISABLED = "img/menus/nightmare/PreviousPageButton_Disabled.png";
	            constexpr SpritePath NEXT_BUTTON = "img/menus/nightmare/NextPageButton.png";
	            constexpr SpritePath NEXT_BUTTON_DISABLED = "img/menus/nightmare/NextPageButton_Disabled.png";
            }

        }
    }
    namespace Visual {
        namespace LevelSelection {
            constexpr int COLUMNS = 4;
            constexpr int ROWS = 2;
            constexpr float OUTER_MARGIN = .2f;
            constexpr float GRID_MARGIN = .05f;
        }
    }
}