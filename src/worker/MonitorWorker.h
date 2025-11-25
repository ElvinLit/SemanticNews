#ifndef MONITORWORKER_H
#define MONITORWORKER_H

#include <QObject>
#include <QThread>
#include <QList>
#include "models/Headline.h"
#include "models/HeadlineMatch.h"

class DataStore;
class EmbeddingClient;
class RelevanceEngine;

class MonitorWorker : public QObject {
    Q_OBJECT

public:
    explicit MonitorWorker(DataStore* dataStore, 
                          EmbeddingClient* embeddingClient,
                          RelevanceEngine* relevanceEngine,
                          QObject* parent = nullptr);
    
    void processHeadlines(const QList<Headline>& headlines);

signals:
    void headlinesProcessed(const QList<Headline>& headlines, const QList<HeadlineMatch>& matches);
    void errorOccurred(const QString& error);

private slots:
    void onEmbeddingsReady(const QVector<QVector<float>>& embeddings);

private:
    void processBatch(const QList<Headline>& headlines, const QVector<QVector<float>>& embeddings);
    
    DataStore* m_dataStore;
    EmbeddingClient* m_embeddingClient;
    RelevanceEngine* m_relevanceEngine;
    QList<Headline> m_pendingHeadlines;
};

#endif // MONITORWORKER_H




