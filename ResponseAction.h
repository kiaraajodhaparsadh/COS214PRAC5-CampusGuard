// command participant
#pragma once

class ResponseAction
{
public:
    ResponseAction() = default;
    virtual ~ResponseAction() = default;

    virtual void execute() = 0; // pure virtual function that all concrete commands will implement

    virtual void undo() = 0; // undoes command with memento
};
