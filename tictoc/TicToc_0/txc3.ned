simple Txc3
{
    parameters:
        @display("i=block/routing");
        
    gates:
        input in;
        output out;
}


network Tictoc3
{
    submodules:
        tic: Txc3{
            parameters:
                @display("i=,blue");
        }
        toc: Txc3{
            parameters:
                @display("i=,red");
        }
    connections:
        tic.out --> {  delay = 100ms; } --> toc.in;
        tic.in <-- {  delay = 100ms; } <-- toc.out;
}