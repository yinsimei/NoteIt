#ifndef ENUMS_H
#define ENUMS_H

#include <QMap>
#include <QString>
// Notes
/** @brief EnumNames est un outil développé pour faciliter la conversion entre enum et QString. Elle hérite de QMap.
 */
class EnumNames : public QMap<int,QString>
{
private:
    int cnt;
public:
    EnumNames() : cnt(0) {}
    /** On surcharge l'opérateur << pour donner les QString pour des enums en ordre
     @param s[in] string d'un enum
    */
    inline EnumNames &operator<< (const QString &s) {
        insert(cnt, s);
        ++cnt;
        return *this;
    }
};

/** @brief EnumNoteStatus : deux états de note : active ou supprimée, l'état archivée est representée par un bool à côté pour simplifier le recherche des notes dans la corbeille*/
enum  EnumNoteStatus {
    e_active, /**< active*/
    e_deleted /**< supprimée*/
};
const EnumNames noteStatusNames = EnumNames() << "Active" << "Supprimé" << "Archivé";

/** @brief EnumNoteType : 3 types de notes : e_article, e_task, e_resource, et e_all qui représente un ensemble des tous les notes */
enum EnumNoteType {
    e_article, /**< article*/
    e_task, /**< tâche*/
    e_resource, /**< resource*/
    e_all /**< un ensemble des tous les notes*/
};

/** @brief EnumNoteType : 3 types de resources : image, audio, vidéo*/
enum ResourceType{
    e_image, /**< image*/
    e_audio, /**< audio*/
    e_video /**< vidéo*/
};
const EnumNames resourceTypeNames = EnumNames() << "Image" << "Audio" << "Vidéo";

/** @brief EnumTaskStatus : non démarré, en cours, fini*/
enum EnumTaskStatus {
    e_notStarted, /**< non démarré*/
    e_ongoing, /**< en cours*/
    e_finished /**< fini*/
};
const EnumNames taskStatusNames = EnumNames() << "Non démarré" << "En cours" << "Fini";

/** @brief EnumPriority : basse, normale, haute, urgente
 */
enum EnumPriority {
    e_low, /**< basse*/
    e_normal, /**< normale*/
    e_high,/**< Élevée*/
    e_highest /**< Urgente*/
};
const EnumNames priorityNames = EnumNames() << "Basse" << "Normale" << "Élevée" << "Urgente";

#endif // ENUMS_H
