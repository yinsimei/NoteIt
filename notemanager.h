#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <unordered_map>
#include <vector>

#include "article.h"
#include "task.h"
#include "resource.h"
#include "note.h"

using namespace std;

class NotesException {
private:
    QString msg;
public:
    NotesException(const QString &m) : msg(m) {}
    QString getMsg() const { return msg; }
};

class NoteManager
{
private:
    struct Handler {
        NoteManager* instance;
        Handler(): instance(nullptr) {}
        ~Handler() { if (instance) delete instance; }
    };

    static Handler handler;
    unordered_map<int, vector<Article *>> articles;
    unordered_map<int, vector<Task *>> tasks;
    unordered_map<int, vector<Resource *>> resources;
    int cur_id;
    NoteManager() : cur_id(0) {}
    ~NoteManager();

public:
    static NoteManager &getInstance();

    // Articles
    Article *getArticle(int id, int version);
    Article *getLastestArticleVersion(int id);
    vector<Article *> &getArticleVersions(int id);
    vector<int> getArticles(EnumNoteStatus noteStatus);
    int addArticle(const Article& note);

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
    Note *getNote(int id, int version);
    Note *getLastestNoteVersion(int id);
    vector<Note *> getNoteVersions(int id);
    vector<int> getNotes(EnumNoteType noteType, EnumNoteStatus noteStatus);
    vector<int> getNotes(EnumNoteStatus noteStatus);
    void resetToVersion(int id, int index);
    void restoreNote(int id);
    void deleteNote(int id);
    void dropNote(int id);

    EnumNoteType getNoteType(int id);
};

#endif // NOTEMANAGER_H
