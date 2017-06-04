#ifndef RELATIONNODE_H
#define RELATIONNODE_H
#include <vector>

using namespace std;

class RelationNode
{
private:
    int id;
    vector<RelationNode *> descendants;
    vector<RelationNode *> ascendants;

public:
    RelationNode();
};

#endif // RELATIONNODE_H
