#ifndef RESIZABLESVGPOLYGONITEM_H
#define RESIZABLESVGPOLYGONITEM_H

#include "ResizableSvgItem.h"

class ResizableSvgPolygonItem : public ResizableSvgItem
{
public:
    ResizableSvgPolygonItem(const QString& fileName, QGraphicsItem* parent = nullptr);
    bool isFillable() const override { return true; } // 多边形可填充
};
#endif // RESIZABLESVGPOLYGONITEM_H
