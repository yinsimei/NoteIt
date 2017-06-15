#ifndef DELETEARCHIVEDDIALOG_H
#define DELETEARCHIVEDDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteArchivedDialog;
}

class DeleteArchivedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteArchivedDialog(QWidget *parent = 0);
    ~DeleteArchivedDialog();
    void setNote(int id);

private slots:
    void on_delete_no_clicked();
    void on_delete_yes_clicked();

signals:
    void deleteArchived(int);

private:
    Ui::DeleteArchivedDialog *ui;
    int id_archived;
};

#endif // DELETEARCHIVEDDIALOG_H
