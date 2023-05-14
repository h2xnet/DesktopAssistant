#include "system_cursor_deal.h"

#include <QGuiApplication>
#include <QCursor>
#include <QPixmap>
#include <QPoint>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

namespace SystemCursorDealSpace {

SystemCursorDeal::SystemCursorDeal(QObject *parent) : QObject(parent) {

}

SystemCursorDeal::~SystemCursorDeal() {
    QGuiApplication::restoreOverrideCursor();
}

int SystemCursorDeal::setNormalCursor(QString normalCursor) {
    QGuiApplication::restoreOverrideCursor();
    m_normalCursor = normalCursor;
    QCursor nCursor = QCursor(QPixmap(m_normalCursor));
    QGuiApplication::setOverrideCursor(nCursor);
    return 0;
}

QPoint SystemCursorDeal::getNativeCursorPosition() {
    QDesktopWidget* widget= QApplication::desktop();
    QPoint pos = widget->cursor().pos();
    for (QScreen *screen : QGuiApplication::screens()) {
        QRect screenRect = screen->geometry();
        if (screenRect.contains(pos)) {
            QPoint origin = screenRect.topLeft();
            return origin + (pos - origin) * screen->devicePixelRatio();
        }
    }

    return pos * qApp->devicePixelRatio();
}

QString SystemCursorDeal::getNormalCursor() {
    return m_normalCursor;
}

int SystemCursorDeal::setHighlightCursor(QString hightCursor) {
    QGuiApplication::restoreOverrideCursor();
    m_hightCursor = hightCursor;
    QCursor nCursor = QCursor(QPixmap(m_hightCursor));
    QGuiApplication::setOverrideCursor(nCursor);
    return 0;
}

QString SystemCursorDeal::getHighlightCursor(){
    return m_hightCursor;
}

void  SystemCursorDeal::restoreOverrideCursor() {
    QGuiApplication::restoreOverrideCursor();
}

} // end namespace SystemCursorDealSpace
