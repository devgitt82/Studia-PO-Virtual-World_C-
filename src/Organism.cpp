#include "Organism.h"
#include "World.h"


namespace world {

//*******************************
//* static counter for SerialNo *
//*******************************
int Organism::objectCounter = 0;


Organism::~Organism(){}

//*********************************
//* prescribing organism to world *
//*********************************
void Organism::setWorld(World *const world) {
            this->world = world;
}

//******************
//* bool operators *
//******************
bool operator == (const Organism &a, const Organism &b) {
   return a.serialNo == b.serialNo;
}

bool operator < (const Organism& a, const Organism& b) {
   if (a.initiative != b.initiative)
      return a.initiative > b.initiative;
   else
      return a.serialNo < b.serialNo;
}

//************************************
//* get current position of organism *
//************************************
std::pair<int, int> Organism::getPosition(){
		return position;
}

//**********************************
//* organism behavior in each turn *
//**********************************
void Organism::action() {}


//***************************
//* Combat of two organisms *
//***************************
void Organism::combat(Organism& enemy){
   //**************************
   //* at first power decides *
   //**************************
   if (power > enemy.power) {
      world->addToDefeatedAfterKilling(*this, enemy);
      enemy.setIsAlive(false);
   }
   else if (power < enemy.power) {
      world->addToDefeatedAfterKilling(enemy, *this);
      setIsAlive(false);
   }
	//********************************************************************************
	//* if power the same - initiative decides - which means this organism has moved *
	//********************************************************************************
		else {
			if (initiative > enemy.initiative) {
			world->addToDefeatedAfterKilling(*this, enemy);
			enemy.setIsAlive(false);
		}
      else if (initiative < enemy.initiative) {
			world->addToDefeatedAfterKilling(enemy, *this);
			setIsAlive(false);
		}
      //*****************************************************
      //* if power & initiative the same - SerialNo decides *
      //*****************************************************
		else if (serialNo < enemy.getSerialNo()) {
         world->addToDefeatedAfterKilling(*this, enemy);
         enemy.setIsAlive(false);
		}
		else if (serialNo > enemy.getSerialNo()) {
         world->addToDefeatedAfterKilling(enemy, *this);
         setIsAlive(false);
      }
   }
}

//**************************************
//* show organism symbol on the screen *
//**************************************
void Organism::show() {
   Menu::gotoXY(position.first+1, position.second+1);
   std::cout << iD;
   Menu::gotoXY(0,24);
}


//******************************
//* create newborn of organism *
//******************************
void Organism::createNewborn(const int x, const int y, Organism *newOrganism) {
	world->addNewOrganism(newOrganism);
}


//******************************************************************************************************************
//* remove organism from world  and check if there is contraction of the eaten organism / plant or other in future *
//******************************************************************************************************************
void Organism::eat(Organism& organism) {
   world->addToDeafetedAfterEating(*this, organism);
   organism.setIsAlive(false);
   organism.abnormalCollision(this);
}

} // End namespace World
