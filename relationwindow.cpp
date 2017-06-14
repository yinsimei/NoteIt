#include "relationwindow.h"
#include "ui_relationwindow.h"

RelationWindow::RelationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RelationWindow)
{
    ui->setupUi(this);
}

RelationWindow::~RelationWindow()
{
    delete ui;
}

void RelationWindow::showEvent(QShowEvent *ev) {
    QDialog::showEvent(ev);

    // Init interface
}

void RelationWindow::on_relation_backButton_clicked()
{
    hide();
}

void RelationWindow::on_relation_listWidget_currentRowChanged(int currentRow)
{

}

void RelationWindow::on_relation_addButton_clicked()
{

}

void RelationWindow::on_relation_deleteButton2_clicked()
{

}

void RelationWindow::on_relation_editButton_clicked()
{

}

void RelationWindow::on_relation_deleteButton_clicked()
{

}

void RelationWindow::on_relation_saveButton_clicked()
{

}

void RelationWindow::on_relation_cancelButton_clicked()
{

}

void RelationWindow::on_relation_coupleList_currentRowChanged(int currentRow)
{

}

void RelationWindow::on_relation_addCoupleButton_clicked()
{

}

void RelationWindow::on_relation_deleteCoupleButton_clicked()
{

}
