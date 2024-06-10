#ifndef RESIZABLESVGITEM_H
#define RESIZABLESVGITEM_H

#include <QGraphicsSvgItem>
#include <QDomDocument>
#include <QColor>
#include <QGraphicsSceneMouseEvent>

class ResizableSvgItem : public QGraphicsSvgItem
{
public:
    ResizableSvgItem(const QString& fileName, QGraphicsItem* parent = nullptr);

    void fillSvgItem(const QColor& color);
    void setStrokeColor(const QColor& color);   
    void setStrokeWidth(double width);          
    virtual bool isFillable() const { return false; } // 默认不可填充
    QString elementId() const { return m_elementId; }
    void setElementId(const QString& id) { m_elementId = id; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    bool m_isResizing;
    QPointF m_lastMousePos;
    QRectF m_initialRect;
    QString m_svgFileName;
    QDomDocument m_domDocument;
    QString m_elementId;
};

#endif // RESIZABLESVGITEM_H
