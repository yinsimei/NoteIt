#ifndef ADDCOUPLEDIAG_H
#define ADDCOUPLEDIAG_H

#include <vector>
#include <QDialog>

namespace Ui {
class AddCoupleDiag;
}

using namespace std;

class AddCoupleDiag : public QDialog
{
    Q_OBJECT

public:
    explicit AddCoupleDiag(QWidget *parent = 0);
    ~AddCoupleDiag();
    void setInfo(int id, int rIdx);

private slots:
    void on_relation_noteList_currentRowChanged(int currentRow);

    void on_relation_addCoupleButton_clicked();

    void on_relation_cancelButton_clicked();

private:
    Ui::AddCoupleDiag *ui;
    int id1;
    int id2;
    int relationIdx;
    bool clearingList;
    vector<int> list_id2;
};


#endif // ADDCOUPLEDIAG_H
