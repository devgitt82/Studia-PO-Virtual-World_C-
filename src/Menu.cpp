#include "Menu.h"

namespace world{

Menu::Menu(){}
Menu::~Menu(){}

//********************
//* Main Menu layout *
//********************
void Menu::showMainMenu() {
   int y = 2;
   gotoXY(N + 5, y++);
   std::cout<<("Press: \n");
   gotoXY(N + 5, y++);
   std::cout<<("n - next round");
   gotoXY(N + 5, y++);
   std::cout<<("s - save game");
   gotoXY(N + 5, y++);
   std::cout<<("r - save game and return to main menu");
   gotoXY(N + 5, y++);
   std::cout<<("q - exit game without saving and return to main menu");
}


//*****************
//* internal menu *
//*****************
char Menu::showStartMenu() {
   //***************************************
   //* console looks better without cursor *
   //***************************************
   hideCursor();
   showBox();
   gotoXY(N + 5, 0);
   std::cout<<("Welcome to Virtual World by s178201 - Michal Scibisz");
   int y = 2;
   gotoXY(N + 5, y++);
   std::cout<<("Press: \n");
   gotoXY(N + 5, y++);
   std::cout<<("n - new game");
   gotoXY(N + 5, y++);
   std::cout<<("l - load previous game from file");
   gotoXY(N + 5, y++);
   std::cout<<("q - quit");
   char c;
   c = getch();
   system("cls");
   return c;
}

//***********************************************************
//* set world size to adjust stars and layout in the future *
//***********************************************************
void Menu::setN(int N){
    this->N = N;
}


//********
// stars *
//********
void Menu::showBox() {
   Menu::gotoXY(0,0);
   for (int i=0; i<N+2; i++)
       std::cout<<"*";
   for (int i=0; i<N+2; i++){
       Menu::gotoXY(0,i);
       std::cout<<"*";
       Menu::gotoXY(N+1,i);
       std::cout<<"*";
   }
   Menu::gotoXY(0,N+1);
   for (int i=0; i<N+2; i++)
       std::cout<<"*";
}

//******************
//* console gotoXY *
//******************
void Menu::gotoXY(short x, short y){
   HANDLE output= GetStdHandle(STD_OUTPUT_HANDLE);
   COORD pos = {x,y};
   SetConsoleCursorPosition(output, pos);
}


//*****************
//* hiding cursor *
//*****************
void Menu::hideCursor(){
   HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO hCCI;
   GetConsoleCursorInfo(hConsoleOut, &hCCI);
   hCCI.bVisible = FALSE;
   SetConsoleCursorInfo(hConsoleOut, &hCCI);
}


//******************
//* showing cursor *
//******************
void Menu::showCursor(){
   HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO hCCI;
   GetConsoleCursorInfo(hConsoleOut, &hCCI);
   hCCI.bVisible = TRUE;
   SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

}//end of namespace world
