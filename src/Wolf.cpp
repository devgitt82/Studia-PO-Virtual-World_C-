#include "Wolf.h"

namespace world {
	namespace animals {

		void Wolf::createNewborn(const int x, const int y) {
			Organism::createNewborn(x, y, new Wolf(x, y));
		}
	}
}
