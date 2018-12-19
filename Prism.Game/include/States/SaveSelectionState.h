#pragma once

#include "WorldSelectionState.h"

namespace States {
    class SaveSelectionState : public WorldSelectionState {
    public:
        SaveSelectionState() : WorldSelectionState(Variables::Resources::SAVES) {
        }
    };
}