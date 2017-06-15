#include "treeform.h"
#include "ui_treeform.h"
#include "notemanager.h"
#include "relationmanager.h"

TreeForm::TreeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeForm)
{
    ui->setupUi(this);
}

TreeForm::~TreeForm()
{
    delete ui;
}

void TreeForm::setNoteTree(int id) {
    idNote = id;
    parentNotes.clear();
    childNotes.clear();
    ui->tree_parentList->clear();
    ui->tree_childList->clear();
    ui->tree_relationNameLabel->setText("");

    if (id < 0)
        return;

    ui->tree_relationNameLabel->setText(NoteManager::getInstance().getLastestNoteVersion(id)->getTitle());
    // set list widget
    int nbRelation = RelationManager::getInstance().getRelationNb();
    for (int i = 0; i < nbRelation; ++i) {
        QString relationName = RelationManager::getInstance().getRelation(i).getTitle();
        vector<Couple> parentCouples = RelationManager::getInstance().getParentNotes(i, id);
        vector<Couple> childCouples = RelationManager::getInstance().getChildrenNotes(i, id);
        for (auto it = parentCouples.begin(); it != parentCouples.end(); ++it) {
            ui->tree_parentList->addItem(relationName
                                         + " : " + (*it).label + " : "
                                         + NoteManager::getInstance().getLastestNoteVersion((*it).n1)->getTitle());
            parentNotes.push_back((*it).n1);
        }
        for (auto it = childCouples.begin(); it != childCouples.end(); ++it) {
            ui->tree_childList->addItem(relationName
                                        + " : " + (*it).label + " : "
                                        + NoteManager::getInstance().getLastestNoteVersion((*it).n2)->getTitle());
            childNotes.push_back((*it).n2);
        }
    }
}

void TreeForm::on_tree_parentList_itemDoubleClicked(QListWidgetItem *item)
{
    emit goToNote(parentNotes[ui->tree_parentList->row(item)]);
}

void TreeForm::on_tree_childList_itemDoubleClicked(QListWidgetItem *item)
{
    emit goToNote(childNotes[ui->tree_childList->row(item)]);
}
