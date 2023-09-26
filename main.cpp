#include <ctime>
#include "World.h"

int main() {
	srand(time(nullptr));
   world::World world;
	world.startGame();
	return 0;
}

