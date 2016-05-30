#ifndef SETSOURCEANDTARGETDIALOG_H
#define SETSOURCEANDTARGETDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class SetSourceAndTargetDialog;
}

class SetSourceAndTargetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetSourceAndTargetDialog(QWidget *parent = 0, QString defaultSource = "", QString defaultTarget = "");
    ~SetSourceAndTargetDialog();

signals:
    void signalSendSourceAndTarget(QString source, QString target);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_sourceToolButton_clicked();

    void on_targetToolButton_clicked();

private:
    Ui::SetSourceAndTargetDialog *ui;
};

#endif // SETSOURCEANDTARGETDIALOG_H
