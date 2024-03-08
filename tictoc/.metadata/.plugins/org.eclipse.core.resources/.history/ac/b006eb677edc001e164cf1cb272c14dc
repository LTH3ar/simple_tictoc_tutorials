#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Txc6 : public cSimpleModule
{
    private:
        int counter;
        cMessage *event = nullptr;
        cMessage *tictocMsg = nullptr;

    public:
        virtual ~Txc6();

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Txc6);

Txc6::~Txc6()
{
    //dispose dynamically allocated the obj
    cancelAndDelete(event);
    delete tictocMsg;
}

void Txc6::initialize()
{
    //create event obj use for timing
    event = new cMessage("event");

    //blank msg
    tictocMsg = nullptr;

    counter = par("limit");
    // Am I Tic or Toc?
    if (par("sendMsgOnInit").boolValue() == true) {
        EV << "Schedule initial message send t=5.0s\n";

        tictocMsg = new cMessage("tictocMsg");

        scheduleAt(5.0, event);
    }
}

void Txc6::handleMessage(cMessage *msg)
{
    counter--;
    WATCH(counter);
    if (counter <= 0){
        EV << "Counter reach: 0";
        delete msg;
        finish();
    }
    else {
        if (msg == event) {
            EV << "Wait period is over, sending back message\n";
            send(tictocMsg, "out");
            tictocMsg = nullptr;
        }
        else{
            EV << "Message arrived, starting to wait 1 sec...\n";
            tictocMsg = msg;
            scheduleAt(simTime()+1.0, event);
        }
    }
}
