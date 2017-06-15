#ifndef RESSOURCE_H
#define RESSOURCE_H
#include <QString>
#include "note.h"

using namespace std;

/** @brief  Resource hérite de Note, qui contient queleques attibuts en plus (url, description de resource, ...)
 */
class Resource :  public Note {
private:
    friend class LoadSaveManager;
    QString descp;
    QString url;
    ResourceType type;
protected:
    /** accesseur à type en écriture
    */
    void setType(ResourceType t) { type = t; }
public:
    /** Constructeur par défaut
    */
    Resource()
        : Note(), descp(""), url(""), type(e_image) {}
    /** Constructeur
     * @param [in] typ type de resource
    */
    Resource(ResourceType typ)
        : Note(), descp(""), url(""), type(typ) {}
    /** Constructeur de recopie
     * @param [in] r resource à copier
    */
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
    /** accesseur à description en lecture
    */
    const QString &getDescp() const { return descp; }
    /** accesseur à Url en lecture
    */
    const QString &getUrl() const { return url; }
    /** accesseur à type en lecture
    */
    ResourceType getType() const { return type; }
    /** accesseur à description en écriture
    */
    void setDescp(const QString &de) { descp = de; }
    /** accesseur à Url en écriture
    */
    void setUrl(const QString &u) { url = u; }
};

#endif // RESSOURCE_H
