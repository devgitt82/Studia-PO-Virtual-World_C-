#include "World.h"

namespace world {

   //******************
   //* game main loop *
   //******************
   void World::startGame() {
      char c;
      do {
         c = menu_.showStartMenu();
         switch(c){
            case 'n':
               startNewGame();
               break;
            case 'l':
               loadGame();
               break;
            case 'q':
               std::cout<<"Bye Bye\n\n\n";
               break;
            default:
               break;
            }
      }
      while (c != 'q');
   }


   //******************
   //* start new game *
   //******************
   char World::startNewGame() {
      //**************************
      // initial game parameters *
      //**************************
      menu_.setN(N);
      initializeOrganism<animals::Skunk>();
      initializeOrganism<animals::Lion>();
      initializeOrganism<animals::Wolf>();
      initializeOrganism<animals::Sheep>();
      initializeOrganism<animals::Fox>();
      initializeOrganism<plants::Grass>();
      initializeOrganism<plants::Guarana>();
      initializeOrganism<plants::Thorn>();
      continueGame();
      return 'q';
   }


   //*********************
   // continue game loop *
   //*********************
   void World::continueGame(){
      char c;
      system("cls");
      showWorld();
      do {
         //**********************
         // show stars and menu *
         //**********************
         menu_.showBox();
         menu_.showMainMenu();
         menu_.gotoXY(N+5,0);
         std::cout<<"Turn no: "<<turnNumber_;
         c = getch();
         if (c == 'n') nextTurn();
         if (c == 's') saveGame() ;
         if (c == 'r') {saveGame(); c = 'q';}

      }
      while (c != 'q');
      //***************
      //* free memory *
      //***************
      clearOrganisms();
      //**********************
      //* reset turn counter *
      //**********************
      turnNumber_ = 0;
      system("cls");
   }


   //*************
   //* next turn *
   //*************
   void World::nextTurn() {
      turnNumber_++;
      //***************************************************************************************
      //* sort against initiative and serialNo - lambda expression instead of bool operator < *
      //***************************************************************************************
      std::sort(organisms.begin(), organisms.end(),[](Organism* a, Organism*  b) -> bool{
         if (a->getInitiative() != b->getInitiative())
            return a->getInitiative() > b->getInitiative();
         else
            return a->getSerialNo() < b->getSerialNo();
      });
      //******************************************
      //* perform action for each alive organism *
      //******************************************
      for (auto organism: organisms){
         if (organism->getIsAlive())
            organism->action();
         //***************************
         //* and check for collision *
         //***************************
         for (unsigned int i = 0; i < organisms.size(); i++) {
            //******************************************************************************************
            //* collision exist if same coordinates, not same organism & only between living organisms *
            //******************************************************************************************
            if (organism->getPosition() == organisms[i]->getPosition() && organism != organisms[i] && organisms[i]->getIsAlive()) {
               organism->collision(organisms[i]);
            }
         }
      }
      //***************************************
      //* all defeated organism to be deleted *
      //***************************************
      deleteDefeated();
      //*****************
      //* update screen *
      //*****************
      showWorld();
   }


   //******************
   //* get World size *
   //******************
   int World:: getN() const {
      return N;
   }


   //******************
   //* set World size *
   //******************
   void World::setN (const int N) {
       this->N = N;
   }


   //****************************************************
   //* update log - returning reference to object field *
   //****************************************************
   Log& World::updateLog() {
      return log_;


   }
   //***************************************************
   //* add organism if space in the world is available *
   //***************************************************
   void World::addNewOrganism(Organism* newOrganism) {
      if (isClear(newOrganism->getPosition().first, newOrganism->getPosition().second)) {
         newOrganism->setWorld(this);
         newBorns.push_back((Organism*)(newOrganism));
      }
   }


   //********************************************
   //* check if space in the world is available *
   //********************************************
   bool World::isClear(const int x, const int y) {
      if (x < 0 || y < 0 || x >= N || y >= N)
         return false;
      const auto tempPosition = std::make_pair(x, y);
      auto predicate = [&tempPosition](Organism* o) {
         return o->getPosition() == tempPosition;
      };
      return  std::none_of(organisms.begin(), organisms.end(), predicate)
              && std::none_of(newBorns.begin(), newBorns.end(), predicate);
   }


   //*********************************************************
   //* check if space in the world is prescribed to newBorns *
   //*********************************************************
   bool World::isClearFromNewBorns(const int x, const int y) {
      const auto tempPosition = std::make_pair(x, y);
      auto predicate = [&tempPosition](Organism* o) {
         return o->getPosition() == tempPosition;
      };
      return std::none_of(newBorns.begin(), newBorns.end(), predicate);
   }


   //***************************************************************************************************
   //* checking if space in the world is not occupied by stronger organism & not prescribed to newBorns*
   //***************************************************************************************************
   bool World::isClearFromStronger(const int x, const int y, const Organism* organism) {
      if (x < 0 || y < 0 || x >= N || y >= N )
         return false;
      const auto tempPosition = std::make_pair(x, y);
      int tempPower = organism->getPower();
      auto predicate = [&tempPosition, &tempPower](Organism* o){
         if ((o->getPosition() == tempPosition) && (o->getPower() > tempPower))
            return false;
         else
            return true;
      };
      return  std::any_of(organisms.begin(), organisms.end(), predicate)
              && std::none_of(newBorns.begin(), newBorns.end(), predicate);
   }


   //***************************************************************
   //* adding defeated organism pointer to defeatedOrganism vector *
   //***************************************************************
   void World::addToDefeatedAfterKilling(const Organism &winner, const Organism &defeated) {
      log_.addMessage(winner.getSpecies() + " kills " + defeated.getSpecies());
      defeatedOrganisms.push_back(defeated.getSerialNo());
   }


   //************************************************************
   //* adding eated organism pointer to defeatedOrganism vector *
   //************************************************************
   void World::addToDeafetedAfterEating(const Organism &animal, const Organism &plant) {
      std::string description = animal.getSpecies() + " eats " + plant.getSpecies();
      log_.addMessage(description);
      defeatedOrganisms.push_back(plant.getSerialNo());
   }


   //*************************************************************************
   //* removing defeated organisms from "organisms" vector and memory freeing*
   //*************************************************************************
   void World::deleteDefeated() {
      //********************************************
      //* delete elements from "organisms" vector: *
      //********************************************
      organisms.erase(
         //**************************************************************************************
         //* starting deletion from elements removed on the back of the "organisms" vector and  *
         //* matching the serialNo of "deafeatedOrganisms" vector                               *
         //**************************************************************************************
         std::remove_if( organisms.begin(), organisms.end(), [this](Organism* element){
            return std::any_of (defeatedOrganisms.begin(), defeatedOrganisms.end(), [&element](int serialNumber) {
               if ( element->getSerialNo() == serialNumber) {
                  //******************************************************
                  //* free memory of deleted object to avoid memory leak *
                  //******************************************************
                  delete element;
                  return true;
               }
               else
                  return false;});
            })
         //******************************************************
         //* deletion finish with the end of "organisms" vector *
         //******************************************************
         ,organisms.end());
      //**************************************
      //* reset of defeatedOrganisms" vector *
      //**************************************
      defeatedOrganisms.clear();
   }


   //*****************************************
   //* adding newborns to "organisms" vector *
   //*****************************************
   void World::addNewborns() {
      for (auto &newOrganism : newBorns) organisms.push_back(newOrganism);
      newBorns.clear();
   }


   //****************************************
   //* displays current layout of organisms *
   //****************************************
   void World::showOrganisms() {
      std::for_each(organisms.begin(), organisms.end(), [](Organism* organism) { organism->show();});
   }


   //****************************************
   //* displays current layout of the world *
   //****************************************
   void World::showWorld() {
      system("cls");
      addNewborns();
      showOrganisms();
      log_.showEventLog(N+5, 10);
      log_.clearEventLog();
   }


   //******************************************
   // Clear "organisms" vector & free memory: *
   //******************************************
   void World::clearOrganisms(){
         //******************************
         //* free memory to avoid leaks *
         //******************************
         for_each(organisms.begin(), organisms.end(), [] (Organism* temp){delete temp;});
         //*******************************
         //* reset of "organisms" vector *
         //*******************************
         organisms.erase(organisms.begin(), organisms.end());
   }

   //*******************************************************************
   // get pointer to Organism which serialNo matches the searched one: *
   //*******************************************************************
   Organism* World::getBySerialNo(const int serialNo) {
         auto elementIteratora = std::find_if(organisms.begin(), organisms.end(), [&serialNo] (Organism* o) {
            return o->getSerialNo() == serialNo;
         });
         Organism* matchingOrganism = *elementIteratora;
         return matchingOrganism;
   }


   //*************
   //* Game Save *
   //*************
   void World::saveGame()
   {
      std::fstream file;
      Menu::gotoXY(1,N+3);
      std::cout << "Please enter the file:";
      Menu::gotoXY(1,N+4);
      //*****************************
      //* it looks nice with cursor *
      //*****************************
      menu_.showCursor();
      std::string name;
      //*******************
      //* enter file name *
      //*******************
      std::cin>>name;
      menu_.hideCursor();
      file.open(name, std::ios::out | std::ios::trunc);
      //********************************************************************************
      //* save turnnumber, world size, quantity of organisms, last serialNo prescribed *
      //********************************************************************************
      file << this->turnNumber_<<"\n";
      file << this->N<< "\n";
      int i = organisms.size();
      int j = (*organisms[0]).getObjectCounter();
      file << i << "\n";
      file << j << "\n";
      //*********************************
      //* save details of each organism *
      //*********************************
      std::for_each(organisms.begin(), organisms.end(), [&file](Organism* o){
            file << o->getId() << " ";
            file << o->getSerialNo() << " ";
            file << o->getPower() << " ";
            file << o->getInitiative() << " ";
            file << o->getPosition().first << " ";
            file << o->getPosition().second << " ";
       });
       log_.clearEventLog();
       log_.addMessage("Game saved !!!");
       showWorld();
   }


   //*************
   //* Load Game*
   //*************
   void World::loadGame()
   {
      Organism* temp;
      std::fstream file;
      Menu::gotoXY(0,0);
      std::cout << "Please enter the file name\n";
      menu_.showCursor();
      std::string name;
      std::cin >> name;
      menu_.hideCursor();
      //****************************
      //* check if file is correct *
      //****************************
      try {
         file.open(name, std::ios::in);
         if (!file.good())
            throw name;
         //*******************************
         //* load world setup and status *
         //*******************************
         file >> this->turnNumber_;
         file >> this->N;
         int i = 0;
         int j = 0;
         file >> i;
         file >> j;

         char SYMBOL ;
         int serialNo;
         int power;
         int initiative;
         int x;
         int y;
         //**********************************
         //* load details of each organisms *
         //**********************************
         for (int j = 0; j < i; j++){
            file >> SYMBOL>> serialNo >> power >> initiative>>x>>y;
            switch(SYMBOL){
               case 'X':
                  temp = new animals::Skunk;
                  break;
               case 'F':
                  temp = new animals::Fox;
                  break;
               case 'L':
                  temp = new animals::Lion;
                  break;
               case 'S':
                  temp = new animals::Sheep;
                  break;
               case 'W':
                  temp = new animals::Wolf;
                  break;
               case 'g':
                  temp = new plants::Grass;
                  break;
               case 'u':
                  temp = new plants::Guarana;
                  break;
               case 't':
                  temp = new plants::Thorn;
                  break;
               default:
                  break;
            }
            temp->setSerialNo(serialNo);
            temp->setPower(power);
            temp->setInitiative(initiative);
            temp->setPosition(x, y);
            //*******************************************
            //* add loaded organism to "newBorns" vector"
            //*******************************************
            addNewOrganism(temp);
         }
         //********************************************************************
         //* shift all organisms from "newBorns" vector to "organisms" vector *
         //*******************************************************************
         addNewborns();
         //************************************************
         // set static figure of last prescribed serialNo *
         //************************************************
         (*organisms[0]).setObjectCounter (j);
         log_.addMessage("Game Loaded !!!");
         continueGame();
      }
      //****************************
      // if incorrect file loaded: *
      //****************************
      catch (std::string name){
         system("cls");
         Menu::gotoXY(0,N+3);
         std::cout<<" Cannot open file: " + name;
     }
   }

} // End namespace World
