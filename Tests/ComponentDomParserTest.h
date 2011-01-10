#ifndef COMPONENTDOMPARSERTEST_H
#define COMPONENTDOMPARSERTEST_H

#include <QTest>
#include <QDebug>
#include <QVariant>
#include <QMap>

#include <boost/function.hpp>

#include "Components/Components.h"
#include "Components/ComponentDomParser.h"
#include "Common/Config.h"
#include "Utilities/Utilities.h"
#include "ComponentTemplates.h"

namespace kex
{
  class ComponentDomParser;

  class ComponentDomParserTest : public QObject
  {
    Q_OBJECT
  public:
    ComponentDomParserTest();

  private:
    ComponentDomParser m_dom;
    ComponentTemplates m_templates;

    const QString LabelKey;
    const QString DescriptionKey;
    const QString TypeKey;
    const QString DurationMSecsKey;
    const QString DelayMSecsKey;
    const QString FileKey;
    const QString NameKey;

    template<class T>
    void verifyValues(const T& val1, const T& val2, const QString& name) const
    {
      QString msg = "Expected: %1, Received: %2, for component: %3";
      msg = msg.arg(val1).arg(val2).arg(name);

      QVERIFY2(val1 == val2, msg.toAscii());
    }

  private slots:
    void initTestCase();

    // iterator methods
    void readFileTest();
    void componentsTest();
    void cleanupTestCase();

  };
}
#endif // COMPONENTDOMPARSERTEST_H
