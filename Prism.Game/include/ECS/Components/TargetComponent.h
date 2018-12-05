#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
    namespace Components {
        struct TargetComponent : Component {

            unsigned target;

            std::unique_ptr<Component> clone() override {
                return std::make_unique<TargetComponent>();
            }
        };
    }
}
