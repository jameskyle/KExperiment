#ifndef COMPONENTDOMPARSERTEST_H
#define COMPONENTDOMPARSERTEST_H

#include <QTest>
#include <QDebug>
#include <QStringList>

#include <boost/function.hpp>

#include "Components/Components.h"
#include "Components/ComponentDomParser.h"
#include "Common/Config.h"
#include "Utilities/Utilities.h"

namespace kex
{
  class ComponentDomParser;
  
  class ComponentDomParserTest : public QObject
  {
    Q_OBJECT
  public:
    ComponentDomParserTest();
    
  private:
    QStringList m_componentFiles;
    QStringList m_names;
    QStringList m_labels;
    QStringList m_descriptions;
    QList<Component::ComponentTypes> m_types;
    QList<int> m_childrenCount;
    QList<int> m_durationMSecs;
    ComponentDomParser m_dom;
    
  private slots:
    void initTestCase();
    
    // iterator methods
    void readFileTest();
    void componentsTest();
    void cleanupTestCase();
  };
}  
#endif // COMPONENTDOMPARSERTEST_H