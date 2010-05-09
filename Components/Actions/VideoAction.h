#ifndef VIDEOACTION_H
#define VIDEOACTION_H

#include <QFile>

#include "Components/OutputComponent.h"
#include "Action.h"

namespace kex
{
  class VideoAction : public OutputComponent, public Action
  {
    Q_OBJECT
  public:
    VideoAction(QObject *parent = 0);
    ~VideoAction();
    
    const QFile& file() const { return _videoFile;}
    bool setFile(const QString& filePath);

  private:
    QFile _videoFile;
    
  public slots: 
    void begin();
    void abort();
    };
}
#endif