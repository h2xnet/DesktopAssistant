#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <QString>
#include <QMap>
#include <QDebug>

namespace base {


class CommandLine
{
public:
    typedef QMap<QString, QString> StringMap;

    CommandLine();
    virtual ~CommandLine();

    void reset();

    int parse(int argc, char* argv[]);

    bool updateItemValue(QString key, QString value);
    QString getItemValue(const QString& key);
    bool contain(const QString& key);

    void print();

    static const char* getExeFileNameKey();

private:
    QStringList onStringSplit(QString str, const QString& separate);

    StringMap m_command_lines;
};


} // end namespace base

#endif // COMMAND_LINE_H
