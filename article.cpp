#include "article.h"
#include "note.h"

Article::Article(const Article & a) {
    setId(a.getId());
    setTitle(a.getTitle());
    setDateCreate(a.getDateCreate());
    setDateModif(a.getDateModif());
    setNoteStatus(a.getNoteStatus());
    setText(a.getText());
}

