#pragma once
#include "Plant.h"

namespace world {
	namespace plants {

		class Grass : public Plant
		{
		public:
			Grass() : Plant() { initialize(); };
			Grass(const int x, const int y, World *const world = nullptr) : Plant(x, y, world) { initialize(); };
			std::string getSpecies() const { return ("Grass"); }
		private:
			void createNewborn(const int x, const int y);
			void initialize() {
				power = 0;
				iD = 'g';
			}
		};
	}
}
