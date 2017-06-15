#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>
#include <vector>
#include "enums.h"
#include "relation.h"
#include "addcouplediag.h"
#include "treeform.h"
#include "relationwindow.h"

using namespace std;

namespace Ui {
class MainWindow;
}
class Note;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_article_editButton_clicked();
    void on_article_saveButton_clicked();
    void on_article_cancelButton_clicked();
    void on_resource_saveButton_clicked();
    void on_resource_editButton_clicked();
    void on_resource_cancelButton_clicked();
    void on_task_editButton_clicked();
    void on_task_cancelButton_clicked();
    void on_task_saveButton_clicked();
    void on_buttonArticle_clicked();
    void on_buttonTask_clicked();
    void on_buttonResource_clicked();
    void on_buttonTrash_clicked();
    void on_tree_showHideButton_clicked();
    void on_actionArticle_triggered();
    void on_actionTask_triggered();
    void on_actionAudio_triggered();
    void on_actionVideo_triggered();
    void on_actionImage_triggered();
    void on_actionQuitter_triggered();
    void on_note_resetVersionButton_clicked();
    void on_trash_deleteButton_clicked();
    void on_trash_restoreButton_clicked();
    void on_note_deleteButton_clicked();
    void on_note_manageRelationButton_clicked();
    void on_note_listWidget_currentRowChanged(int currentRow);
    void on_note_versionList_currentRowChanged(int currentRow);
    void on_note_relationSelect_currentIndexChanged(const QString &arg1);
    void on_note_addCoupleButton_clicked();
    void on_note_deleteCoupleButton_clicked();
    void on_note_relationCoupleList_currentRowChanged(int currentRow);
    void on_treeitem_doubleclick(int id);

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    AddCoupleDiag *addCoupleDiag;
    TreeForm *treeForm;
    RelationWindow *relationWindow;

    enum EnumWindowState {
        e_default,
        e_article_view,
        e_article_edit,
        e_task_view,
        e_task_edit,
        e_resource_view,
        e_resource_edit,
        e_trash_article,
        e_trash_task,
        e_trash_resource,
        e_trash_no
    };

    struct CurrentNoteListInfo{
        int currId;
        int currVer;
        vector<int> id_notelist;

        int currIdx() {
            for (unsigned int i = 0; i < id_notelist.size(); ++i) {
                if (id_notelist[i] == currId)
                    return i;
            }
            return -1;
        }
        CurrentNoteListInfo() : currId(-1), currVer(-1) {}
    };

    struct CurrentRelationListInfo{
        int currRelation;
        vector<Couple> coupleList;
        int currCoupleIndex;

        Couple currCouple() { return coupleList[currCoupleIndex]; }
    };

    EnumWindowState currState;
    bool isTreeShown;
    CurrentNoteListInfo currNoteInfo[e_all + 1];
    CurrentRelationListInfo currRelationInfo;
    bool clearingNoteList;
    bool clearingVersionList;
    bool clearingRelationList;
    bool clearingRelationComboBox;

    EnumNoteType getCurrentType();
    void resetNoteList(EnumNoteType noteType, EnumNoteStatus noteStatus = e_active);
    void resetRelationList();
    void setToNoteCommun(int id, int ver = -1);
    void setToNote(int id, int ver = -1);
    void setToArticle(int id, int ver = -1);
    void setToTask(int id, int ver = -1);
    void setToResource(int id, int ver = -1);
    void onCreateResource(ResourceType type);

    // show hide interface
    void setMainWindowState(EnumWindowState newStatus);
    void showNoteCommon();
    void hideNoteCommon();
    void showTrash(EnumNoteType noteType);
    void hideTrash();
    void showTree();
    void hideTree();
    void setNoteView(EnumNoteType noteType);
    void setTrashView(int id);

    // save & load
    void saveAs();
};

#endif // MAINWINDOW_H
