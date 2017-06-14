#include <QtGlobal>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notemanager.h"
#include "article.h"
#include "task.h"
#include "resource.h"
#include "notemanager.h"
#include "relationmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMainWindowState(e_default);
    addCoupleDiag = new AddCoupleDiag(this);

    // default values
    showTree = false;
    clearingNoteList = false;
    clearingVersionList = false;
    clearingRelationList = false;
    clearingRelationComboBox = false;

    // set combo box
    for (auto it = taskStatusNames.begin(); it != taskStatusNames.end(); ++it) {
        ui->task_statusComboBox->addItem(it.value());
    }
    for (auto it = priorityNames.begin(); it != priorityNames.end(); ++it) {
        ui->task_priorityEdit->addItem(it.value());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetNoteList(EnumNoteType noteType, EnumNoteStatus noteStatus) {
    clearingNoteList = true;
    ui->note_listWidget->clear();
    clearingNoteList = false;
    // set list view
    vector<int> newList = NoteManager::getInstance().getNotes(noteType, noteStatus);
    currNoteInfo[noteType].id_notelist.clear();
    currNoteInfo[noteType].id_notelist.reserve(newList.size());
    currNoteInfo[noteType].id_notelist.assign(newList.begin(), newList.end());

    if (currNoteInfo[noteType].id_notelist.size() == 0) {
        currNoteInfo[noteType].currId = -1;
    } else {
        if (currNoteInfo[noteType].currId == -1)
            currNoteInfo[noteType].currId = currNoteInfo[noteType].id_notelist[0];
        for (auto it = currNoteInfo[noteType].id_notelist.begin(); it != currNoteInfo[noteType].id_notelist.end(); ++it) {
            ui->note_listWidget->addItem(NoteManager::getInstance().getLastestNoteVersion(*it)->getTitle());
        }
        ui->note_listWidget->item(currNoteInfo[noteType].currIdx())->setSelected(true);
    }

    // activate current article item
    if (noteType == e_all)
        setTrashView(currNoteInfo[noteType].currId);
    setToNote(currNoteInfo[noteType].currId);
}

void MainWindow::resetRelationList() {
    clearingRelationList = true;
    ui->note_relationCoupleList->clear();
    clearingRelationList = false;

    EnumNoteType type = getCurrentType();
    Q_ASSERT(currRelationInfo.currRelation >= 0 && currNoteInfo[type].currId >= 0);

    // set ComboBox
    clearingRelationComboBox = true;
    ui->note_relationSelect->clear();
    int relationNb = RelationManager::getInstance().getRelationNb();
    for (int i = 0; i < relationNb; ++i) {
        ui->note_relationSelect->addItem(RelationManager::getInstance().getRelationTitle(i));
    }
    clearingRelationComboBox = false;

    // set couple list
    currRelationInfo.coupleList = RelationManager::getInstance().getRelatedNotes(currRelationInfo.currRelation, currNoteInfo[type].currId);
    for (auto it = currRelationInfo.coupleList.begin(); it != currRelationInfo.coupleList.end(); ++it) {
        ui->note_relationCoupleList->addItem((*it).label);
    }
}

void MainWindow::setToNoteCommun(int id, int ver) {
    if (id < 0) {
        ui->note_deleteButton->hide();
        // clear date
        ui->note_dateCreateText->setText("");
        ui->note_dateModifText->setText("");
        // clear versions
        clearingVersionList = true;
        ui->note_versionList->clear();
        clearingVersionList = false;
        // clear relations
        currRelationInfo.currRelation = -1;
        currRelationInfo.currCoupleIndex = -1;
        clearingRelationList = true;
        ui->note_relationCoupleList->clear();
        clearingRelationList = false;
        return;
    }
    // set date
    Note *note;
    if (ver < 0)
        note = NoteManager::getInstance().getLastestNoteVersion(id);
    else
        note = NoteManager::getInstance().getNote(id, ver);
    ui->note_dateCreateText->setText(note->getDateCreate().toString());
    ui->note_dateModifText->setText(note->getDateModif().toString());

    // set versions
    clearingVersionList = true;
    ui->note_versionList->clear();
    clearingVersionList = false;
    vector<Note *> note_versions = NoteManager::getInstance().getNoteVersions(id);
    for (auto it = note_versions.begin(); it != note_versions.end(); ++it) {
        ui->note_versionList->addItem((*it)->getDateModif().toString());
    }
    ui->note_resetVersionButton->hide();

    // set relations
    currRelationInfo.currRelation = 0;
    currRelationInfo.currCoupleIndex = -1;
    resetRelationList();
}

EnumNoteType MainWindow::getCurrentType() {
    switch (currState) {
    case e_article_view:
    case e_article_edit:
        return e_article;
    case e_task_view:
    case e_task_edit:
        return e_task;
    case e_resource_view:
    case e_resource_edit:
        return e_resource;
    case e_trash_article:
    case e_trash_task:
    case e_trash_resource:
    case e_trash_no:
        return e_all;
    default:
        Q_ASSERT(0);
    }
}

void MainWindow::setToNote(int id, int ver) {
    if (currState == e_trash_no) {
        Q_ASSERT(id == -1);
        return;
    }
    setToNoteCommun(id);
    switch (currState) {
    case e_article_view:
    case e_trash_article:
    case e_article_edit:
        setToArticle(id, ver);
        break;
    case e_resource_view:
    case e_trash_resource:
    case e_resource_edit:
        setToResource(id, ver);
        break;
    case e_task_view:
    case e_trash_task:
    case e_task_edit:
        setToTask(id, ver);
        break;
    default:
        Q_ASSERT(0);
        break;
    }
}

void MainWindow::showNoteCommon() {
    ui->note_dateWidget->show();
    ui->note_deleteButton->show();
    ui->note_versionWidget->show();
    ui->note_resetVersionButton->hide();
    ui->note_relationWidget->show();
    ui->tree_showHideButton->show();
}

void MainWindow::hideNoteCommon() {
    ui->note_dateWidget->hide();
    ui->note_deleteButton->hide();
    ui->note_versionWidget->hide();
    ui->note_relationWidget->hide();
    ui->tree_showHideButton->hide();
}

void MainWindow::setToArticle(int id, int ver) {
    if (id == -1) {
        ui->article_titleEdit->setText("");
        ui->article_textEdit->clear();
        ui->article_editButton->hide();
        return;
    }
    Q_ASSERT(NoteManager::getInstance().getNoteType(id) == e_article);
    Article *a;
    if (ver < 0) {
        a = NoteManager::getInstance().getLastestArticleVersion(id);
        currNoteInfo[e_article].currVer = -1;
    } else
        a = NoteManager::getInstance().getArticle(id, ver);
    ui->article_titleEdit->setText(a->getTitle());
    ui->article_textEdit->setPlainText(a->getText());
}

void MainWindow::setToTask(int id, int ver) {
    if (id == -1) {
        ui->task_priorityEdit->setCurrentIndex(0);
        ui->task_actionEdit->clear();
        ui->task_titleEdit->setText("");
        ui->task_ddlTimeEdit->clear();
        ui->task_editButton->hide();
        return;
    }
    Q_ASSERT(NoteManager::getInstance().getNoteType(id) == e_task);
    Task *t;
    if (ver < 0) {
        t = NoteManager::getInstance().getLastestTaskVersion(id);
        currNoteInfo[e_task].currVer = -1;
    }
    else
        t = NoteManager::getInstance().getTask(id, ver);
    ui->task_titleEdit->setText(t->getTitle());
    ui->task_actionEdit->setPlainText(t->getAction());
    ui->task_ddlTimeEdit->setTime(t->getDeadline().time());
    ui->task_priorityEdit->setCurrentIndex(t->getPriority());
}

void MainWindow::setToResource(int id, int ver) {
    if (id == -1) {
        ui->resource_titleEdit->setText("");
        ui->resource_typeText->setText("");
        ui->resource_url->setText("");
        ui->resource_despEdit->setPlainText("");
        ui->resource_editButton->hide();
        return;
    }
    Q_ASSERT(NoteManager::getInstance().getNoteType(id) == e_resource);
    Resource *t;
    if (ver < 0) {
         t = NoteManager::getInstance().getLastestResourceVersion(id);
         currNoteInfo[e_resource].currVer = -1;
    }
    else
        t = NoteManager::getInstance().getResource(id, ver);
    ui->resource_titleEdit->setText(t->getTitle());
    ui->resource_typeText->setText(resourceTypeNames[t->getType()]);
    ui->resource_url->setText(t->getUrl());
    ui->resource_despEdit->setPlainText(t->getDescp());
}

// view modification

void MainWindow::showTrash(EnumNoteType noteType) {
    ui->trash_buttonWidget->show();
    switch (noteType) {
    case e_article:
        ui->trash_noNote->hide();
        ui->article_titleEdit->setEnabled(false);
        ui->article_textEdit->setEnabled(false);
        ui->article_editButton->hide();
        ui->article_saveButton->hide();
        ui->article_cancelButton->hide();
        break;

    case e_task:
        ui->trash_noNote->hide();
        ui->task_titleEdit->setEnabled(false);
        ui->task_actionEdit->setEnabled(false);
        ui->task_ddlTimeEdit->setEnabled(false);
        ui->task_priorityEdit->setEnabled(false);
        ui->task_editButton->hide();
        ui->task_saveButton->hide();
        ui->task_cancelButton->hide();
        break;

    case e_resource:
        ui->trash_noNote->hide();
        ui->resource_titleEdit->setEnabled(false);
        ui->resource_urlSelect->hide();
        ui->resource_despEdit->setEnabled(false);
        ui->resource_editButton->hide();
        ui->resource_saveButton->hide();
        ui->resource_cancelButton->hide();
        break;

    default:
        Q_ASSERT(0);
        break;
    }
}

void MainWindow::setTrashView(int id) {
    if (id < 0) {
        setMainWindowState(e_trash_no);
        return;
    }
    EnumNoteType type = NoteManager::getInstance().getNoteType(id);
    switch (type) {
    case e_article:
        setMainWindowState(e_trash_article);
        break;
    case e_resource:
        setMainWindowState(e_trash_resource);
        break;
    case e_task:
        setMainWindowState(e_trash_task);
        break;
    default:
        Q_ASSERT(0);
        break;
    }
}

void MainWindow::hideTrash() {
    ui->trash_buttonWidget->hide();
    ui->trash_noNote->hide();
}

void MainWindow::setNoteView(EnumNoteType noteType) {
    switch (noteType) {
    case e_article:
        ui->article_allWidget->show();
        ui->task_allWidget->hide();
        ui->resource_allWidget->hide();
        break;

    case e_task:
        ui->article_allWidget->hide();
        ui->task_allWidget->show();
        ui->resource_allWidget->hide();
        break;

    case e_resource:
        ui->article_allWidget->hide();
        ui->task_allWidget->hide();
        ui->resource_allWidget->show();
        break;

    default:
        Q_ASSERT(0);
        break;
    }
}

void MainWindow::setMainWindowState(EnumWindowState newState) {
    switch (newState) {
    case e_default:
        setMainWindowState(e_article_view);
        setToNote(-1);
        return;

    case e_article_view:
        setNoteView(e_article);
        showNoteCommon();
        hideTrash();
        ui->treeWidget->hide();
        ui->article_titleEdit->setEnabled(false);
        ui->article_textEdit->setEnabled(false);
        ui->article_editButton->show();
        ui->article_saveButton->hide();
        ui->article_cancelButton->hide();
        break;

    case e_article_edit:
        setNoteView(e_article);
        showNoteCommon();
        hideTrash();
        ui->treeWidget->hide();
        ui->article_titleEdit->setEnabled(true);
        ui->article_textEdit->setEnabled(true);
        ui->article_editButton->hide();
        ui->article_saveButton->show();
        ui->article_cancelButton->show();
        break;

    case e_task_view:
        setNoteView(e_task);
        showNoteCommon();
        hideTrash();
        ui->treeWidget->hide();
        ui->task_titleEdit->setEnabled(false);
        ui->task_actionEdit->setEnabled(false);
        ui->task_ddlTimeEdit->setEnabled(false);
        ui->task_priorityEdit->setEnabled(false);
        ui->task_statusComboBox->setEnabled(false);
        ui->task_editButton->show();
        ui->task_saveButton->hide();
        ui->task_cancelButton->hide();
        break;

    case e_task_edit:
        setNoteView(e_task);
        showNoteCommon();
        hideTrash();
        ui->treeWidget->hide();
        ui->task_titleEdit->setEnabled(true);
        ui->task_actionEdit->setEnabled(true);
        ui->task_ddlTimeEdit->setEnabled(true);
        ui->task_priorityEdit->setEnabled(true);
        ui->task_statusComboBox->setEnabled(true);
        ui->task_editButton->hide();
        ui->task_saveButton->show();
        ui->task_cancelButton->show();
        break;

    case e_resource_view:
        setNoteView(e_resource);
        showNoteCommon();
        hideTrash();
        ui->treeWidget->hide();
        ui->resource_titleEdit->setEnabled(false);
        ui->resource_urlSelect->hide();
        ui->resource_despEdit->setEnabled(false);
        ui->resource_editButton->show();
        ui->resource_saveButton->hide();
        ui->resource_cancelButton->hide();
        break;

    case e_resource_edit:
        setNoteView(e_resource);
        showNoteCommon();
        hideTrash();
        ui->treeWidget->hide();
        ui->resource_titleEdit->setEnabled(true);
        ui->resource_urlSelect->show();
        ui->resource_despEdit->setEnabled(true);
        ui->resource_editButton->hide();
        ui->resource_saveButton->show();
        ui->resource_cancelButton->show();
        break;

    case e_trash_article:
        setNoteView(e_article);
        hideNoteCommon();
        showTrash(e_article);
        ui->treeWidget->hide();
        break;

    case e_trash_task:
        setNoteView(e_task);
        hideNoteCommon();
        showTrash(e_task);
        ui->treeWidget->hide();
        break;

    case e_trash_resource:
        setNoteView(e_resource);
        hideNoteCommon();
        showTrash(e_resource);
        ui->treeWidget->hide();
        break;

    case e_trash_no:
        ui->resource_allWidget->hide();
        ui->article_allWidget->hide();
        ui->task_allWidget->hide();
        hideNoteCommon();
        ui->trash_buttonWidget->hide();
        ui->trash_noNote->show();
        break;

    default:
        Q_ASSERT(0);
        break;
    }
    currState = newState;
}

void MainWindow::on_article_editButton_clicked()
{
    setMainWindowState(e_article_edit);
}

void MainWindow::on_resource_editButton_clicked()
{
    setMainWindowState(e_resource_edit);
}

void MainWindow::on_task_editButton_clicked()
{
    setMainWindowState(e_task_edit);
}

void MainWindow::on_article_saveButton_clicked()
{
    Article a;
    a.setId(currNoteInfo[e_article].currId);
    a.setDateCreate(QDateTime::fromString(ui->note_dateCreateText->text()));
    a.setDateModif(QDateTime::currentDateTime());
    a.setTitle(ui->article_titleEdit->text());
    a.setText(ui->article_textEdit->toPlainText());
    currNoteInfo[e_article].currId = NoteManager::getInstance().addArticle(a);
    setMainWindowState(e_article_view);
    resetNoteList(e_article);
}

void MainWindow::on_resource_saveButton_clicked()
{
    Resource r((ResourceType)resourceTypeNames.key(ui->resource_typeText->text()));
    r.setId(currNoteInfo[e_resource].currId);
    r.setDateCreate(QDateTime::fromString(ui->note_dateCreateText->text()));
    r.setDateModif(QDateTime::currentDateTime());
    r.setTitle(ui->resource_titleEdit->text());
    r.setUrl(ui->resource_url->text());
    r.setDescp(ui->resource_despEdit->toPlainText());
    currNoteInfo[e_resource].currId = NoteManager::getInstance().addResource(r);
    setMainWindowState(e_resource_view);
    resetNoteList(e_resource);
}

void MainWindow::on_task_saveButton_clicked()
{
    Task t;
    t.setId(currNoteInfo[e_task].currId);
    t.setDateCreate(QDateTime::fromString(ui->note_dateCreateText->text()));
    t.setDateModif(QDateTime::currentDateTime());
    t.setTitle(ui->task_titleEdit->text());
    t.setDeadline(QDateTime::fromString(ui->task_ddlTimeEdit->text()));
    t.setAction(ui->task_actionEdit->toPlainText());
    t.setPriority((EnumPriority)priorityNames.key(ui->task_priorityEdit->currentText()));
    t.setTaskStatus((EnumTaskStatus)taskStatusNames.key(ui->task_statusComboBox->currentText()));
    currNoteInfo[e_task].currId = NoteManager::getInstance().addTask(t);
    setMainWindowState(e_task_view);
    resetNoteList(e_task);
}

void MainWindow::on_article_cancelButton_clicked()
{
    setMainWindowState(e_article_view);
    resetNoteList(e_article);
}

void MainWindow::on_resource_cancelButton_clicked()
{
    setMainWindowState(e_resource_view);
    resetNoteList(e_resource);
}

void MainWindow::on_task_cancelButton_clicked()
{
    setMainWindowState(e_task_view);
    resetNoteList(e_task);
}

void MainWindow::on_buttonArticle_clicked()
{
    setMainWindowState(e_article_view);
    resetNoteList(e_article);
}

void MainWindow::on_buttonTask_clicked()
{
    setMainWindowState(e_task_view);
    resetNoteList(e_task);
}


void MainWindow::on_buttonResource_clicked()
{
    setMainWindowState(e_resource_view);
    resetNoteList(e_resource);
}

void MainWindow::on_buttonTrash_clicked()
{
    resetNoteList(e_all, e_deleted);
}

void MainWindow::on_tree_showHideButton_clicked()
{
    if (showTree) {
        ui->treeWidget->hide();
        ui->tree_showHideButton->setText("<");
    } else {
        ui->treeWidget->show();
        ui->tree_showHideButton->setText(">");
    }
    showTree = !showTree;
}

void MainWindow::on_actionArticle_triggered()
{
    resetNoteList(e_article);
    setMainWindowState(e_article_edit);
    // empty all fields
    currNoteInfo[e_article].currId = -1;
    setToNote(-1);

    // set dates
    ui->note_dateCreateText->setText(QDateTime::currentDateTime().toString());
    ui->note_dateModifText->setText(QDateTime::currentDateTime().toString());
}

void MainWindow::on_actionTask_triggered()
{
    resetNoteList(e_task);
    setMainWindowState(e_task_edit);
    // empty all fields
    currNoteInfo[e_task].currId = -1;
    setToNote(-1);

    // set dates
    ui->note_dateCreateText->setText(QDateTime::currentDateTime().toString());
    ui->note_dateModifText->setText(QDateTime::currentDateTime().toString());
}

void MainWindow::onCreateResource(ResourceType type) {
    resetNoteList(e_resource);
    setMainWindowState(e_resource_edit);
    // empty all fields
    currNoteInfo[e_resource].currId = -1;
    setToNote(-1);

    // set type
    ui->resource_typeText->setText(resourceTypeNames[type]);
    // set dates
    ui->note_dateCreateText->setText(QDateTime::currentDateTime().toString());
    ui->note_dateModifText->setText(QDateTime::currentDateTime().toString());
}

void MainWindow::on_actionAudio_triggered()
{
    onCreateResource(e_audio);
}

void MainWindow::on_actionVideo_triggered()
{
    onCreateResource(e_video);
}

void MainWindow::on_actionImage_triggered()
{
    onCreateResource(e_image);
}

void MainWindow::on_actionQuitter_triggered()
{
    close();
}

void MainWindow::on_note_listWidget_currentRowChanged(int currentRow)
{
    if (clearingNoteList)
        return;
    EnumNoteType type = getCurrentType();
    currNoteInfo[type].currId = currNoteInfo[type].id_notelist[currentRow];
    if (type == e_all) {
        setTrashView(currNoteInfo[type].currId);
    }
    setToNote(currNoteInfo[type].currId);
}

void MainWindow::on_note_versionList_currentRowChanged(int currentRow)
{
    if (clearingVersionList)
        return;
    EnumNoteType type = getCurrentType();
    Q_ASSERT(currNoteInfo[type].currId >= 0);
    currNoteInfo[type].currVer = currentRow;
    setToNote(currNoteInfo[type].currId, currNoteInfo[type].currVer);
    ui->note_resetVersionButton->show();
}

void MainWindow::on_note_resetVersionButton_clicked()
{
    EnumNoteType type = getCurrentType();
    Q_ASSERT(currNoteInfo[type].currId >= 0 && currNoteInfo[type].currVer >= 0);
    NoteManager::getInstance().resetToVersion(currNoteInfo[type].currId, currNoteInfo[type].currVer);
    resetNoteList(type);
}

void MainWindow::on_note_deleteButton_clicked()
{
    EnumNoteType type = getCurrentType();
    if (currNoteInfo[type].currId < 0)
        return;
    NoteManager::getInstance().deleteNote(currNoteInfo[type].currId);
    currNoteInfo[type].currId = -1;
    currNoteInfo[type].currVer = -1;
    resetNoteList(type);
}

void MainWindow::on_note_manageRelationButton_clicked()
{
    EnumNoteType type = getCurrentType();
    if (currNoteInfo[type].currId < 0)
        return;
}

void MainWindow::on_trash_deleteButton_clicked()
{
    EnumNoteType type = getCurrentType();
    Q_ASSERT(type == e_all);
    Q_ASSERT(currNoteInfo[type].currId >= 0);
    NoteManager::getInstance().dropNote(currNoteInfo[type].currId);
    currNoteInfo[type].currId = -1;
    resetNoteList(e_all, e_deleted);
}

void MainWindow::on_trash_restoreButton_clicked()
{
    EnumNoteType type = getCurrentType();
    Q_ASSERT(type == e_all);
    Q_ASSERT(currNoteInfo[type].currId >= 0);
    NoteManager::getInstance().restoreNote(currNoteInfo[type].currId);
    resetNoteList(e_all, e_deleted);
}

void MainWindow::on_note_relationSelect_currentIndexChanged(const QString &arg1)
{
    if (clearingRelationComboBox)
        return;
    currRelationInfo.currRelation = RelationManager::getInstance().getIdxFromTitle(arg1);
    resetRelationList();
}

void MainWindow::on_note_addCoupleButton_clicked()
{
    EnumNoteType type = getCurrentType();
    if (currNoteInfo[type].currId >= 0 && currRelationInfo.currRelation >= 0) {
        addCoupleDiag->setInfo(currNoteInfo[type].currId, currRelationInfo.currRelation);
        addCoupleDiag->exec();
        resetRelationList();
    }
}

void MainWindow::on_note_deleteCoupleButton_clicked()
{

}

void MainWindow::on_note_relationCoupleList_currentRowChanged(int currentRow)
{
    EnumNoteType type = getCurrentType();
    if (currNoteInfo[type].currId >= 0 && currRelationInfo.currRelation >= 0 && currRelationInfo.currCoupleIndex >= 0) {
        RelationManager::getInstance().deleteCouple(currRelationInfo.currRelation, currRelationInfo.currCouple());
        resetRelationList();
    }
}
