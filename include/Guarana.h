#pragma once
#include "Animal.h"
#include "Plant.h"

namespace world {
	namespace plants {

		class Guarana : public Plant {

		public:
			Guarana() : Plant() { initialize(); };
			Guarana(const int x, const int y, World *const world = nullptr) : Plant(x, y, world) { initialize(); };
			std::string getSpecies() const { return ("Guarana"); }
			void abnormalCollision(Organism* with);
		private:
			void createNewborn(const int x, const int y);
			void initialize() {
				power = 0;
				iD = 'u';
			}
		};
	}
}
