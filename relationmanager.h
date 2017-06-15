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
/**
 * @brief RelationManager est une classe sigleton qui permet de gérer tout ce qui concenrne des relations
*/
class RelationManager
{
protected:
    friend class LoadSaveManager;
    /**
     * @brief singleton Handler
    */
    struct Handler {
        RelationManager* instance; ///< singleton instance
        Handler(): instance(nullptr) {}
        ~Handler() { if (instance) delete instance; }
    };

    static Handler handler; ///< signleton handler
    vector<Relation *> relations; ///< un vecteur qui enregistres toues les relations
    RelationManager();
    ~RelationManager();
    /** ajouter d'une relation
     * @param [in] relationTitle titre de la relation
     * @param [in] relationDescp description de la relation
     * @param [in] oriented orientation ou pas de la relation
     * @param [in] reference reference ou pas de la relation
    */
    void addRelation(QString relationTitle, QString relationDescp, bool oriented, bool reference = false);

public:
    /** singleton
    */
    static RelationManager &getInstance();
    /** accesseur à nombre de relations en écriture
     * @return nombre de relations
    */
    int getRelationNb() const { return relations.size(); }
    /** accesseur à une relation selon
     * @param [in] relationIdx index d'une relation
    */
    const Relation &getRelation(int relationIdx) const { Q_ASSERT(relationIdx >= 0 && relationIdx < getRelationNb()); return *relations[relationIdx]; }
    /** accesseur à index en écriture selon
     * @param [in] title titre de la relation
    */
    int getIdxFromTitle(QString title) const;
    /** Retourner toutes les couples d'une relation saisie qui a la note comme parent
     * @param [in] relationIdx l'index de relation
     * @param [in] id l'id de la note
    */
    vector<Couple> getParentNotes(int relationIdx, int id) const;
    /** Retourner toutes les couples d'une relation saisie qui a la note comme enfant
     * @param [in] relationIdx l'index de relation
     * @param [in] id l'id de la note
    */
    vector<Couple> getChildrenNotes(int relationIdx, int id) const;
    /** Retourner toutes les couples d'une relation saisie qui contient la note
     * @param [in] relationIdx l'index de relation
     * @param [in] id l'id de la note
    */
    vector<Couple> getRelatedNotes(int relationIdx, int id) const;
    /** Retourner toutes les couples d'une relation saisie
     * @param [in] relationIdx l'index de relation
    */
    vector<Couple> getCouples(int relationIdx) const;
    /** supprimer tous les relations définitivement
    */
    void clear();
    /** Ajouter une relation
     * @param [in] relationIdx l'index relation
     * @param [in] r la relation à ajouter
     * @return l'index de la nouvelle relation
    */
    int addRelation(int relationIdx, const Relation & r);
    /** Ajouter une couple dans une relation
     * @param [in] relationIdx l'index de la relation
     * @param [in] id1 l'id de note parente
     * @param [in] id2 l'id de note enfant
     * @param [in] label label de couple
    */
    bool addCouple(int relationIdx, int id1, int id2, QString label);
    /** Supprimer une couple en donner l'index de relation et l'id de deux notes
     * @param [in] relationIdx l'index de la relation
     * @param [in] id1 l'id de note parente
     * @param [in] id2 l'id de note enfant
    */
    void deleteCouple(int relationIdx,int id1, int id2);
    /** Supprimer une couple en donner l'index de relation et la couple
     * @param [in] relationIdx l'index de la relation
     * @param [in] c le couple
    */
    void deleteCouple(int relationIdx, Couple c);
    /** Supprimer tous les couples liées à une note choisie
     * @param [in] id l'id de la note
    */
    bool deleteAllCouplesOf(int id);
    /** Supprimer une relation en donner l'index de la relation
     * @param [in] relationIdx l'index de la relation
    */
    void deleteRelation(int relationIdx);
    /** Vérifier si une couple existe déjà dans la relation
     * @param [in] relationIdx l'index de la relation
     * @param [in] id1 l'id de note parente
     * @param [in] id2 l'id de note enfant
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
