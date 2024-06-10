#include "CanvasWidget.h"
#include <QVBoxLayout>
#include <QFile>

CanvasWidget::CanvasWidget(QWidget* parent)
    : QWidget(parent), view(new QGraphicsView(this)), scene(new QGraphicsScene(this)), selectedItem(nullptr)
{
    view->setScene(scene);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    // 连接场景的 selectionChanged 信号
    connect(scene, &QGraphicsScene::selectionChanged, this, [this]() {
        auto items = scene->selectedItems();
        if (!items.isEmpty()) {
            selectedItem = dynamic_cast<ResizableSvgItem*>(items.first());
        }
        else {
            selectedItem = nullptr;
        }
        });
}

CanvasWidget::~CanvasWidget()
{
    delete scene;
    delete view;
}

void CanvasWidget::addLineItem()
{
    QString svgContent = R"(
        <svg width="200" height="200" xmlns="http://www.w3.org/2000/svg">
            <line id="line" x1="10" y1="10" x2="190" y2="190" stroke="black" stroke-width="2"/>
        </svg>
    )";
    QString fileName = "line.svg";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(svgContent.toUtf8());
        file.close();
    }

    ResizableSvgLineItem* lineItem = new ResizableSvgLineItem(fileName);
    scene->addItem(lineItem);
}

void CanvasWidget::addCircleItem()
{
    
    QString svgContent = R"(
        <svg width="200" height="200" xmlns="http://www.w3.org/2000/svg">
            <circle id="circle" cx="100" cy="100" r="50" fill="none" stroke="black" />
        </svg>
    )";
    QString fileName = "circle.svg";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(svgContent.toUtf8());
        file.close();
    }

    ResizableSvgCircleItem* circleItem = new ResizableSvgCircleItem(fileName);
    scene->addItem(circleItem);
}

void CanvasWidget::addRectangleItem()
{
    QString svgContent = R"(
        <svg width="200" height="200" xmlns="http://www.w3.org/2000/svg">
            <rect id="rect" x="50" y="50" width="100" height="100" fill="none" stroke="black"/>
        </svg>
    )";
    QString fileName = "rectangle.svg";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(svgContent.toUtf8());
        file.close();
    }

    ResizableSvgRectangleItem* rectangleItem = new ResizableSvgRectangleItem(fileName);
    scene->addItem(rectangleItem);
}

void CanvasWidget::addPolygonItem()
{
    QString svgContent = R"(
        <svg width="200" height="200" xmlns="http://www.w3.org/2000/svg">
            <polygon id="polygon" points="100,10 170,60 140,140 60,140 30,60" fill="none" stroke="black" stroke-width="2"/>
        </svg>
    )";
    QString fileName = "polygon.svg";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(svgContent.toUtf8());
        file.close();
    }

    ResizableSvgPolygonItem* polygonItem = new ResizableSvgPolygonItem(fileName);
    scene->addItem(polygonItem);
}

void CanvasWidget::addStarItem()
{
    
    QString svgContent = R"(
        <svg width="200" height="200" xmlns="http://www.w3.org/2000/svg">
            <polygon id="star" points="100,10 40,198 190,78 10,78 160,198" fill="none" stroke="black" stroke-width="2"/>
        </svg>
    )";
    QString fileName = "star.svg";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(svgContent.toUtf8());
        file.close();
    }

    ResizableSvgStarItem* starItem = new ResizableSvgStarItem(fileName);
    scene->addItem(starItem);
}

void CanvasWidget::clearCanvas()
{
    scene->clear();
    selectedItem = nullptr;
}

void CanvasWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
}

ResizableSvgItem* CanvasWidget::getSelectedItem() const
{
    return selectedItem;
}
