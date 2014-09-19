// This file is part of RSS Guard.
//
// Copyright (C) 2011-2014 by Martin Rotter <rotter.martinos@gmail.com>
//
// RSS Guard is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// RSS Guard is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RSS Guard. If not, see <http://www.gnu.org/licenses/>.

#include "miscellaneous/application.h"

#include "miscellaneous/iconfactory.h"
#include "gui/feedsview.h"
#include "gui/feedmessageviewer.h"
#include "gui/messagebox.h"
#include "gui/formmain.h"

#include <QSessionManager>
#include <QThread>
#include <QProcess>


Application::Application(const QString &id, int &argc, char **argv)
  : QtSingleApplication(id, argc, argv),
    m_closeLock(NULL), m_userActions(QList<QAction*>()), m_mainForm(NULL),
    m_trayIcon(NULL), m_settings(NULL), m_system(NULL), m_skins(NULL),
    m_localization(NULL), m_icons(NULL), m_database(NULL) {
  connect(this, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));
  connect(this, SIGNAL(commitDataRequest(QSessionManager&)), this, SLOT(onCommitData(QSessionManager&)));
  connect(this, SIGNAL(saveStateRequest(QSessionManager&)), this, SLOT(onSaveState(QSessionManager&)));
}

Application::~Application() {
  delete m_closeLock;
}

QList<QAction*> Application::userActions() {
  if (m_mainForm != NULL && m_userActions.isEmpty()) {
    m_userActions = m_mainForm->allActions();
  }

  return m_userActions;
}

IconFactory *Application::icons() {
  if (m_icons == NULL) {
    m_icons = new IconFactory(this);
  }

  return m_icons;
}

void Application::processExecutionMessage(const QString &message) {
  qDebug("Received '%s' execution message from another application instance.",
         qPrintable(message));

  if (message == APP_IS_RUNNING) {
    if (SystemTrayIcon::isSystemTrayActivated()) {
      qApp->trayIcon()->showMessage(APP_NAME,
                                    tr("Application is already running."),
                                    QSystemTrayIcon::Information,
                                    TRAY_ICON_BUBBLE_TIMEOUT);
    }

    mainForm()->display();
  }
  else if (message == APP_QUIT_INSTANCE) {
    quit();
  }
}

SystemTrayIcon *Application::trayIcon() {
  if (m_trayIcon == NULL) {
    m_trayIcon = new SystemTrayIcon(APP_ICON_PATH, APP_ICON_PLAIN_PATH, m_mainForm);
  }

  return m_trayIcon;
}

void Application::showTrayIcon() {
  qDebug("Showing tray icon.");
  trayIcon()->show();

  if (m_mainForm != NULL) {
    m_mainForm->tabWidget()->feedMessageViewer()->feedsView()->notifyWithCounts();
  }
}

void Application::deleteTrayIcon() {
  if (m_trayIcon != NULL) {
    qDebug("Disabling tray icon, deleting it and raising main application window.");
    m_mainForm->display();
    delete m_trayIcon;
    m_trayIcon = NULL;

    // Make sure that application quits when last window is closed.
    setQuitOnLastWindowClosed(true);
  }
}

void Application::showGuiMessage(const QString& title, const QString& message,
                                 QSystemTrayIcon::MessageIcon message_type,
                                 QWidget *parent, int duration) {
  if (SystemTrayIcon::isSystemTrayActivated()) {
    // TODO: Maybe show OSD instead if tray icon bubble, depending on settings.
    trayIcon()->showMessage(title, message, message_type, duration);
  }
  else {
    // TODO: Tray icon or OSD is not available, display simple text box.
    MessageBox::show(parent, (QMessageBox::Icon) message_type, title, message);
  }
}

void Application::onCommitData(QSessionManager &manager) {
  qDebug("OS asked application to commit its data.");

  manager.setRestartHint(QSessionManager::RestartNever);
  manager.release();
}

void Application::onSaveState(QSessionManager &manager) {
  qDebug("OS asked application to save its state.");

  manager.setRestartHint(QSessionManager::RestartNever);
  manager.release();
}

void Application::onAboutToQuit() {
  // Make sure that we obtain close lock
  // BEFORE even trying to quit the application.
  bool locked_safely = closeLock()->tryLock(CLOSE_LOCK_TIMEOUT);

  processEvents();

  qDebug("Cleaning up resources and saving application state.");

  mainForm()->tabWidget()->feedMessageViewer()->quit();
  database()->saveDatabase();
  mainForm()->saveSize();

  if (locked_safely) {
    // Application obtained permission to close
    // in a safety way.
    qDebug("Close lock was obtained safely.");

    // We locked the lock to exit peacefully, unlock it to avoid warnings.
    closeLock()->unlock();
  }
  else {
    // Request for write lock timed-out. This means
    // that some critical action can be processed right now.
    qDebug("Close lock timed-out.");
  }
}