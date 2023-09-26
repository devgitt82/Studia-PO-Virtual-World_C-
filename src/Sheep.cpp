#include "Sheep.h"

namespace world {
	namespace animals {

		void Sheep::createNewborn(const int x, const int y) {
			Organism::createNewborn(x, y, new Sheep(x, y));
		}
	}
}
