#pragma once
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

namespace world {

	class World;
	class Menu;


   class NoSpaceForNewbornException : public std::exception {
      public:
         NoSpaceForNewbornException(const char *msg) : message(msg) {}
         //******************************
         //* overriding what() function *
         //******************************
         const char* what() const noexcept {return message.c_str();}
      private:
         std::string message;
	};


	class Organism {
      friend class World;

      public:
         Organism() : Organism(0, 0, nullptr) {}
         Organism(const int x, const int y, World* const world = nullptr) : position(std::make_pair(x, y)) {
            objectCounter++;
            serialNo = objectCounter;
         }
         virtual ~Organism();

         void                    setWorld(World* const world);
         virtual void            action();
         virtual void            abnormalCollision(Organism* with) {}
         virtual void            collision(Organism* with) {}
         void                    show();

         int                     getInitiative() const { return initiative; }
         int                     getPower() const { return power; }
         int                     getSerialNo() const { return serialNo; }
         char                    getId() const { return iD; }
         virtual std::string     getSpecies() const = 0;
         std::pair<int, int>     getPosition();
         int                     getObjectCounter() const { return objectCounter;}
         bool                    getIsAlive() const {return isAlive_;}
         void                    setIsAlive(bool isAlive){isAlive_ = isAlive;}

         friend bool operator == (const Organism &a, const Organism &b);
         friend bool operator < (const Organism &a, const Organism &b);

      protected:

         virtual void      initialize() = 0;
         virtual void      eat(Organism& o);
         virtual void      combat(Organism &enemy);
         virtual void      createNewborn(const int x, const int y) = 0;
         virtual void      createNewborn(const int x, const int y, Organism *o);
         int               serialNo;
         std::pair<int, int> position;
         std::pair<int, int> previousPosition;
         bool isAlive_ = true;
         int power;
         int initiative = 0;
         char iD = ' ';
         World *world;
         static int objectCounter;

         void         setInitiative(int initiative) { this->initiative = initiative; };
         void         setPower(int power) { this->power = power; };
         void         setSerialNo(int serialNo) {this->serialNo = serialNo;}
         void         setPosition(int x, int y){position.first = x; position.second = y;};
         void         setObjectCounter(int counter) { objectCounter = counter;};

	};

} // End namespace World
