#include <QMessageBox>
#include "relationwindow.h"
#include "ui_relationwindow.h"
#include "notemanager.h"
#include "relationmanager.h"

RelationWindow::RelationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RelationWindow)
{
    ui->setupUi(this);
}

RelationWindow::~RelationWindow()
{
    delete ui;
    clearingRelationList = false;
    clearingCoupleList = false;
}

void RelationWindow::showEvent(QShowEvent *ev) {
    QDialog::showEvent(ev);

    // Init interface
    currRelationIdx = -1;
    currCoupleIdx = -1;
    resetRelationList();
    ui->relation_descpEdit->setEnabled(false);
    ui->relation_titleEdit->setEnabled(false);
    ui->relation_editDeleteWidget->show();
    ui->relation_saveCancelWidget->hide();
}

void RelationWindow::resetRelationList() {
    if (currRelationIdx < 0)
        currRelationIdx = 0;
    clearingRelationList = true;
    ui->relation_listWidget->clear();
    int relationNb = RelationManager::getInstance().getRelationNb();
    for (int i = 0; i < relationNb; ++i) {
        ui->relation_listWidget->addItem(RelationManager::getInstance().getRelation(i).getTitle());
    }
    ui->relation_listWidget->item(currRelationIdx)->setSelected(true);
    clearingRelationList = false;
    setToRelation(currRelationIdx);
}

void RelationWindow::resetCoupleList() {
    clearingCoupleList = true;
    ui->relation_coupleList->clear();
    clearingCoupleList = false;

    if (currRelationIdx < 0)
        return;
    // set couple list
    const vector<Couple> &coupleList = RelationManager::getInstance().getCouples(currRelationIdx);
    bool isOriented = RelationManager::getInstance().getRelation(currRelationIdx).isOriented();
    for (auto it = coupleList.begin(); it != coupleList.end(); ++it) {
        QString str = (*it).label
                + " : "
                + NoteManager::getInstance().getLastestNoteVersion((*it).n1)->getTitle()
                + (isOriented ? " -> " : " <-> ")
                + NoteManager::getInstance().getLastestNoteVersion((*it).n2)->getTitle();
        ui->relation_coupleList->addItem(str);
    }
}

void RelationWindow::setToRelation(int id) {
    if (id < 0) {
        ui->relation_descpEdit->setText("");
        ui->relation_titleEdit->setText("");
        ui->relation_orientedCheck->setChecked(false);
        resetCoupleList();
        return;
    }
    Relation r = RelationManager::getInstance().getRelation(id);
    ui->relation_titleEdit->setText(r.getTitle());
    ui->relation_descpEdit->setText(r.getDescp());
    ui->relation_orientedCheck->setChecked(r.isOriented());
    resetCoupleList();
}

void RelationWindow::deleteRelation() {
    Q_ASSERT(currRelationIdx >= 0);
    if (RelationManager::getInstance().getRelation(currRelationIdx).isReference()) {
        QMessageBox::warning(this, "Attention", "La relation Référence ne peut pas être supprimée");
        return;
    }
    RelationManager::getInstance().deleteRelation(currRelationIdx);
    --currRelationIdx;
    resetRelationList();
}

void RelationWindow::on_relation_listWidget_currentRowChanged(int currentRow)
{
    if (clearingRelationList)
        return;
    currRelationIdx = currentRow;
    setToRelation(currRelationIdx);
}

void RelationWindow::on_relation_addButton_clicked()
{
    ui->relation_descpEdit->setEnabled(true);
    ui->relation_titleEdit->setEnabled(true);
    ui->relation_orientedCheck->setEnabled(true);
    ui->relation_editDeleteWidget->hide();
    ui->relation_saveCancelWidget->show();
    currRelationIdx = -1;
    setToRelation(currRelationIdx);
}

void RelationWindow::on_relation_deleteButton2_clicked()
{
    deleteRelation();
}

void RelationWindow::on_relation_editButton_clicked()
{
    ui->relation_descpEdit->setEnabled(true);
    ui->relation_titleEdit->setEnabled(true);
    ui->relation_orientedCheck->setEnabled(false);
    ui->relation_editDeleteWidget->hide();
    ui->relation_saveCancelWidget->show();
}

void RelationWindow::on_relation_deleteButton_clicked()
{
    deleteRelation();
}

void RelationWindow::on_relation_saveButton_clicked()
{
    const QString title = ui->relation_titleEdit->text();
    if (title == "") {
        QMessageBox::warning(this, "Attention", "Le titre de relation ne doit pas être vide");
        return;
    }
    ui->relation_descpEdit->setEnabled(false);
    ui->relation_titleEdit->setEnabled(false);
    ui->relation_orientedCheck->setEnabled(false);
    ui->relation_editDeleteWidget->show();
    ui->relation_saveCancelWidget->hide();
    Relation r(title,
               ui->relation_descpEdit->toPlainText(),
               ui->relation_orientedCheck->isChecked());
    RelationManager::getInstance().addRelation(currRelationIdx, r);
    resetRelationList();
}

void RelationWindow::on_relation_cancelButton_clicked()
{
    ui->relation_descpEdit->setEnabled(false);
    ui->relation_titleEdit->setEnabled(false);
    ui->relation_orientedCheck->setEnabled(false);
    ui->relation_editDeleteWidget->show();
    ui->relation_saveCancelWidget->hide();
    resetRelationList();
}

void RelationWindow::on_relation_coupleList_currentRowChanged(int currentRow)
{
    currCoupleIdx = currentRow;
}

void RelationWindow::on_relation_addCoupleButton_clicked()
{
    QMessageBox::warning(this, "Attention", "Non implémenté, Veuillez ajouter couple des notes dans l'interface de note");
}

void RelationWindow::on_relation_deleteCoupleButton_clicked()
{
    if (currCoupleIdx < 0) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner une couple pour supprimer.");
        return;
    }
    Couple toDelete = RelationManager::getInstance().getRelation(currRelationIdx).getCouples()[currCoupleIdx];
    RelationManager::getInstance().deleteCouple(currRelationIdx, toDelete);
    resetCoupleList();
}
