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
public:
    Resource(const QDateTime & dc, const QString &t, ResourceType typ)
        : Note(dc, t), descp(""), url(""), type(typ) {}

    Resource(const Resource & r) : Note(r.getDateCreate(), r.getTitle()) {
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
    void setType(ResourceType t) { type = t; }

};

class Image : public Resource {
public:
    Image(const QDateTime &dc, const QString &t)
        : Resource(dc, t, e_image) {}
};

class Audio : public Resource {
public:
    Audio(const QDateTime & dc, const QString &t)
        : Resource(dc, t, e_audio) {}
};

class Video : public Resource {
public:
    Video(const QDateTime & dc, const QString &t)
        : Resource(dc, t, e_video) {}
};

#endif // RESSOURCE_H
