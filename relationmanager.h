#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H

#include <unordered_map>
#include <vector>
#include <QString>

#include "article.h"
#include "task.h"
#include "resource.h"
#include "relation.h"

using namespace std;

class RelationManager
{
protected:
    friend class LoadSaveManager;
    struct Handler {
        RelationManager* instance;
        Handler(): instance(nullptr) {}
        ~Handler() { if (instance) delete instance; }
    };

    static Handler handler;
    vector<Relation *> relations;
    RelationManager();
    ~RelationManager();
    void addRelation(QString relationTitle, QString relationDescp, bool oriented, bool reference = false);

public:
    static RelationManager &getInstance();

    int getRelationNb() const { return relations.size(); }

    const Relation &getRelation(int relationIdx) const { Q_ASSERT(relationIdx >= 0 && relationIdx < getRelationNb()); return *relations[relationIdx]; }

    int getIdxFromTitle(QString title) const;
    /** Retourner toutes les couples d'une relation saisie qui a la note comme parent
     * @param relationIdx[in] l'index de relation
     * @param id[in] l'id de la note
    */
    vector<Couple> getParentNotes(int relationIdx, int id) const;
    /** Retourner toutes les couples d'une relation saisie qui a la note comme enfant
     * @param relationIdx[in] l'index de relation
     * @param id[in] l'id de la note
    */
    vector<Couple> getChildrenNotes(int relationIdx, int id) const;
    /** Retourner toutes les couples d'une relation saisie qui contient la note
     * @param relationIdx[in] l'index de relation
     * @param id[in] l'id de la note
    */
    vector<Couple> getRelatedNotes(int relationIdx, int id) const;
    /** Retourner toutes les couples d'une relation saisie
     * @param relationIdx[in] l'index de relation
    */
    vector<Couple> getCouples(int relationIdx) const;
    /** supprimer tous les relations définitivement
    */
    void clear();
    /** Ajouter une relation
     * @param relationIdx[in] l'index relation
     * @param r[in] la relation à ajouter
     * @return l'index de la nouvelle relation
    */
    int addRelation(int relationIdx, const Relation & r);
    /** Ajouter une couple dans une relation
     * @param relationIdx[in] l'index de la relation
     * @param id1[in] l'id de note parente
     * @param id2[in] l'id de note enfant
     * @param label[in] label de couple
    */
    bool addCouple(int relationIdx, int id1, int id2, QString label);
    /** Supprimer une couple en donner l'index de relation et l'id de deux notes
     * @param relationIdx[in] l'index de la relation
     * @param id1[in] l'id de note parente
     * @param id2[in] l'id de note enfant
    */
    void deleteCouple(int relationIdx,int id1, int id2);
    /** Supprimer une couple en donner l'index de relation et la couple
     * @param relationIdx[in] l'index de la relation
     * @param c[in] le couple
    */
    void deleteCouple(int relationIdx, Couple c);
    /** Supprimer tous les couples liées à une note choisie
     * @param id[in] l'id de la note
    */
    bool deleteAllCouplesOf(int id);
    /** Supprimer une relation en donner l'index de la relation
     * @param relationIdx[in] l'index de la relation
    */
    void deleteRelation(int relationIdx);
    /** Vérifier si une couple existe déjà dans la relation
     * @param relationIdx[in] l'index de la relation
     * @param id1[in] l'id de note parente
     * @param id2[in] l'id de note enfant
    */
    bool checkExist(int relationIdx, int id1, int id2) const;

    /** Obtenir la relation référence
    */
    Relation *getReference();

    /** Vérifier si une note archivée peut être supprimée
     * @param [in] idArchived l'id d'une note archivée
    */
    bool ableToDeleteArchived(int idArchived);

    /** Retourner une liste de notes archivée qui peuvent être supprimées après une suppression de note
    */
    vector<int> archivedCanBeDeleted();
};

#endif // RELATIONMANAGER_H
