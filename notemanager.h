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
    string msg;
public:
    NotesException(const string &m) : msg(m) {}
    string getMsg() const { return msg; }
};

class NoteManager
{
private:
    static NoteManager* instance;
    unordered_map<int, vector<Article *>> articles;
    unordered_map<int, vector<Task *>> tasks;
    unordered_map<int, vector<Resource *>> resources;
    int cur_id;
    NoteManager() : cur_id(0) {}

public:
    static NoteManager &getInstance();
    static void freeInstance();

    Article *getLastestArticleVersion(int id);
    vector<Article *> &getArticleVersions(int id);
    vector<int> getArticles(EnumNoteStatus noteStatus);
    void addArticle(const Article& note);
    Article *editArticle(int id);

    Task *getLastestTaskVersion(int id);
    vector<Task *> &getTaskVersions(int id);
    vector<int> getTasks(EnumNoteStatus noteStatus);
    void addTask(const Task& note);
    Task *editTask(int id);

    Resource *getLastestResourceVersion(int id);
    vector<Resource *> &getResourceVersions(int id);
    vector<int> getResources(EnumNoteStatus noteStatus);
    void addResource(const Resource& r);
    Resource *editResource(int id);

    void resetToVersion(int id, int index);
    void deleteNote(int id);
    void archiveNote(int id);
};

#endif // NOTEMANAGER_H