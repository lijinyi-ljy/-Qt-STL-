#ifndef RESIZABLESVGLINEITEM_H
#define RESIZABLESVGLINEITEM_H

#include "ResizableSvgItem.h"

class ResizableSvgLineItem : public ResizableSvgItem
{
public:
    ResizableSvgLineItem(const QString& fileName, QGraphicsItem* parent = nullptr);
};

#endif // RESIZABLESVGLINEITEM_H
