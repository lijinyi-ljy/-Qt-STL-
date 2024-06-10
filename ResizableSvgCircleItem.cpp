#include "ResizableSvgCircleItem.h"

ResizableSvgCircleItem::ResizableSvgCircleItem(const QString& fileName, QGraphicsItem* parent)
    : ResizableSvgItem(fileName, parent) {
    setElementId("circle"); // 指定要操作的元素ID
}
