#ifndef SLIDENAVIGATOR_COMMUNICATOR_H
#define SLIDENAVIGATOR_COMMUNICATOR_H

#include "Controller.h"

class Controller;

class Communicator {

private:
    Controller controller;
    bool setNewCommand(char newCommand, int newPram);
    String commands = "HNPCFK";
    char currentCommand = 0;
    int commandPram = 0;

public:
    Communicator();
    bool hasNewCommand();
    int getCommandPram();
    char getCommand();
    void commandComplete();
};


#endif //SLIDENAVIGATOR_COMMUNICATOR_H
