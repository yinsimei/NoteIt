#ifndef NOTE_H
#define NOTE_H
#include <QString>
#include <QDateTime>
#include "enums.h"

using namespace std;

/**
 * @brief Note est une classe abstraire qui est la classe parente de Article, Resource et Task
*/
class Note
{    
protected:
    int id; ///< identificateur de note
    QString title; ///< titre de note
    QDateTime dateCreate; ///< date de création
    QDateTime dateModif; ///< date de modification
    EnumNoteStatus noteStatus; ///< état de note : active ou supprmée
    bool archived; ///< si supprimée, archivée ou pas

public:
    Note() : id(-1), title(""), dateCreate(QDateTime::currentDateTime()),
        dateModif(QDateTime::currentDateTime()), noteStatus(e_active), archived(false) {}
    /** Getter de l'identifiacteur de note
    */
    int getId()const {return id;}
    /** Getter de l'état de note
    */
    EnumNoteStatus getNoteStatus() const { return noteStatus; }
    /** Getter du titre de note
    */
    const QString &getTitle() const { return title; }
    /** Getter de la date de création de note
    */
    const QDateTime &getDateCreate() const { return dateCreate; }
    /** Getter de la date de modification de note
    */
    const QDateTime &getDateModif() const { return dateModif; }
    /** Si la note est archivée
    */
    bool isArchived() const { return archived; }

    /** Setter de l'identifiacteur de note
    */
    void setId(int i){id = i;}
    /** Setter du titre de note
    */
    void setTitle(const QString &t) {title = t;}
    /** Setter de la date de création de note
    */
    void setDateCreate(const QDateTime &dc) {dateCreate = dc;}
    /** Setter de la date de modification de note
    */
    void setDateModif(const QDateTime &dm) {dateModif = dm;}
    /** Setter de l'état de note
    */
    void setNoteStatus(EnumNoteStatus ns) {noteStatus = ns;}
    /** Setter si le note est archivée
    */
    void setArchived(bool a) { archived = a; }
};



#endif // NOTE_H
