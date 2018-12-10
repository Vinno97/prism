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
            constexpr SpritePath BACK = "img/Back.png";
            constexpr SpritePath GAME_OVER = "img/gameover.png";
            constexpr SpritePath NEW_GAME = "img/NewGameButton.png";
        }
    }
    namespace Visual {
        namespace LevelSelection {
            constexpr int COLUMNS = 4;
            constexpr int ROWS = 2;
            constexpr float OUTER_MARGIN = .1f;
            constexpr float GRID_MARGIN = .05f;
        }
    }
}