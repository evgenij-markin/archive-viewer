#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QVector>

#include "arch_info.h"
#include "mymodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT    
private:
    QHBoxLayout *layout{};
    QLabel      *label1{};
    QPushButton *btn1{};
    QTableView  *tableView{};
    QVBoxLayout *vlay{};
    QWidget     *wdg{};

    QVector<Archive_info> arch_contents;

public:
    int32_t minizip_list(const char *path);

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnBtn1Clicked();

};
#endif // MAINWINDOW_H
