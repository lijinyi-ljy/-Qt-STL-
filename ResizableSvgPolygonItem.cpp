#include "ResizableSvgPolygonItem.h"

ResizableSvgPolygonItem::ResizableSvgPolygonItem(const QString& fileName, QGraphicsItem* parent)
    : ResizableSvgItem(fileName, parent) {
    setElementId("polygon"); // 指定要操作的元素ID
}
