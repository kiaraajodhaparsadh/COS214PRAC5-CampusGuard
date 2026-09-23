// command participant

class ResponseAction
{
public:
    ResponseAction() = default;
    virtual ~ResponseAction() = default;

    virtual void execute() = 0; // pure virtual function that all concrete commands will implement
};
