#include <unordered_map>
#include <vector>


#include "notemanager.h"
#include "article.h"
#include "note.h"
#include "task.h"
#include "resource.h"

NoteManager* NoteManager::instance = nullptr;

NoteManager &NoteManager::getInstance(){
    if (!instance)
        instance =new NoteManager();
    return *instance;
}

void NoteManager::freeInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

Article *NoteManager::getLastestArticleVersion(int id) {
    return getArticleVersions(id).back();
}

Task *NoteManager::getLastestTaskVersion(int id) {
    return getTaskVersions(id).back();
}

Resource *NoteManager::getLastestResourceVersion(int id) {
    return getResourceVersions(id).back();
}



vector<Article *> &NoteManager::getArticleVersions(int id){
    if (articles.find(id) == articles.end()) {
        throw NotesException("not found");
    }
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

void NoteManager::addArticle(const Article& a){
    vector<Article *> article;
    Article* article_ptr = new Article(a);
    article_ptr->setId(cur_id);
    article.push_back(article_ptr);
    articles[cur_id] = article;
    cur_id++;
}

Article *NoteManager::editArticle(int id){
    if (articles.find(id) == articles.end()) {
        throw NotesException("Article not found");
    }
    vector<Article *> &articleVersions = articles[id];
    Article *version_ptr = new Article(*articleVersions.back());
    articleVersions.push_back(version_ptr);
    return version_ptr;
}

vector<Task *> &NoteManager::getTaskVersions(int id){
    if (tasks.find(id) == tasks.end()) {
        throw NotesException("not found");
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

void NoteManager::addTask(const Task& t){
    vector<Task *> task;
    Task* article_ptr = new Task(t);
    article_ptr->setId(cur_id);
    task.push_back(article_ptr);
    tasks[cur_id] = task;
    cur_id++;
}

Task* NoteManager::editTask(int id){
    if (tasks.find(id) == tasks.end()) {
        throw NotesException("not found");
    }
    vector<Task *> &taskVersions = tasks[id];
    Task *version_ptr = new Task(*taskVersions.back());
    taskVersions.push_back(version_ptr);
    return version_ptr;
}

vector<Resource *> &NoteManager::getResourceVersions(int id){
    if (resources.find(id) == resources.end()) {
        throw NotesException("not found");
    }
    return resources[id];
}

vector<Note *> NoteManager::getResources(EnumNoteStatus noteStatus){
    vector<int> res;
    for (auto it = resources.begin(); it < resources.end(); ++it) {
        if ((*it).back()->getStatus() == noteStatus) {
            res.push_back(id);
        }
    }
    return res;
}

void NoteManager::addResource(const Resource& r){
    vector<Resource *> resource = resources;
    Resource* resource_ptr = new Resource(r);
    resource_ptr->setId(cur_id);
    resource.push_back(resource_ptr);
    cur_id++;
}

Resource* NoteManager::editResource(int id){
    if (resources.find(id) == resources.end()) {
      throw NotesException("not found");
        return null;
    }
    vector<Resource *> &resourceVersions = resources[id];
    Resource *version_ptr = new Resource(resources[id].back());
    resourceVersions.push_back(version_ptr);
    return *version_ptr;
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
        Resource *version_ptr = resourceVersion[index];
        resourceVersions.erase(resourceVersions.begin() + index);
        resourceVersions.push_back(version_ptr);
        return;
    }
}

void NoteManager::archiveNote(int id){
    // Article
    if (articles.find(id) != articles.end()) {
        vector<Article *> &articleVersions = articles[id];
        int i=0;
        while (articleVersions[i] != NULL){
            articleVersions[i].setStatus(archived);
            i++;
        }

    }
}


void NoteManager::deleteNote(int id){
    //Article
    if (articles.find(id) != articles.end()) {
        vector<Article *> &articleVersions = articles[id];
        delete articleVersions;
    }
}
