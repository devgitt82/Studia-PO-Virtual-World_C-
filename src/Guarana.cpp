#include "Guarana.h"

namespace world {
	namespace plants {

		void Guarana::createNewborn(const int x, const int y) {
			Organism::createNewborn(x, y, new Guarana(x, y));
		}
      //********************************
      //* Guarana increases power by 3 *
      //********************************
		void Guarana::abnormalCollision(Organism* with) {
			auto animal = dynamic_cast<animals::Animal*>(with);
			animal->increasePower(3);
		}

	}
}
