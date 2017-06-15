#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include "loadsavemanager.h"
#include "notemanager.h"
#include "relationmanager.h"

LoadSaveManager::Handler LoadSaveManager::handler = LoadSaveManager::Handler();

LoadSaveManager::LoadSaveManager() : filename("")
{

}

LoadSaveManager &LoadSaveManager::getInstance(){
    if (!handler.instance)
        handler.instance =new LoadSaveManager();
    return *handler.instance;
}

LoadSaveManager::~LoadSaveManager(){
    //if (filename != "") save();
}

void LoadSaveManager::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("datafile");

    NoteManager &noteManager = NoteManager::getInstance();

    // NOTES
    stream.writeStartElement("notes");
    stream.writeTextElement("cur_id", QString::number(noteManager.cur_id));

    // ARTICLES
    stream.writeStartElement("articles");
    for (auto it = noteManager.articles.begin(); it != noteManager.articles.end(); ++it){
        stream.writeStartElement("articleVersions");
        stream.writeTextElement("id", QString::number(it->first));
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            stream.writeStartElement("article");
            stream.writeTextElement("id", QString::number((*it2)->getId()));
            stream.writeTextElement("noteStatus", QString::number((*it2)->getNoteStatus()));
            stream.writeTextElement("title", (*it2)->getTitle());
            stream.writeTextElement("dateCreate", (*it2)->getDateCreate().toString());
            stream.writeTextElement("dateModif", (*it2)->getDateModif().toString());
            stream.writeTextElement("isArchived", QString::number((*it2)->isArchived()));

            stream.writeTextElement("text", (*it2)->getText());
            stream.writeEndElement(); // end article
        }
        stream.writeEndElement(); // end article versions
    };
    stream.writeEndElement(); // end articles

    // TASKS
    stream.writeStartElement("tasks");
    for (auto it = noteManager.tasks.begin(); it != noteManager.tasks.end(); ++it){
        stream.writeStartElement("taskVersions");
        stream.writeTextElement("id", QString::number(it->first));
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            stream.writeStartElement("task");
            stream.writeTextElement("id", QString::number((*it2)->getId()));
            stream.writeTextElement("noteStatus", QString::number((*it2)->getNoteStatus()));
            stream.writeTextElement("title", (*it2)->getTitle());
            stream.writeTextElement("dateCreate", (*it2)->getDateCreate().toString());
            stream.writeTextElement("dateModif", (*it2)->getDateModif().toString());
            stream.writeTextElement("isArchived", QString::number((*it2)->isArchived()));

            stream.writeTextElement("action", (*it2)->getAction());
            stream.writeTextElement("priority", QString::number((*it2)->getPriority()));
            stream.writeTextElement("taskStatus", QString::number((*it2)->getTaskStatus()));
            stream.writeTextElement("deadline", (*it2)->getDeadline().toString());
            stream.writeEndElement(); // end task
        }
        stream.writeEndElement(); // end task versions
    };
    stream.writeEndElement(); // end tasks

    // RESOURCE
    stream.writeStartElement("resources");
    for (auto it = noteManager.resources.begin(); it != noteManager.resources.end(); ++it){
        stream.writeStartElement("resourceVersions");
        stream.writeTextElement("id", QString::number(it->first));
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            stream.writeStartElement("resource");
            stream.writeTextElement("id", QString::number((*it2)->getId()));
            stream.writeTextElement("noteStatus", QString::number((*it2)->getNoteStatus()));
            stream.writeTextElement("title", (*it2)->getTitle());
            stream.writeTextElement("dateCreate", (*it2)->getDateCreate().toString());
            stream.writeTextElement("dateModif", (*it2)->getDateModif().toString());
            stream.writeTextElement("isArchived", QString::number((*it2)->isArchived()));

            stream.writeTextElement("descp", (*it2)->getDescp());
            stream.writeTextElement("url", (*it2)->getUrl());
            stream.writeTextElement("type", QString::number((*it2)->getType()));
            stream.writeEndElement(); // end resource
        }
        stream.writeEndElement(); // end resource versions
    };
    stream.writeEndElement(); // end resources
    stream.writeEndElement(); // end notes

    // RELATIONS
    RelationManager &relationManager = RelationManager::getInstance();
    stream.writeStartElement("relations");
    for(auto it = relationManager.relations.begin(); it != relationManager.relations.end(); ++it){
        stream.writeStartElement("relation");
        stream.writeTextElement("title", (*it)->getTitle());
        stream.writeTextElement("descp", (*it)->getDescp());
        stream.writeTextElement("isOriented",QString::number((*it)->isOriented()));
        stream.writeTextElement("isReference",QString::number((*it)->isReference()));
        stream.writeStartElement("couples");
        for (auto it2 = (*it)->getCouples().begin(); it2 != (*it)->getCouples().end(); ++it2) {
            stream.writeStartElement("couple");
            stream.writeTextElement("title", (*it2).label);
            stream.writeTextElement("n1", QString::number((*it2).n1));
            stream.writeTextElement("n2", QString::number((*it2).n2));
            stream.writeEndElement(); // end couple
        }
        stream.writeEndElement(); // end couples
        stream.writeEndElement(); // end relation
    }
    stream.writeEndElement(); // end relations

    stream.writeEndElement(); // end datafile
    stream.writeEndDocument(); // end document
    newfile.close();
}

void LoadSaveManager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;

        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if (xml.name() == "datafile") continue;

            // NOTES
            if (xml.name() == "notes") {
                NoteManager &noteManager = NoteManager::getInstance();
                noteManager.clear();
                xml.readNext();
                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "notes")) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement) {
                        if (xml.name() == "cur_id") {
                            xml.readNext();
                            noteManager.cur_id = xml.text().toInt();
                        }

                        // ARTICLES
                        if (xml.name() == "articles") {
                            xml.readNext();
                            while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "articles")) {
                                if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if (xml.name() == "articleVersions") {
                                        int id_article_version = -1;
                                        xml.readNext();
                                        while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "articleVersions")) {
                                            if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                                if (xml.name() == "id") {
                                                    xml.readNext();
                                                    id_article_version = xml.text().toInt();
                                                    noteManager.articles[id_article_version] = vector<Article *>();
                                                }

                                                if (xml.name() == "article") {
                                                    Article new_article;
                                                    Q_ASSERT(id_article_version >= 0);
                                                    xml.readNext();
                                                    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                                                        if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                                            if (xml.name() == "id") {
                                                                xml.readNext();
                                                                new_article.setId(xml.text().toInt());
                                                            }
                                                            if (xml.name() == "noteStatus") {
                                                                xml.readNext();
                                                                new_article.setNoteStatus((EnumNoteStatus)xml.text().toInt());
                                                            }
                                                            if (xml.name() == "noteStatus") {
                                                                xml.readNext();
                                                                new_article.setNoteStatus((EnumNoteStatus)xml.text().toInt());
                                                            }
                                                            if (xml.name() == "title") {
                                                                xml.readNext();
                                                                new_article.setTitle(xml.text().toString());
                                                            }
                                                            if (xml.name() == "dateCreate") {
                                                                xml.readNext();
                                                                new_article.setDateCreate(QDateTime::fromString(xml.text().toString()));
                                                            }
                                                            if (xml.name() == "dateModif") {
                                                                xml.readNext();
                                                                new_article.setDateModif(QDateTime::fromString(xml.text().toString()));
                                                            }
                                                            if (xml.name() == "isArchived") {
                                                                xml.readNext();
                                                                new_article.setArchived((bool)xml.text().toInt());
                                                            }
                                                            if (xml.name() == "text") {
                                                                xml.readNext();
                                                                new_article.setText(xml.text().toString());
                                                            }
                                                        }
                                                        xml.readNext();
                                                    }
                                                    noteManager.addArticle(new_article);
                                                }
                                            }
                                            xml.readNext();
                                        }
                                        // do nothing here
                                    }
                                }
                                xml.readNext();
                            }
                        }

                        // TASKS
                        if (xml.name() == "tasks") {
                            xml.readNext();
                            while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tasks")) {
                                if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if (xml.name() == "taskVersions") {
                                        int id_task_version = -1;
                                        xml.readNext();
                                        while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "taskVersions")) {
                                            if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                                if (xml.name() == "id") {
                                                    xml.readNext();
                                                    id_task_version = xml.text().toInt();
                                                    noteManager.tasks[id_task_version] = vector<Task *>();
                                                }

                                                if (xml.name() == "task") {
                                                    Task new_task;
                                                    Q_ASSERT(id_task_version >= 0);
                                                    xml.readNext();
                                                    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "task")) {
                                                        if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                                            if (xml.name() == "id") {
                                                                xml.readNext();
                                                                new_task.setId(xml.text().toInt());
                                                            }
                                                            if (xml.name() == "noteStatus") {
                                                                xml.readNext();
                                                                new_task.setNoteStatus((EnumNoteStatus)xml.text().toInt());
                                                            }
                                                            if (xml.name() == "noteStatus") {
                                                                xml.readNext();
                                                                new_task.setNoteStatus((EnumNoteStatus)xml.text().toInt());
                                                            }
                                                            if (xml.name() == "title") {
                                                                xml.readNext();
                                                                new_task.setTitle(xml.text().toString());
                                                            }
                                                            if (xml.name() == "dateCreate") {
                                                                xml.readNext();
                                                                new_task.setDateCreate(QDateTime::fromString(xml.text().toString()));
                                                            }
                                                            if (xml.name() == "dateModif") {
                                                                xml.readNext();
                                                                new_task.setDateModif(QDateTime::fromString(xml.text().toString()));
                                                            }
                                                            if (xml.name() == "isArchived") {
                                                                xml.readNext();
                                                                new_task.setArchived((bool)xml.text().toInt());
                                                            }
                                                            if (xml.name() == "action") {
                                                                xml.readNext();
                                                                new_task.setAction(xml.text().toString());
                                                            }
                                                            if (xml.name() == "priority") {
                                                                xml.readNext();
                                                                new_task.setPriority((EnumPriority)xml.text().toInt());
                                                            }
                                                            if (xml.name() == "taskStatus") {
                                                                xml.readNext();
                                                                new_task.setTaskStatus((EnumTaskStatus)xml.text().toInt());
                                                            }
                                                            if (xml.name() == "deadline") {
                                                                xml.readNext();
                                                                new_task.setDeadline((QDateTime::fromString(xml.text().toString())));
                                                            }
                                                        }
                                                        xml.readNext();
                                                    }
                                                    noteManager.addTask(new_task);
                                                }
                                            }
                                            xml.readNext();
                                        }
                                        // do nothing here
                                    }
                                }
                                xml.readNext();
                            }
                        }

                        // RESOURCES
                        if (xml.name() == "resources") {
                            xml.readNext();
                            while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "resources")) {
                                if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if (xml.name() == "resourceVersions") {
                                        int id_resource_version = -1;
                                        xml.readNext();
                                        while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "resourceVersions")) {
                                            if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                                if (xml.name() == "id") {
                                                    xml.readNext();
                                                    id_resource_version = xml.text().toInt();
                                                    noteManager.resources[id_resource_version] = vector<Resource *>();
                                                }

                                                if (xml.name() == "resource") {
                                                    Resource new_resource;
                                                    Q_ASSERT(id_resource_version >= 0);
                                                    xml.readNext();
                                                    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "resource")) {
                                                        if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                                            if (xml.name() == "id") {
                                                                xml.readNext();
                                                                new_resource.setId(xml.text().toInt());
                                                            }
                                                            if (xml.name() == "noteStatus") {
                                                                xml.readNext();
                                                                new_resource.setNoteStatus((EnumNoteStatus)xml.text().toInt());
                                                            }
                                                            if (xml.name() == "noteStatus") {
                                                                xml.readNext();
                                                                new_resource.setNoteStatus((EnumNoteStatus)xml.text().toInt());
                                                            }
                                                            if (xml.name() == "title") {
                                                                xml.readNext();
                                                                new_resource.setTitle(xml.text().toString());
                                                            }
                                                            if (xml.name() == "dateCreate") {
                                                                xml.readNext();
                                                                new_resource.setDateCreate(QDateTime::fromString(xml.text().toString()));
                                                            }
                                                            if (xml.name() == "dateModif") {
                                                                xml.readNext();
                                                                new_resource.setDateModif(QDateTime::fromString(xml.text().toString()));
                                                            }
                                                            if (xml.name() == "isArchived") {
                                                                xml.readNext();
                                                                new_resource.setArchived((bool)xml.text().toInt());
                                                            }
                                                            if (xml.name() == "descp") {
                                                                xml.readNext();
                                                                new_resource.setDescp(xml.text().toString());
                                                            }
                                                            if (xml.name() == "url") {
                                                                xml.readNext();
                                                                new_resource.setUrl(xml.text().toString());
                                                            }
                                                            if (xml.name() == "type") {
                                                                xml.readNext();
                                                                new_resource.setType((ResourceType)xml.text().toInt());
                                                            }

                                                        }
                                                        xml.readNext();
                                                    }
                                                    noteManager.addResource(new_resource);
                                                }
                                            }
                                            xml.readNext();
                                        }
                                        // do nothing here
                                    }
                                }
                                xml.readNext();
                            }
                        }

                    }
                    xml.readNext();
                }
            }

            // RELATIONS
            if (xml.name() == "relations") {
                RelationManager &relationManager = RelationManager::getInstance();
                relationManager.clear();
                xml.readNext();
                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "relations")) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement) {
                        if (xml.name() == "relation") {
                            Relation relation;
                            xml.readNext();
                            while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "relation")) {
                                if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if (xml.name() == "title") {
                                        xml.readNext();
                                        relation.setTitle(xml.text().toString());
                                    }
                                    if (xml.name() == "descp") {
                                        xml.readNext();
                                        relation.setDescp(xml.text().toString());
                                    }
                                    if (xml.name() == "isOriented") {
                                        xml.readNext();
                                        relation.setOriented((bool)xml.text().toInt());
                                    }
                                    if (xml.name() == "isReference") {
                                        xml.readNext();
                                        relation.setReference((bool)xml.text().toInt());
                                    }
                                    if (xml.name() == "couples") {
                                        xml.readNext();
                                        while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "couples")) {
                                            if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                                if (xml.name() == "couple") {
                                                    Couple couple;
                                                    xml.readNext();
                                                    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "couple")) {
                                                        if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                                            if (xml.name() == "title") {
                                                                xml.readNext();
                                                                couple.label = xml.text().toString();
                                                            }
                                                            if (xml.name() == "n1") {
                                                                xml.readNext();
                                                                couple.n1 = xml.text().toInt();
                                                            }
                                                            if (xml.name() == "n2") {
                                                                xml.readNext();
                                                                couple.n2 = xml.text().toInt();
                                                            }
                                                        }
                                                        xml.readNext();
                                                    }
                                                    relation.couples.push_back(couple);
                                                }
                                            }
                                            xml.readNext();
                                        }
                                    }
                                }
                                xml.readNext();
                            }
                            relationManager.addRelation(-1, relation);
                        }
                    }
                    xml.readNext();
                }
            }
        }
    }

    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }

    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    fin.close();
}
