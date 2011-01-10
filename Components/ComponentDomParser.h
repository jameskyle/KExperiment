#ifndef COMPONENTDOMPARSER_H
#define COMPONENTDOMPARSER_H

#include <QDomElement>
#include <QFile>
#include <QObject>
#include <QList>
#include <QListIterator>
#include <QVariant>

#include <boost/function.hpp>
#include <ostream>

#include "Components.h"
#include "ComponentFactory.h"
#include "Common/Logger.h"
#include "Utilities/Utilities.h"

namespace kex
{
  /** \brief  Parses an xml file representing a Component definition.
   *
   * Copyright 2010 KSpace MRI. All Rights Reserved.
   *
   * \author James Kyle
   * \author $LastBy$
   * \date 2010-5-10
   * \date $LastChangedDate$
   * \version $Rev$  \sa Component
   **/
  class ComponentDomParser
  {
  public:
    static const QString ActionTagName;
    static const QString EventTagName;
    static const QString TrialTagName;
    static const QString ExperimentTagName;
    static const QString HeaderTagName;
    static const QString ItemTagName;
    static const QString NameTagName;
    static const QString DurationTagName;
    static const QString AudioTagName;
    static const QString ImageTagName;
    static const QString VideoTagName;
    static const QString SourcePropertyName;
    static const QString CategoriesTagName;
    static const QString CreateChildParseAction;
    static const QString RestTagName;
    static const QString TextTagName;

    explicit ComponentDomParser(const QString& fileName=QString());
    void clear() {m_globalList.clear();}

    ComponentDomParser& readFile(const QString &fileName);
    ComponentDomParser& readFile(QFile& file);
    ComponentDomParser& readFile();

    Component::Pointer createComponent(const QDomElement& root) const;

    ComponentDomParser& operator<<(QFile& file);
    ComponentDomParser& operator<<(const QString& fileName);

  private:
    Component::SharedPointer templateComponent(const QDomElement &root) const;

    void setComponentProperty(const QString& property,
                              const QVariant& value,
                              Component::Pointer component) const;

    void parseElement(const QDomElement &element,
                      Component::Pointer component) const;

    bool isValidElement(const QDomElement &root) const;
    void parseHeaderElement(const QDomElement &element,
                            Component::Pointer component) const;

    void parseActionElement(const QDomElement &element,
                            Component::Pointer component) const;

    void parseEventElement(const QDomElement &element,
                           Component::Pointer component) const;

    void parseTrialElement(const QDomElement &element,
                           Component::Pointer component) const;

    void parseExperimentElement(const QDomElement &element,
                                Component::Pointer component) const;

    void parseCategoriesElement(const QDomElement &element,
                                Component::Pointer component) const;

    void createChildComponent(const QDomElement &element,
                              Component::Pointer component) const;

    void resolveName(Component::Pointer component) const;

    void setupParseMap();

    QString cleanText(const QString& text) const;

    typedef boost::function<void (const ComponentDomParser*,
                                  const QDomElement &element,
                                  Component::Pointer component)>
                                  parseFunc;

    typedef boost::function<void (Component*, QString& value)>
                                  setComponentValue;


    QString m_filename;
    Component::ComponentList& m_globalList;
    QMap<QString, parseFunc> m_parseMap;
    QMap<QString, setComponentValue> m_setValueMap;

  };
}

#endif // COMPONENTDOMPARSSER_HisValidElement
