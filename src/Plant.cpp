#include "Plant.h"
#include "World.h"

namespace world {
	namespace plants {


//**********************************
//* 25% chances for multiplication *
//**********************************
void Plant::action() {
   if(rand() < RAND_MAX / 4) {
      multiply();
   }
}

//**************************************************************************************************
//* multiplication possible if position in the world is clear from existing organisms and newborns *
//**************************************************************************************************
void Plant::multiply() {
   if (world->isClear(position.first - 1, position.second)
   && (world->isClearFromNewBorns(position.first - 1, position.second)))
         createNewborn(position.first - 1, position.second);

   else if ((world->isClear(position.first + 1, position.second))
   && (world->isClearFromNewBorns(position.first + 1, position.second)))
         createNewborn(position.first + 1, position.second);

   else if ((world->isClear(position.first, position.second - 1))
   && (world->isClearFromNewBorns(position.first, position.second-1)))
         createNewborn(position.first, position.second - 1);

   else if ((world->isClear(position.first, position.second + 1))
   && (world->isClearFromNewBorns(position.first, position.second+1)))
         createNewborn(position.first, position.second + 1);
    }


	} // End namespace Plants
} // End namespace World
