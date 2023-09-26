#include "Grass.h"

namespace world {
	namespace plants {


      void Grass::createNewborn(const int x, const int y) {
         Organism::createNewborn(x, y, new Grass(x, y));
      }
	}
}
