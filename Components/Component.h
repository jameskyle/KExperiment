#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>
#include <QStringList>
#include <QSet>
#include <QIcon>
#include <QDebug>
#include <QVariant>

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
  class Component : public QObject
  {
    Q_OBJECT
    Q_FLAGS(ComponentType ComponentTypes)
    Q_FLAGS(ComponentPosition ComponentPositions)
    Q_PROPERTY(quint64 durationMSecs READ durationMSecs)

  public:
    typedef Component* Pointer;
    typedef QSharedPointer<Component> SharedPointer;

    static const QString DEFAULT_ICON;

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

    enum ComponentPosition
    {
      CenterPosition        = 0x1,
      TopLeftPosition       = 0x1 << 1,
      TopCenterPosition     = 0x1 << 2,
      TopRightPosition      = 0x1 << 3,
      CenterRightPosition   = 0x1 << 4,
      BottomRightPosition   = 0x1 << 5,
      BottomCenterPosition  = 0x1 << 6,
      BottomLeftPosition    = 0x1 << 7,
      CenterLeftPosition    = 0x1 << 8,
      DefaultPosition       = 0x1,
    };
    Q_DECLARE_FLAGS(ComponentPositions, ComponentPosition)

    explicit Component(QObject             *parent = 0,
                       Component::Pointer   parentComponent=0,
                       const QString&       name=QString(""),
                       const QString&       description=QString(""),
                       const QString&       label=QString(""),
                       const QSet<QString>& categories=QSet<QString>()) :
    QObject(parent),
    m_parentComponent(parentComponent),
    m_name(name),
    m_description(description),
    m_label(label),
    m_categories(categories)
    {
      this->setProperty("durationMSecs", QVariant(200));
    }

    /** \brief  Clone constructor
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-6
     * \date $LastChangedDate$
     * \return Component::Pointer a new component that is a logical copy
     * \version $Rev$
     **/
    virtual Component::Pointer clone() const = 0;

    virtual ~Component();

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

    /** \brief Returns the set of categories for the component.
     *
     * The categories are used
     *
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \return Returns a QString containing a brief description of the Action.
     * \sa QString
     **/
    const QSet<QString> categories() const {return m_categories;}

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

    /** \brief Adds a category for the Component instance.
     *
     * The category is used for sorting and library organization of Components.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \param  category category to add to set. Maximum of 56 characters.
     **/
    void addCategory(const QString& category);

    /** \brief Removes a category for the Component instance.
     *
     * The category is used for sorting and library organization of Components.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \param  category category to remove from set. Maximum of 56 characters.
     **/
    bool removeCategory(const QString& category);

    /** \brief String representation for the Component.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \return QString representation of the component
     **/
    virtual const QString toString() const;

    /** \brief Returns the type for Component.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \return ComponentTypes type of component
     **/
    virtual ComponentTypes componentType() const;

    /** \brief Total duration of component in milliseconds
     *
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \return quint64 duration of component in milliseconds
     **/
    virtual quint64 durationMSecs() const = 0;

    static const quint64 MAX_DURATION = 1800000; //!< maximum run time, 30m

    /** \brief Returns a QString representation of the component type.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \param t a ComponentTypes object
     * \return QString the string  representation for t
     **/
    static const QString componentTypeToString(ComponentTypes t);

    /** \brief Returns a QString representation of the component type.
     *
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \param t a ComponentTypes object
     * \return QString the string  representation for t
     **/
    static const QStringList actionTypes();

    /** \brief Determines equality for Component and other
     *
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \param other the component to determine equality with
     * \return bool true if equal, false otherwise
     **/
    virtual bool operator==(const Component& other) const;

    /** \brief Determines inequality for Component and other
     *
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \param other the component to determine inequality with
     * \return bool true if not equal, false otherwise
     **/
    virtual bool operator!=(const Component& other) const;

    /** \brief Returns a pointer to the parent component
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-17
     * \return Pointer a pointer to the parent component
     **/
    Pointer parentComponent() const {return m_parentComponent;}

    /** \brief Sets the parent component
     *
     * \author James Kyle KSpace MRI
     * \date 2010-12-17
     * \param p parent to the component to set as parent
     **/
    void setParentComponent(Pointer p) {m_parentComponent = p;}

  protected:
    ComponentTypes  m_componentType; //!< type for component

  private:
    Component::Pointer m_parentComponent; //!< the component parent
    QString         m_name; //!< name of the component
    QString         m_description; //!< detailed description of the component
    QString         m_label; //!< brief description of the component
    QSet<QString>   m_categories; //!< list of all categories for component
  };
  const QString Component::DEFAULT_ICON(":/images/other/Science-64.png");
};

Q_DECLARE_OPERATORS_FOR_FLAGS(kex::Component::ComponentTypes)
Q_DECLARE_OPERATORS_FOR_FLAGS(kex::Component::ComponentPositions)
#endif
