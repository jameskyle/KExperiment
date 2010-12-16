#ifndef RESTACTION_H
#define RESTACTION_H

#include "Components/Component.h"

namespace kex
{
  class RestAction : public Component
  {
    Q_OBJECT
  public:
    typedef RestAction* Pointer ;
    explicit RestAction(QObject *parent = 0,
               const QString& name=QString(""),
               const QString& description=QString(""),
               const QString& label=QString(""),
               const QSet<QString>& categories=QSet<QString>(),
               quint64 durationMSecs=0);
    ~RestAction();

    /** \brief Sets the duration for RestAction in milliseconds.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param durationMSecs duration in milliseconds
    **/
    void setDurationMSecs(quint64 durationMSecs) {m_durationMSecs = durationMSecs;}

   /** \brief Gets the duration for RestAction in milliseconds.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return quint64 duration in milliseconds
    **/
    quint64 durationMSecs() const { return m_durationMSecs;}

    Pointer clone() const;

    bool operator==(const Component& other) const;
    bool operator!=(const Component& other) const;

  private:
    quint64 m_durationMSecs;
    };
}
#endif
