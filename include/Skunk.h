#pragma once
#include "Animal.h"
#include "World.h"

namespace world {
	namespace animals {

		class Skunk : public Animal
		{
		public:
			Skunk() : Animal() { initialize(); }
			Skunk(const int x, const int y, World *const world = nullptr) : Animal(x, y, world) { initialize(); }
			~Skunk() {};
			virtual bool isCombatAllowed(Animal *enemy);
			virtual void collision(Organism* with);
			std::string    getSpecies() const { return ("Skunk"); }

		private:
			bool isSteady = true;
			void           createNewborn(const int x, const int y);
			void           initialize() {
         iD = 'X';
			power = 2;
			initiative = 3;
			}

		};

	}
}

