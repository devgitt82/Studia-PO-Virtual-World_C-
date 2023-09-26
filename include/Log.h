#pragma once
#include <vector>
#include <algorithm>
#include<iostream>
#include <Menu.h>
#include <string>


namespace world{

class Menu;
class World;



class Event{
   public:
      //****************************
      //* friend ostream& operator *
      //****************************

      friend std::ostream & operator<< (std::ostream &out, Event &right);
      int counter = 1;
      int number = 1;
      std::string message;
   private:

} ;


class Log
{
    public:

        Log(){};
        virtual ~Log(){};
        void    addMessage(std::string &msg);
        void    addMessage(std::string &&msg);
        void    showEventLog(int x, int y);
        void    clearEventLog();

    protected:

    private:
        std::vector<Event> eventLog; // Lista zdarzeñ

};

}
