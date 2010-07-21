#ifndef VIDEOACTION_H
#define VIDEOACTION_H

#include <QFile>

#include "Components/Component.h"
#include "Action.h"

namespace kex
{
  class VideoAction : public Action
  {
    Q_OBJECT
    Q_PROPERTY(QString file READ file WRITE setFile)
    
  public:
    VideoAction(QObject *parent = 0);
    ~VideoAction();
    
    const QString file() const { return _videoFile.fileName();}
    bool setFile(const QString& filePath);

  private:
    QFile _videoFile;
    
  public slots: 
    void begin();
    void abort();
    };
}
#endif