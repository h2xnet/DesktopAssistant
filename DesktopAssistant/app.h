#ifndef APP_H
#define APP_H

#include <QDebug>
#include <QString>

class App : public QObject
{
    Q_OBJECT
public:
    App(QObject* parent = nullptr);
    ~App();

    bool init();
};

#endif // APP_H
