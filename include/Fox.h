#pragma once
#include "Animal.h"

namespace world {
	namespace animals {

		class Fox : public Animal
		{
         public:
            Fox() : Animal() { initialize(); }
            Fox(const int x, const int y, World *const world = nullptr) : Animal(x, y, world) { initialize(); }
            ~Fox() {};
            std::string getSpecies() const { return ("Fox"); }

         private:
            bool isClearFromStronger(const int x, const int y);
            void moveX(const int direction);
            void moveY(const int direction);
            void createNewborn(const int x, const int y);
            void initialize() {
               iD = 'F';
               power = 3;
               initiative = 7;
            }
         };
	}
}
