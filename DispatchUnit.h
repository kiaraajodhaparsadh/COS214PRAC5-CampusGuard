// concrete command

class ResponseComponent; // recievers
class ResponseAction;    // command interface

class DispatchUnit : public ResponseAction
{
private:
    ResponseComponent *reciever;

public:
    DispatchUnit();
    ~DispatchUnit();
    void execute();
};
