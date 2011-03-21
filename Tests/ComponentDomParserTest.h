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

    /** \brief Method for testing two values of the same type for equivalence
    *
    * This method takes the first and second argument and tests for equivalence.
    * If they are not equal, a log message is printed out which specifies the
    * expected value, the received value, and the name of the component.
    *
    * \author James Kyle KSpace MRI
    * \date 2011-03-16
    * \param val1 the first value to test equivalence
    * \param val2 the second value to test for equivalence
    * \param name the name of the component being tested
    **/
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
