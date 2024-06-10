#include "ResizableSvgItem.h"
#include <QSvgRenderer>
#include <QFile>
#include <QTextStream>

ResizableSvgItem::ResizableSvgItem(const QString& fileName, QGraphicsItem* parent)
    : QGraphicsSvgItem(parent), m_isResizing(false), m_svgFileName(fileName)
{
    QSvgRenderer* renderer = new QSvgRenderer(fileName, this);
    setSharedRenderer(renderer);

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        m_domDocument.setContent(&file);
        file.close();
    }

    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
}

void ResizableSvgItem::fillSvgItem(const QColor& color)
{
    QDomElement root = m_domDocument.documentElement();
    QDomNodeList elements = root.elementsByTagName(elementId());

    for (int i = 0; i < elements.size(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (!element.isNull()) {
            element.setAttribute("fill", color.name());
        }
    }

    QFile file(m_svgFileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << m_domDocument.toString();
        file.close();
    }

    QSvgRenderer* renderer = new QSvgRenderer(m_svgFileName, this);
    setSharedRenderer(renderer);
}

void ResizableSvgItem::setStrokeColor(const QColor& color)
{
    QDomElement root = m_domDocument.documentElement();
    QDomNodeList elements = root.elementsByTagName(elementId());

    for (int i = 0; i < elements.size(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (!element.isNull()) {
            element.setAttribute("stroke", color.name());
        }
    }

    QFile file(m_svgFileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << m_domDocument.toString();
        file.close();
    }

    QSvgRenderer* renderer = new QSvgRenderer(m_svgFileName, this);
    setSharedRenderer(renderer);
}

void ResizableSvgItem::setStrokeWidth(double width)
{
    QDomElement root = m_domDocument.documentElement();
    QDomNodeList elements = root.elementsByTagName(elementId());

    for (int i = 0; i < elements.size(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (!element.isNull()) {
            element.setAttribute("stroke-width", QString::number(width));
        }
    }

    QFile file(m_svgFileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << m_domDocument.toString();
        file.close();
    }

    QSvgRenderer* renderer = new QSvgRenderer(m_svgFileName, this);
    setSharedRenderer(renderer);
}

void ResizableSvgItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        QRectF rect = boundingRect();
        QPointF pos = event->pos();
        if (rect.contains(pos)) {
            m_isResizing = (pos.x() > rect.width() - 10 && pos.y() > rect.height() - 10);
            m_lastMousePos = event->pos();
            m_initialRect = rect;
        }
    }
    QGraphicsSvgItem::mousePressEvent(event);
}

void ResizableSvgItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_isResizing) {
        QPointF delta = event->pos() - m_lastMousePos;
        QRectF newRect = m_initialRect.adjusted(0, 0, delta.x(), delta.y());
        if (newRect.width() > 10 && newRect.height() > 10) {
            QTransform transform;
            transform.scale(newRect.width() / m_initialRect.width(), newRect.height() / m_initialRect.height());
            setTransform(transform);
        }
    }
    else {
        QGraphicsSvgItem::mouseMoveEvent(event);
    }
}

void ResizableSvgItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_isResizing = false;
    }
    QGraphicsSvgItem::mouseReleaseEvent(event);
}
