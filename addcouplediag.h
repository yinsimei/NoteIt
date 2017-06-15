#ifndef ADDCOUPLEDIAG_H
#define ADDCOUPLEDIAG_H

#include <vector>
#include <QDialog>

/** @brief   Namespace pour des élément d'interface
 *  @author  Simei YIN, Jiacheng ZHOU
 */
namespace Ui {
class AddCoupleDiag;
}

using namespace std;

/** @brief   Pop-up dialogue qui permet de créer une couple de note par choisir la deuxième note dans une liste, avec la première note déjà selectionnée dans l'interface précédent.
 *  @author  Simei YIN, Jiacheng ZHOU
 */
class AddCoupleDiag : public QDialog
{
    Q_OBJECT

public:
    /** Constructeur de AddCoupleDiag
    */
    explicit AddCoupleDiag(QWidget *parent = 0);
    ~AddCoupleDiag();

    /** Méthode qui permet d'initialiser l'interface de dialogue avec identificateur de note et relation en entrée. On enregistre la liste des deuxièmes notes possibles à local pendant l'initialisation. çe veut dire que des notes qui est différent de note 1 en entrée, aussi n'est pas déjà dans une couple avec note 1
     *@param [in] id identificateur de la première note dans la couple
     *@param [in] rIdx index de relation dans la liste de RelationManager, qui permet de trouver la relation où on veut ajouter la couple
    */
    void setInfo(int id, int rIdx);

private slots:
    /** slot méthode qui réagit au changement de sélection dans la liste : mettre à jour le choix de deuième note de couple
     @param [in] currentRow idx de la nouvelle objet dans la liste
    */
    void on_relation_noteList_currentRowChanged(int currentRow);
    /** slot méthode pour bouton "Ajouter" qui vérifie si le titre a été bien saisie et la deuxième note bien sélectionnée et en suite créer une nouvelle couple dans la relation
    */
    void on_relation_addCoupleButton_clicked();
    /** slot méthode pour bouton "Annuler"
    */
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
