#pragma once

namespace Util
{
	class DistanceUtil
	{
	public:
		DistanceUtil() = default;
		int CalculateDistance(int targetX, int targetY, int playerX, int playerY);
		~DistanceUtil() = default;
	};
}
