#include "setsourceandtargetdialog.h"
#include "ui_setsourceandtargetdialog.h"

SetSourceAndTargetDialog::SetSourceAndTargetDialog(QWidget *parent, QString defaultSource, QString defaultTarget) :
    QDialog(parent),
    ui(new Ui::SetSourceAndTargetDialog)
{
    ui->setupUi(this);
    ui->sourceLineEdit->setText(defaultSource);
    ui->targetLineEdit->setText(defaultTarget);
}

SetSourceAndTargetDialog::~SetSourceAndTargetDialog()
{
    delete ui;
}

void SetSourceAndTargetDialog::on_pushButton_clicked()
{
    emit signalSendSourceAndTarget(ui->sourceLineEdit->text(), ui->targetLineEdit->text());
    this->accept();
}

void SetSourceAndTargetDialog::on_pushButton_2_clicked()
{
    this->reject();
}

void SetSourceAndTargetDialog::on_sourceToolButton_clicked()
{
    QString sourcename;
    if(!ui->sourceLineEdit->text().isEmpty())
        sourcename = QFileDialog::getExistingDirectory(this, "", ui->sourceLineEdit->text());
    else
        sourcename = QFileDialog::getExistingDirectory();
    ui->sourceLineEdit->setText(sourcename);
}

void SetSourceAndTargetDialog::on_targetToolButton_clicked()
{
    QString targetname;
    if(!ui->targetLineEdit->text().isEmpty())
       targetname = QFileDialog::getExistingDirectory(this, "", ui->targetLineEdit->text());
    else
        targetname = QFileDialog::getExistingDirectory();
    ui->targetLineEdit->setText(targetname);
}
