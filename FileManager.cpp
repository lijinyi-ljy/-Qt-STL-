#include "FileManager.h"
#include <QDebug>

FileManager::FileManager(CanvasWidget* canvas, QObject* parent)
    : QObject(parent), m_canvas(canvas)
{
}

FileManager::~FileManager()
{
}

void FileManager::newFile()
{
    qDebug() << "新建文件";
    // 实现新建文件的逻辑
}

void FileManager::openFile()
{
    qDebug() << "打开文件";
    // 实现打开文件的逻辑
}

void FileManager::saveFile()
{
    qDebug() << "保存文件";
    // 实现保存文件的逻辑
}

void FileManager::clearCanvas()
{
    qDebug() << "清空画布";
    if (m_canvas) {
        m_canvas->clearCanvas();
    }
}
