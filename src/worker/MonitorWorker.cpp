#include "MonitorWorker.h"
#include "DataStore.h"
#include "network/EmbeddingClient.h"
#include "engine/RelevanceEngine.h"
#include <QDebug>

MonitorWorker::MonitorWorker(DataStore* dataStore,
                             EmbeddingClient* embeddingClient,
                             RelevanceEngine* relevanceEngine,
                             QObject* parent)
    : QObject(parent) {
    // TODO: Store pointers, connect signals
}

void MonitorWorker::processHeadlines(const QList<Headline>& headlines) {
    // TODO: Request embeddings for headline titles
    // TODO: Store headlines for processing when embeddings arrive
}

void MonitorWorker::onEmbeddingsReady(const QVector<QVector<float>>& embeddings) {
    // TODO: Match embeddings with pending headlines
    // TODO: Call processBatch
}

void MonitorWorker::processBatch(const QList<Headline>& headlines, const QVector<QVector<float>>& embeddings) {
    // TODO: For each headline:
    //   - Insert into database
    //   - Compute relevance matches using RelevanceEngine
    //   - Store matches in database
    //   - Emit headlinesProcessed signal
}
