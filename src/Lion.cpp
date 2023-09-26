#include "Lion.h"
#include "World.h"

namespace world {
	namespace animals {

		void  Lion::createNewborn(const int x, const int y) {
               Organism::createNewborn(x, y, new Lion(x, y));
		}

      //******************************************************************************************************
      //* Lion is normally  too strong for weak animals, if Lion hasn't moved, they shall be afraid to enter  *
      //******************************************************************************************************
      bool  Lion::isCombatAllowed(Animal *enemy) {
               if ((initiative < enemy->getInitiative()) && (enemy->getPower() < 5 )){
                  enemy->moveBack();
                  world->updateLog().addMessage("Lion is too strong for: " + enemy->getSpecies());
                  return false;
               }
               else
                  return true;
      }
	}
}



