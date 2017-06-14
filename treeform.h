#ifndef TREEFORM_H
#define TREEFORM_H

#include <vector>
#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class TreeForm;
}

using namespace std;

class TreeForm : public QWidget
{
    Q_OBJECT

public:
    explicit TreeForm(QWidget *parent = 0);
    ~TreeForm();
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
