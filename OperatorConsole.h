#pragma once
#include "ResponseAction.h"
#include <vector>
// invoker
class OperatorConsole
{
private:
    std::vector<ResponseAction *> commandHistory; // stores all executed commands so we can potentially undo them all with memento

public:
    OperatorConsole() = default;
    ~OperatorConsole();

    void executeCommand(ResponseAction *command);
    void undoLastCommand(); // witht the help of memento
};
