#ifndef ARTICLE_H
#define ARTICLE_H
#include <QString>
#include "note.h"

using namespace std;

/** @brief   Class Article qui hérite de classe Note
 *  @author  Simei YIN, Jiacheng ZHOU
 */
class Article : public Note
{
private:
    QString text;

public:
    Article() : Note(), text("") {}

    /** Constructeur d'Article en copie
    */
    Article(const Article &a) : Note() {
        setDateCreate(a.getDateCreate());
        setTitle(a.getTitle());
        setId(a.getId());
        setDateModif(a.getDateModif());
        setNoteStatus(a.getNoteStatus());
        setText(a.getText());
    }

    /** getter de texte de Article
    */
    const QString &getText() const {return text;}
    /** setter de texte de Article
    */
    void setText(const QString &tx) {text = tx;}
};

#endif // ARTICLE_H
