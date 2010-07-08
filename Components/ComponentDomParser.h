#ifndef COMPONENTDOMPARSER_H
#define COMPONENTDOMPARSER_H

#include <QDomElement>
#include <QFile>
#include <QObject>
#include <QList>
#include <QVariant>

#include <boost/function.hpp>

#include "OutputComponent.h"
#include "ComponentFactory.h"
#include "ComponentList.h"
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
   * \version $Rev$  \sa OutputComponent
   **/
  class ComponentDomParser
  {
  public:
    ComponentDomParser();
    ComponentDomParser(const QString& fileName);

    void clear() {m_globalList.clear();}

    ComponentDomParser& readFile(const QString &fileName);
    ComponentDomParser& readFile();
    ComponentList components() const;
    
  private:
    typedef boost::function<void (const ComponentDomParser*,
                                  const QDomElement &element,
                                  ComponentList::Node::Pointer node)> 
                                  parseFunc;
    
    typedef boost::function<void (OutputComponent*,
                                  QString& value)> 
                                  setComponentValue;
    
    QString m_filename;
    ComponentList m_globalList;
    QMap<QString, parseFunc> m_parseMap;
    QMap<QString, setComponentValue> m_setValueMap;
    
    bool isValidElement(const QDomElement &root) const;
    void parseHeaderElement(const QDomElement &element,
                            ComponentList::Node::Pointer node) const;

    void parseElement(const QDomElement &element,
                      ComponentList::Node::Pointer node) const;

    void parseActionElement(const QDomElement &element,
                            ComponentList::Node::Pointer node) const;

    void parseEventElement(const QDomElement &element,
                           ComponentList::Node::Pointer node) const;

    void parseTrialElement(const QDomElement &element,
                           ComponentList::Node::Pointer node) const;

    void parseExperimentElement(const QDomElement &element,
                                ComponentList::Node::Pointer node) const;
    
    void parseCategoriesElement(const QDomElement &element,
                                ComponentList::Node::Pointer node) const;
    
    void parseDurationElement(const QDomElement &element,
                              ComponentList::Node::Pointer node) const;
    
    void setMainCategory(const QDomElement &element,
                         ComponentList::Node::Pointer node) const;

    void createChildComponent(const QDomElement &element,
                              ComponentList::Node::Pointer node) const;
    
    void resolveName(ComponentList::Node::Pointer node) const;

    ComponentList::Node::Pointer createComponentNode(const QDomElement& root) const;
    
    void setupParseMap();


  };
}
#endif // COMPONENTDOMPARSSER_HisValidElement
