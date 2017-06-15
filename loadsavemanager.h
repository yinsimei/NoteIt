#ifndef LOADSAVEMANAGER_H
#define LOADSAVEMANAGER_H

#include <QString>

class LoadSaveManager
{
private:
    struct Handler {
        LoadSaveManager* instance;
        Handler(): instance(nullptr) {}
        ~Handler() { if (instance) delete instance; }
    };

    mutable QString filename;
    static Handler handler;
    LoadSaveManager();
    ~LoadSaveManager();
public:
    static LoadSaveManager &getInstance();
    // save & load file
    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename = f; }
    void load(); // load notes from file filename
    void save() const; // save notes in file filename
};

#endif // LOADSAVEMANAGER_H
