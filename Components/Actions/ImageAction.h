#ifndef IMAGEACTION_H
#define IMAGEACTION_H

#include <QFile>

#include "Components/Component.h"
#include "Action.h"

namespace kex
{
  class ImageAction : public Action
  {
    Q_OBJECT
    Q_PROPERTY(QString file READ file WRITE setFile)
    
  public:
    ImageAction(QObject *parent = 0);
    ~ImageAction();

    const QString file() const { return _imageFile.fileName();}
    bool setFile(const QString& filePath);

  private:
    QFile _imageFile;
    
  public slots:
    void begin();
    void abort();
  };
}
#endif