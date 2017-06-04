#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notemanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMainWindowState(e_default);
    showTree = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

// view modification
void MainWindow::setMainWindowState(EnumWindowState newState) {
    switch (newState) {
    case e_default:
        setMainWindowState(e_article_view);
        break;

    case e_article_view:
        if (currState != e_article_view && currState != e_article_edit && currState != e_trash_article) {
            ui->article_allWidget->show();
            ui->task_allWidget->hide();
            ui->resource_allWidget->hide();
        }
        ui->treeWidget->hide();
        ui->note_deleteButton->show();
        ui->note_manageRelationButton->show();
        ui->note_versionWidget->show();
        ui->note_resetVersionButton->hide();
        ui->note_relationWidget->show();
        ui->trash_deleteButton->hide();
        ui->trash_restoreButton->hide();
        ui->trash_noNote->hide();
        ui->article_titleEdit->setEnabled(false);
        ui->article_textEdit->setEnabled(false);
        ui->article_editButton->show();
        ui->article_saveButton->hide();
        ui->article_cancelButton->hide();
        break;

    case e_article_edit:
        if (currState != e_article_view) {
            ui->article_allWidget->show();
            ui->task_allWidget->hide();
            ui->resource_allWidget->hide();
        }
        ui->treeWidget->hide();
        ui->note_deleteButton->show();
        ui->note_manageRelationButton->show();
        ui->note_versionWidget->show();
        ui->note_resetVersionButton->hide();
        ui->note_relationWidget->show();
        ui->trash_deleteButton->hide();
        ui->trash_restoreButton->hide();
        ui->trash_noNote->hide();
        ui->article_titleEdit->setEnabled(true);
        ui->article_textEdit->setEnabled(true);
        ui->article_editButton->hide();
        ui->article_saveButton->show();
        ui->article_cancelButton->show();
        break;

    case e_task_view:
        if (currState != e_task_view && currState != e_task_edit && currState != e_trash_task) {
            ui->task_allWidget->show();
            ui->article_allWidget->hide();
            ui->resource_allWidget->hide();
        }
        ui->treeWidget->hide();
        ui->note_deleteButton->show();
        ui->note_manageRelationButton->show();
        ui->note_versionWidget->show();
        ui->note_resetVersionButton->hide();
        ui->note_relationWidget->show();
        ui->trash_deleteButton->hide();
        ui->trash_restoreButton->hide();
        ui->trash_noNote->hide();
        ui->task_titleEdit->setEnabled(false);
        ui->task_actionEdit->setEnabled(false);
        ui->task_ddlTimeEdit->setEnabled(false);
        ui->task_priorityEdit->setEnabled(false);
        ui->task_editButton->show();
        ui->task_saveButton->hide();
        ui->task_cancelButton->hide();
        break;

    case e_task_edit:
        if (currState != e_task_view) {
            ui->task_allWidget->show();
            ui->article_allWidget->hide();
            ui->resource_allWidget->hide();
        }
        ui->treeWidget->hide();
        ui->note_deleteButton->show();
        ui->note_manageRelationButton->show();
        ui->note_versionWidget->show();
        ui->note_resetVersionButton->hide();
        ui->note_relationWidget->show();
        ui->trash_deleteButton->hide();
        ui->trash_restoreButton->hide();
        ui->trash_noNote->hide();
        ui->task_titleEdit->setEnabled(true);
        ui->task_actionEdit->setEnabled(true);
        ui->task_ddlTimeEdit->setEnabled(true);
        ui->task_priorityEdit->setEnabled(true);
        ui->task_editButton->hide();
        ui->task_saveButton->show();
        ui->task_cancelButton->show();
        break;

    case e_resource_view:
        if (currState != e_resource_view && currState != e_resource_edit && currState != e_trash_resource) {
            ui->resource_allWidget->show();
            ui->article_allWidget->hide();
            ui->task_allWidget->hide();
        }
        ui->treeWidget->hide();
        ui->note_deleteButton->show();
        ui->note_manageRelationButton->show();
        ui->note_versionWidget->show();
        ui->note_resetVersionButton->hide();
        ui->note_relationWidget->show();
        ui->trash_deleteButton->hide();
        ui->trash_restoreButton->hide();
        ui->trash_noNote->hide();
        ui->resource_titleEdit->setEnabled(false);
        ui->resource_urlSelect->hide();
        ui->resource_despEdit->setEnabled(false);
        ui->resource_editButton->show();
        ui->resource_saveButton->hide();
        ui->resource_cancelButton->hide();
        break;

    case e_resource_edit:
        if (currState != e_resource_view) {
            ui->task_allWidget->show();
            ui->article_allWidget->hide();
            ui->resource_allWidget->hide();
        }
        ui->treeWidget->hide();
        ui->note_deleteButton->show();
        ui->note_manageRelationButton->show();
        ui->note_versionWidget->show();
        ui->note_resetVersionButton->hide();
        ui->note_relationWidget->show();
        ui->trash_deleteButton->hide();
        ui->trash_restoreButton->hide();
        ui->trash_noNote->hide();
        ui->resource_titleEdit->setEnabled(true);
        ui->resource_urlSelect->show();
        ui->resource_despEdit->setEnabled(true);
        ui->resource_editButton->hide();
        ui->resource_saveButton->show();
        ui->resource_cancelButton->show();
        break;

    case e_trash_article:
        if (currState != e_article_view && currState != e_article_edit && currState != e_trash_article) {
            ui->article_allWidget->show();
            ui->task_allWidget->hide();
            ui->resource_allWidget->hide();
        }
        ui->treeWidget->hide();
        ui->note_deleteButton->hide();
        ui->note_manageRelationButton->hide();
        ui->note_versionWidget->hide();
        ui->note_relationWidget->hide();
        ui->trash_deleteButton->show();
        ui->trash_restoreButton->show();
        ui->trash_noNote->hide();
        ui->article_titleEdit->setEnabled(false);
        ui->article_textEdit->setEnabled(false);
        ui->article_editButton->hide();
        ui->article_saveButton->hide();
        ui->article_cancelButton->hide();
        break;

    case e_trash_task:
        if (currState != e_task_view && currState != e_task_edit && currState != e_trash_task) {
            ui->task_allWidget->show();
            ui->article_allWidget->hide();
            ui->resource_allWidget->hide();
        }
        ui->treeWidget->hide();
        ui->note_deleteButton->hide();
        ui->note_manageRelationButton->hide();
        ui->note_versionWidget->hide();
        ui->note_relationWidget->hide();
        ui->trash_deleteButton->show();
        ui->trash_restoreButton->show();
        ui->task_titleEdit->setEnabled(false);
        ui->task_actionEdit->setEnabled(false);
        ui->task_ddlTimeEdit->setEnabled(false);
        ui->task_priorityEdit->setEnabled(false);
        ui->task_editButton->hide();
        ui->task_saveButton->hide();
        ui->task_cancelButton->hide();
        break;

    case e_trash_resource:
        if (currState != e_resource_view && currState != e_resource_edit && currState != e_trash_resource) {
            ui->resource_allWidget->show();
            ui->article_allWidget->hide();
            ui->task_allWidget->hide();
        }
        ui->treeWidget->hide();
        ui->note_deleteButton->hide();
        ui->note_manageRelationButton->hide();
        ui->note_versionWidget->hide();
        ui->note_relationWidget->hide();
        ui->trash_deleteButton->show();
        ui->trash_restoreButton->show();
        ui->trash_noNote->hide();
        ui->resource_titleEdit->setEnabled(false);
        ui->resource_urlSelect->hide();
        ui->resource_despEdit->setEnabled(false);
        ui->resource_editButton->hide();
        ui->resource_saveButton->hide();
        ui->resource_cancelButton->hide();
        break;

    case e_trash_no:
        ui->resource_allWidget->hide();
        ui->article_allWidget->hide();
        ui->task_allWidget->hide();
        ui->note_deleteButton->hide();
        ui->note_manageRelationButton->hide();
        ui->note_versionWidget->hide();
        ui->note_relationWidget->hide();
        ui->trash_deleteButton->hide();
        ui->trash_restoreButton->hide();
        ui->trash_noNote->show();
        break;

    default:
        throw NotesException("Unknown main window state!");
        break;
    }
    currState = newState;
}

void MainWindow::on_article_editButton_clicked()
{
    setMainWindowState(e_article_edit);
}

void MainWindow::on_article_saveButton_clicked()
{
    setMainWindowState(e_article_view);
}

void MainWindow::on_article_cancelButton_clicked()
{
    setMainWindowState(e_article_view);
}

void MainWindow::on_resource_editButton_clicked()
{
    setMainWindowState(e_resource_edit);
}

void MainWindow::on_resource_saveButton_clicked()
{
    setMainWindowState(e_resource_view);
}


void MainWindow::on_resource_cancelButton_clicked()
{
    setMainWindowState(e_resource_view);
}

void MainWindow::on_task_editButton_clicked()
{
    setMainWindowState(e_task_edit);
}

void MainWindow::on_task_cancelButton_clicked()
{
    setMainWindowState(e_task_view);
}

void MainWindow::on_task_saveButton_clicked()
{
    setMainWindowState(e_task_view);
}

void MainWindow::on_buttonArticle_clicked()
{
    setMainWindowState(e_article_view);
}

void MainWindow::on_buttonTask_clicked()
{
    setMainWindowState(e_task_view);
}


void MainWindow::on_buttonResource_clicked()
{
    setMainWindowState(e_resource_view);
}

void MainWindow::on_buttonTrash_clicked()
{
    setMainWindowState(e_trash_no);
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
    setMainWindowState(e_article_edit);
}

void MainWindow::on_actionTask_triggered()
{
    setMainWindowState(e_trash_edit);
}

void MainWindow::on_actionAudio_triggered()
{

}

void MainWindow::on_actionVideo_triggered()
{

}

void MainWindow::on_actionImage_triggered()
{

}
