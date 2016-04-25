#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void signalWriteToList(QString string);

private slots:
    void on_maskPushButton_clicked();
    void slotWriteToList(QString string);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
