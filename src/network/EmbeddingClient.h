#ifndef EMBEDDINGCLIENT_H
#define EMBEDDINGCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QStringList>
#include <QVector>
#include <QVector>

class EmbeddingClient : public QObject {
    Q_OBJECT

public:
    explicit EmbeddingClient(QObject* parent = nullptr);
    ~EmbeddingClient();
    
    void setServiceUrl(const QString& url);
    void getEmbeddings(const QStringList& texts);
    
signals:
    void embeddingsReady(const QVector<QVector<float>>& embeddings);
    void errorOccurred(const QString& errorMessage);

private slots:
    void onReplyFinished();

private:
    QNetworkAccessManager* m_networkManager;
    QString m_serviceUrl;
};

#endif // EMBEDDINGCLIENT_H



