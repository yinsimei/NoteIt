#ifndef RELATIONWINDOW_H
#define RELATIONWINDOW_H

#include <QDialog>

namespace Ui {
class RelationWindow;
}

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

private:
    Ui::RelationWindow *ui;
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
