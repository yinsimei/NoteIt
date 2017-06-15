#ifndef DELETEARCHIVEDDIALOG_H
#define DELETEARCHIVEDDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteArchivedDialog;
}

/** @brief   Pop-up window qui demande si l'utilisateur veut supprimer une note archivée quand les couple qui le contiennent sont supprimée.
 *Si l'utilisateur confirme la suppression, un signal sera envoyé.
 */
class DeleteArchivedDialog : public QDialog
{
    Q_OBJECT

public:
    /** constructeur de deleteArchiveDialog
     */
    explicit DeleteArchivedDialog(QWidget *parent = 0);
    ~DeleteArchivedDialog();
    /** méthode qui permet d'initialiser l'interface avec l'identificateur de note archivée en entrée
    */
    void setNote(int id);

private slots:
    void on_delete_no_clicked();
    void on_delete_yes_clicked();

signals:
    /** Signal envoyé pour signaler des autres fenêtes à mettre à jour leur interface
    */
    void deleteArchived(int);
    void notDeleteArchived(int);

private:
    Ui::DeleteArchivedDialog *ui;
    int id_archived;
};

#endif // DELETEARCHIVEDDIALOG_H
