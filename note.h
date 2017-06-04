#ifndef NOTE_H
#define NOTE_H
#include <string>
#include <QDateTime>

using namespace std;

enum  EnumNoteStatus {
    e_active,
    e_deleted,
    e_archived
};

class Note
{
protected:
    int id;
    string title;
    QDateTime dateCreate;
    QDateTime dateModif;
    EnumNoteStatus noteStatus;

public:
    Note(void) : id(-1), title(""), dateCreate(QDateTime::currentDateTime()), dateModif(QDateTime::currentDateTime()), noteStatus(e_active) {}
    Note(const QDateTime &dc, const string &t)
        : id(-1), title(t), dateCreate(dc), dateModif(dc), noteStatus(e_active) {}

    int getId()const {return id;}
    EnumNoteStatus getNoteStatus() const { return noteStatus; }
    const string &getTitle() const {return title;}
    const QDateTime &getDateCreate() const {return dateCreate;}
    const QDateTime &getDateModif() const {return dateModif;}

    void setId(int i){id = i;}
    void setTitle(const string &t) {title = t;}
    void setDateCreate(const QDateTime &dc) {dateCreate = dc;}
    void setDateModif(const QDateTime &dm) {dateModif = dm;}
    void setNoteStatus(EnumNoteStatus ns) {noteStatus = ns;}
};



#endif // NOTE_H
