#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include "CanvasWidget.h" 

class FileManager : public QObject
{
    Q_OBJECT

public:
    explicit FileManager(CanvasWidget* canvas, QObject* parent = nullptr); // 修改构造函数
    ~FileManager();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void clearCanvas(); 

private:
    CanvasWidget* m_canvas; 
};

#endif // FILEMANAGER_H
