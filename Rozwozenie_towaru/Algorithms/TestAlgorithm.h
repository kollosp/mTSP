#ifndef TESTALGORITHM_H
#define TESTALGORITHM_H

#include "Algorithm.h"

class TestAlgorithm : public Algorithm
{
    //configuration for algorithm
    int loops = 50;
    int sameTimeArtificial;

public:
    TestAlgorithm(CPPGraph &graph, DisplayArgument &displayArgument);
    ~TestAlgorithm();

    void run() override;

    virtual void applyParams() noexcept override;
};

#endif // TESTALGORITHM_H
