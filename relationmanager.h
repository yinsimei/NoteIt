#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H

#include <unordered_map>
#include <vector>

#include "article.h"
#include "task.h"
#include "resource.h"
#include "relationtree.h"
#include "relation.h"

class RelationManager
{
private:
    static RelationManager* instance;
    vector<Relation *> relations;

public:
    RelationManager();
    vector<int> getRelatedNotes(int id);
    RelationManager& getInstance();
    RelationTree getRelationTree(int id, int uplevel, int downlevel);
    void addRelation(int id1, int id2, bool oriented);
    void deleteRelation(int id);

};

#endif // RELATIONMANAGER_H
