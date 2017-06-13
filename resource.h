#ifndef RESSOURCE_H
#define RESSOURCE_H
#include <QString>
#include "note.h"

using namespace std;

class Resource :  public Note {
private:
    QString descp;
    QString url;
    ResourceType type;
protected:
    void setType(ResourceType t) { type = t; }
public:
    Resource(ResourceType typ)
        : Note(), descp(""), url(""), type(typ) {}

    Resource(const Resource & r) : Note() {
        setDateCreate(r.getDateCreate());
        setTitle(r.getTitle());
        setId(r.getId());
        setDateModif(r.getDateModif());
        setNoteStatus(r.getNoteStatus());
        setDescp(r.getDescp());
        setUrl(r.getUrl());
        setType(r.getType());
    }

    const QString &getDescp() const { return descp; }
    const QString &getUrl() const { return url; }
    ResourceType getType() const { return type; }

    void setDescp(const QString &de) { descp = de; }
    void setUrl(const QString &u) { url = u; }
};

#endif // RESSOURCE_H
