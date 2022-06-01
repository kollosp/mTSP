#ifndef MAPGRAPHGENERATOR_H
#define MAPGRAPHGENERATOR_H

#include <QPen>
#include <QWidget>
#include "Graph/GraphTypes.h"

#include <Monitor/Observable.h>

class MapGraphGenerator : public QWidget, public Observable
{
    Q_OBJECT

    bool bgLoaded;
    QImage bg;

    CPPGraph& graph;
    QPoint mousePositionWhenClick;
    QPoint anchor = QPoint(-100,-100);
    QPoint anchorMouseMove;

    unsigned int pointSize = 25;

    QPen vertexPen;
    QPen vertexLabelPen;
    QPen edgePen;

    //operation variables
    /**
     * @brief activeVertex variable is used when vertex is moved. Selected (hovered) vertex's index is stored here
     */
    int activeVertex=-1;
    int contextVertex = -1;
    bool edgeAdding = false;
    bool enableBg = true;
    bool mouseMoveAnchor = false;
public:
    explicit MapGraphGenerator(CPPGraph &graph, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void customMenuRequested(QPoint pos);

    int hoverVertex(QPoint point);
    /**
     * @brief hoverRect chech if point is in bounding box created by p1 and p2
     * @param point
     * @param p1
     * @param p2
     * @return
     */
    int hoverRect(QPoint point, QPoint p1, QPoint p2);

    //create custom menu
    void onBGContextRequested(QPoint pos);

    void printVertex(QPainter& painter, const CPPVertex &v, unsigned int index);
    void printEdge(QPainter& painter, const CPPVertex &v1, const CPPVertex &v2, int value);
    void loadImage(QString fileName = "");

    void updateAll();

    bool& enableBackground() noexcept;
    bool enableBackground() const noexcept;
    void disableBackground();
signals:

public slots:
    void onAddVertexClicked();
    void onRemoveVertexClicked();
    void onAddEdgeClicked();
};

#endif // MAPGRAPHGENERATOR_H
