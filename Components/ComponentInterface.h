#ifndef COMPONENTINTERFACE_H
#define COMPONENTINTERFACE_H
#include <QStringList>

#include <Common/Uncopyable.h>

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
  class ComponentInterface : private Uncopyable
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
    ComponentInterface () : _name(""), _description(""), _label(""), _category("") {}

    /** \brief This is the destructor for the Action base class
    *
    * Performs basic clean up required by the Action base class
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    virtual ~ComponentInterface () {}
    
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
    const QString name() const {return _name;}

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
    const QString description() const {return _description;}

    /** \brief Returns the label for an Action class.
    *
    * The label is a brief description of maximum 256 characters.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return Returns a QString containing a brief description of the Action.
    * \sa QString
    **/
    const QString label() const {return _label;}

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
    const QString category() const {return _category;}

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
    void setName(const QString& name) {_name = name;}

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
    void setDescription(const QString& desc) {_description = desc;}

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
    void setLabel(const QString& label) {_label = label;}

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
    void setCategory(const QString& category) {_category = category;}


    static const quint32 MAX_DURATION = 1800000; //!< maximum run time
    
  private:
    /*
      TODO doc for private vars
    */
    QString _name; //!< name of the component
    QString _description; //!< detailed description of the component
    QString _label; //!< brief description of the component
    QString _category; //!< main group identifier
    QStringList _tagList; //!< list of associated tags for sorting/filtering
    
  };
}
#endif