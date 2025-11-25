#ifndef RELEVANCEENGINE_H
#define RELEVANCEENGINE_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QString>
#include "models/HeadlineMatch.h"

struct EventProfile {
    int eventId;
    int groupId;
    QString text;
    QVector<float> embedding;
    
    EventProfile() : eventId(-1), groupId(-1) {}
    EventProfile(int eventId, int groupId, const QString& text, const QVector<float>& embedding)
        : eventId(eventId), groupId(groupId), text(text), embedding(embedding) {}
};

class RelevanceEngine : public QObject {
    Q_OBJECT

public:
    explicit RelevanceEngine(QObject* parent = nullptr);
    
    void setEventProfiles(const QList<EventProfile>& profiles);
    void setGlobalThreshold(double threshold);
    
    QList<HeadlineMatch> computeMatches(const QVector<float>& headlineEmbedding, int headlineId);

private:
    double cosineSimilarity(const QVector<float>& a, const QVector<float>& b);
    
    QList<EventProfile> m_eventProfiles;
    double m_globalThreshold;
};

#endif // RELEVANCEENGINE_H




