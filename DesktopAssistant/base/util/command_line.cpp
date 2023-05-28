#include "command_line.h"

namespace base {

CommandLine::CommandLine()
{

}

CommandLine::~CommandLine() {

}

void CommandLine::reset() {
    if (!m_command_lines.isEmpty()) {
        m_command_lines.clear();
    }
}

int CommandLine::parse(int argc, char* argv[]) {
    reset();
    if (argc <= 0 || !argv) {
        return -1;
    }

    this->updateItemValue(CommandLine::getExeFileNameKey(), argv[0]);

    for(int i = 1; i < argc; i++) {
        qInfo() << "命令行参数项，序号:" << i << " 值:" << argv[i];
        QString strItem = argv[i];
        QStringList arrs = this->onStringSplit(strItem, "=");
        if (arrs.size() != 2) {
            continue;
        }
        QString key = arrs.at(0);
        if (key.at(0) != '-') {
            continue;
        }
        QString validKey = key.trimmed();
        QString validValue = arrs.at(1).trimmed();
        this->updateItemValue(validKey, validValue);
    }
    return m_command_lines.size();
}

QStringList CommandLine::onStringSplit(QString str, const QString& separate) {
    QStringList list;
    if (!str.isEmpty()) {
        list = str.split(separate);
    }
    return list;
}

bool CommandLine::updateItemValue(QString key, QString value) {
    if (key.isEmpty()) {
        return false;
    }
    m_command_lines[key] = value;
    return true;
}

QString CommandLine::getItemValue(const QString& key) {
    auto it = m_command_lines.find(key);
    if (it != m_command_lines.end()) {
        return it.value();
    }
    return QString("");
}

bool CommandLine::contain(const QString& key) {
    return m_command_lines.contains(key);
}

void CommandLine::print() {
    qInfo() << "有效命令行参数列表:";

    qInfo() << "    命令行总个数:" << m_command_lines.size();
    for(auto it = m_command_lines.begin(); it != m_command_lines.end(); it++) {
        qInfo() <<" 命令行项参数: " << it.key() << " => " << it.value();
    }

    qInfo() << "输出完毕";
}

const char* CommandLine::getExeFileNameKey() {
    return "exeFileName";
}

const char* CommandLine::getStartViewKey() {
    return "startView";
}

const char* CommandLine::getViewIPCServerNameKey() {
    return "viewIPCServerName";
}

} // end namespace base
