#ifndef GRAPHDRAWINGWIDGET_H
#define GRAPHDRAWINGWIDGET_H

#include <QPen>
#include <QWidget>

#include "Graph/GraphTypes.h"
#include "Helpers/DisplayArguments.h"

class GraphDrawingWidget : public QWidget
{
    Q_OBJECT

    CPPGraph& graph;

    int pointSize = 25;

    QPen artificialVertexPen;
    QBrush artificialVertexBrush;
    QPen vertexPen;
    QBrush vertexBrush;
    QPen vertexLabelPen;
    QPen edgePen;

    QPoint p0;
    QPoint margin;

    DisplayArgument displayArgument;
    std::vector<QColor> colors = {QColor(255,0,0,155),QColor(255,255,0,155),QColor(0,255,0,155),QColor(0,255,255,155),QColor(0,0,255,155)};


public:
    explicit GraphDrawingWidget(CPPGraph &graph, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    void drawGraph(QPainter &painter);
    void drawCompleteGraph(QPainter &painter, unsigned int vertices);

    void drawDisplayArguments(QPainter &painter);

    void printVertex(QPainter &painter, const CPPVertex &v, unsigned int index);
    void printEdge(QPainter &painter, const CPPVertex &v1, const CPPVertex &v2, int value);
    void printShiftedEdge(QPainter &painter, const CPPVertex &v1, const CPPVertex &v2, int xShift=0, int yShift=0);
    void printArtificialVertex(QPainter &painter, const CPPVertex &v, unsigned int index);

    void setDisplayArguments(const DisplayArgument &ds);
signals:

};

#endif // GRAPHDRAWINGWIDGET_H
