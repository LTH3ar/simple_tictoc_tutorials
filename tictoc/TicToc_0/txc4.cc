#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Txc4 : public cSimpleModule
{
    private:
        int counter;

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Txc4);

void Txc4::initialize()
{
    counter = par("limit");
    // Am I Tic or Toc?
    if (par("sendMsgOnInit").boolValue() == true) {
        cMessage *msg = new cMessage("tictocMsg");
        EV << "Sending initial message\n";
        send(msg, "out");
    }
}

void Txc4::handleMessage(cMessage *msg)
{
    counter--;
    WATCH(counter);
    if (counter <= 0){
        EV << "Counter reach: 0";
        delete msg;
        finish();
    }
    else {
        EV << "Received message: " << msg->getName() << ", send back.";
        send(msg, "out"); // send out the message
    }
}
