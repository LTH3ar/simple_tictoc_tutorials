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
        EV << "\"Losing\" message " << msg << endl;
        bubble("message lost");
        delete msg;
    }
    else {
        EV << msg << "Sending back same message as confirmation.\n";
        delete msg;
        send(new cMessage("ack"), "out");
    }
}


class Tic9 : public Toc9 {
    private:
        simtime_t timeout;  // timeout
        cMessage *timeoutEvent = nullptr;
        int seq;
        cMessage *message = nullptr;

    public:
        virtual ~Tic9();

    protected:
        virtual cMessage *generateNewMessage();
        virtual void sendCopyOf(cMessage *msg);
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
    seq = 0;
    timeout = 1.0;
    timeoutEvent = new cMessage("timeoutEvent");

    // Generate and send initial message.
    EV << "Sending initial message\n";
    message = generateNewMessage();
    sendCopyOf(message);
    scheduleAt(simTime()+timeout, timeoutEvent);
}

cMessage *Tic9::generateNewMessage()
{
    // Generate a message with a different name every time.
    char msgname[20];
    sprintf(msgname, "tic-%d", ++seq);
    cMessage *msg = new cMessage(msgname);
    return msg;
}

void Tic9::sendCopyOf(cMessage *msg)
{
    // Duplicate message and send the copy.
    cMessage *copy = (cMessage *)msg->dup();
    send(copy, "out");
}

void Tic9::handleMessage(cMessage *msg)
{
    if (msg == timeoutEvent) {
        // If we receive the timeout event, that means the packet hasn't
        // arrived in time and we have to re-send it.
        EV << "Timeout expired, resending message and restarting timer\n";
        sendCopyOf(message);
        scheduleAt(simTime()+timeout, timeoutEvent);
    }
    else {  // message arrived
            // Confirmation received -- delete the received message and cancel
            // the timeout event.
        EV << "Received: " << msg->getName() << "\n";
        delete msg;
        EV << "Timer cancelled.\n";
        cancelEvent(timeoutEvent);
        delete message;

        // Ready to send another one.
        message = generateNewMessage();
        sendCopyOf(message);
        scheduleAt(simTime()+timeout, timeoutEvent);
    }
}
