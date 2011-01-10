#ifndef EXPERIMENT_H
#define EXPERIMENT_H
#include <QString>
#include <QObject>

#include "../Components.h"
#include "../ComponentCollection.h"

namespace kex
{
  /** \brief  A collection of Trial type components.
  *
  * An Experiment a type of component that is a collection of trials.
  * It has the same basic properties of an component.
  *
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-12-15
  * \date $LastChangedDate$
  **/

  class Experiment : public ComponentCollection
  {
    Q_OBJECT
  public:
    typedef Experiment* Pointer;
    /** \brief Constructor for the Experiment class.
    *
    * The constructor for the Experiment class ensures all core type have been
    * allocated and instantiated.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    **/
    Experiment(QObject *parent = 0,
               Component::Pointer parentComponent=0,
               const QString& name=QString(""),
               const QString& description=QString(""),
               const QString& label=QString(""),
               const QSet<QString>& categories=QSet<QString>());

    /** \brief The destructor for the Experiment class
    *
    * Ensures all allocated resources of the Experiment class have been freed.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    **/
    ~Experiment () {}

   /** \brief Returns the total duration in milliseconds for event.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \return quint64 duration in milliseconds for Experiment
    **/
    quint64 durationMSecs() const;

   /** \brief Creates a copy of the component.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \return Experiment::Pointer pointer to a new component that is a copy of original
    **/
    Experiment::Pointer clone() const;
  };
}
#endif
