#include "Component.h"

namespace kex
{

  const QString Component::DEFAULT_ICON(":/images/other/Science-64.png");
  Component::Component(QObject *parent,
                       Component::Pointer parentComponent,
                       const QString &name,
                       const QString &description,
                       const QString &label,
                       const QSet<QString> &categories) :
    QObject(parent),
    m_parentComponent(parentComponent),
    m_name(name),
    m_description(description),
    m_label(label),
    m_categories(categories)
  {
  }

  Component::~Component()
  {
  }

  const QString Component::mainCategory() const
  {
    return componentTypeToString(m_componentType);
  }

  const QString Component::toString() const
  {
    QString output;

    output.append("Object: %1");
    output.append("\nName: %2");
    output.append("\nDescription: %3");
    output.append("\nLabel: %4");
    output.append("\nMainCategory: %5");

    return output.arg(componentTypeToString(m_componentType), name(), description(), label(),
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
    m_categories.insert(category.trimmed());
  }

  bool Component::removeCategory(const QString& category)
  {
    return m_categories.remove(category.trimmed());
  }

  Component::ComponentTypes Component::componentType() const
  {
    return m_componentType;
  }

  Component::ComponentTypes Component::componentTypeFromString(QString st)
  {
    ComponentTypes t;

    if(st == "RestActionType")
      t = Component::RestActionType;
    else if(st == "TextActionType")
      t = Component::TextActionType;
    else if(st == "ImageActionType")
      t = Component::ImageActionType;
    else if(st == "AudioActionType")
      t = Component::AudioActionType;
    else if(st == "VideoActionType")
      t = Component::VideoActionType;
    else if(st == "ActionType")
      t = Component::ActionType;
    else if(st == "EventType")
      t = Component::EventType;
    else if(st == "TrialType")
      t = Component::TrialType;
    else if(st == "ExperimentType")
      t = Component::ExperimentType;

    return t;
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

  bool Component::operator!=(const Component& other) const
  {
    return !(*this == other);
  }

  bool Component::operator==(const Component& other) const
  {
    bool equal = (name()        == other.name()        &&
                  description() == other.description() &&
                  label()       == other.label()       &&
                  categories()  == other.categories()  &&
                  durationMSecs() == other.durationMSecs());
    return equal;
  }

  const QStringList Component::actionTypes()
  {
   QStringList list;

   list << componentTypeToString(Component::RestActionType);
   list << componentTypeToString(Component::TextActionType);
   list << componentTypeToString(Component::ImageActionType);
   list << componentTypeToString(Component::AudioActionType);
   list << componentTypeToString(Component::VideoActionType);

   return list;
  }

  Component::ComponentList& Component::globalList()
  {
    static ComponentList g_list;
    return g_list;
  }
  void Component::setParentComponent(Pointer p) {
    Q_ASSERT(p->componentType() & ~Component::ActionType);
    m_parentComponent = p;
  }
}
