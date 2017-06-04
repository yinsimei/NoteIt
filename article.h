#ifndef ARTICLE_H
#define ARTICLE_H
#include <string>
#include "note.h"

using namespace std;

class Article : public Note
{
private:
    string text;

public:
    Article(const QDateTime & dc, const string &t)
        : Note(dc, t), text("") {}

    Article(const Article & a);

    const string &getText() const {return text;}
    void setText(const string &tx) {text = tx;}
};

#endif // ARTICLE_H
