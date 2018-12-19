#pragma once

#include "WorldSelectionState.h"

namespace States {
class LevelSelectionState : public WorldSelectionState {
public:
    LevelSelectionState() : WorldSelectionState(Variables::Resources::LEVELS) {
    }
};
}