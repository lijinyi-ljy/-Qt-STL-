#ifndef RESIZABLESVGCIRCLEITEM_H
#define RESIZABLESVGCIRCLEITEM_H

#include "ResizableSvgItem.h"

class ResizableSvgCircleItem : public ResizableSvgItem
{
public:
    ResizableSvgCircleItem(const QString& fileName, QGraphicsItem* parent = nullptr);
    bool isFillable() const override { return true; } // 圆形可填充
};
#endif // RESIZABLESVGCIRCLEITEM_H
