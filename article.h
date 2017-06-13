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
    Article() : Note(), text("") {}

    Article(const Article &a) : Note() {
        setDateCreate(a.getDateCreate());
        setTitle(a.getTitle());
        setId(a.getId());
        setDateModif(a.getDateModif());
        setNoteStatus(a.getNoteStatus());
        setText(a.getText());
    }

    const QString &getText() const {return text;}
    void setText(const QString &tx) {text = tx;}
};

#endif // ARTICLE_H
