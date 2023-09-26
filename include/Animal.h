#pragma once
#include "Organism.h"
#include "Plant.h"

namespace world {
	namespace animals {

		class NotAnAnimalException : public std::exception {
            public:
                NotAnAnimalException(const char *info) : message(info) {}
                NotAnAnimalException(const std::string &info) : message(info) {}


            private:
                std::string message;
        };


		class Animal : public Organism
		{
         public:
            Animal() : Organism() { previousPosition = position; };
            Animal(const int x, const int y, World *const world = nullptr) : Organism(x, y, world) { previousPosition = position; };
            virtual void action();
            virtual void abnormalCollision(Organism* with) {};
            void collision(Organism* with);
            void increasePower(int by) { power += by; };
            void decreasePower(int by) { power -= by; };
            virtual void moveBack();
            virtual void moveAway();
            virtual void moveX(const int direction);
            virtual void moveY(const int direction);

         protected:
            enum DIRECTIONS {  LEFT = -1, RIGHT = 1, UP = -1, DOWN = 1 };
            virtual bool isCombatAllowed(Animal *enemy) { return true; }
            virtual void eat(Organism *plant);
		};

	}
}
