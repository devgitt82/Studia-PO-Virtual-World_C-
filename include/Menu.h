#ifndef MENU_H
#define MENU_H
#include <windows.h>
#include<iostream>
#include <conio.h>

namespace world{
    class world;
    class Menu
    {
        public:
            Menu();
            virtual ~Menu();
            static void gotoXY(short x, short y);
            char showStartMenu();
            void showMainMenu();
            void showBox();
            static void hideCursor();
            static void showCursor();
            void setN(int N);

        private:
            int N=20;
    };
}
#endif // MENU_H
