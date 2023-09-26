#pragma once
#include "Animal.h"

namespace world {
	namespace animals {

		class Sheep : public Animal
		{
         public:
            Sheep() : Animal() { initialize(); }
            Sheep(const int x, const int y, World *const world = nullptr) : Animal(x, y, world) { initialize(); }
            ~Sheep() {};
            std::string getSpecies() const { return ("Sheep"); }

         private:
            void createNewborn(const int x, const int y);
            void initialize() {
               iD = 'S';
               power = 4;
               initiative = 4;
            }
		};
	}
}
