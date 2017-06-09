#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

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

private:
    Ui::MainWindow *ui;

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

    EnumWindowState currState;
    bool showTree;
    void setMainWindowState(EnumWindowState newStatus);
};

#endif // MAINWINDOW_H
