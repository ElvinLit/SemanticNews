#ifndef EVENTBUILDERWIDGET_H
#define EVENTBUILDERWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QColorDialog>
#include "models/Group.h"
#include "models/Event.h"

class EventBuilderWidget : public QWidget {
    Q_OBJECT

public:
    explicit EventBuilderWidget(QWidget* parent = nullptr);
    
    void setGroups(const QList<Group>& groups);
    void setEvents(const QList<Event>& events);
    QList<Group> getGroups() const;
    QList<Event> getEvents() const;

signals:
    void eventsSavedAndMonitorRequested();

private slots:
    void onAddGroupClicked();
    void onEditGroupClicked();
    void onDeleteGroupClicked();
    void onAddEventClicked();
    void onEditEventClicked();
    void onDeleteEventClicked();
    void onSaveAndStartClicked();

private:
    void updateGroupTable();
    void updateEventTable();
    QString getGroupName(int groupId) const;
    
    QTableWidget* m_groupTable;
    QTableWidget* m_eventTable;
    QList<Group> m_groups;
    QList<Event> m_events;
    int m_nextGroupId;
    int m_nextEventId;
};

#endif // EVENTBUILDERWIDGET_H




