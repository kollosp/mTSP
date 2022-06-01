#include "GraphTests.h"

GraphTests::GraphTests()
{

}

void GraphTests::run()
{
    std::cout<<"Starting tests..."<<std::endl;
//    test1();
//    test2();
//    writeToFileTest();
//    displayTest();

    test5();
    std::cout<<"All tests passed"<<std::endl;
}

void GraphTests::test1()
{
    std::cout<<"TEST 1"<<std::endl;
    std::cout<<"scope: graph creation, edge definition and modification"<<std::endl;

    //init graph and use 'int' type as edge weight type
    std::cout<<"Integer graph Graph<int>"<<std::endl;
    Graph<int> graphI;

    //insert vertices
    graphI.pushbackVertex(10);
    graphI.pushbackVertex(Vertex<int>(1, 54, 89));

    testEqualValue("Size: ", graphI.size(), (unsigned)2);
    testEqualValue("modified edge from V0 to V1 is: ", graphI.edge(0,1).directValue(), 0);
    testEqualValue("modified edge from V1 to V0 is: ", graphI.edge(0,1 ).directValue(), 0);

    //set value for vertices
    graphI.edge(0,1) = 4;
    graphI.edge(1,0) = 6;

    //modified edge values
    //std::cout<<<<<<std::endl;
    testEqualValue("modified edge from V0 to V1 is: ", graphI.edge(0,1).directValue(), 4);
    testEqualValue("modified edge from V1 to V0 is: ", graphI.edge(1,0).directValue(), 6);

    std::cout<<"Float graph Graph<float>"<<std::endl;
    Graph<float> graphF;

    //insert vertices
    graphF.pushbackVertex();
    graphF.pushbackVertex();

    //set value for vertices
    graphF.edge(0,1) = 2.2;
    graphF.edge(1,0) = M_PI;

    //modified edge values
    testEqualValue("modified edge from V0 to V1 is: ", graphF.edge(0,1).directValue(), (float)2.2);
    testEqualValue("modified edge from V1 to V0 is: ", graphF.edge(1,0).directValue(), (float)M_PI);


    std::cout<<"TEST 1 done"<<std::endl;
}

void GraphTests::test2()
{

    std::cout<<"TEST 2"<<std::endl;
    std::cout<<"scope: bidirectional and selfretation"<<std::endl;

    //create bidirectional and not self related graph
    Graph<int> graphBi(true);
    testEqualValue("Check bidirectional flag", graphBi.bidirectionalFlag(), true);
    testEqualValue("Check selfRelation flag", graphBi.selfRelationFlag(), false);

    graphBi.pushbackVertex();
    graphBi.pushbackVertex();

    //set value of 0-1 edge and check
    graphBi.edge(0,1) = 4;
    testEqualValue("(1) check if e(0,1) == e(1,0)", graphBi.edge(0,1).directValue(), graphBi.edge(1,0).directValue());


    graphBi.bidirectionalFlag() = false;
    testEqualValue("Setting bidirectional flag to 0: ", graphBi.bidirectionalFlag(), false);

    graphBi.edge(1,0) = 8;
    testEqualValue("Modified edge value e(0,1)", graphBi.edge(0,1).directValue(), 4);
    testEqualValue("Modified edge value e(0,1)", graphBi.edge(1,0).directValue(), 8);


    graphBi.selfRelationFlag() = false;
    testEqualValue("Setting selfRelation flag to 0: ", graphBi.selfRelationFlag(), false);

    try {
        graphBi.edge(1,1);
        std::abort();
    } catch (...) {
        std::cout<<"[OK] When Selfrelation==false graphBi.edge(1,1) throws exception"<<std::endl;
    }

    graphBi.selfRelationFlag() = true;
    testEqualValue("Setting selfRelation flag to 1: ", graphBi.selfRelationFlag(), true);

    try {
        graphBi.edge(1,1) = 10;
        testEqualValue("Modified self edge value e(1,1)", graphBi.edge(1,1).directValue(), 10);

    } catch (...) {
        std::cout<<"[ERROR] When Selfrelation==true graphBi.edge(1,1) should not throw exception"<<std::endl;
        std::abort();
    }

    std::cout<<"TEST 2 done"<<std::endl;
}

void GraphTests::vertexTest()
{

    std::cout<<"TEST 1 Vertex"<<std::endl;

    Vertex<int> v;

    testEqualValue("Default x position", v.x(), 0);
    testEqualValue("Default y position", v.y(), 0);

    std::cout<<"TEST 2 done"<<std::endl;
}

void GraphTests::writeToFileTest()
{
    std::cout<<"TEST 3"<<std::endl;

    Graph<int> graphBi(true);

    //create complete 3v graph
    graphBi.pushbackVertex(2);
    graphBi.pushbackVertex(Vertex<int>(1, 45, 85));
    graphBi.pushbackVertex(Vertex<int>(1, 10, 21));
    graphBi.edge(0,1) = 3;
    graphBi.edge(1,2) = 4;
    graphBi.edge(2,0) = 5;

    std::cout<<graphBi<<std::endl;
    graphBi.writeToFile("graph.txt");

    Graph<int> graph2;
    graph2.readFromFile("graph.txt");

    std::cout<<graph2<<std::endl;

    testEqualValue("Check if loaded and original graphs are the same", graph2.toString(), graphBi.toString());

    std::cout<<"TEST 3 done"<<std::endl;
}

void GraphTests::displayTest()
{
    std::cout<<"TEST 4"<<std::endl;

    Graph<int> graphBi(true);

    //create complete 3v graph
    graphBi.pushbackVertex(2);
    graphBi.pushbackVertex(Vertex<int>(1, 45, 85));
    graphBi.pushbackVertex(Vertex<int>(1, 10, 21));
    graphBi.edge(0,1) = 3;
    graphBi.edge(1,2) = 4;
    graphBi.edge(2,0) = 5;

    std::cout<<graphBi<<std::endl;

    std::cout<<"TEST 4 done"<<std::endl;
}

void GraphTests::test5()
{
    std::cout<<"TEST 5"<<std::endl;

    Vertex<int> v;
    v.artificialFlag() = true;
    testEqualValue("Check if art flag set", v.artificialFlag(), true);
    v.artificialFlag() = false;
    testEqualValue("Check if art flag set", v.artificialFlag(), false);

    std::cout<<"TEST 5 done"<<std::endl;
}
