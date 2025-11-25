#ifndef HEADLINE_H
#define HEADLINE_H

#include <QString>
#include <QDateTime>

struct Headline {
    int id;
    QString title;
    QString url;
    QString source;
    QDateTime publishedAt;
    QDateTime firstSeenAt;
    QString hash;
    
    Headline() : id(-1) {}
    Headline(const QString& title, const QString& url, const QString& source, 
             const QDateTime& publishedAt = QDateTime())
        : id(-1), title(title), url(url), source(source), 
          publishedAt(publishedAt), firstSeenAt(QDateTime::currentDateTime()) {}
};

#endif // HEADLINE_H




