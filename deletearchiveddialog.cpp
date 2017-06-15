#include "deletearchiveddialog.h"
#include "ui_deletearchiveddialog.h"
#include "notemanager.h"

DeleteArchivedDialog::DeleteArchivedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteArchivedDialog)
{
    ui->setupUi(this);
}

DeleteArchivedDialog::~DeleteArchivedDialog()
{
    delete ui;
}

void DeleteArchivedDialog::setNote(int id) {
    id_archived = id;
    ui->delete_msg->setText("La note "
                            + NoteManager::getInstance().getLastestNoteVersion(id)->getTitle()
                            + " concernée dans ce couple est dans l'état Archivée.\n"
                            + "Voulez-vous le supprimer définitivement ?");
}

void DeleteArchivedDialog::on_delete_no_clicked()
{
    hide();
}

void DeleteArchivedDialog::on_delete_yes_clicked()
{
    emit deleteArchived(id_archived);
    hide();
}
