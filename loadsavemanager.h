#ifndef LOADSAVEMANAGER_H
#define LOADSAVEMANAGER_H

#include <QString>

/** @brief LoadSaveManager est une classe singleton qui gère le sauvegarde des informations dans un fichier xml et le chargement à partir d'une
 * Elle va remplir des champs privés dans NoteManager et RelationManager en passant par leurs accesseurs
 */
class LoadSaveManager
{
private:
    /** Handler singleton
    */
    struct Handler {
        LoadSaveManager* instance;
        Handler(): instance(nullptr) {}
        ~Handler() { if (instance) delete instance; }
    };

    mutable QString filename;
    static Handler handler;
    LoadSaveManager();
    ~LoadSaveManager();
public:
    /** Getter singleton
    */
    static LoadSaveManager &getInstance();
    // save & load file
    /** Getter de nom du fichier
    */
    QString getFilename() const { return filename; }
    /** Setter de nom du fichier
    */
    void setFilename(const QString& f) { filename = f; }
    /** Chargement des notes dans NoteManager et relations dans RelationManager
    */
    void load(); // load notes from file filename
    /** Sauvegarde des notes et relations dans une fichier xml
    */
    void save() const; // save notes in file filename
};

#endif // LOADSAVEMANAGER_H
