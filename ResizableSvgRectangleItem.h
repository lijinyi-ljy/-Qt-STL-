#ifndef RESIZABLESVGRECTANGLEITEM_H
#define RESIZABLESVGRECTANGLEITEM_H

#include "ResizableSvgItem.h"

class ResizableSvgRectangleItem : public ResizableSvgItem
{
public:
    ResizableSvgRectangleItem(const QString& fileName, QGraphicsItem* parent = nullptr);
    bool isFillable() const override { return true; } // 矩形可填充
};
#endif // RESIZABLESVGRECTANGLEITEM_H
