#ifndef TASK_H
#define TASK_H
#include <string>
#include <QDateTime>
#include "note.h"

using namespace std;

class Task : public Note {
public:
    enum EnumTaskStatus {
        notStarted,
        ongoing,
        finished
    };

    enum EnumPriority {
        lowest,
        low,
        normal,
        high,
        highest
    };

private:
    string action;
    EnumPriority priority;
    QDateTime deadline;
    EnumTaskStatus taskStatus;
public:
    Task(const QDateTime & dc, const string &t)
        : Note(dc, t), action(""), priority(highest), deadline(QDateTime::currentDateTime()), taskStatus(notStarted) {}

    Task(const Task & t) {
        setId(t.getId());
        setTitle(t.getTitle());
        setDateCreate(t.getDateCreate());
        setDateModif(t.getDateModif());
        setNoteStatus(t.getNoteStatus());
        setAction(t.getAction());
        setPriority(t.getPriority());
        setDeadline(t.getDeadline());
        setTaskStatus(t.getTaskStatus());
    }


    const string &getAction() const { return action; }
    EnumPriority getPriority() const { return priority; }
    EnumTaskStatus getTaskStatus() const { return taskStatus; }
    const QDateTime &getDeadline() const { return deadline; }

    void setAction(const string &tx) { action = tx; }
    void setPriority(EnumPriority p) { priority = p; }
    void setDeadline(QDateTime dl) { deadline = dl; }
    void setTaskStatus(EnumTaskStatus ts) { taskStatus = ts; }
};

#endif // TASK_H
