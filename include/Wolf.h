#pragma once
#include "Animal.h"

namespace world {
	namespace animals {

		class Wolf : public Animal{
		   public:
            Wolf() : Animal() { initialize(); }
            Wolf(const int x, const int y, World *const world = nullptr) : Animal(x, y, world) { initialize(); }
            ~Wolf() {};
            std::string  getSpecies() const { return ("Wolf"); }

         private:
            void  createNewborn(const int x, const int y);
            void initialize() {
               iD = 'W';
               power = 9;
               initiative = 5;
            }
      };
	}
}
