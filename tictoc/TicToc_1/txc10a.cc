#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

/**
 * Let's make it more interesting by using several (n) `tic' modules,
 * and connecting every module to every other. For now, let's keep it
 * simple what they do: module 0 generates a message, and the others
 * keep tossing it around in preset directions until it arrives at
 * module index 6.
 */
class Txc10a : public cSimpleModule
{
    protected:
        virtual void forwardMessage(cMessage *msg);
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txc10a);

void Txc10a::initialize()
{
    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        char msgname[20];
        sprintf(msgname, "tic-%d", getIndex());
        cMessage *msg = new cMessage(msgname);
        scheduleAt(0.0, msg);
    }
}

void Txc10a::handleMessage(cMessage *msg)
{
    if (getIndex() == 2) {
        // Message arrived.
        EV << "Message " << msg << " arrived.\n";
        delete msg;
        finish();
    }
    else {
        forwardMessage(msg);
    }
}

void Txc10a::forwardMessage(cMessage *msg)
{
    // check received node: how many connections does it have? (outgoing)
    int n = gateSize("out");

    // if there are more than 2 outgoing connections, and one of them is the node that
    // the message came from, send the message to the other node
    // if there are less than 2 outgoing connections, send the message to the only other node
    // 
    int k = intuniform(0, n-1);
    if (k == getIndex()) {
        k = (k + 1) % n;
    }

    EV << "Forwarding message " << msg << " on port out[" << k << "]\n";
    send(msg, "out", k);
}
