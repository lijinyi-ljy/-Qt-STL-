#include "MainWindow.h"
#include <QFormLayout>
#include <QInputDialog>
#include <QColorDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    // 设置主窗口大小
    resize(1000, 600);

    // 初始化画布控件
    canvasWidget = new CanvasWidget(this);
    canvasWidget->setStyleSheet("background-color: white;"); // 设置画布背景为白色

    // 初始化 FileManager，传递 canvasWidget
    fileManager = new FileManager(canvasWidget, this);

    // 创建右侧参数框
    createParameterBox();

    // 创建布局
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(canvasWidget, 4); // 占布局的4/5
    mainLayout->addWidget(parameterWidget, 1); // 占布局的1/5
    setCentralWidget(centralWidget);

    // 设置主窗口背景颜色为灰色
    setStyleSheet("QMainWindow { background-color: gray; }"); // 仅设置主窗口的背景颜色

    // 创建菜单栏
    createMenu();

    // 创建工具栏
    createToolbar();
}

MainWindow::~MainWindow()
{
    delete fileManager;
    delete canvasWidget;
    delete toolbar;
    delete parameterWidget;
    // 不需要手动删除 colorDialog，因为它是 parameterWidget 的子控件，会自动被删除
}

void MainWindow::createMenu()
{
    QMenuBar* bar = menuBar();
    setMenuBar(bar);

    QMenu* fileMenu = bar->addMenu("文件");

    QAction* newAction = fileMenu->addAction("新建");
    connect(newAction, &QAction::triggered, fileManager, &FileManager::clearCanvas); // 新建按钮调用清空画布槽函数

    QAction* openAction = fileMenu->addAction("打开");
    connect(openAction, &QAction::triggered, fileManager, &FileManager::openFile);

    QAction* saveAction = fileMenu->addAction("保存");
    connect(saveAction, &QAction::triggered, fileManager, &FileManager::saveFile);
}

void MainWindow::createToolbar()
{
    toolbar = new QToolBar("工具栏", this);
    addToolBar(Qt::LeftToolBarArea, toolbar);

    QAction* lineAction = toolbar->addAction("直线");
    connect(lineAction, &QAction::triggered, this, &MainWindow::drawLine);

    QAction* circleAction = toolbar->addAction("圆形");
    connect(circleAction, &QAction::triggered, this, &MainWindow::drawCircle);

    QAction* rectangleAction = toolbar->addAction("矩形");
    connect(rectangleAction, &QAction::triggered, this, &MainWindow::drawRectangle);

    QAction* polygonAction = toolbar->addAction("五边形");
    connect(polygonAction, &QAction::triggered, this, &MainWindow::drawPolygon);

    QAction* starAction = toolbar->addAction("五角星");
    connect(starAction, &QAction::triggered, this, &MainWindow::drawStar);

}

void MainWindow::changeCanvasColor()
{
    QColor selectedColor = colorDialog->selectedColor();
    QString colorStyle = QString("background-color: %1;").arg(selectedColor.name());
    canvasWidget->setStyleSheet(colorStyle);
}

void MainWindow::createParameterBox()
{
    parameterWidget = new QWidget(this);
    parameterWidget->setStyleSheet("background-color: lightgray; color: black;");

    QVBoxLayout* mainLayout = new QVBoxLayout(parameterWidget);

    // 创建上半部分的布局
    QFormLayout* formLayout = new QFormLayout();
    QLabel* widthLabel = new QLabel("画布宽度", parameterWidget);
    canvasWidthLineEdit = new QLineEdit(parameterWidget);
    canvasWidthLineEdit->setText("600");
    formLayout->addRow(widthLabel, canvasWidthLineEdit);

    QLabel* heightLabel = new QLabel("画布高度", parameterWidget);
    canvasHeightLineEdit = new QLineEdit(parameterWidget);
    canvasHeightLineEdit->setText("400");
    formLayout->addRow(heightLabel, canvasHeightLineEdit);

    QLabel* canvasColorLabel = new QLabel("画布颜色", parameterWidget);
    colorButton = new QPushButton("选择颜色", parameterWidget);
    formLayout->addRow(canvasColorLabel, colorButton);

    mainLayout->addLayout(formLayout);

    colorDialog = new QColorDialog(parameterWidget);
    connect(colorButton, &QPushButton::clicked, colorDialog, &QColorDialog::show);
    connect(colorDialog, &QColorDialog::colorSelected, this, &MainWindow::changeCanvasColor);
    connect(canvasWidthLineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateCanvasSize);
    connect(canvasHeightLineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateCanvasSize);

    // 创建下半部分的“图形点亮”标签和按钮
    QHBoxLayout* shapeLightLayout = new QHBoxLayout();
    QLabel* shapeLightLabel = new QLabel("图形点亮", parameterWidget);
    lightUpButton = new QPushButton("选择颜色", parameterWidget);
    connect(lightUpButton, &QPushButton::clicked, this, &MainWindow::onLightUpButtonClicked);
    shapeLightLayout->addWidget(shapeLightLabel);
    shapeLightLayout->addWidget(lightUpButton);
    mainLayout->addLayout(shapeLightLayout);

    // 创建“更改边框颜色”按钮
    QHBoxLayout* borderColorLayout = new QHBoxLayout();
    QLabel* borderColorLabel = new QLabel("边框颜色", parameterWidget);
    borderColorButton = new QPushButton("选择颜色", parameterWidget);
    connect(borderColorButton, &QPushButton::clicked, this, &MainWindow::changeBorderColor);
    borderColorLayout->addWidget(borderColorLabel);
    borderColorLayout->addWidget(borderColorButton);
    mainLayout->addLayout(borderColorLayout);

    // 创建“更改边框宽度”按钮
    QHBoxLayout* borderWidthLayout = new QHBoxLayout();
    QLabel* borderWidthLabel = new QLabel("边框宽度", parameterWidget);
    borderWidthButton = new QPushButton("设置宽度", parameterWidget);
    connect(borderWidthButton, &QPushButton::clicked, this, &MainWindow::changeBorderWidth);
    borderWidthLayout->addWidget(borderWidthLabel);
    borderWidthLayout->addWidget(borderWidthButton);
    mainLayout->addLayout(borderWidthLayout);

    parameterWidget->setLayout(mainLayout);
}

void MainWindow::updateCanvasSize()
{
    bool widthOk, heightOk;
    int width = canvasWidthLineEdit->text().toInt(&widthOk);
    int height = canvasHeightLineEdit->text().toInt(&heightOk);
    if (widthOk && heightOk && width > 0 && height > 0) {
        canvasWidget->resize(width, height);
    }
}

void MainWindow::onLightUpButtonClicked()
{
    if (canvasWidget) {
        ResizableSvgItem* selectedItem = canvasWidget->getSelectedItem();
        if (selectedItem && selectedItem->isFillable()) {
            QColor color = QColorDialog::getColor(Qt::white, this, "选择颜色");
            if (color.isValid()) {
                selectedItem->fillSvgItem(color);
            }
        }
    }
}

void MainWindow::changeBorderColor()
{
    if (canvasWidget) {
        ResizableSvgItem* selectedItem = canvasWidget->getSelectedItem();
        if (selectedItem) {
            QColor color = QColorDialog::getColor(Qt::black, this, "选择边框颜色");
            if (color.isValid()) {
                selectedItem->setStrokeColor(color);
            }
        }
    }
}

void MainWindow::changeBorderWidth()
{
    if (canvasWidget) {
        ResizableSvgItem* selectedItem = canvasWidget->getSelectedItem();
        if (selectedItem) {
            bool ok;
            double width = QInputDialog::getDouble(this, "设置边框宽度", "请输入边框宽度:", 1.0, 0.1, 10.0, 1, &ok);
            if (ok) {
                selectedItem->setStrokeWidth(width);
            }
        }
    }
}

void MainWindow::drawLine()
{
    canvasWidget->addLineItem();
}

void MainWindow::drawCircle()
{
    canvasWidget->addCircleItem();
}

void MainWindow::drawRectangle()
{
    canvasWidget->addRectangleItem();
}

void MainWindow::drawPolygon()
{
    canvasWidget->addPolygonItem();
}

void MainWindow::drawStar()
{
    canvasWidget->addStarItem();
}
