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
#include "deletearchiveddialog.h"

using namespace std;

namespace Ui {
class MainWindow;
}
class Note;

/** @brief   MainWindow est l'interface principal de l'application NoteIt, qui permet d'afficher, éditer, supprimer une note, et aussi gérer des relations autour d'une note
 */
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
    void deleteArchivedNote(int id);
    void setArchivedNoteDeleted(int id);
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionOpen_triggered();
    void on_resource_urlSelect_clicked();
    void on_resource_openUrlButton_clicked();

private:
    Ui::MainWindow *ui;
    AddCoupleDiag *addCoupleDiag;
    TreeForm *treeForm;
    RelationWindow *relationWindow;
    DeleteArchivedDialog *deleteArchived;

    /** @brief EnumWindowState : une enumération qui permet de classifier différent de états de l'interface de main window */
    enum EnumWindowState {
        e_default, /**< default = active*/
        e_article_view, /**< article, mode de vue*/
        e_article_edit, /**< article, mode d'édition*/
        e_task_view, /**< tâche, mode de vue*/
        e_task_edit, /**< tâche, mode d'édition*/
        e_resource_view, /**< ressource, mode de vue*/
        e_resource_edit, /**< ressource, mode d'édition*/
        e_trash_article, /**< corbeille, vue d'article*/
        e_trash_task, /**< corbeille, vue de tâche*/
        e_trash_resource, /**< corbeille, vue de ressource*/
        e_trash_no /**< corbeille, pas de note*/
    };

    /**
     * @brief CurrentNoteListInfo : une structure qui enregistre des information sur la dernière note affichée d'une certaine type et aussi
     * une liste qui permet d'indexer entre la liste de widget et l'identificateur de note
    */
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

    /**
     * @brief CurrentNoteListInfo : une structure qui enregistre des information sur la dernière note affichée d'une certaine type et aussi
     * une liste qui permet d'indexer entre la liste de widget et l'identificateur de note
    */
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
    void resetNoteList(EnumNoteType noteType);
    void resetRelationList();
    void setToNoteCommun(int id, int ver = -1);
    void setToNote(int id, int ver = -1);
    void setToArticle(int id, int ver = -1);
    void setToTask(int id, int ver = -1);
    void setToResource(int id, int ver = -1);
    void onCreateResource(ResourceType type);

    // show hide interface
    /** C'est une state machine qui gère le changement entre des différents état de l'interface
    @param newStatus[in]
    */
    void setMainWindowState(EnumWindowState newStatus);
    /** Afficher la liste de version, date de création/modification etc.
    */
    void showNoteCommon();
    /** Cacher la liste de version, date de création/modification etc. si vue de corbeille
    */
    void hideNoteCommon();
    /** Afficher tous éléments qui concernent la corbeille, par exemple la bouton de restaurer, etc
     * et changer l'apparence d'affichage de contenu de note selon son type: article, task, resource
    @param noteType[in]
    */
    void showTrash(EnumNoteType noteType);
    /** Cacher tous éléments qui concernent la corbeille
    */
    void hideTrash();
    /** Afficher l'arbre de relation de notes
    */
    void showTree();
    /** Cacher l'arbre de relation de notes
    */
    void hideTree();
    /** Afficher une des interfaces parmi article, task, resource selon le type
    @param noteType[in]
    */
    void setNoteView(EnumNoteType noteType);
    /** Changer l'apparance de l'interface de corbeille pour article, task, resource
    */
    void setTrashView(int id);

    // save & load
    void saveAs();
    bool checkIsEditing();
    void checkArchivedNote();
};

#endif // MAINWINDOW_H
