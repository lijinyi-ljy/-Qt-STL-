#include "ResizableSvgRectangleItem.h"

ResizableSvgRectangleItem::ResizableSvgRectangleItem(const QString& fileName, QGraphicsItem* parent)
    : ResizableSvgItem(fileName, parent) {
    setElementId("rect"); // 指定要操作的元素ID
}
