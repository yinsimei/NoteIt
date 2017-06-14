#include "relationmanager.h"

RelationManager::Handler RelationManager::handler = RelationManager::Handler();

RelationManager &RelationManager::getInstance(){
    if (!handler.instance)
        handler.instance = new RelationManager();
    return *handler.instance;
}

RelationManager::RelationManager() {
    // add reference as init
    addRelation("Référence", "Référence entre deux notes", true);
}

RelationManager::~RelationManager() {
    for (auto it = relations.begin(); it != relations.end(); ++it) {
        delete (*it);
    }
}

int RelationManager::getIdxFromTitle(QString title) {
    for (unsigned int i = 0; i < relations.size(); ++i) {
        if (relations[i]->getTitle() == title)
            return i;
    }
    Q_ASSERT(0); // relation title not find
}

vector<Couple> RelationManager::getParentNotes(int relationIdx, int id) {
    Q_ASSERT(relationIdx >= 0 && relationIdx < (int)relations.size());
    return relations[relationIdx]->getParents(id);
}

vector<Couple> RelationManager::getChildrenNotes(int relationIdx, int id) {
    Q_ASSERT(relationIdx >= 0 && relationIdx < (int)relations.size());
    return relations[relationIdx]->getChildren(id);
}

vector<Couple> RelationManager::getRelatedNotes(int relationIdx, int id) {
    Q_ASSERT(relationIdx >= 0 && relationIdx < (int)relations.size());
    return relations[relationIdx]->getRelatedNotes(id);
}

bool RelationManager::addCouple(int relationIdx, int id1, int id2, QString label) {
    Q_ASSERT(relationIdx >= 0 && relationIdx < (int)relations.size());
    return relations[relationIdx]->addCouple(id1, id2, label);
}

void RelationManager::deleteCouple(int relationIdx, int id1, int id2) {
    Q_ASSERT(relationIdx >= 0 && relationIdx < (int)relations.size());
    return relations[relationIdx]->deleteCouple(id1, id2);
}

void RelationManager::deleteCouple(int relationIdx, Couple c) {
    Q_ASSERT(relationIdx >= 0 && relationIdx < (int)relations.size());
    relations[relationIdx]->deleteCouple(c);
}

bool RelationManager::deleteAllCouplesOf(int id) {
    bool res = true;
    for (auto it = relations.begin(); it != relations.end(); ++it) {
        res = res && (*it)->deleteAllCouplesOf(id);
    }
    return res;
}

void RelationManager::addRelation(QString relationTitle, QString relationDescp, bool oriented) {
    Relation *newRelation = new Relation(relationTitle, relationDescp, oriented);
    relations.push_back(newRelation);
}

void RelationManager::deleteRelation(int relationIdx) {
    Q_ASSERT(relationIdx >= 0 && relationIdx < (int)relations.size());
    delete (relations[relationIdx]);
    relations.erase(relations.begin() + relationIdx);
}

bool RelationManager::checkExist(int relationIdx, int id1, int id2) {
    Q_ASSERT(relationIdx >= 0 && relationIdx < (int)relations.size());
    return relations[relationIdx]->checkExist(id1, id2);
}
