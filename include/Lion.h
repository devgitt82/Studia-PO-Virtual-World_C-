#pragma once
#include "Animal.h"

namespace world {
	namespace animals {

		class Lion : public Animal
		{
		public:
			Lion() : Animal() { initialize(); }
			Lion(const int x, const int y, World *const world = nullptr) : Animal(x, y, world) { initialize(); }
			~Lion() {};
			std::string getSpecies() const { return ("Lion"); }

		private:
			enum DIRECTIONS { LEFT = -1, RIGHT = 1, UP = -1, DOWN = 1 };
			virtual bool isCombatAllowed(Animal *enemy);
			void createNewborn(const int x, const int y);
			bool isSteady = true;
			void initialize() {
				iD = 'L';
				power = 11;
				initiative = 7;
			}
		};

	}
}
