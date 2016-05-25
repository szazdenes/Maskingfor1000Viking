#include "sourceandtargetdialog.h"
#include "ui_sourceandtargetdialog.h"

SourceAndTargetDialog::SourceAndTargetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SourceAndTargetDialog)
{
    ui->setupUi(this);
}

SourceAndTargetDialog::~SourceAndTargetDialog()
{
    delete ui;
}

void SourceAndTargetDialog::on_pushButton_clicked()
{
    this->accept();
    emit signalSourceAndTarget(sourceList);
}

void SourceAndTargetDialog::on_pushButton_2_clicked()
{
    this->reject();
}

void SourceAndTargetDialog::on_sourcePushButton_clicked()
{
    sourceList.clear();
    sourceList = QFileDialog::getOpenFileNames();
    ui->sourceListWidget->addItems(sourceList);
    ui->sourceListWidget->scrollToBottom();

}
