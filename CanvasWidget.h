#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "ResizableSvgLineItem.h"
#include "ResizableSvgCircleItem.h"
#include "ResizableSvgRectangleItem.h"
#include "ResizableSvgPolygonItem.h"
#include "ResizableSvgStarItem.h"

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget* parent = nullptr);
    ~CanvasWidget();

    void addLineItem();
    void addCircleItem();
    void addRectangleItem();
    void addPolygonItem();
    void addStarItem();
    void clearCanvas(); // 清空画布方法
    ResizableSvgItem* getSelectedItem() const; // 获取当前选中的图形

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    ResizableSvgItem* selectedItem; // 当前选中的图形
};

#endif // CANVASWIDGET_H
