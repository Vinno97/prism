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
            constexpr SpritePath BACK = "img/Back.png";
            constexpr SpritePath GAME_OVER = "img/gameover.png";
            constexpr SpritePath NEW_GAME = "img/NewGameButton.png";
            constexpr SpritePath LEVEL_SLOT_FILLED = "img/LoadLevelButton_Filled.png";
            constexpr SpritePath LEVEL_SLOT_EMPTY = "img/LoadLevelButton_Empty.png";
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