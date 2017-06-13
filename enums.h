#ifndef ENUMS_H
#define ENUMS_H

#include <QMap>
#include <QString>
// Notes
class EnumNames : public QMap<int,QString>
{
private:
    int cnt;
public:
    EnumNames() : cnt(0) {}
    inline EnumNames &operator<< (const QString &s) {
        insert(cnt, s);
        ++cnt;
        return *this;
    }
};

enum  EnumNoteStatus {
    e_active,
    e_deleted
};
const EnumNames noteStatusNames = EnumNames() << "Active" << "Supprimé" << "Archivé";

enum EnumNoteType {
    e_article,
    e_task,
    e_resource,
    e_all
};

enum ResourceType{
    e_image,
    e_audio,
    e_video
};
const EnumNames resourceTypeNames = EnumNames() << "Image" << "Audio" << "Vidéo";

enum EnumTaskStatus {
    e_notStarted,
    e_ongoing,
    e_finished
};
const EnumNames taskStatusNames = EnumNames() << "Non démarré" << "En cours" << "Fini";

enum EnumPriority {
    e_low,
    e_normal,
    e_high,
    e_highest
};
const EnumNames priorityNames = EnumNames() << "Basse" << "Normale" << "Élevée" << "Urgente";

#endif // ENUMS_H
