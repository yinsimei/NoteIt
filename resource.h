#ifndef RESSOURCE_H
#define RESSOURCE_H
#include <string>
#include "note.h"

using namespace std;

class Resource :  public Note {
public:
    enum ResourceType{
        image,
        audio,
        video
    };

private:
    string descp;
    string url;
    ResourceType type;
public:
    Resource(const QDateTime & dc, const string &t, ResourceType typ)
        : Note(dc, t), descp(""), Url(""), type(typ) {}

    Resource(const Resource & r) {
        setId(r.getId());
        setTitle(r.getTitle());
        setDateCreate(r.getDateCreate());
        setDateModif(r.getDateModif());
        setNoteStatus(r.getStatus());
        setDescp(r.getDescp);
        setUrl(r.getUrl());
        setType(r.getType());
    }

    const string &getDescp() const {return descp;}
    const string &getUrl() const {return url;}
    ResourceType &getType() const {return type;}

    void setDescp(const string &de) {descp = de;}
    void setUrl(const string &u) {url = u;}
    void setType(ResourceType ) {url = u;}

};

class Image : public Resource {
public:
    Image(const QDateTime & dc, const string &t)
        : Ressource(dc, t, image) {}
};

class Audio : public Resource {
public:
    Audio(const QDateTime & dc, const string &t)
        : Ressource(dc, t, audio) {}
};

class Video : public Resource {
public:
    Video(const QDateTime & dc, const string &t)
        : Ressource(dc, t, video) {}
};

#endif // RESSOURCE_H
