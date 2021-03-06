#ifndef SOURCEANDTARGETDIALOG_H
#define SOURCEANDTARGETDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class SourceAndTargetDialog;
}

class SourceAndTargetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SourceAndTargetDialog(QWidget *parent = 0);
    ~SourceAndTargetDialog();

signals:
    void signalSourceAndTarget(QStringList source);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_sourcePushButton_clicked();

private:
    Ui::SourceAndTargetDialog *ui;
    QStringList sourceList;
};

#endif // SOURCEANDTARGETDIALOG_H
