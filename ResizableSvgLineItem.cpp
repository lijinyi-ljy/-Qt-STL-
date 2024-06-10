#include "ResizableSvgLineItem.h"

ResizableSvgLineItem::ResizableSvgLineItem(const QString& fileName, QGraphicsItem* parent)
    : ResizableSvgItem(fileName, parent) {
    setElementId("line"); // 指定要操作的元素ID
}
