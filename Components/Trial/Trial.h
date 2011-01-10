#ifndef TRIAL_H
#define TRIAL_H
#include <QString>
#include <QList>

#include "../ComponentCollection.h"
#include "../Components.h"

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
  class Trial : public ComponentCollection
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

   /** \brief Creates a copy of the component.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-15
    * \return Trial::Pointer pointer to a new component that is a copy of original
    **/
    Trial::Pointer clone() const;
  };
}
#endif // TRIAL_H
