#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QStackedWidget>
#include <QJsonDocument>
#include "DataStore.h"
#include "ui/LandingPageWidget.h"
#include "ui/EventBuilderWidget.h"
#include "ui/MonitorWidget.h"
#include "network/RSSFetcher.h"
#include "network/EmbeddingClient.h"
#include "engine/RelevanceEngine.h"
#include "worker/MonitorWorker.h"
#include <QThread>

class AppController : public QObject {
    Q_OBJECT

public:
    explicit AppController(QObject* parent = nullptr);
    ~AppController();
    
    bool initialize();
    QWidget* getMainWidget();

private slots:
    void onStartMonitorRequested();
    void onClearHistoryRequested();
    void onEventsSavedAndMonitorRequested();
    void onNewHeadlinesAvailable(const QList<Headline>& headlines);
    void onHeadlinesProcessed(const QList<Headline>& headlines, const QList<HeadlineMatch>& matches);
    void onEventEmbeddingsReady(const QVector<QVector<float>>& embeddings);

private:
    bool loadConfig();
    void initializeEventProfiles();
    void startMonitor();
    void stopMonitor();
    QString getGroupName(int groupId) const;
    QString getGroupColor(int groupId) const;
    
    DataStore* m_dataStore;
    EmbeddingClient* m_embeddingClient;
    RSSFetcher* m_rssFetcher;
    RelevanceEngine* m_relevanceEngine;
    MonitorWorker* m_monitorWorker;
    QThread* m_workerThread;
    
    QStackedWidget* m_stackedWidget;
    LandingPageWidget* m_landingPage;
    EventBuilderWidget* m_eventBuilder;
    MonitorWidget* m_monitorWidget;
    
    QList<Group> m_groups;
    QList<Event> m_events;
    QList<FeedConfig> m_feeds;
    
    QString m_embeddingServiceUrl;
    int m_pollInterval;
    double m_globalThreshold;
    bool m_waitingForEventEmbeddings;
};

#endif // APPCONTROLLER_H

