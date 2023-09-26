#include "Skunk.h"


namespace world {
   namespace animals {

void  Skunk::createNewborn(const int x, const int y) {
      Organism::createNewborn(x, y, new Skunk(x, y));
}
//**********************************************************
//* if Skunk is attacked, it forces the enemy to move back *
//**********************************************************
bool Skunk::isCombatAllowed(Animal *enemy){
   if (isSteady == true) {
      enemy->moveBack();
      world->updateLog().addMessage("Skunk Odour coused: " + enemy->getSpecies()+" to move back");
      return false;
   }
   else
      return true;
}
//**********************************************************
//* if Skunk is attacking, it reduces the enemy power by 3 *
//**********************************************************
void Skunk::collision(Organism *with){
   isSteady = false;
   //*********************************************************
   //* check if the enemy is animal and of different spieces *
   //*********************************************************
   Animal* enemy = dynamic_cast<Animal*>(with);
      if ((enemy != nullptr) && (enemy->getId() != 'X')){
         //*******************
         //* if indeed it is *
         //*******************
         enemy->decreasePower(3);
         world->updateLog().addMessage("Skunk Odour reduced: " + enemy->getSpecies()+" power by 3");
      }
      Animal::collision(with);
      //******************************************************************
      //* make sure that after collision enemy restores its normal power *
      //******************************************************************
      if ((enemy != nullptr) && (enemy->getId() != 'X'))
         enemy->increasePower(3);
      isSteady = true;

}

   }   //end of namespace animals
}   //end namepace world
