#ifndef EVENT_H
#define EVENT_H

#include <QString>

struct Event {
    int id;
    int groupId;
    QString name;
    QString description;
    
    Event() : id(-1), groupId(-1) {}
    Event(int id, int groupId, const QString& name, const QString& description)
        : id(id), groupId(groupId), name(name), description(description) {}
};

#endif // EVENT_H




