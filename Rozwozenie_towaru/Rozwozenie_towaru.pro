QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    About.cpp \
    Algorithms/Algorithm.cpp \
    Algorithms/BruteforceAlgorithm.cpp \
    Algorithms/GeneticAlgorithm.cpp \
    Algorithms/NearestNeighbor.cpp \
    Algorithms/TestAlgorithm.cpp \
    Graph/Edge.cpp \
    Graph/Graph.cpp \
    Graph/GraphProcessing.cpp \
    Graph/GraphTests.cpp \
    Graph/Tree.cpp \
    Graph/Vertex.cpp \
    GraphDrawing/GraphDrawingWidget.cpp \
    GraphGenerator/MapGraphGenerator.cpp \
    GraphWatcher.cpp \
    Graphgenerator.cpp \
    Helpers/DisplayArguments.cpp \
    Helpers/VectorInteger.cpp \
    Monitor/Observable.cpp \
    Monitor/Observer.cpp \
    Simulator.cpp \
    adresses.cpp \
    clients.cpp \
    csvreader.cpp \
    main.cpp \
    mainwindow.cpp \
    neighbour.cpp \
    trucks.cpp

HEADERS += \
    About.h \
    Algorithms/Algorithm.h \
    Algorithms/BruteforceAlgorithm.h \
    Algorithms/GeneticAlgorithm.h \
    Algorithms/NearestNeighbor.h \
    Algorithms/TestAlgorithm.h \
    Graph/Edge.h \
    Graph/Graph.h \
    Graph/GraphProcessing.h \
    Graph/GraphTests.h \
    Graph/GraphTypes.h \
    Graph/Tree.h \
    Graph/Vertex.h \
    GraphDrawing/GraphDrawingWidget.h \
    GraphGenerator/MapGraphGenerator.h \
    GraphWatcher.h \
    Graphgenerator.h \
    Helpers/DisplayArguments.h \
    Helpers/VectorInteger.h \
    Monitor/Observable.h \
    Monitor/Observer.h \
    Operators.h \
    Simulator.h \
    adresses.h \
    clients.h \
    csvreader.h \
    mainwindow.h \
    neighbour.h \
    trucks.h

FORMS += \
    About.ui \
    Graphgenerator.ui \
    Simulator.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
