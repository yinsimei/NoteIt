/*! \mainpage projet LO21 - programmation orientée objet
 *
 * \section Introduction
 * L’objectif de ce projet est de concevoir et développer l’application NoteIt, destinée à éditer et gérer un ensemble de notes (des mémos)
 * qui peuvent correspondre à du texte ou des images. Une note peut par exemple correspondre au compte-rendu d’une réunion, à des notes
 * prises lors d’une séance de cours, ou encore à des tâches à effectuer. *
 */
#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <unordered_map>
#include <vector>

#include "article.h"
#include "task.h"
#include "resource.h"
#include "note.h"

using namespace std;

/**
 * @brief NotesException qui permet la gestion des erreur
*/
class NotesException {
private:
    QString msg;
public:
    NotesException(const QString &m) : msg(m) {}
    QString getMsg() const { return msg; }
};

/**
 * @brief NoteManager est une classe sigleton qui permet de gérer tout ce qui concenrne des notes
*/
class NoteManager
{
protected:
    friend class LoadSaveManager;
    /**
     * @brief singleton Handler
    */
    struct Handler {
        NoteManager* instance;
        Handler(): instance(nullptr) {}
        ~Handler() { if (instance) delete instance; }
    };

    static Handler handler; ///< signleton handler
    unordered_map<int, vector<Article *>> articles; ///< un map qui enregistres toues les verions des articles
    unordered_map<int, vector<Task *>> tasks; ///< un map qui enregistres toues les verions des tasks
    unordered_map<int, vector<Resource *>> resources; ///< un map qui enregistres toues les verions des resources
    int cur_id; ///< un incrementeur de l'identité
    NoteManager() : cur_id(0) {}
    ~NoteManager();

public:
    static NoteManager &getInstance();
    void clear();

    // Articles
    /** Getter d'un article selon
     * @param id[in] l'identificateur
     * @param version[in] l'index de version dans vector
    */
    Article *getArticle(int id, int version);
    /** Getter de la dernière version d'article
     * @param id[in] l'identificateur
    */
    Article *getLastestArticleVersion(int id);
    /** Getter de toutes les version d'un article
     * @param id[in] l'identificateur
    */
    vector<Article *> &getArticleVersions(int id);
    /** Getter d'un ensemble des identificateurs des articles d'un certain état
     * @param noteStatus[in] l'état de note
    */
    vector<int> getArticles(EnumNoteStatus noteStatus);
    /** Ajouter un nouvel article/une nouvelle version d'article dans la liste, determiné par l'existenece de son id ou pas
     * @param a[in] article en entrée
    */
    int addArticle(const Article& a);

    // Tasks
    Task *getTask(int id, int version);
    Task *getLastestTaskVersion(int id);
    vector<Task *> &getTaskVersions(int id);
    vector<int> getTasks(EnumNoteStatus noteStatus);
    int addTask(const Task& note);

    // Resources
    Resource *getResource(int id, int version);
    Resource *getLastestResourceVersion(int id);
    vector<Resource *> &getResourceVersions(int id);
    vector<int> getResources(EnumNoteStatus noteStatus);
    int addResource(const Resource& r);

    // Notes
    /** Getter d'une note
     * @param id[in] l'identificateur de note
     * @param version[in] l'index de version dans vector
    */
    Note *getNote(int id, int version);
    /** Getter de la dernière version de note
     * @param id[in] l'identificateur de note
    */
    Note *getLastestNoteVersion(int id);
    /** Getter de toutes les version de note
     * @param id[in] l'identificateur de note
    */
    vector<Note *> getNoteVersions(int id);
    /** Getter d'un ensemble des identificateurs de certain type d'un certain état
     * @param noteStatus[in] l'état de note
     * @param noteType[in] le type de note
    */
    vector<int> getNotes(EnumNoteType noteType, EnumNoteStatus noteStatus);
    /** Getter d'un ensemble des identificateurs d'un certain état
     * @param noteStatus[in] l'état de note
    */
    vector<int> getNotes(EnumNoteStatus noteStatus);
    /** Reset de note à une ancienne version
     * @param id[in] l'identificateur de note à reset
     * @param index[in] l'index de version
    */
    void resetToVersion(int id, int index);
    /** Restaurer une note du corbeille
     * @param id[in] l'identificateur de note à restaurer
    */
    void restoreNote(int id);
    /** Mettre une note dans la corbeille
     * @param id[in] l'identificateur de note à supprimer (mettre en corbeille)
    */
    void deleteNote(int id);
    /** Supprimer une note définitivement
     * @param id[in] l'identificateur de note à Supprimer définitivement
    */
    void dropNote(int id);

    /** Obtenir le type de note à partir de son id
     * @param id[in] l'identificateur de note
    */
    EnumNoteType getNoteType(int id);
};

#endif // NOTEMANAGER_H
