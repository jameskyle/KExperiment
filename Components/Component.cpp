#include "Component.h"

namespace kex
{
  Component::Component(QObject *parent) : 
    QObject(parent),
    m_startTimeMSecs(),
    m_componentType(),
    m_name(),
    m_description(),
    m_label(),
    m_mainCategory(),
    m_categorySet(),
    m_icon()
  {
    m_icon = QIcon(":/images/other/Science-64.png");
  }
  
  void Component::updateStartTime(quint32 startTimeMSecs)
  {
    m_startTimeMSecs = startTimeMSecs;
  }
  
  Component::~Component()
  {
  }
  
  const QString Component::toString() const
  {
    QString output;
    
    output.append("\nObject: %1\n");
    output.append("\tName: %2\n");
    output.append("\tDescription: %3\n");
    output.append("\tLabel: %4\n");
    output.append("\tMainCategory: %5\n");
    
    return output.arg(typeid(this).name(), name(), description(), label(), 
                      mainCategory());
  }
  
  const QString Component::name() const 
  {
    return m_name;
  }
  
  const QString Component::description() const 
  {
    return m_description;
  }
  
  const QString Component::label() const 
  {
    return m_label;
  }
  
  const QString Component::mainCategory() const 
  {
    return m_mainCategory;
  }
  
  void Component::setMainCategory(const QString& cat) 
  {
    m_mainCategory = cat.trimmed();
  }
  
  void Component::setName(const QString& name) 
  {
    m_name = name.trimmed();
  }
  
  void Component::setDescription(const QString& desc)
  {
    m_description = desc.trimmed();
  }
  
  void Component::setLabel(const QString& label)
  {
    m_label = label.trimmed();
  }
  
  void Component::addCategory(const QString& category) 
  {
    m_categorySet.insert(category);
  }
  
  bool Component::removeCategory(const QString& category) 
  {
    return m_categorySet.remove(category);
  }
    
  const QIcon Component::icon()
  {
    return m_icon;
  }
  
  void Component::setIcon(const QIcon& icon)
  {
    m_icon = icon;
  }
    
  void Component::setComponentType(ComponentTypes t)
  {
    m_componentType = t;
  }
  
  const QString Component::componentTypeToString(ComponentTypes t)
  {
    QString typeString;
    switch (t)
    {
      case RestActionType:
        typeString = "RestAction";
        break;
      case TextActionType:
        typeString = "TextAction";
        break;
      case ImageActionType:
        typeString = "ImageAction";
        break;
      case AudioActionType:
        typeString = "AudioAction";
        break;
      case VideoActionType:
        typeString = "VideoAction";
        break;
      case ActionType:
        typeString = "Action";
        break;
      case EventType:
        typeString = "Event";
        break;
      case TrialType:
        typeString = "Trial";
        break;
      case ExperimentType:
        typeString = "Experiment";
        break;
      default:
        typeString = "Undefined";
        break;
    }
    
    return typeString;
  }
  
  void Component::updateFromTemplate(const SharedPointer t)
  {
    Q_CHECK_PTR(t);
    // the default updateFromTemplate pulls in the base information
    // If our component has a field defined and it is not empty, we pull the 
    // data form the provided template
    
    // We don't change the name
    if (t->description() != m_description)
    {
      if (m_description.isEmpty())
      {
        m_description = t->description();
      }
    }
    
    if (t->label() != m_label)
    {
      if (m_label.isEmpty())
      {
        m_label = t->label();
      }
    }
    
    if (t->mainCategory() != m_mainCategory)
    {
      if (m_mainCategory.isEmpty())
      {
        m_mainCategory = t->mainCategory();
      }
    }
  }
}