#include <QMessageBox>
#include "addcouplediag.h"
#include "ui_addcouplediag.h"
#include "notemanager.h"
#include "relationmanager.h"

AddCoupleDiag::AddCoupleDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCoupleDiag)
{
    ui->setupUi(this);
    clearingList = false;
}

AddCoupleDiag::~AddCoupleDiag()
{
    delete ui;
}

void AddCoupleDiag::on_relation_noteList_currentRowChanged(int currentRow)
{
    if (clearingList)
        return;
    id2 = list_id2[currentRow];
}

void AddCoupleDiag::on_relation_addCoupleButton_clicked()
{
    if (id2 < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez choisir une note pour créer le couple.");
        return;
    }
    QString label = ui->relation_coupleNameEdit->text();
    if (label == "") {
        QMessageBox::warning(this, "Erreur", "Le label de couple ne doit pas être vide.");
        return;
    }
    bool success = RelationManager::getInstance().addCouple(relationIdx, id1, id2, label);
    if (!success) {
        QMessageBox::warning(this, "Erreur", "Ce couple existe déjà dans la relation.");
        return;
    }
    hide();
}

void AddCoupleDiag::on_relation_cancelButton_clicked()
{
    hide();
}

void AddCoupleDiag::setInfo(int id, int rIdx) {
    id1 = id;
    relationIdx = rIdx;
    id2 = -1;
    // reset all graphical elements
    clearingList = true;
    ui->relation_noteList->clear();
    clearingList = false;
    QString relationName = RelationManager::getInstance().getRelation(relationIdx).getTitle();
    ui->relation_nameLabel->setText(relationName);
    ui->relation_coupleNameEdit->setText("");

    // get available indexes liste
    list_id2 = NoteManager::getInstance().getNotes(e_all, e_active);
    auto it = list_id2.begin();
    while (it != list_id2.end()) {
        if (*it == id1 || RelationManager::getInstance().checkExist(relationIdx, id1, *it)) {
            it = list_id2.erase(it);
        } else {
            ++it;
        }
    }
    if (list_id2.size() == 0) {
        QMessageBox::warning(this, "Pas possible à créer une couple", "Dans la relation " + relationName + ", cette note est déjà reliée avec toutes les autres notes actives.");
        hide();
    }

    // set list
    for (auto it = list_id2.begin(); it != list_id2.end(); ++it) {
        ui->relation_noteList->addItem(NoteManager::getInstance().getLastestNoteVersion(*it)->getTitle());
    }
}
