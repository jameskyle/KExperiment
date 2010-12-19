#ifndef TRIAL_H
#define TRIAL_H
#include <QString>
#include <QList>

#include "../Components.h"
#include "../ComponentExceptions.h"

namespace kex
{
  /** \brief Collection of Trial and Action type components.
   *
   * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
   *
   * \author James Kyle KSpace MRI
   * \author $LastChangedBy$
   * \date 2010-12-15
   * \date $LastChangedDate$
   * \version $Rev$  \sa Action OutputAction RestAction
   **/
  class Trial : public Component
  {
    Q_OBJECT
  public:
    typedef Trial* Pointer;

   /** \brief Constructor for the Trial class.
    *
    * The constructor for the Trial class ensures all core type have been
    * allocated and instantiated.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \sa Action()
    **/
    Trial(QObject *parent = 0,
          Component::Pointer parentComponent=0,
          const QString& name=QString(""),
          const QString& description=QString(""),
          const QString& label=QString(""),
          const QSet<QString>& categories=QSet<QString>());

    /** \brief The destructor for the Trial class
    *
    * Ensures all allocated resources of the Trial class have been freed.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \sa ~Action()
    **/
    ~Trial () {}

   /** \brief Returns the total duration in milliseconds for trial.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \return quint64 duration in milliseconds for Trial
    * \sa Component()
    **/
    quint64 durationMSecs() const;

   /** \brief Returns the list of child components for Trial
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

   /** \brief The equivalence operator for the Trial object.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \return bool true if equal, false otherwise
    **/
    bool operator==(const Component& other) const;

   /** \brief The inequivalence operator for the Trial object.
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
    * \return Trial::Pointer pointer to a new component that is a copy of original
    **/
    Trial::Pointer clone() const;

  private:
    QList<Component *> m_components; //!< list of components
  };
}
#endif // TRIAL_H
