#ifndef EXPERIMENT_H
#define EXPERIMENT_H
#include <QString>
#include <QObject>

namespace kex
{
  class Experiment : public QObject
  {
    Q_OBJECT
    public:
      Experiment(QObject *parent = 0);
      
      
      const quint32 name() const;
      const QString instructions() const;
      const QString language() const;
      const QString category() const;
      const QString description() const;
      
      
    private:
      QString _name;
      QString _instructions;
      QString _description;
      QString _category;
      QString _language;
    };
  }
  #endif