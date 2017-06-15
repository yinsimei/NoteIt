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
private:
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
    vector<Couple> getParentNotes(int relationIdx, int id) const;
    vector<Couple> getChildrenNotes(int relationIdx, int id) const;
    vector<Couple> getRelatedNotes(int relationIdx, int id) const;
    vector<Couple> getCouples(int relationIdx) const;

    void addRelation(int relationIdx, const Relation & r);
    bool addCouple(int relationIdx, int id1, int id2, QString label);
    void deleteCouple(int relationIdx,int id1, int id2);
    void deleteCouple(int relationIdx, Couple c);
    bool deleteAllCouplesOf(int id);
    void deleteRelation(int relationIdx);
    bool checkExist(int relationIdx, int id1, int id2) const;
};

#endif // RELATIONMANAGER_H
