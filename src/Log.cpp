#include <Log.h>


namespace world{

//**********************************************
//* ostream operator << for Event class object *
//**********************************************
std::ostream& operator << (std::ostream &out, Event &right){
   std::cout<<right.number<<") "<<right.message<<" (x"<<right.counter<<")";
   return out;
}

//*******************************
//* add new messages to the log *
//*******************************

void Log::addMessage(std::string &msg) {
        auto sameLogEntry = std::find_if(eventLog.begin(), eventLog.end(), [&msg](Event &event) { return event.message == msg; });   // #include <memory> for get
        //*******************************
        //* if new message is to be add *
        //*******************************
        if (sameLogEntry == eventLog.end()) {
            Event newEvent;
            newEvent.number = eventLog.size() +1;
            newEvent.message = msg;
            eventLog.push_back(newEvent);
        }
        //*****************************************************************
        //* otherwise increase the counter of the existing same log entry *
        //*****************************************************************
        else
            (*sameLogEntry).counter++;
    }
    void Log::addMessage(std::string &&msg) {
         auto sameLogEntry = std::find_if(eventLog.begin(), eventLog.end(), [&msg](Event &event) { return event.message == msg; });   // #include <memory> for get
        //*******************************
        //* if new message is to be add *
        //*******************************
        if (sameLogEntry == eventLog.end()) {
            Event newEvent;
            newEvent.number = eventLog.size() +1;
            newEvent.message = msg;
            eventLog.push_back(newEvent);
        }
        //****************************************************
        //* otherwise increase the counter of same log entry *
        //****************************************************
        else
            (*sameLogEntry).counter++;

    }
//*************************************************************
//* Show all entries of the log on the screen in position x,y *
//*************************************************************
void Log::showEventLog(int x, int y){
         Menu::gotoXY( x, y);
         std::cout<<"Event log:";
         std::for_each(eventLog.begin(), eventLog.end(), [&x,&y,this](Event &event) {
             y++;
             Menu::gotoXY(x, y);
             std::cout<<event;
         });
    }
//**********************
//* delete all entires *
//**********************
    void Log::clearEventLog(){
        eventLog.clear();
    }
} //end of namespace world
