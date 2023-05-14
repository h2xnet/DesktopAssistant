#ifndef SYSTEM_CURSOR_DEAL_H
#define SYSTEM_CURSOR_DEAL_H

#include <QObject>

namespace SystemCursorDealSpace {

class SystemCursorDeal : public QObject {
    Q_OBJECT
public:
    SystemCursorDeal(QObject *parent = nullptr);
    ~SystemCursorDeal();

public:
    Q_INVOKABLE  int setNormalCursor(QString normalCursor);
    Q_INVOKABLE  QString getNormalCursor();

    Q_INVOKABLE  int setHighlightCursor(QString hightCursor);
    Q_INVOKABLE  QString getHighlightCursor();

    Q_INVOKABLE  void  restoreOverrideCursor();

private:

    QPoint getNativeCursorPosition();

public:

    QString m_normalCursor;
    QString m_hightCursor;
};


} // end namespace SystemCursorDealSpace

#endif // SYSTEM_CURSOR_DEAL_H
