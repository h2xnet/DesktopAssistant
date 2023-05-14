#include <QApplication>
#include <QMenu>
#include <QAction>
#include "system_tray_icon.h"

MyAction::MyAction(QObject *parent)
	:   QAction(parent)
{
	setObjectName("MyAction");
}

MyAction::~MyAction()
{

}

QUrl MyAction::icon() const
{
	return m_icon;
}

void MyAction::setIcon(const QUrl &arg)
{
	if(m_icon != arg)
	{
		QString str = arg.toLocalFile();
		if(str == "") str = arg.toString();     //如果转换失败
		if( str.mid (0, 3) == "qrc")
			str = str.mid (3, str.count() - 3);
		QAction::setIcon(QIcon(str));
		m_icon = arg;
		emit iconChanged();
	}
}

MySeparator::MySeparator(QObject *parent)
	:   QObject(parent)
{
	setObjectName("MySeparator");
}

MySeparator::~MySeparator()
{

}

MyMenu::MyMenu(QQuickItem *parent)
	:   QQuickItem(parent)
{
	setObjectName("MyMenu");
	m_menu = new QMenu();
}

MyMenu::~MyMenu()
{

}

int MyMenu::width() const
{
	return m_menu->width();
}

int MyMenu::height() const
{
	return m_menu->height();
}

void MyMenu::clear()    //清空caidan
{
	m_menu->clear();
}

void MyMenu::setWidth(int arg)
{
	if (m_menu->width() != arg)
	{
		m_menu->setFixedWidth(arg);
		emit widthChanged();
	}
}

void MyMenu::setHeight(int arg)
{
	if (m_menu->height() != arg)
	{
		m_menu->setFixedHeight(arg);
		emit heightChanged();
	}
}

void MyMenu::addAction(MyAction *action)
{
	m_menu->addAction(action);
}

void MyMenu::addSeparator()
{
	m_menu->addSeparator();
}

void MyMenu::addMenu(MyMenu *menu)
{
	m_menu->addMenu(menu->m_menu);
}

void MyMenu::componentComplete()        //在菜单完成构建后调用，将自定义Action,Menu,Separator通过objectName判断加入
{
	QQuickItem::componentComplete();
	QObjectList list = children();
	for (auto it : list)
	{
		if (it->objectName() == "MyAction")
		{
			MyAction *action = qobject_cast<MyAction *>(it);
			m_menu->addAction(action);
		}
		else if (it->objectName() == "MySeparator")
		{
			m_menu->addSeparator();
		}
		else if (it->objectName() == "MyMenu")
		{
			MyMenu *menu = qobject_cast<MyMenu *>(it);
			m_menu->addMenu(menu->m_menu);
		}
	}
}

SystemTrayIcon::SystemTrayIcon(QQuickItem *parent)
	:   QQuickItem(parent)
{
	m_systemTray = new QSystemTrayIcon(this);
	connect(m_systemTray, &QSystemTrayIcon::activated, this, &SystemTrayIcon::onActivated);
	connect(this, &SystemTrayIcon::visibleChanged, this, &SystemTrayIcon::onVisibleChanged);
	setVisible(false);              //给visible一个初始值，否则会不显示
}

SystemTrayIcon::~SystemTrayIcon()
{

}

int SystemTrayIcon::x() const
{
	return m_systemTray->geometry().x();
}

int SystemTrayIcon::y() const
{
	return m_systemTray->geometry().y();
}

QUrl SystemTrayIcon::icon() const
{
	return m_icon;
}

QString SystemTrayIcon::toolTip() const
{
	return m_systemTray->toolTip();
}

MyMenu *SystemTrayIcon::menu() const
{
	return m_menu;
}

void SystemTrayIcon::setIcon(const QUrl &arg)
{
	if(m_icon != arg)
	{
		QString str = arg.toLocalFile();
		if(str == "") str = arg.toString(); //如果转换失败
		if( str.mid (0, 3) == "qrc")
			str = str.mid (3, str.count() - 3);
		m_systemTray->setIcon(QIcon(str));
		m_icon = arg;
		emit iconChanged();
	}
}

void SystemTrayIcon::setToolTip(const QString &arg)
{
	if (m_toolTip != arg)
	{
		m_systemTray->setToolTip(arg);
		m_toolTip = arg;
		emit toolTipChanged();
	}
}

void SystemTrayIcon::setMenu(MyMenu *arg)
{
	if (m_menu != arg)
    {
		m_menu = arg;
		m_systemTray->setContextMenu(m_menu->m_menu);
		m_systemTray->installEventFilter(this);
		emit menuChanged();
    }
}

void SystemTrayIcon::onVisibleChanged()
{
	m_systemTray->setVisible(isVisible());
}

void SystemTrayIcon::onActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::DoubleClick:
	case QSystemTrayIcon::Trigger:
		emit trigger();            //单击双击托盘图标时发送trigger()信号, reason类似还有Context,MiddleClick,Unknow

	default:
		break;
	}
}

void SystemTrayIcon::onExit()    //应在程序退出时调用，防止图标不消失
{
	m_systemTray->hide();
	QApplication::exit(0);
}
