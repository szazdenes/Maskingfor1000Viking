#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, &MainWindow::signalWriteToList, this, &MainWindow::slotWriteToList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_maskPushButton_clicked()
{
    QDir folder = QFileDialog::getExistingDirectory();
    QStringList nameList = folder.entryList(QStringList(), QDir::Files | QDir::NoDotAndDotDot);
    QStringList degList, maskList;
    foreach(QString name, nameList){
        if(name.contains("_gdeg.tiff"))
            degList.append(folder.absoluteFilePath(name));
        if(name.contains("_mask.tiff"))
            maskList.append(folder.absoluteFilePath(name));
    }
    emit signalWriteToList("Deglist and Masklist loaded.");

    if(degList.size() == maskList.size()){
        for(int i = 0; i < degList.size(); i++){
            QImage degIm(degList.at(i));
            QImage maskIm(maskList.at(i));
            QString maskedName = degList.at(i);
            maskedName.remove(".tiff");

            for(int j = 0; j < degIm.width(); j++){
                for(int k = 0; k < degIm.height(); k++){
                    QColor maskcol = maskIm.pixel(j,k);
                    if(maskcol == QColor(Qt::red))
                        degIm.setPixelColor(j,k, QColor(Qt::red));
                }
            }
            QApplication::processEvents();
            emit signalWriteToList("Masking " + QString::number(100*i/degList.size()) + " % ready.");
            degIm.save(maskedName + "_masked.tiff");
        }
    }
    else
        emit signalWriteToList("Different size of Deglist and Masklist");

    emit signalWriteToList("Masking ready.");

}

void MainWindow::slotWriteToList(QString string)
{
    if(ui->listWidget->count() > 100)
        ui->listWidget->takeItem(0);

    ui->listWidget->addItem(string);
    ui->listWidget->scrollToBottom();
}
