#ifndef TRIAL_H
#define TRIAL_H
#include <QString>
#include <QList>

#include "Components/Component.h"

namespace kex
{
  /** \brief Collection of Event and Action type components.
   * 
   * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
   *
   * \author James Kyle KSpace MRI
   * \author $LastChangedBy$
   * \date 2010-04-01
   * \date $LastChangedDate$
   * \version $Rev$  \sa Action OutputAction RestAction
   **/
  class Trial : public Component
  {
    Q_OBJECT
  public:
    /** \brief Constructor for the Event class.
     * 
     * The constructor for the Event class ensures all core type have been 
     * allocated and instantiated.
     * 
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \sa Action()
     **/
    Trial (QObject *parent = 0) : Component(parent) {}
    
    // TODO implement specifics
    virtual void updateFromTemplate(const Component::SharedPointer t);

    
    /** \brief The destructor for the Event class
     * 
     * Ensures all allocated resources of the Event class have been freed.
     * 
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \sa ~Action()
     **/
    ~Trial () {}
    
  public slots:
    void begin() {}
    void abort() {}
  };
}
#endif // TRIAL_H