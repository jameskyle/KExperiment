#include "Component.h"

namespace kex
{
  Component::Component(QObject *parent,
                       const QString &name,
                       const QString &description,
                       const QString &label,
                       const QSet<QString> &categories,
                       const QIcon &icon) :
    QObject(parent),
    m_name(name),
    m_description(description),
    m_label(label),
    m_categories(categories),
    m_icon(icon)
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
    m_categories.insert(category);
  }

  bool Component::removeCategory(const QString& category)
  {
    return m_categories.remove(category);
  }

  const QIcon Component::icon() const
  {
    return m_icon;
  }

  void Component::setIcon(const QIcon& icon)
  {
    m_icon = icon;
  }

  bool Component::operator==(const Component& other) const
  {
    return true;
  }

  bool Component::operator!=(const Component& other) const
  {
    return !(*this == other);
  }

  Component::ComponentTypes Component::componentType() const
  {
    return m_componentType;
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
}
