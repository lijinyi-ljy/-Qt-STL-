#include "ResizableSvgStarItem.h"

ResizableSvgStarItem::ResizableSvgStarItem(const QString& fileName, QGraphicsItem* parent)
    : ResizableSvgItem(fileName, parent) {
    setElementId("star"); // 指定要操作的元素ID
}
