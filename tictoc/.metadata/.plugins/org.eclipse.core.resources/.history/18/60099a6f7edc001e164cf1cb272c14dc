simple Txc6
{
    parameters:
        @display("i=block/routing");
        bool sendMsgOnInit = default(false);
        int limit = default(5);
        
    gates:
        input in;
        output out;
}


simple Tic6 extends Txc6
{
    parameters:
        sendMsgOnInit = true;
        @display("i=,blue");
}

simple Toc6 extends Txc6
{
    parameters:
        sendMsgOnInit = false;
        @display("i=,red");
}

network Tictoc6
{
    submodules:
        tic: Tic6;
        toc: Toc6;
    connections:
        tic.out --> {  delay = 100ms; } --> toc.in;
        tic.in <-- {  delay = 100ms; } <-- toc.out;
}