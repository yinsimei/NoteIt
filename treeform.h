#ifndef TREEFORM_H
#define TREEFORM_H

#include <vector>
#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class TreeForm;
}

using namespace std;

/** @brief   TreeForm est l'interface de l'arbre de relation des notes, qui est une widget affiché sur la fnêtre pricipale
 */
class TreeForm : public QWidget
{
    Q_OBJECT

public:
    explicit TreeForm(QWidget *parent = 0);
    ~TreeForm();
    /** Initialiser l'interface de l'arbre de relation
     * @param id[in] l'identifiateur de note à afficher l'arbre
    */
    void setNoteTree(int id);

signals:
    void goToNote(int);

private slots:
    void on_tree_parentList_itemDoubleClicked(QListWidgetItem *item);

    void on_tree_childList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::TreeForm *ui;
    int idNote;
    vector<int> parentNotes;
    vector<int> childNotes;
};

#endif // TREEFORM_H
