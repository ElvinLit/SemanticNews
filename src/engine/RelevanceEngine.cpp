#include "RelevanceEngine.h"
#include <QDebug>
#include <cmath>
#include <algorithm>
#include <numeric>  

RelevanceEngine::RelevanceEngine(QObject* parent)
    : QObject(parent), m_globalThreshold(0.0), m_eventProfiles(QList<EventProfile>()) {
}

void RelevanceEngine::setEventProfiles(const QList<EventProfile>& profiles) {
    m_eventProfiles = profiles;
}

void RelevanceEngine::setGlobalThreshold(double threshold) {
    m_globalThreshold = threshold;
}

QList<HeadlineMatch> RelevanceEngine::computeMatches(const QVector<float>& headlineEmbedding, int headlineId) {
    QList<HeadlineMatch> matches;  

    for (const EventProfile& profile : m_eventProfiles) {
        double similarity = cosineSimilarity(headlineEmbedding, profile.embedding);
        if (similarity >= m_globalThreshold) {
            HeadlineMatch match(headlineId, profile.eventId, profile.groupId, similarity);
            matches.append(match);
        }
    }

    std::sort(matches.begin(), matches.end(), [](const HeadlineMatch& a, const HeadlineMatch& b) {
        return a.similarity > b.similarity;
    });

    return matches;

}

double RelevanceEngine::cosineSimilarity(const QVector<float>& a, const QVector<float>& b) {
    if (a.size() != b.size()) {
        qDebug() << "Error: Vector size mismatch in cosineSimilarity";
        return 0.0;
    }
    // Since embeddings are normalized (from Python service), cosine similarity = dot product (no need to divide by norms)
    
    return std::inner_product(a.cbegin(), a.cend(), b.cbegin(), 0.0);
}
