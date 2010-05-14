#ifndef OUTPUTCOMPONENT_H
#define OUTPUTCOMPONENT_H

#include <QObject>


namespace kex
{
  /** \brief  Interface class for output components
   * 
   * Copyright 2010 KSpace MRI. All Rights Reserved.
   *
   * \author James Kyle
   * \author $LastChangedBy$
   * \date 2010-5-7
   * \date $LastChangedDate$
   * \version $Rev$
   **/
  class OutputComponent : public QObject
  {
    Q_OBJECT
  public:
    OutputComponent(QObject *parent = 0) : QObject(parent) {}
    virtual ~OutputComponent() {}
    
  private:
    quint32 _startTimeMSecs;
    
  signals:
    void startTimeChanged();
    void complete();
    
  public slots:
    virtual void begin() = 0;
    virtual void abort() = 0;
    void updateStartTime(quint32 startTimeMSecs);
  };
}
#endif