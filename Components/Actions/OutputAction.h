#ifndef OUTPUTACTION_H
#define OUTPUTACTION_H
#include "Action.h"

#include <QObject>

namespace kex
{
  class OutputAction : public QObject, public Action
  {
    Q_OBJECT
    public:
      OutputAction(QObject *parent = 0) : QObject(parent), Action() {}
      virtual ~OutputAction() {}
      
      const quint32 durationMSecs() const {return _durationMSecs;}
      const quint32 startTimeMSecs() const {return _startTimeMSecs;}
      
      void setDurationMSecs(const quint32 duration) 
        {_durationMSecs = duration;}
          
    private:
      quint32 _durationMSecs;
      quint32 _startTimeMSecs;
      
    signals:
      void startTimeChanged();
      void complete();
      
    public slots:
      virtual void begin() = 0;
      virtual void abort() = 0;
      void updateStartTime();
    };
  }
  #endif