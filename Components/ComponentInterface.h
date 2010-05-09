#ifndef COMPONENTINTERFACE_H
#define COMPONENTINTERFACE_H
#include <QStringList>
#include <QTextStream>

#include <typeinfo>

#include <Common/Uncopyable.h>
#include <ComponentDataPrivate.h>

namespace kex
{
  /** \brief  The Action class is the base class for all Action objects.
  *
  *
  * The Action class is the core of al Action objects. Actions are inherently
  * unique. Thus we disallow copying of actions. 
  *
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-01
  * \date $LastChangedDate$
  * \version $Rev$  \sa
  **/
  class ComponentInterface
  {
  public:
    /** \brief This is the constructor for the Action base class.
    *
    * Instantiates the Action class with all attributes set to an empty
    * string
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    ComponentInterface();
    
    /** \brief  Copy constructor for the ComponentInterface
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-6
     * \date $LastChangedDate$
     * \param component the component to be copied
     * \version $Rev$
     **/
    ComponentInterface(const ComponentInterface &component);
    
    /** \brief  Assignment operator.
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-6
     * \date $LastChangedDate$
     * \param component the component being assigned
     * \version $Rev$
     **/
    ComponentInterface& operator=(const ComponentInterface &component);
    
    /** \brief This is the destructor for the Action base class
    *
    * Performs basic clean up required by the Action base class
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    virtual ~ComponentInterface ();
    
    /** \brief Returns the name attribute.
    *
    * The name attribute serves as a unique identifier for every class
    * instance.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return Returns the name of the Action.
    * \sa QList
    **/
    const QString name() const;

    /** \brief Returns the description for the Action class.
    *
    * The description of a base class is a QString with maximum length of
    * 1024 characters.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return QString of maximum size of 512 characters.
    * \sa QString
    **/
    const QString description() const;

    /** \brief Returns the label for an Action class.
    *
    * The label is a brief description of maximum 256 characters.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return Returns a QString containing a brief description of the Action.
    * \sa QString
    **/
    const QString label() const;

    /** \brief Returns the category for the Action class.
    *
    * The category for an Action class is used for sorting and filtering with
    * other Action classes. The category can have a maximum of 56 characters.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return Returns a QString of maximum 56 characters.
    * \sa QString
    **/
    const QString mainCategory() const;

    void setMainCategory(const QString& cat);
    
    /** \brief Sets the name attribute of the Action class.
    *
    * The name attribute serves as a unique identifier for each Action
    * instance. An Action's name is a maximum of 56 characters.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param  name the user provided name for the Action.
    * \sa QString name()
    **/
    void setName(const QString& name);

    /** \brief Sets the description for the Action class.
    *
    * The Action description is a verbose description of any pertinent details
    * about the Action instance. The description is a maximum of 1024
    * characters.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param  description the user provided description for the Action
    * \return description of return value
    * \sa QString description()
    **/
    void setDescription(const QString& desc);

    /** \brief Sets the label of an Action class.
    *
    * An Action's label is a short description of the Action and is displayed
    * in Action summaries and tables.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param  label the user provided label for a an Action.
    * \sa QString label()
    **/
    void setLabel(const QString& label);

    /** \brief Sets the category for the Action instance.
    *
    * The category is used for sorting and library organization of Actions.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param  category the user provided category for the Action. Maximum of
    * 56 characters.
    * \sa QString category()
    **/
    void addCategory(const QString& category);
    
    void removeCategory(const QString& category);
    
    virtual const quint32 durationMSecs() const;
          
    virtual const QString toString() const;
    
    static const quint32 MAX_DURATION = 1800000; //!< maximum run time, 30m

  private:
    /** \brief  Detaches from shared component data.
     * 
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * Ensures this instance of the component is the only one referring to this
     * specific data. Copy-on-Write.
     * 
     * If multiple components share common data, this component dereferences 
     * the data and gets a copy of the data. Nothing is done if there is only
     * a single reference.
     * 
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-6
     * \date $LastChangedDate$
     * \version $Rev$  \sa ComponentDataPrivate
     **/
    void detach();
    class ComponentDataPrivate *d;
    
  public:
    typedef ComponentDataPrivate* DataPtr;
    inline DataPtr &data_ptr() {return d;}
    
  };
}
#endif