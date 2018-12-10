#pragma once

#include <string>

namespace Variables {
    namespace Resources {
        constexpr const char *BASE_DIR = "res";
        constexpr const char *LEVELS = "levels";
        constexpr const char *SAVES = "saves";
        constexpr const char *LEVEL_EXTENSION = ".json";
    }

    namespace Visual {
        namespace LevelSelection {
            constexpr int COLUMNS = 4;
            constexpr int ROWS = 3;
            constexpr float OUTER_MARGIN = .1f;
            constexpr float GRID_MARGIN = .1f;
        }
    }
}