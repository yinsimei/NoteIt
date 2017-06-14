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
public:
    static RelationManager &getInstance();

    int getRelationNb() { return relations.size(); }
    const QString &getRelationTitle(int relationIdx) { Q_ASSERT(relationIdx >= 0 && relationIdx < (int)getRelationNb()); return relations[relationIdx]->getTitle(); }
    bool isRelationOriented(int relationIdx) { Q_ASSERT(relationIdx >= 0 && relationIdx < (int)getRelationNb()); return relations[relationIdx]->isOriented(); }
    int getIdxFromTitle(QString title);
    vector<Couple> getParentNotes(int relationIdx, int id);
    vector<Couple> getChildrenNotes(int relationIdx, int id);
    vector<Couple> getRelatedNotes(int relationIdx, int id);
    bool addCouple(int relationIdx, int id1, int id2, QString label);
    void deleteCouple(int relationIdx,int id1, int id2);
    void deleteCouple(int relationIdx, Couple c);
    bool deleteAllCouplesOf(int id);
    void addRelation(QString relationTitle, QString relationDescp, bool oriented);
    void deleteRelation(int relationIdx);
    bool checkExist(int relationIdx, int id1, int id2);
};

#endif // RELATIONMANAGER_H
