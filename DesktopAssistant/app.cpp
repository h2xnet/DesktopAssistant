#include "app.h"

#include <QTextCodec>

extern core::Startup g_startup; // 启动器对象

App::App(QObject* parent) : QObject(parent)
{

}

App::~App() {

}

bool App::init() {

    // 设置编码
  #if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
  #if _MSC_VER
      QTextCodec *codec = QTextCodec::codecForName("GBK");
  #else
      QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  #endif
      QTextCodec::setCodecForLocale(codec);
      QTextCodec::setCodecForCStrings(codec);
      QTextCodec::setCodecForTr(codec);
  #else
      QTextCodec *codec = QTextCodec::codecForName("UTF-8");
      QTextCodec::setCodecForLocale(codec);
  #endif

    return true;
}

core::Startup* App::getStartup() {
    return &g_startup;
}
