#include "OutputComponent.h"

namespace kex
{
  OutputComponent::OutputComponent(QObject *parent) : 
  QObject(parent)
  {
    _icon = QIcon(":/images/other/Science-64.png");
  }
  
  void OutputComponent::updateStartTime(quint32 startTimeMSecs)
  {
    _startTimeMSecs = startTimeMSecs;
  }
  
  OutputComponent::~OutputComponent()
  {
  }
  
  const QString OutputComponent::toString() const
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
  
  const QString OutputComponent::name() const 
  {
    return _name;
  }
  
  const QString OutputComponent::description() const 
  {
    return _description;
  }
  
  const QString OutputComponent::label() const 
  {
    return _label;
  }
  
  const QString OutputComponent::mainCategory() const 
  {
    return _mainCategory;
  }
  
  void OutputComponent::setMainCategory(const QString& cat) 
  {
    _mainCategory = cat;
  }
  
  void OutputComponent::setName(const QString& name) 
  {
    _name = name;
  }
  
  void OutputComponent::setDescription(const QString& desc)
  {
    _description = desc;
  }
  
  void OutputComponent::setLabel(const QString& label)
  {
    _label = label;
  }
  
  void OutputComponent::addCategory(const QString& category) 
  {
    _categorySet.insert(category);
  }
  
  bool OutputComponent::removeCategory(const QString& category) 
  {
    return _categorySet.remove(category);
  }
  
  void OutputComponent::appendChild(OutputComponent* child)
  {
    _childComponents.append(child);
  }

  void OutputComponent::removeChild(int index)
  {
    _childComponents.removeAt(index);
  }
  
  void OutputComponent::insertChild(int index, OutputComponent* component)
  {
    _childComponents.insert(index, component);
  }
  
  QList<OutputComponent*> OutputComponent::childComponents() const
  {
    return _childComponents;
  }
  
  const QIcon OutputComponent::icon()
  {
    return _icon;
  }
  
  void OutputComponent::setIcon(const QIcon& icon)
  {
    _icon = icon;
  }
  
  const quint32 OutputComponent::durationMSecs() const
  {
    return 0;
  }
  
  void OutputComponent::setComponentType(ComponentTypes t)
  {
    _componentType = t;
  }
  
  const QString OutputComponent::componentTypeToString(ComponentTypes t)
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
}