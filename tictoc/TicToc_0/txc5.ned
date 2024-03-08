simple Txc5
{
    parameters:
        @display("i=block/routing");
        bool sendMsgOnInit = default(false);
        int limit = default(5);
        
    gates:
        input in;
        output out;
}


simple Tic5 extends Txc5
{
    parameters:
        sendMsgOnInit = true;
        @display("i=,blue");
}

simple Toc5 extends Txc5
{
    parameters:
        sendMsgOnInit = false;
        @display("i=,red");
}

network Tictoc5
{
    submodules:
        tic: Tic5;
        toc: Toc5;
    connections:
        tic.out --> {  delay = 100ms; } --> toc.in;
        tic.in <-- {  delay = 100ms; } <-- toc.out;
}