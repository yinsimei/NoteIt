#ifndef TASK_H
#define TASK_H
#include <string>
#include <QDateTime>
#include "note.h"

using namespace std;

class Task : public Note {
public:
    enum EnumTaskStatus {
        e_notStarted,
        e_ongoing,
        e_finished
    };

    enum EnumPriority {
        e_lowest,
        e_low,
        e_normal,
        e_high,
        e_highest
    };

private:
    string action;
    EnumPriority priority;
    QDateTime deadline;
    EnumTaskStatus taskStatus;
public:
    Task(const QDateTime & dc, const string &t)
        : Note(dc, t), action(""), priority(e_normal), deadline(QDateTime::currentDateTime()), taskStatus(e_notStarted) {}

    Task(const Task &t) : Note(t.getDateCreate(), t.getTitle()){
        setId(t.getId());
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
