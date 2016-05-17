#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, &MainWindow::signalWriteToList, this, &MainWindow::slotWriteToList);
    connect(this, &MainWindow::signalSendConsoleCommand, this, &MainWindow::slotSendConsoleCommant);
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

    QImage bigMask("/home/denes/Documents/Labor/Viking/1000Viking/MaskingAndMovingToFolders/nagymaszk.png");

    if(degList.size() == maskList.size()){
        for(int i = 0; i < degList.size(); i++){
            QImage degIm(degList.at(i));
            QImage degIm2(degList.at(i));
            QImage maskIm(maskList.at(i));
            QString maskedName = degList.at(i);
            maskedName.remove(".tiff");

            for(int j = 0; j < degIm.width(); j++){
                for(int k = 0; k < degIm.height(); k++){
                    QColor maskcol = maskIm.pixel(j,k);
                    QColor degcol = degIm.pixel(j,k);
                    QColor bigMaskcol = bigMask.pixel(j,k);
                    if(maskcol == QColor(Qt::red) || bigMaskcol == QColor(Qt::red) || degcol.blackF() >= 0.9 || degcol.blackF() <= 0.05){
                        if((degcol.blackF() >= 0.9 || degcol.blackF() <= 0.05) && maskcol != QColor(Qt::red) && bigMaskcol != QColor(Qt::red))
                            degIm2.setPixelColor(j,k, QColor(Qt::green));
                        degIm.setPixelColor(j,k, QColor(Qt::red));
                    }
                }
            }
            QApplication::processEvents();
            if(100*i/degList.size() != 100*(i+1)/degList.size())
                emit signalWriteToList("Masking " + QString::number(100*i/degList.size()) + " % ready.");
            degIm.save(maskedName + "_masked.tiff");
            degIm2.save(maskedName + "_motionartefact_masked.tiff");
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

void MainWindow::on_movePushButton_clicked()
{
    QMap<QString, QStringList> folderToImageListMap;
    QDir folder = QFileDialog::getExistingDirectory();
    QStringList folderNameList = folder.entryList(QStringList(), QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i < folderNameList.size(); i++){
        QString currentfolder = folderNameList.at(i);
        folderNameList.replace(i, folder.absolutePath() + "/" + currentfolder);
    }

    foreach(QString currentFolder, folderNameList){
        if(!currentFolder.contains("maszkolni")){
            QDir currDir(currentFolder);
            folderToImageListMap[currentFolder] = currDir.entryList(QStringList("*_col.png"), QDir::Files | QDir::NoDotAndDotDot);
        }
    }

    foreach(QString currDirname, folderToImageListMap.keys()){
        foreach(QString currImagename, folderToImageListMap[currDirname]){
            QStringList maskedList = QDir("/home/denes/Documents/Labor/Viking/1000Viking/alma").entryList(QStringList("*_masked.tiff"), QDir::Files | QDir::NoDotAndDotDot);
            foreach(QString currMask, maskedList){
                if(currMask.split("_").first() == currImagename.split("_").first()){
                    QFile file("/home/denes/Documents/Labor/Viking/1000Viking/alma/" + currMask);
                    emit signalSendConsoleCommand(currDirname, "rm " + currMask);
                    file.rename(currDirname + "/" + currMask);
                }
            }
        }
        QApplication::processEvents();
        emit signalWriteToList("Masked images moved to " + currDirname + ".");
    }
    emit signalWriteToList("Ready.");
}

void MainWindow::slotSendConsoleCommant(QString dirPath, QString cmd)
{
    QProcess proc;
    QDir::setCurrent(dirPath);
    proc.execute(cmd);
    proc.waitForFinished();
    proc.close();
}

void MainWindow::on_logPushButton_clicked()
{
    QDir folder = QFileDialog::getExistingDirectory();
    QStringList folderNameList = folder.entryList(QStringList(), QDir::Files | QDir::NoDotAndDotDot);
    for(int i = 0; i < folderNameList.size(); i++){
        folderNameList.replace(i, QString(folderNameList.at(i)).split("_").first());
        if(i != 0 && QString(folderNameList.at(i)).split("_").first() == QString(folderNameList.at(i-1)).split("_").first()){
            folderNameList.removeAt(i);
            i--;
        }
    }
//    folderNameList.removeLast();

    foreach(QString currentName, folderNameList){
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/2014-06/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/2014-07/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/2014-08/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/2014-09/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/201410/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/201412/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/201501/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/201502/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/201503/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/201504/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/201505/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/201506/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/201508/" + currentName + ".log");
        emit signalSendConsoleCommand("/home/denes/Documents/Labor/Viking/1000Viking/log_1000viking", "wget https://arago.elte.hu/szombathely/felho/201509/" + currentName + ".log");
        QApplication::processEvents();
        signalWriteToList(currentName + ".log downloaded.");
    }
    emit signalWriteToList("All log files downloaded.");
}

void MainWindow::on_sunPushButton_clicked()
{
    QFile sunFile("/home/denes/Documents/Labor/Viking/1000Viking/MaskingAndMovingToFolders/sunpos.dat");
    if(!sunFile.open(QIODevice::ReadOnly | QIODevice::Text))
        emit signalWriteToList("sunpos.dat cannot be opened.");

    QMap<QString, QPair<double, double> > sunMap; /*first: azimuth, second: elevation*/
    QString filename;
    double az, el;
    QTextStream stream(&sunFile);
    while(!stream.atEnd()){
        QString line = stream.readLine();
        QTextStream linestream(&line);
        linestream >> filename >> az >> el;
        filename.remove(".log");
        sunMap[filename].first = az;
        sunMap[filename].second = el;
    }
    sunFile.close();

    QMap<QString, QStringList> folderToImageListMap;
    QDir folder = QFileDialog::getExistingDirectory();
    QStringList folderNameList = folder.entryList(QStringList(), QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i < folderNameList.size(); i++){
        QString currentfolder = folderNameList.at(i);
        folderNameList.replace(i, folder.absolutePath() + "/" + currentfolder);
    }

    foreach(QString currentFolder, folderNameList){
        if(!currentFolder.contains("maszkolni")){
            QDir currDir(currentFolder);
            folderToImageListMap[currentFolder] = currDir.entryList(QStringList("*_gdeg_masked.tiff"), QDir::Files | QDir::NoDotAndDotDot);
        }
    }

    foreach(QString currDirname, folderToImageListMap.keys()){
        foreach(QString currImagename, folderToImageListMap[currDirname]){
            QImage currImage(currDirname + "/" + currImagename);
            emit signalSendConsoleCommand(currDirname, "rm " + currImagename);
            currImagename.remove("_gdeg_masked.tiff");
            QVector2D sunPosition;
            QVector2D sunDes;
            sunPosition.setY((0+sunMap[currImagename].first)*Pi/180.0); //from right to counter-clockwise
            sunPosition.setX(90.0-sunMap[currImagename].second);  //in deg horizon->zenith: 0->90
            sunDes.setX(currImage.width()/2.0+(currImage.width()/2.0/90.0)*sunPosition.x()*cos(sunPosition.y()));
            sunDes.setY(currImage.height()/2.0-(currImage.height()/2.0/90.0)*sunPosition.x()*sin(sunPosition.y()));
            QPainter painter(&currImage);
            QPen pen;
            pen.setWidth(1);
            pen.setColor(Qt::green);
            painter.setPen(pen);
            painter.drawPoint(QPointF(sunDes.x(), sunDes.y()));
            painter.end();
            currImage.save(currDirname + "/" + currImagename + "_gdeg_masked.tiff");

            bool isGreenDot = false;
            for(int i = 0; i < currImage.width(); i++){
                for(int j = 0; j < currImage.height(); j++){
                    QColor pixCol = currImage.pixelColor(i,j);
                    if(pixCol == QColor(Qt::green))
                        isGreenDot = true;
                }
            }
            if(isGreenDot == false)
                emit signalWriteToList(currImagename + " sun position not detected.");

        }
        QApplication::processEvents();
        emit signalWriteToList("Sun positions added in " + currDirname + ".");
    }
    emit signalWriteToList("Sun positions ready.");
}
