#pragma once

#include "Component.h"

#include "Math/Vector2.h"

namespace ECS {
	namespace Components {
		struct PositionComponent : Component {
			PositionComponent() = default;
			PositionComponent(double x_, double y_) : x(x_), y(y_) { };
			PositionComponent(double x_, double y_, double z_) : x(x_), y(y_), z(z_) { };

			/// <summary>
			///	The position in units
			/// </summary>
			double x{ 0 };

			// NOLINTNEXTLINE(google-explicit-constructor)
			operator Math::Vector2d() const { return Math::Vector2d{x, y}; }

            // NOLINTNEXTLINE(google-explicit-constructor)
            PositionComponent(Math::Vector2d& vector) : x(vector.x), y(vector.y) {
            };
			/// <summary>
			///	The position in units
			/// </summary>
			double y{ 0 };

			double z{ 0 };
            std::unique_ptr<Component> clone() override {
                auto component = std::make_unique<PositionComponent>();
                component->y = y;
                component->x = x;
				component->z = z;
                return component;
            }
        };
    }
}
