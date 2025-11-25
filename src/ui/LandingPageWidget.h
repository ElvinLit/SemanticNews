#ifndef LANDINGPAGEWIDGET_H
#define LANDINGPAGEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class LandingPageWidget : public QWidget {
    Q_OBJECT

public:
    explicit LandingPageWidget(QWidget* parent = nullptr);

signals:
    void startMonitorRequested();
    void clearHistoryRequested();

private slots:
    void onStartMonitorClicked();
    void onClearHistoryClicked();

private:
    QPushButton* m_startButton;
    QPushButton* m_clearButton;
};

#endif // LANDINGPAGEWIDGET_H




