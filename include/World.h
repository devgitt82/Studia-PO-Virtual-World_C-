#pragma once
#include "Animals.h"
#include "Plants.h"
#include <Log.h>
#include <Menu.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ios>


namespace world {

	class World
	{
        friend class Organism;

        public:
            World(){};
            ~World(){};

            void         startGame();
            bool         isClear(const int x, const int y);
            bool         isClearFromNewBorns(const int x, const int y);
            bool         isClearFromStronger(const int x, const int y, const Organism* organism);
            int          getN() const;
            void         setN (const int N);
            Log&         updateLog();


        private:
            int                        turnNumber_ = 0;
            Menu                       menu_;
            Log                        log_;
            int                        N = 20;
            std::vector<Organism*>     organisms;
            std::vector<Organism*>     newBorns;
            std::vector<int>           defeatedOrganisms;

            char         startNewGame();
            void         continueGame();
            void         nextTurn();
            void         addToDefeatedAfterKilling(const Organism &winner, const Organism &defeated);
            void         addToDeafetedAfterEating(const Organism &animal, const Organism &plant);
            void         deleteDefeated();
            void         showOrganisms();
            void         showWorld();
            void         addNewborns();
            void         addNewOrganism(Organism* newOrganism);
            void         saveGame();
            void         loadGame();
            void         clearOrganisms();
            Organism*    getBySerialNo(const int serialNo);

            template <class T>
            void initializeOrganism() {
               for (int i = 0; i < 10; i++) {
                  T *temp = new T(rand() % N, rand() % N);
                  if (isClear(temp->getPosition().first, temp->getPosition().second)) {
                     addNewOrganism(temp);
                  }
                }
                addNewborns();
            }
   };
} //end of namespace world
