#ifndef RELATION_H
#define RELATION_H

#include <QString>
#include <vector>

using namespace std;

/** @brief  Couple est la strcture qui contient des informations sur deux notes
 */
struct Couple {
    QString label; ///< label de couple
    int n1; ///< id de note parente
    int n2; ///< id de note enfant
    /** operateur de copie
     * @param [in] c couple à copier
    */
    bool operator==(Couple c);
    /** Constructeur par défaut
    */
    Couple() : label(""), n1(-1), n2(-1) {}
    /** Constructeur
     * @param [in] l label de couple
     * @param [in] _n1 l'id note de parent dans la couple
     * @param [in] _n2 l'id note d'enfant dans la couple
    */
    Couple(const QString &l, int _n1, int _n2) : label(l), n1(_n1), n2(_n2) {}
};

/** @brief  Relation est contient un ensemble de couple de cette même relation, "référence" par exemple.
 * Une relation peut être orientér ou non orientée, assignée à la création, non modifiable après
 */
class Relation
{
protected:
    friend class LoadSaveManager;

    QString title; ///< title de la relation
    QString descp; ///< description de la relation
    bool oriented; ///< orientation ou pas de la relation
    bool reference; ///< reference ou pas de la relation
    vector<Couple> couples; ///< couples qui est contenues dans la relation

public:
    /** Constructeur par default
    */
    Relation() : title(""), descp(""), oriented(false), reference(false) {}
    /** Constructeur en copie
     * @param [in] r relation à copier
    */
    Relation(const Relation &r);
    /** Constructeur
     * @param [in] t titre
     * @param [in] d description
     * @param [in] o orientation
     * @param [in] r reference
    */
    Relation(const QString &t, const QString &d, bool o, bool r = false) : title(t), descp(d), oriented(o), reference(r) {}
    /** accesseur à titre en lecture
    */
    const QString &getTitle() const { return title; }
    /** accesseur à la description en lecture
    */
    const QString &getDescp() const { return descp; }
    /** accesseur à l'orientation en lectrure
    */
    bool isOriented() const { return oriented; }
    /** accesseur à la reference en lecture
    */
    bool isReference() const { return reference; }
    /** accesseur aux couples de la relation en lecture
    */
    const vector<Couple> &getCouples() const { return couples; }
    /** Retourner toutes les couples qui a la note comme enfant
     * @param [in] n l'id de note
    */
    vector<Couple> getChildren(int n) const;
    /** Retourner toutes les couples qui a la note comme parent
     * @param [in] n l'id de note
    */
    vector<Couple> getParents(int n) const;
    /** Retourner toutes les couples qui contient une note
     * @param [in] n l'id de note
    */
    vector<Couple> getRelatedNotes(int n) const;
    /** Vérifier si une couple existe déjà dans la relation
     * @param [in] id1 l'id note de parent dans la couple
     * @param [in] id2 l'id note d'enfant dans la couple
    */
    bool checkExist(int id1, int id2) const;
    /** Setter du titre de relation
     * @param [in] t le titre de relation
    */
    void setTitle(const QString & t) { title = t; }
    /** Setter de la description de relation
     * @param [in] d la description de relation
    */
    void setDescp(const QString & d) { descp = d; }
    /** Setter de l'orientation de relation
     * @param [in] o le bool d'orientation de relation
    */
    void setOriented(bool o) { oriented = o; }
    /** Setter de la reference de relation
     * @param [in] r le bool de reference de relation
    */
    void setReference(bool r) { reference = r; }
    /** Ajouter une couple
     * @param [in] id1 l'id de note parente
     * @param [in] id2 l'id de note enfant
     * @param [in] label label de couple
    */
    bool addCouple(int id1, int id2, const QString & label);
    /** Supprimer une couple en donner l'id de deux notes
     * @param [in] id1 l'id de note parente
     * @param [in] id2 l'id de note enfant
    */
    void deleteCouple(int id1, int id2);
    /** Supprimer une couple en donnant la couple directement
     * @param [in] c la couple à supprimer
    */
    void deleteCouple(Couple c);
    /** Supprimer toutes les couples qui contiennent une note
     * @param [in] id l'id de note
    */
    bool deleteAllCouplesOf(int id);
};

#endif // RELATION_H
