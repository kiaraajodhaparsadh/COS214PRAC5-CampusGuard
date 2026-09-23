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

void OperatorConsole::undoLastCommand()
{
    if (commandHistory.empty())
    {
        std::cout << "[OperatorConsole] Error: No commands to undo.\n";
        return;
    }

    std::cout << "[OperatorConsole] Initiating system undo sequence...\n";

    ResponseAction *prevCommand = commandHistory.back();
    prevCommand->undo();

    // remove command from history.
    // if we want to implement redo later, wi do not need to delete it here
    commandHistory.pop_back();
    delete prevCommand;
}
