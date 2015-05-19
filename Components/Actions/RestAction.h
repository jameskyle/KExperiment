#ifndef RESTACTION_H
#define RESTACTION_H

#include "Components/Component.h"

namespace kex
{
  class RestAction : public Component
  {
    Q_OBJECT
    Q_PROPERTY(qint64 duration READ durationMSecs WRITE setDurationMSecs)
  public:
    typedef RestAction* Pointer;

    /** \brief Default constructor
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-16
    * \param parent the Qt parent for the object
    * \param name the name for the object, should be unique
    * \param description a long description for object
    * \param label a brief description for object
    * \param categories a set of categories that object belongs to
    * \param durationMSecs the duration for rest period in milliseconds
    * \return RestAction a newly created rest action
    **/
    explicit RestAction(QObject             *parent = 0,
                        Component::Pointer   parentComponent=0,
                        const QString&       name=QString(""),
                        const QString&       description=QString(""),
                        const QString&       label=QString(""),
                        const QSet<QString>& categories=QSet<QString>(),
                        qint64              durationMSecs=0);
   /** \brief Destructor for the object
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-16
    **/
    ~RestAction();

    /** \brief Sets the duration for RestAction in milliseconds.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param durationMSecs duration in milliseconds
    **/
    void setDurationMSecs(qint64 durationMSecs) {m_durationMSecs = durationMSecs;}

   /** \brief Gets the duration for RestAction in milliseconds.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return qint64 duration in milliseconds
    **/
    qint64 durationMSecs() const { return m_durationMSecs;}

   /** \brief Returns a RestAction that is a clone of the current one
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return Pointer pointer to a new RestAction object
    **/
    Pointer clone() const;

   /** \brief Returns true if objects are logically equal, false otherwise
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return bool returns true if objects are equal
    **/
    bool operator==(const Component& other) const;

   /** \brief Returns true if objects are not logically equal, false otherwise
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return bool returns true if objects are not equal
    **/
    bool operator!=(const Component& other) const;

  private:
    qint64 m_durationMSecs; //!< the rest duration for component
    };
};
#endif
