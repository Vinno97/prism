#include "Util/DistanceUtil.h"
#include <cmath>

namespace Util
{
	int DistanceUtil::CalculateDistance(int targetX, int targetY, int playerX, int playerY)
	{
		return sqrt(pow((targetX - playerX), 2.0) + pow((targetY - playerY), 2.0));
	}
}
