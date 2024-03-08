#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Toc9 : public cSimpleModule
{
    protected:
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Toc9);

void Toc9::handleMessage(cMessage *msg)
{
    if (uniform(0, 1) < 0.1) {
        EV << "\"losing\" message.\n";
        bubble("message lost");
        delete msg;
    }
    else {
        EV << "Sending back same message as confirmation.\n";
        send(msg, "out");
    }
}


class Tic9 : public Toc9 {
    private:
        simtime_t timeout;  // timeout
        cMessage *timeoutEvent = nullptr;

    public:
        virtual ~Tic9();

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Tic9);

Tic9::~Tic9()
{
    cancelAndDelete(timeoutEvent);
}

void Tic9::initialize()
{
    // Initialize variables.
    timeout = 1.0;
    timeoutEvent = new cMessage("timeoutEvent");

    // Generate and send initial message.
    EV << "Sending initial message\n";
    cMessage *msg = new cMessage("tictocMsg");
    send(msg, "out");
    scheduleAt(simTime()+timeout, timeoutEvent);
}

void Tic9::handleMessage(cMessage *msg)
{
    if (msg == timeoutEvent) {
        // If we receive the timeout event, that means the packet hasn't
        // arrived in time and we have to re-send it.
        EV << "Timeout expired, resending message and restarting timer\n";
        cMessage *newMsg = new cMessage("tictocMsg");
        send(newMsg, "out");
        scheduleAt(simTime()+timeout, timeoutEvent);
    }
    else {  // message arrived
            // Confirmation received -- delete the received message and cancel
            // the timeout event.
        EV << "Timer cancelled.\n";
        cancelEvent(timeoutEvent);
        delete msg;

        // Ready to send another one.
        cMessage *newMsg = new cMessage("tictocMsg");
        send(newMsg, "out");
        scheduleAt(simTime()+timeout, timeoutEvent);
    }
}
