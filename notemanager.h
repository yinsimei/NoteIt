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
    /** Constructeur
     * @param [in] m message à afficher
    */
    NotesException(const QString &m) : msg(m) {}
    /** accesseur au message en lecture
    */
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
        NoteManager* instance; ///< singleton instance
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
    /** singleton
    */
    static NoteManager &getInstance();
    /** supprimer tous les notes
    */
    void clear();

    // Articles
    /** Getter d'un article selon
     * @param [in] id l'identificateur
     * @param [in] version l'index de version dans vector
    */
    Article *getArticle(int id, int version);
    /** Getter de la dernière version d'article
     * @param [in] id l'identificateur
    */
    Article *getLastestArticleVersion(int id);
    /** Getter de toutes les version d'un article
     * @param [in] id l'identificateur
    */
    vector<Article *> &getArticleVersions(int id);
    /** Getter d'un ensemble des identificateurs des articles d'un certain état
     * @param [in] noteStatus l'état de note
    */
    vector<int> getArticles(EnumNoteStatus noteStatus);
    /** Ajouter un nouvel article/une nouvelle version d'article dans la liste, determiné par l'existenece de son id ou pas
     * @param [in] a article en entrée
    */
    int addArticle(const Article& a);

    // Tasks
    /** Getter d'une tache selon
     * @param [in] id l'identificateur
     * @param [in] version l'index de version dans vector
    */
    Task *getTask(int id, int version);
    /** Getter de la dernière version de tache
     * @param [in] id l'identificateur
    */
    Task *getLastestTaskVersion(int id);
    /** Getter de toutes les version d'une tache
     * @param [in] id l'identificateur
    */
    vector<Task *> &getTaskVersions(int id);
    /** Getter d'un ensemble des identificateurs des taches d'un certain état
     * @param [in] noteStatus l'état de note
    */
    vector<int> getTasks(EnumNoteStatus noteStatus);
    /** Ajouter un nouveau tache/une nouvelle version de tache dans la liste, determiné par l'existenece de son id ou pas
     * @param [in] note tache en entrée
    */
    int addTask(const Task& note);

    // Resources
    /** Getter d'une ressource selon
     * @param [in] id l'identificateur
     * @param [in] version l'index de version dans vector
    */
    Resource *getResource(int id, int version);
    /** Getter de la dernière version de ressource
     * @param [in] id l'identificateur
    */
    Resource *getLastestResourceVersion(int id);
    /** Getter de toutes les version d'une ressource
     * @param [in] id l'identificateur
    */
    vector<Resource *> &getResourceVersions(int id);
    /** Getter d'un ensemble des identificateurs des ressource d'un certain état
     * @param [in] noteStatus l'état de note
    */
    vector<int> getResources(EnumNoteStatus noteStatus);
    /** Ajouter une nouvelle ressource/une nouvelle version de ressource dans la liste, determiné par l'existenece de son id ou pas
     * @param [in] r ressource en entrée
    */
    int addResource(const Resource& r);

    // Notes
    /** Getter d'une note
     * @param [in] id l'identificateur de note
     * @param [in] version l'index de version dans vector
    */
    Note *getNote(int id, int version);
    /** Getter de la dernière version de note
     * @param [in] id l'identificateur de note
    */
    Note *getLastestNoteVersion(int id);
    /** Getter de toutes les version de note
     * @param [in] id l'identificateur de note
    */
    vector<Note *> getNoteVersions(int id);
    /** Getter d'un ensemble des identificateurs de certain type d'un certain état
     * @param [in] noteStatus l'état de note
     * @param [in] noteType le type de note
    */
    vector<int> getNotes(EnumNoteType noteType, EnumNoteStatus noteStatus);
    /** Getter d'un ensemble des identificateurs d'un certain état
     * @param [in] noteStatus l'état de note
    */
    vector<int> getNotes(EnumNoteStatus noteStatus);
    /** Reset de note à une ancienne version
     * @param [in] id l'identificateur de note à reset
     * @param [in] index l'index de version
    */
    void resetToVersion(int id, int index);
    /** Restaurer une note du corbeille
     * @param [in] id l'identificateur de note à restaurer
    */
    void restoreNote(int id);
    /** Mettre une note dans la corbeille
     * @param [in] id l'identificateur de note à supprimer (mettre en corbeille)
    */
    void deleteNote(int id);
    /** Supprimer une note définitivement
     * @param [in] id l'identificateur de note à Supprimer définitivement
    */
    void dropNote(int id);

    /** Obtenir le type de note à partir de son id
     * @param [in] id l'identificateur de note
    */
    EnumNoteType getNoteType(int id);
};

#endif // NOTEMANAGER_H
