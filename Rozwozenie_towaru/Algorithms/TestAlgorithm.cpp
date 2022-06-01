#include "TestAlgorithm.h"

#include <QThread>

TestAlgorithm::TestAlgorithm(CPPGraph &graph, DisplayArgument& displayArgument) : Algorithm(graph, displayArgument, "TestAlgorithm")
{
    addParam(ConfigParam("Loops", Algorithm::ConfigParam::NUMBER, "50"));
    addParam(ConfigParam("In the same time", Algorithm::ConfigParam::NUMBER, "1"));
}

TestAlgorithm::~TestAlgorithm()
{

}

void TestAlgorithm::run()
{
    for(int i=0;i<loops;++i){
        for(unsigned int j=0;j<graph().size();++j){
            graph().vertex(j).artificialFlag() = false;
        }

        unsigned int index = i % graph().size();
        graph().vertex(index).artificialFlag() = true;
        this->notify();
        QThread::msleep(100);
    }
}

void TestAlgorithm::applyParams() noexcept
{
    loops = QString::fromStdString(params().at(0).value()).toInt();
    sameTimeArtificial = QString::fromStdString(params().at(1).value()).toInt();
}
