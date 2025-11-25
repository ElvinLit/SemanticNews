#ifndef DATASTORE_H
#define DATASTORE_H

#include <QSqlDatabase>
#include <QList>
#include <QString>
#include "models/Group.h"
#include "models/Event.h"
#include "models/Headline.h"
#include "models/HeadlineMatch.h"

class DataStore {
public:
    DataStore();
    ~DataStore();
    
    bool initialize(const QString& dbPath = "news_monitor.db");
    void close();
    
    // Groups
    QList<Group> loadGroups();
    bool saveGroup(const Group& group);
    bool deleteGroup(int groupId);
    
    // Events
    QList<Event> loadEvents();
    bool saveEvent(const Event& event);
    bool deleteEvent(int eventId);
    
    // Headlines
    int insertHeadline(const Headline& headline);
    QList<Headline> loadRecentHeadlines(int limit = 100);
    
    // Relevance
    bool insertHeadlineRelevance(const HeadlineMatch& match);
    
    // Settings
    QString getSetting(const QString& key, const QString& defaultValue = "");
    bool setSetting(const QString& key, const QString& value);
    
    // History
    bool clearMonitorHistory();
    
private:
    QSqlDatabase m_db;
    bool createSchema();
};

#endif // DATASTORE_H




