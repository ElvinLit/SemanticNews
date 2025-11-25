#include "EventBuilderWidget.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QDebug>

EventBuilderWidget::EventBuilderWidget(QWidget* parent)
    : QWidget(parent) {
    // TODO: Set up UI with group and event tables, add/edit/delete buttons, "Save & Start Monitor" button
}

void EventBuilderWidget::setGroups(const QList<Group>& groups) {
    // TODO: Store groups and update table
}

void EventBuilderWidget::setEvents(const QList<Event>& events) {
    // TODO: Store events and update table
}

QList<Group> EventBuilderWidget::getGroups() const {
    // TODO: Return current groups
    return QList<Group>();
}

QList<Event> EventBuilderWidget::getEvents() const {
    // TODO: Return current events
    return QList<Event>();
}

void EventBuilderWidget::onAddGroupClicked() {
    // TODO: Show dialog to add new group (name, color)
}

void EventBuilderWidget::onEditGroupClicked() {
    // TODO: Edit selected group
}

void EventBuilderWidget::onDeleteGroupClicked() {
    // TODO: Delete selected group
}

void EventBuilderWidget::onAddEventClicked() {
    // TODO: Show dialog to add new event (name, select group)
}

void EventBuilderWidget::onEditEventClicked() {
    // TODO: Edit selected event
}

void EventBuilderWidget::onDeleteEventClicked() {
    // TODO: Delete selected event
}

void EventBuilderWidget::onSaveAndStartClicked() {
    // TODO: Validate (at least one group and event), emit eventsSavedAndMonitorRequested
}

void EventBuilderWidget::updateGroupTable() {
    // TODO: Refresh group table display
}

void EventBuilderWidget::updateEventTable() {
    // TODO: Refresh event table display
}

QString EventBuilderWidget::getGroupName(int groupId) const {
    // TODO: Return group name for ID
    return QString();
}
