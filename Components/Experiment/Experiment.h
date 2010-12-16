#ifndef EXPERIMENT_H
#define EXPERIMENT_H
#include <QString>
#include <QObject>

#include "../Components.h"
#include "../ComponentExceptions.h"

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

  class Experiment : public Component
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

   /** \brief Returns the list of child components for Experiment
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \return QList<Component *> list of components
    **/
    const QList<Component *> components() const {return m_components;}

   /** \brief Appends the given component to the child list
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \param component the component to be appended
    **/
    void appendComponent(Component* component);

   /** \brief Removes the given component found at index
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \param index the index for the component to be removed
    **/
    void removeComponentAt(int index);

   /** \brief The equivalence operator for the Experiment object.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \return bool true if equal, false otherwise
    **/
    bool operator==(const Component& other) const;

   /** \brief The inequivalence operator for the Experiment object.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \return bool false if equal, true if not
    **/
    bool operator!=(const Component& other) const;

   /** \brief Creates a copy of the component.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \return Experiment::Pointer pointer to a new component that is a copy of original
    **/
    Experiment::Pointer clone() const;

  private:
    QList<Component *> m_components; //!< list of components
  };
}
#endif
