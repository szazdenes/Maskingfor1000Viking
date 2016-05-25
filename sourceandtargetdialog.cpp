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
    emit signalSourceAndTarget(ui->sourceLineEdit->text(), ui->targetLineEdit->text());
}

void SourceAndTargetDialog::on_pushButton_2_clicked()
{
    this->reject();
}

void SourceAndTargetDialog::on_sourcePushButton_clicked()
{
    QString source = QFileDialog::getOpenFileName();
    ui->sourceLineEdit->setText(source);
}

void SourceAndTargetDialog::on_targetPushButton_clicked()
{
    QString target = QFileDialog::getExistingDirectory();
    ui->targetLineEdit->setText(target);
}
