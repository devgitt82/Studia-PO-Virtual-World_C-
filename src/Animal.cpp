#include "Animal.h"
#include "World.h"
#include <string>
#include <typeinfo>


namespace world {
	namespace animals {

//**************************************************************
//* moving LEFT/RIGHT - long moves (more than 1 field included *
//**************************************************************
void Animal::moveX(const int direction) {
   previousPosition = position;
   //***************
   //* moving LEFT *
   //***************
   if (direction < 0) {
      for (int i = -direction; i >= 1; --i) {
         if (position.first - i >= 0) {
            position.first -= i;
            break;
         }
      }
   }
   //***************
   //* moving RIGHT *
   //***************
   else {
      for (int i = direction; i >= 1; --i) {
         if (position.first + i < world->getN()) {
            position.first += i;
            break;
         }
      }
   }
}


//************************************************************
//* moving UP/DOWN - long moves (more than 1 field included) *
//************************************************************
void Animal::moveY(const int direction) {
   //*************
   //* moving UP *
   //*************
   previousPosition = position;
   if (direction < 0) {
      for (int i = -direction; i >= 1; --i) {
         if (position.second - i >= 0) {
            position.second -= i;
            break;
         }
      }
   }
   //*************
   //* moving DOWN *
   //*************
   else {
      for (int i = direction; i >= 1; --i) {
         if (position.second + i < world->getN()) {
            position.second += i;
            break;
         }
      }
   }
}


//******************************************************************************************************
//* checking if there is a an empty field available nearby - free from existing organisms and newBorns *
//******************************************************************************************************
void Animal::moveAway(){
   //************************
   //* checking on the LEFT *
   //************************
   if (world->isClear(position.first - 1, position.second)
   &&  (world->isClearFromNewBorns(position.first - 1, position.second)))
      position.first--;
   //************************
   //* checking on the RIGHT *
   //************************
   else if ((world->isClear(position.first + 1, position.second))
   &&  (world->isClearFromNewBorns(position.first + 1, position.second)))
      position.first++;
   //******************
   //* checking ABOVE *
   //******************
   else if ((world->isClear(position.first, position.second - 1))
   &&  (world->isClearFromNewBorns(position.first, position.second-1)))
      position.second--;
   //******************
   //* checking BELOW *
   //******************
   else if ((world->isClear(position.first, position.second + 1))
   &&  (world->isClearFromNewBorns(position.first, position.second+1)))
      position.second++;
}


//********************
//* ANIMAL IS MOVING *
//********************
void Animal::action(){
   //**********************************************
   //* 25% chance to move in particular direction *
   //**********************************************
   auto randomFigure = rand() % 4;
   //**********************
   //* MOVING TO THE LEFT *
   //**********************
   if ((randomFigure == 0) && world->isClearFromNewBorns(position.first-1, position.second))
      moveX(LEFT);
      //***********************
      //* MOVING TO THE RIGHT *
      //***********************
   else if ((randomFigure == 1) && world->isClearFromNewBorns(position.first+1, position.second))
      moveX(RIGHT);
   //*************
   //* MOVING UP *
   //*************
   else if ((randomFigure == 2) && world->isClearFromNewBorns(position.first, position.second-1))
      moveY(UP);
   //***************
   //* MOVING DOWN *
   //***************
   else if ((randomFigure == 3) && world->isClearFromNewBorns(position.first, position.second+1))
      moveY(DOWN);
}


//******************************************
//* collision with other organism happened *
//******************************************
void Animal::collision(Organism* with) {
   //*********************************
   //* same spicies - multiplication *
   //*********************************
   try {
      if (getId() == with->getId()) {
         //********************************************
         //* animal is moving back where he came from *
         //********************************************
         position = previousPosition;

                  //*******************************************************
                  //* checking if newborn can show up next to 1st animal: *
                  //*******************************************************

         //*****************************
         //* on the LEFT of 1st animal *
         //*****************************
         if (world->isClear(position.first - 1, position.second)  )
            createNewborn(position.first - 1, position.second);
         //******************************
         //* on the RIGHT of 1st animal *
         //******************************
         else if (world->isClear(position.first + 1, position.second))
            createNewborn(position.first + 1, position.second);
         //********************
         //* ABOVE 1st animal *
         //********************
         else if (world->isClear(position.first, position.second - 1))
            createNewborn(position.first, position.second - 1);
         //********************
         //* BELOW 1st animal *
         //********************
         else if (world->isClear(position.first, position.second + 1))
            createNewborn(position.first, position.second + 1);

                   //*******************************************************
                   //* checking if newborn can show up next to 2nd animal: *
                   //*******************************************************

         //*****************************
         //* on the LEFT of 2nd animal *
         //*****************************
         else if (world->isClear( (with->getPosition().first) - 1 , (with->getPosition().second)))
            createNewborn ((with->getPosition().first) - 1 , (with->getPosition().second) );
         //******************************
         //* on the RIGHT of 2nd animal *
         //******************************
         else if (world->isClear(with->getPosition().first + 1 , with->getPosition().second))
            createNewborn(with->getPosition().first + 1, getPosition().second );
         //********************
         //* ABOVE 2nd animal *
         //********************
         else if (world->isClear(with->getPosition().first, with->getPosition().second - 1))
            createNewborn(with->getPosition().first, getPosition().second - 1);
         //********************
         //* BELOW 2nd animal *
         //********************
         else if (world->isClear(with->getPosition().first, with->getPosition().second + 1))
            createNewborn(with->getPosition().first, getPosition().second + 1);
         //*************************************
         //* if no space available for newborn *
         //*************************************
         else
            throw NoSpaceForNewbornException("No space for newborns of: ");
         //**************************
         //* if no exception thrown *
         //**************************
         world->updateLog().addMessage(getSpecies()+" multiplies");
      }
      //************************
      //* if different spicies *
      //************************
      else {
         //**********************************************
         //* checcking if different spicie ia an animal *
         //**********************************************
         try {
            Animal* enemy = dynamic_cast<Animal*>(with);
            if (enemy == nullptr)
               throw std::bad_cast();
                        //*****************
                        //* if not thrown: *
                        //*****************

            //***************************************************
            // check if if they should fight against each other *
            //***************************************************
            if (isCombatAllowed(enemy) && enemy->isCombatAllowed(this)) {
               combat(*with);
            }
            //**********************************************
            //* if they shouldn't then abnormal collision: *
            //**********************************************
            else {
               abnormalCollision(with);
               with->abnormalCollision(this);
            }
         }
         //*********************************************************
         //* not animal exception caught - it means  it is a plant *
         //*********************************************************
         catch (const std::bad_cast &e) {
            eat(with);
         }
      }
   }
   //****************************
   //* if no space for newborns *
   //****************************
   catch (NoSpaceForNewbornException &newException){
      world->updateLog().addMessage(newException.what() + getSpecies());
   }
}// end of collision


//**********
//* eating *
//**********
void Animal::eat(Organism *plant) {
   Organism::eat(*plant);
}
//************************************
//* moving back to previous position *
//************************************
void Animal::moveBack() {
   position = previousPosition;
}

	} // End namespace Animals
} // End namespace World
