#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QDateTime>
#include "note.h"

using namespace std;

class Task : public Note {
private:
    QString action;
    EnumPriority priority;
    QDateTime deadline;
    EnumTaskStatus taskStatus;
public:
    Task() : Note(), action(""), priority(e_normal), deadline(QDateTime::currentDateTime()), taskStatus(e_notStarted) {}

    Task(const Task &t) : Note(){
        setDateCreate(t.getDateCreate());
        setTitle(t.getTitle());
        setId(t.getId());
        setDateModif(t.getDateModif());
        setNoteStatus(t.getNoteStatus());
        setAction(t.getAction());
        setPriority(t.getPriority());
        setDeadline(t.getDeadline());
        setTaskStatus(t.getTaskStatus());
    }


    const QString &getAction() const { return action; }
    EnumPriority getPriority() const { return priority; }
    EnumTaskStatus getTaskStatus() const { return taskStatus; }
    const QDateTime &getDeadline() const { return deadline; }

    void setAction(const QString &tx) { action = tx; }
    void setPriority(EnumPriority p) { priority = p; }
    void setDeadline(QDateTime dl) { deadline = dl; }
    void setTaskStatus(EnumTaskStatus ts) { taskStatus = ts; }
};

#endif // TASK_H
