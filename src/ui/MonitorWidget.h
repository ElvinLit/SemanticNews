#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QTreeWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QAbstractTableModel>
#include "models/Headline.h"
#include "models/Group.h"
#include "models/HeadlineMatch.h"

class RecentHeadlinesModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit RecentHeadlinesModel(QObject* parent = nullptr);
    
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    
    void addHeadline(const Headline& headline);
    void clear();
    Headline getHeadline(int row) const;

private:
    QList<Headline> m_headlines;
};

class RelevantHeadlinesModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit RelevantHeadlinesModel(QObject* parent = nullptr);
    
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    
    void addMatch(const HeadlineMatch& match, const Headline& headline, const QString& groupName, const QString& groupColor);
    void clear();
    void setGroups(const QList<Group>& groups);
    void filterByGroups(const QSet<int>& groupIds);
    void setSortByRelevance(bool byRelevance);
    QString getHeadlineUrl(int row) const;
    
private:
    struct RelevantItem {
        HeadlineMatch match;
        Headline headline;
        QString groupName;
        QString groupColor;
    };
    
    QList<RelevantItem> m_items;
    QList<RelevantItem> m_filteredItems;
    QList<Group> m_groups;
    QSet<int> m_filteredGroupIds;
    bool m_sortByRelevance;
    
    void updateFilteredItems();
};

class MonitorWidget : public QWidget {
    Q_OBJECT

public:
    explicit MonitorWidget(QWidget* parent = nullptr);
    
    void addRecentHeadline(const Headline& headline);
    void addRelevantMatch(const HeadlineMatch& match, const Headline& headline, const QString& groupName, const QString& groupColor);
    void setGroups(const QList<Group>& groups);
    void clear();

private slots:
    void onSearchTextChanged(const QString& text);
    void onGroupFilterChanged();
    void onSortChanged(int index);
    void onRecentHeadlineDoubleClicked(const QModelIndex& index);
    void onRelevantHeadlineDoubleClicked(const QModelIndex& index);

private:
    void setupUI();
    void filterAndSort();
    
    RecentHeadlinesModel* m_recentModel;
    RelevantHeadlinesModel* m_relevantModel;
    QTableView* m_recentView;
    QTableView* m_relevantView;
    QLineEdit* m_searchEdit;
    QComboBox* m_groupFilterCombo;
    QComboBox* m_sortCombo;
    QList<Group> m_groups;
};

#endif // MONITORWIDGET_H

