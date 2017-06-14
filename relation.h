#ifndef RELATION_H
#define RELATION_H

#include <QString>
#include <vector>

using namespace std;

struct Couple {
    QString label;
    int n1, n2;
    bool operator==(Couple c);
    Couple(const QString &l, int _n1, int _n2) : label(l), n1(_n1), n2(_n2) {}
};

class Relation
{
private:
    QString title;
    QString descp;
    vector<Couple> couples;
    bool oriented;
    bool reference;

public:
    Relation() : title(""), descp(""), oriented(false), reference(false) {}
    Relation(const QString &t, const QString &d, bool o, bool r = false) : title(t), descp(d), oriented(o), reference(r) {}
    const QString &getTitle() const { return title; }
    const QString &getDescp() const { return descp; }
    bool isOriented() const { return oriented; }
    bool isReference() const { return reference; }
    vector<Couple> getChildren(int n);
    vector<Couple> getParents(int n);
    vector<Couple> getRelatedNotes(int n);
    bool addCouple(int id1, int id2, const QString & label);
    void deleteCouple(int id1, int id2);
    void deleteCouple(Couple c);
    bool deleteAllCouplesOf(int id);
    bool checkExist(int id1, int id2);
};

#endif // RELATION_H
