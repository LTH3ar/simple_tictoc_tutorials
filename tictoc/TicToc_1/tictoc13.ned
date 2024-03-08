simple Txc13
{
    parameters:
        @display("i=block/routing");
    gates:
        inout gate[];  // declare two way connections
}

network Tictoc13
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        tic[6]: Txc13;
    connections:
        tic[0].gate++ <--> Channel <--> tic[1].gate++;

        tic[1].gate++ <--> Channel <--> tic[2].gate++;

        tic[1].gate++ <--> Channel <--> tic[4].gate++;

        tic[4].gate++ <--> Channel <--> tic[3].gate++;

        tic[4].gate++ <--> Channel <--> tic[5].gate++;
}