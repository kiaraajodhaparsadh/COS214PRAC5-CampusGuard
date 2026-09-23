#include "OperatorConsole.h"
#include <iostream>
OperatorConsole::~OperatorConsole()
{
    for (ResponseAction *command : commandHistory)
    {
        delete command;
    }
    commandHistory.clear();
}

void OperatorConsole::executeCommand(ResponseAction *command)
{
    if (command != nullptr)
    {
        std::cout << "[OpertorConsole] Executing operator command...\n";

        command->execute();

        // store the command in the vector after it executes
        commandHistory.push_back(command);
    }
}
