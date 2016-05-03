#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QColor>
#include <QFile>
#include <QProcess>
#include <QRegExp>

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
    void signalSendConsoleCommand(QString dirPath, QString cmd);

private slots:
    void on_maskPushButton_clicked();
    void slotWriteToList(QString string);
    void on_movePushButton_clicked();
    void slotSendConsoleCommant(QString dirPath, QString cmd);


    void on_logPushButton_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
