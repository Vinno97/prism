#pragma once

#include "Component.h"

#include "Math/Vector2.h"

namespace ECS {
    namespace Components {
        struct PositionComponent : Component {
            PositionComponent() = default;

            PositionComponent(double x_, double y_) : x(x_), y(y_) {
            };

            // NOLINTNEXTLINE(google-explicit-constructor)
            PositionComponent(Math::Vector2<double>& vector) : x(vector.x), y(vector.y) {
            };

            // NOLINTNEXTLINE(google-explicit-constructor)
            operator Math::Vector2<double>() const { return Math::Vector2<double>{x, y}; }

            /// <summary>
            ///	The position in units
            /// </summary>
            double x{0};

            /// <summary>
            ///	The position in units
            /// </summary>
            double y{0};

            std::unique_ptr<Component> clone() override {
                auto component = std::make_unique<PositionComponent>();
                component->x = x;
                component->y = y;
                return component;
            }
        };
    }
}
