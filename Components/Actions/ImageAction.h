#ifndef IMAGEACTION_H
#define IMAGEACTION_H

#include <QFile>

#include "Components/OutputComponent.h"
#include "Action.h"

namespace kex
{
  class ImageAction : public OutputComponent, public Action
  {
    Q_OBJECT
  public:
    ImageAction(QObject *parent = 0);
    ~ImageAction();

    const QFile& file() const { return _imageFile;}
    bool setFile(const QString& filePath);

  private:
    QFile _imageFile;
    
  public slots:
    void begin();
    void abort();
  };
}
#endif