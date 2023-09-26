#pragma once
#include "Plant.h"
#include "World.h"

namespace world {
	namespace plants {

		// Wilcze jagody
		class Thorn : public Plant {
         public:
            Thorn() : Plant() { initialize(); };
            Thorn(const int x, const int y, World *const world = nullptr) : Plant(x, y, world) { initialize(); };
            std::string getSpecies() const { return ("Thorn"); }

         private:
            void createNewborn(const int x, const int y);
            void action();
            void initialize() {
               power = 2;
               iD = 't';
            }
		};

   }
}
