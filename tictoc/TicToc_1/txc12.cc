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
class Txc12 : public cSimpleModule
{
    private:
        int destination = 2;

    protected:
        virtual void forwardMessage(cMessage *msg);
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txc12);

void Txc12::initialize()
{
    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        char msgname[20];
        sprintf(msgname, "tic-%d", getIndex());
        cMessage *msg = new cMessage(msgname);
        scheduleAt(0.0, msg);
    }
}

void Txc12::handleMessage(cMessage *msg)
{
    if (getIndex() == destination) {
        // Message arrived.
        EV << "Message " << msg << " arrived.\n";
        delete msg;
        finish();
    }
    else {
        forwardMessage(msg);
    }
}

void Txc12::forwardMessage(cMessage *msg)
{
    // check received node: how many connections does it have? (outgoing)
    int n = gateSize("gate$o");

    /** if there are more than 2 outgoing connections, and one of them is the node that
     * the message came from, send the message to the other node, put more priority on the
     * node with index closest to the destination node.
     * This can be done by checking the index of nodes that connect to the current node holding
     * the message, and then sending the message to the node with the index closest to the
     * destination node.
     */

    /**
     * if there is only one outgoing connection, send the message to that node.
     */

    int k = intuniform(0, n-1);
    if (n < 2) {
        EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
        send(msg, "gate$o", k);
    }
    else if (n >= 2) {
        int closestIndex = 0;
        int closestDistance = 0;
        for (int i = 0; i < n; i++) {
            if (i != k) {
                int distance = abs(destination - i);
                if (i == 0) {
                    closestDistance = distance;
                    closestIndex = i;
                }
                else if (distance < closestDistance) {
                    closestDistance = distance;
                    closestIndex = i;
                }
            }
        }
        EV << "Forwarding message " << msg << " on gate[" << closestIndex << "]\n";
        send(msg, "gate$o", closestIndex);
    }
    
}
