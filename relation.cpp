#include "relation.h"

vector<Couple> Relation::getChildren(int n) {
    vector<Couple> res;
    for (auto it = couples.begin(); it != couples.end(); ++it) {
        if (it->n1 == n || (!oriented && it->n2 == n))
            res.push_back(*it);
    }
    return res;
}

vector<Couple> Relation::getParents(int n) {
    vector<Couple> res;
    for (auto it = couples.begin(); it != couples.end(); ++it) {
        if (it->n2== n || (!oriented && it->n1 == n))
            res.push_back(*it);
    }
    return res;
}

vector<Couple> Relation::getRelatedNotes(int n) {
    vector<Couple> res;
    for (auto it = couples.begin(); it != couples.end(); ++it) {
        if (it->n1== n || it->n2== n) {
            res.push_back(*it);
        }
    }
    return res;
}

bool Relation::addCouple(int id1, int id2, const QString &label) {
    if (checkExist(id1, id2)) {
        return false;
    }
    Couple newCouple(label, id1, id2);
    couples.push_back(newCouple);
    return true;
}

void Relation::deleteCouple(int id1, int id2) {
    auto it = couples.begin();
    while (it != couples.end()) {
        if ((it->n1== id1 && it->n2== id2) || (!oriented && it->n1== id2 && it->n2== id1)) {
            it = couples.erase(it);
        } else {
            ++it;
        }
    }
}

void Relation::deleteCouple(Couple c) {
    auto pos = find(couples.begin(), couples.end(), c);
    if (pos != couples.end())
        couples.erase(pos);
    else
        Q_ASSERT(0); // don't find the couple to delete
}

bool Relation::deleteAllCouplesOf(int id) {
    bool res = true;
    auto it = couples.begin();
    while (it != couples.end()) {
        if (reference && it->n2 == id) {
            res = false;
            ++it;
        } else if (it->n1== id || it->n2 == id) {
            it = couples.erase(it);
        } else {
            ++it;
        }
    }
    return res;
}

bool Relation::checkExist(int id1, int id2) {
    for (auto it = couples.begin(); it != couples.end(); ++it) {
        if (it->n1== id1 && it->n2== id2)
            return true;
        if (!oriented && it->n1== id2 && it->n2== id1)
            return true;
    }
    return false;
}

bool Couple::operator==(Couple c) {
    return (label == c.label && n1 == c.n1 && n2 == c.n2);
}
