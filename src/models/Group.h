#ifndef GROUP_H
#define GROUP_H

#include <QString>

struct Group {
    int id;
    QString name;
    QString colorHex;
    
    Group() : id(-1) {}
    Group(int id, const QString& name, const QString& colorHex)
        : id(id), name(name), colorHex(colorHex) {}
};

#endif // GROUP_H




