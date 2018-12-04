#include "Util/AdvertisementSystem.h"
#include "Util/FileSystem.h"
#include <time.h>

namespace Util {

	std::string AdvertisementSystem::RandomAdvertisement()
	{
		FileSystem fs;
		std::vector<std::string> filenames = fs.getFilenamesInDirectory("img/advertisements");
		
		// Deze seed kan uiteindelijk weg
		srand(time(NULL));
		int randomIndex = rand() % filenames.size();

		return filenames[randomIndex].c_str();
	}

}