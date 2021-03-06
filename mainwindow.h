#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define Pi 3.1415926536

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QColor>
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QPainter>
#include <QPen>
#include <QVector2D>

#include "sourceandtargetdialog.h"
#include "setsourceandtargetdialog.h"

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
    void slotSourceAndTarget(QStringList sourceList);
    void slotGetSourceAndTarget(QString source, QString target);


    void on_logPushButton_clicked();

    void on_sunPushButton_clicked();

    void on_removePushButton_clicked();

    void on_replacePushButton_clicked();

    void on_chSubhorizonPushButton_clicked();

    void on_ultimateResultsPushButton_clicked();

    void on_averagedUltimateResultsPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString SourceFolder, targetFolder;

};

#endif // MAINWINDOW_H
