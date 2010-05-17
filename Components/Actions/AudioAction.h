#ifndef AUDIOACTION_H
#define AUDIOACTION_H

#include <QFile>

#include "Components/OutputComponent.h"
#include "Action.h"

namespace kex
{
  class AudioAction : public Action
  {
    Q_OBJECT
    Q_PROPERTY(QString file WRITE setFile READ file)
    
  public:
    AudioAction(QObject *parent = 0);
    ~AudioAction();

    const QString file() const {return _audioFile.fileName();}
    bool setFile(const QString& filePath);
    
  private:
    QFile _audioFile;
    
  public slots:
    void begin();
    void abort();
    };
}
#endif