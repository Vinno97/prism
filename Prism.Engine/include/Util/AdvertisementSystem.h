#pragma once
#include <string>
#include <vector>

namespace Util {
	class AdvertisementSystem
	{
	public:
		AdvertisementSystem() = default;
		~AdvertisementSystem() = default;
		std::string RandomAdvertisement();
	};
}