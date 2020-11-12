#ifndef SLIDENAVIGATOR_COMMUNICATOR_H
#define SLIDENAVIGATOR_COMMUNICATOR_H

#include "Controller.h"

class Controller;

class Communicator {

private:
    Controller controller;
    char currentCommand;

    void confirmReceived();

public:
    Communicator();
    bool hasNewCommand();
    void confirmComplete();
};


#endif //SLIDENAVIGATOR_COMMUNICATOR_H
