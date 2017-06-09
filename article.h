#ifndef ARTICLE_H
#define ARTICLE_H
#include <QString>
#include "note.h"

using namespace std;

class Article : public Note
{
private:
    QString text;

public:
    Article(const QDateTime &dc, const QString &t)
        : Note(dc, t), text("") {}

    Article(const Article &a) : Note(a.getDateCreate(), a.getTitle()) {
        setId(a.getId());
        setDateModif(a.getDateModif());
        setNoteStatus(a.getNoteStatus());
        setText(a.getText());
    }

    const QString &getText() const {return text;}
    void setText(const QString &tx) {text = tx;}
};

#endif // ARTICLE_H
