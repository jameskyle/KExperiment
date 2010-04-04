#ifndef UTILITIES_H
#define UTILITIES_H

#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QObject>
#include <QApplication>

#include "Config.h"

namespace kex
{
  namespace Utilities
  {
    void setupAppStorageEnvironment();
    void configAppEnvironment(QApplication* app);
  }
}
#endif