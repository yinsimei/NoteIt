#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QDateTime>
#include "note.h"

using namespace std;

/** @brief  Task hérite de Note, qui contient queleques attibuts en plus (par exemple, action, priorité, ...)
 */
class Task : public Note {
private:
    QString action;
    EnumPriority priority;
    QDateTime deadline;
    EnumTaskStatus taskStatus;
public:
    /** Constructeur par défaut
    */
    Task() : Note(), action(""), priority(e_normal), deadline(QDateTime::currentDateTime()), taskStatus(e_notStarted) {}
    /** Constructeur de recopie
     * @param [in] t task à copier
    */
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
    /** accesseur à action en lecture
    */
    const QString &getAction() const { return action; }
    /** accesseur à priority en lecture
    */
    EnumPriority getPriority() const { return priority; }
    /** accesseur à taskstatus en lecture
    */
    EnumTaskStatus getTaskStatus() const { return taskStatus; }
    /** accesseur à deadline en lecture
    */
    const QDateTime &getDeadline() const { return deadline; }
    /** accesseur à action en écriture
    */
    void setAction(const QString &tx) { action = tx; }
    /** accesseur à priority en écriture
    */
    void setPriority(EnumPriority p) { priority = p; }
    /** accesseur à deadline en écriture
    */
    void setDeadline(QDateTime dl) { deadline = dl; }
    /** accesseur à taskstatus en écriture
    */
    void setTaskStatus(EnumTaskStatus ts) { taskStatus = ts; }
};

#endif // TASK_H
