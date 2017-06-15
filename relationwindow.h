#ifndef RELATIONWINDOW_H
#define RELATIONWINDOW_H

#include <QDialog>
#include "deletearchiveddialog.h"

namespace Ui {
class RelationWindow;
}

/** @brief  RelationWindow est l'interface qui permet de gérer, éditer, supprimer, enrichir des relations
 */
class RelationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RelationWindow(QWidget *parent = 0);
    ~RelationWindow();

protected:
    void showEvent(QShowEvent *ev);

private slots:
    void on_relation_listWidget_currentRowChanged(int currentRow);
    void on_relation_addButton_clicked();
    void on_relation_deleteButton2_clicked();
    void on_relation_editButton_clicked();
    void on_relation_deleteButton_clicked();
    void on_relation_saveButton_clicked();
    void on_relation_cancelButton_clicked();
    void on_relation_coupleList_currentRowChanged(int currentRow);
    void on_relation_addCoupleButton_clicked();
    void on_relation_deleteCoupleButton_clicked();
    void deleteArchivedNote(int id);
    void setArchivedNoteDeleted(int id);

private:
    Ui::RelationWindow *ui;
    DeleteArchivedDialog *deleteArchived;

    int currRelationIdx;
    int currCoupleIdx;
    bool clearingRelationList;
    bool clearingCoupleList;

    void resetRelationList();
    void resetCoupleList();
    void setToRelation(int id);
    void deleteRelation();
};

#endif // RELATIONWINDOW_H
