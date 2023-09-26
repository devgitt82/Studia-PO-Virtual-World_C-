#include "Thorn.h"


namespace world {
	namespace plants {

      void Thorn::createNewborn(const int x, const int y) {
         Organism::createNewborn(x, y, new Thorn(x, y));
      }

      //**************************
      //* thorn always multipies *
      //**************************
      void Thorn::action() {
         multiply();
      }


   }//end of namespace plants
}//end of namespace world
