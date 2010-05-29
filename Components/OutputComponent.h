#ifndef OUTPUTCOMPONENT_H
#define OUTPUTCOMPONENT_H

#include <QObject>
#include <QSet>
#include <QIcon>
#include <QDebug>
namespace kex
{
  /** \brief  Interface class for output components
   * 
   * Copyright 2010 KSpace MRI. All Rights Reserved.
   *
   * \author James Kyle
   * \author $LastChangedBy$
   * \date 2010-5-7
   * \date $LastChangedDate$
   * \version $Rev$
   **/
  class OutputComponent : public QObject
  {
    Q_OBJECT
    Q_FLAGS(ComponentType ComponentTypes)
        
  public:
    typedef OutputComponent* Pointer;
    typedef QSharedPointer<OutputComponent> SharedPointer;
    
    enum ComponentType
    {
      RestActionType            = 0x1,
      TextActionType            = 0x1 << 1,
      ImageActionType           = 0x1 << 2,
      AudioActionType           = 0x1 << 3,
      VideoActionType           = 0x1 << 4,
      EventType                 = 0x1 << 5,
      TrialType                 = 0x1 << 6,
      ExperimentType            = 0x1 << 7,
      ActionType                = (RestActionType | TextActionType |
                                   ImageActionType | AudioActionType |
                                   VideoActionType),
      AllComponents             = (ActionType | EventType | 
                                   TrialType | ExperimentType),
    };
    Q_DECLARE_FLAGS(ComponentTypes, ComponentType)
    
    OutputComponent(QObject *parent = 0);
    
    /** \brief  Copy constructor
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
   // OutputComponent(const OutputComponent &component);
        
    virtual ~OutputComponent();
    
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
    
    bool removeCategory(const QString& category);
        
    virtual const QString toString() const;
    
    ComponentTypes componentType() const {return _componentType;}
    
    /** \brief  Holds the type of component represented.
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * This stores a mask for the various component types represented. For 
     * a componentType equal to OutputComponent::EventType the method
     * toComponent() would return a pointer to a new Event object.
     * 
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-10
     * \date $LastChangedDate$
     * \param t the type of component
     * \version $Rev$  \sa componentType()
     **/
    void setComponentType(ComponentTypes t);
    
    const QIcon icon();
    void setIcon(const QIcon& icon);
    
    static const quint32 MAX_DURATION = 1800000; //!< maximum run time, 30m
    static const QString componentTypeToString(ComponentTypes t);
    
    virtual void updateFromTemplate(const SharedPointer t);  

  private:
    quint32        _startTimeMSecs;
    ComponentTypes _componentType;
    QString        _name; //!< name of the component
    QString        _description; //!< detailed description of the component
    QString        _label; //!< brief description of the component
    QString        _mainCategory; //!< main group identifier
    QSet<QString>  _categorySet; //!< list of all categories for component
    QIcon          _icon;
    
  signals:
    void startTimeChanged();
    void complete();
    
  public slots:
    virtual void begin() = 0;
    virtual void abort() = 0;
    void updateStartTime(quint32 startTimeMSecs);
  };
  // FIXME http://tinyurl.com/2ga3sdx
//  Q_DECLARE_OPERATORS_FOR_FLAGS(OutputComponent::ComponentTypes)
}
#endif