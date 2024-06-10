#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QColorDialog>
#include <QToolBar>
#include "CanvasWidget.h"
#include "FileManager.h"
#include "QMenuBar"
#include <QInputDialog>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onLightUpButtonClicked();
    void changeCanvasColor();
    void updateCanvasSize();
    void drawLine();
    void drawCircle();
    void drawRectangle();
    void drawPolygon();
    void drawStar();
    void changeBorderColor();
    void changeBorderWidth();

private:
    void createMenu();
    void createToolbar();
    void createParameterBox();

    CanvasWidget* canvasWidget;
    FileManager* fileManager;
    QToolBar* toolbar;

    QWidget* parameterWidget;
    QVBoxLayout* parameterLayout;
    QLineEdit* canvasWidthLineEdit;
    QLineEdit* canvasHeightLineEdit;
    QPushButton* colorButton;
    QColorDialog* colorDialog;
    QPushButton* lightUpButton;
    QPushButton* borderColorButton;
    QPushButton* borderWidthButton;
};

#endif // MAINWINDOW_H
