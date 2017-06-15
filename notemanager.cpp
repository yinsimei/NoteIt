#include <QtGlobal>
#include <unordered_map>
#include <vector>

#include "notemanager.h"
#include "article.h"
#include "note.h"
#include "task.h"
#include "resource.h"

NoteManager::Handler NoteManager::handler = NoteManager::Handler();

NoteManager &NoteManager::getInstance(){
    if (!handler.instance)
        handler.instance =new NoteManager();
    return *handler.instance;
}

NoteManager::~NoteManager() {
    clear();
}

void NoteManager::clear() {
    for (auto it = articles.begin(); it != articles.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            delete (*it2);
            *it2 = nullptr;
        }
        it->second.clear();
    }
    articles.clear();

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            delete (*it2);
            *it2 = nullptr;
        }
        it->second.clear();
    }
    tasks.clear();

    for (auto it = resources.begin(); it != resources.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            delete (*it2);
            *it2 = nullptr;
        }
        it->second.clear();
    }
    tasks.clear();
}

Article *NoteManager::getArticle(int id, int version) {
    const vector<Article *> &res = getArticleVersions(id);
    Q_ASSERT(version >=0 && version < (int)res.size());
    return res[version];
}

Article *NoteManager::getLastestArticleVersion(int id) {
    return getArticleVersions(id).back();
}

Task *NoteManager::getTask(int id, int version) {
    const vector<Task *> &res = getTaskVersions(id);
    Q_ASSERT(version >=0 && version < (int)res.size());
    return res[version];
}

Task *NoteManager::getLastestTaskVersion(int id) {
    return getTaskVersions(id).back();
}

Resource *NoteManager::getResource(int id, int version) {
    const vector<Resource *> &res = getResourceVersions(id);
    Q_ASSERT(version >=0 && version < (int)res.size());
    return res[version];
}

Resource *NoteManager::getLastestResourceVersion(int id) {
    return getResourceVersions(id).back();
}

vector<Article *> &NoteManager::getArticleVersions(int id){
    Q_ASSERT(articles.find(id) != articles.end());
    return articles[id];

}

vector<int> NoteManager::getArticles(EnumNoteStatus noteStatus){
    vector<int> res;
    for (auto it = articles.begin(); it != articles.end(); ++it) {
        if (it->second.back()->getNoteStatus() == noteStatus) {
            res.push_back(it->first);
        }
    }
    return res;
}

int NoteManager::addArticle(const Article& a){
    int id = a.getId();
    Article* article_ptr = new Article(a);
    if (id >= 0) {
        Q_ASSERT(articles.find(id) != articles.end());
        vector<Article *> &articleVersions = articles[id];
        articleVersions.push_back(article_ptr);
    } else {
        id = cur_id;
        vector<Article *> article;
        Article* article_ptr = new Article(a);
        article_ptr->setId(id);
        article.push_back(article_ptr);
        articles[id] = article;
        cur_id++;
    }
    return id;
}

vector<Task *> &NoteManager::getTaskVersions(int id){
    if (tasks.find(id) == tasks.end()) {
        throw NotesException("Task not found");
    }
    return tasks[id];
}

vector<int> NoteManager::getTasks(EnumNoteStatus noteStatus) {
    vector<int> res;
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->second.back()->getNoteStatus() == noteStatus) {
            res.push_back(it->first);
        }
    }
    return res;
}

int NoteManager::addTask(const Task& t){
    int id = t.getId();
    Task* task_ptr = new Task(t);
    if (id >= 0 && tasks.find(id) != tasks.end()) {
        vector<Task *> &taskVersions = tasks[id];
        taskVersions.push_back(task_ptr);
    } else {
        id = cur_id;
        vector<Task *> task;
        task_ptr->setId(id);
        task.push_back(task_ptr);
        tasks[id] = task;
        cur_id++;
    }
    return id;
}

vector<Resource *> &NoteManager::getResourceVersions(int id){
    if (resources.find(id) == resources.end()) {
        throw NotesException("Resource not found");
    }
    return resources[id];
}

vector<int> NoteManager::getResources(EnumNoteStatus noteStatus){
    vector<int> res;
    for (auto it = resources.begin(); it != resources.end(); ++it) {
        if (it->second.back()->getNoteStatus() == noteStatus) {
            res.push_back(it->first);
        }
    }
    return res;
}


int NoteManager::addResource(const Resource& r){
    int id = r.getId();
    Resource* resource_ptr = new Resource(r);
    if (id >= 0 && resources.find(id) != resources.end()) {
        vector<Resource *> &resourceVersions = resources[id];
        resourceVersions.push_back(resource_ptr);
    } else {
        id = cur_id;
        vector<Resource *> resource;
        resource_ptr->setId(id);
        resource.push_back(resource_ptr);
        resources[id] = resource;
        cur_id++;
    }
    return id;
}

Note *NoteManager::getNote(int id, int version) {
    if (articles.find(id) != articles.end()) {
        return getArticle(id, version);
    }
    if (tasks.find(id) != tasks.end()) {
        return getTask(id, version);
    }
    if (resources.find(id) != resources.end()) {
        return getResource(id, version);
    }
    Q_ASSERT(0);
}

Note *NoteManager::getLastestNoteVersion(int id) {
    if (articles.find(id) != articles.end()) {
        return getLastestArticleVersion(id);
    }
    if (tasks.find(id) != tasks.end()) {
        return getLastestTaskVersion(id);
    }
    if (resources.find(id) != resources.end()) {
        return getLastestResourceVersion(id);
    }
    Q_ASSERT(0);
}

vector<Note *> NoteManager::getNoteVersions(int id) {
    vector<Note *> res;
    // Article
    if (articles.find(id) != articles.end()) {
        vector<Article *> article_versions = getArticleVersions(id);
        for (auto it = article_versions.begin(); it != article_versions.end(); ++it) {
            res.push_back(*it);
        }
        return res;
    }
    // Task
    if (tasks.find(id) != tasks.end()) {
        vector<Task *> task_versions = getTaskVersions(id);
        for (auto it = task_versions.begin(); it != task_versions.end(); ++it) {
            res.push_back(*it);
        }
        return res;
    }
    // Resource
    if (resources.find(id) != resources.end()) {
        vector<Resource *> resource_versions = getResourceVersions(id);
        for (auto it = resource_versions.begin(); it != resource_versions.end(); ++it) {
            res.push_back(*it);
        }
        return res;
    }
    Q_ASSERT(0);
}

vector<int> NoteManager::getNotes(EnumNoteStatus noteStatus) {
    vector<int> res;
    // Article
    vector<int> notes_article = getArticles(noteStatus);
    res.reserve(res.size() + notes_article.size());
    res.insert(res.end(), notes_article.begin(), notes_article.end());
    // Task
    vector<int> notes_task = getTasks(noteStatus);
    res.reserve(res.size() + notes_task.size());
    res.insert(res.end(), notes_task.begin(), notes_task.end());

    // Resource
    vector<int> notes_resource = getResources(noteStatus);
    res.reserve(res.size() + notes_resource.size());
    res.insert(res.end(), notes_resource.begin(), notes_resource.end());

    return res;
}

vector<int> NoteManager::getNotes(EnumNoteType noteType, EnumNoteStatus noteStatus) {
    switch (noteType) {
    case e_article:
        return getArticles(noteStatus);
    case e_task:
        return getTasks(noteStatus);
    case e_resource:
        return getResources(noteStatus);
    case e_all:
        return getNotes(noteStatus);
    default:
        Q_ASSERT(0);
        break;
    }
}

void NoteManager::resetToVersion(int id, int index){
    // Article
    if (articles.find(id) != articles.end()) {
        vector<Article *> &articleVersions = articles[id];
        Article *version_ptr = articleVersions[index];
        articleVersions.erase(articleVersions.begin() + index);
        articleVersions.push_back(version_ptr);
        return;
    }
    // Task
    if (tasks.find(id) != tasks.end()) {
        vector<Task *> &taskVersions = tasks[id];
        Task *version_ptr = taskVersions[index];
        taskVersions.erase(taskVersions.begin() + index);
        taskVersions.push_back(version_ptr);
        return;
    }
    // Resource
    if (resources.find(id) != resources.end()) {
        vector<Resource *> &resourceVersions = resources[id];
        Resource *version_ptr = resourceVersions[index];
        resourceVersions.erase(resourceVersions.begin() + index);
        resourceVersions.push_back(version_ptr);
        return;
    }
}

void NoteManager::restoreNote(int id) {
    // Article
    if (articles.find(id) != articles.end()) {
        vector<Article *> &articleVersions = articles[id];
        articleVersions.back()->setNoteStatus(e_active);
        return;
    }
    // Task
    if (tasks.find(id) != tasks.end()) {
        vector<Task *> &taskVersions = tasks[id];
        taskVersions.back()->setNoteStatus(e_active);
        return;
    }
    // Resource
    if (resources.find(id) != resources.end()) {
        vector<Resource *> &resourceVersions = resources[id];
        resourceVersions.back()->setNoteStatus(e_active);
        return;
    }
    Q_ASSERT(0); // ID not found
}

void NoteManager::deleteNote(int id){
    // Article
    if (articles.find(id) != articles.end()) {
        vector<Article *> &articleVersions = articles[id];
        articleVersions.back()->setNoteStatus(e_deleted);
        return;
    }
    // Task
    if (tasks.find(id) != tasks.end()) {
        vector<Task *> &taskVersions = tasks[id];
        taskVersions.back()->setNoteStatus(e_deleted);
        return;
    }
    if (resources.find(id) != resources.end()) {
        vector<Resource *> &resourceVersions = resources[id];
        resourceVersions.back()->setNoteStatus(e_deleted);
        return;
    }
    Q_ASSERT(0); // ID not found
}


void NoteManager::dropNote(int id){
    //Article
    if (articles.find(id) != articles.end()) {
        vector<Article *> &articleVersions = articles[id];
        for (unsigned int i = 0; i < articleVersions.size(); ++i) {
            delete articleVersions[i];
        }
        articles.erase(id);
        return;
    }

    //Task
    if (tasks.find(id) != tasks.end()) {
        vector<Task *> &taskVersions = tasks[id];
        for (unsigned int i = 0; i < taskVersions.size(); ++i) {
            delete taskVersions[i];
        }
        tasks.erase(id);
        return;
    }

    //Resource
    if (resources.find(id) != resources.end()) {
        vector<Resource *> &resourceVersions = resources[id];
        for (unsigned int i = 0; i < resourceVersions.size(); ++i) {
            delete resourceVersions[i];
        }
        resources.erase(id);
        return;
    }
     Q_ASSERT(0); // ID not found
}

EnumNoteType NoteManager::getNoteType(int id) {
    if (articles.find(id) != articles.end())
        return e_article;
    if (tasks.find(id) != tasks.end())
        return e_task;
    if (resources.find(id) != resources.end())
        return e_resource;
    Q_ASSERT(0); // ID not found
}
