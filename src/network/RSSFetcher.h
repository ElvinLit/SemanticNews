#ifndef RSSFETCHER_H
#define RSSFETCHER_H

#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSet>
#include <QString>
#include "models/Headline.h"

struct FeedConfig {
    QString name;
    QString url;
    
    FeedConfig() {}
    FeedConfig(const QString& name, const QString& url) : name(name), url(url) {}
};

class RSSFetcher : public QObject {
    Q_OBJECT

public:
    explicit RSSFetcher(QObject* parent = nullptr);
    ~RSSFetcher();
    
    void setFeeds(const QList<FeedConfig>& feeds);
    void setPollInterval(int milliseconds);
    void start();
    void stop();

signals:
    void newHeadlinesAvailable(const QList<Headline>& headlines);

private slots:
    void onTimerTimeout();
    void onFeedReply();

private:
    void parseRSSFeed(const QByteArray& data, const QString& source);
    void parseAtomFeed(const QByteArray& data, const QString& source);
    QString computeHash(const QString& title, const QString& url);
    
    QTimer* m_timer;
    QNetworkAccessManager* m_networkManager;
    QList<FeedConfig> m_feeds;
    QSet<QString> m_recentHashes;
    int m_pollInterval;
    static const int MAX_RECENT_HASHES = 5000;
};

#endif // RSSFETCHER_H



