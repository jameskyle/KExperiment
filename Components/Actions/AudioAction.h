#ifndef AUDIOACTION_H
#define AUDIOACTION_H

#include <QFile>

#include "Components/OutputComponent.h"
#include "Action.h"

namespace kex
{
  class AudioAction : public OutputComponent, public Action
  {
    Q_OBJECT
  public:
    AudioAction(QObject *parent = 0);
    ~AudioAction();

    const QFile& file() const {return _audioFile;}
    bool setFile(const QString& filePath);
    
  private:
    QFile _audioFile;
    
  public slots:
    void begin();
    void abort();
    };
}
#endif