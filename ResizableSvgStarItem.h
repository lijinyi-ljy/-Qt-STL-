#ifndef RESIZABLESVGSTARITEM_H
#define RESIZABLESVGSTARITEM_H

#include "ResizableSvgItem.h"

class ResizableSvgStarItem : public ResizableSvgItem
{
public:
    ResizableSvgStarItem(const QString& fileName, QGraphicsItem* parent = nullptr);
    bool isFillable() const override { return true; } // 五角星可填充
};
#endif // RESIZABLESVGSTARITEM_H
