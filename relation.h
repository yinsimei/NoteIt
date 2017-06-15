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
    bool operator==(Couple c);
    Couple() : label(""), n1(-1), n2(-1) {}
    Couple(const QString &l, int _n1, int _n2) : label(l), n1(_n1), n2(_n2) {}
};

/** @brief  Relation est contient un ensemble de couple de cette même relation, "référence" par exemple.
 * Une relation peut être orientér ou non orientée, assignée à la création, non modifiable après
 */
class Relation
{
protected:
    friend class LoadSaveManager;
    QString title;
    QString descp;
    bool oriented;
    bool reference;
    vector<Couple> couples;

public:
    /** Constructeur par default
    */
    Relat
    Relation() : title(""), descp(""), oriented(false), reference(false) {}
    /** Constructeur en copie
     * @param r[in] relation à copier
    */
    Relation(const Relation &r);
    Relation(const QString &t, const QString &d, bool o, bool r = false) : title(t), descp(d), oriented(o), reference(r) {}
    const QString &getTitle() const { return title; }
    const QString &getDescp() const { return descp; }
    bool isOriented() const { return oriented; }
    bool isReference() const { return reference; }
    const vector<Couple> &getCouples() const { return couples; }
    /** Retourner toutes les couples qui a la note comme enfant
     * @param n[in] l'id de note
    */
    vector<Couple> getChildren(int n) const;
    /** Retourner toutes les couples qui a la note comme parent
     * @param n[in] l'id de note
    */
    vector<Couple> getParents(int n) const;
    /** Retourner toutes les couples qui contient une note
     * @param n[in] l'id de note
    */
    vector<Couple> getRelatedNotes(int n) const;
    /** Vérifier si une couple existe déjà dans la relation
     * @param id1[in] l'id note de parent dans la couple
     * @param id2[in] l'id note d'enfant dans la couple
    */
    bool checkExist(int id1, int id2) const;
    /** Setter du titre de relation
     * @param t[in] le titre de relation
    */
    void setTitle(const QString & t) { title = t; }
    /** Setter de la description de relation
     * @param d[in] la description de relation
    */
    void setDescp(const QString & d) { descp = d; }
    /** Setter de l'orientation de relation
     * @param o[in] le bool d'orientation de relation
    */
    void setOriented(bool o) { oriented = o; }
    /** Setter de la reference de relation
     * @param r[in] le bool de reference de relation
    */
    void setReference(bool r) { reference = r; }
    /** Ajouter une couple
     * @param id1[in] l'id de note parente
     * @param id2[in] l'id de note enfant
     * @param label[in] label de couple
    */
    bool addCouple(int id1, int id2, const QString & label);
    /** Supprimer une couple en donner l'id de deux notes
     * @param id1[in] l'id de note parente
     * @param id2[in] l'id de note enfant
    */
    void deleteCouple(int id1, int id2);
    /** Supprimer une couple en donnant la couple directement
     * @param c[in] la couple à supprimer
    */
    void deleteCouple(Couple c);
    /** Supprimer toutes les couples qui contiennent une note
     * @param id[in] l'id de note
    */
    bool deleteAllCouplesOf(int id);
};

#endif // RELATION_H
