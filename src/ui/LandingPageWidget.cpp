#include "LandingPageWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>

LandingPageWidget::LandingPageWidget(QWidget* parent)
    : QWidget(parent) {
    // TODO: Set up UI with "Start / Continue Monitor" and "Clear Monitor History" buttons
}

void LandingPageWidget::onStartMonitorClicked() {
    // TODO: Emit startMonitorRequested signal
}

void LandingPageWidget::onClearHistoryClicked() {
    // TODO: Emit clearHistoryRequested signal
}
