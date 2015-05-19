#include "ComponentDomParserTest.h"

namespace kex
{
  ComponentDomParserTest::ComponentDomParserTest() :
  m_dom(),
  m_templates(ComponentTemplates()),
  LabelKey("label"),
  DescriptionKey("description"),
  TypeKey("type"),
  DurationMSecsKey("durationMSecs"),
  DelayMSecsKey("delay"),
  FileKey("file"),
  NameKey("name")
  {
    QCoreApplication::setApplicationName(
          kex::Config::instance().applicationName());
    Config::ApplicationDataDirectoryTypes t;

  }

  void ComponentDomParserTest::initTestCase()
  {
  }

  void ComponentDomParserTest::readFileTest()
  {
    Component::SharedPointer sp;
    QString name;
    QMap<QString, QString>* map;

    for (int i = 0; i < m_templates.c_list.size(); ++i)
    {
      map = m_templates.c_list[i];
      name = (*map)[NameKey];

      m_dom.readFile((*map)[FileKey]);
      sp = Component::globalList().back();

      verifyValues((i + 1), Component::globalList().size(), name);

      Component::ComponentTypes t;
      t = Component::componentTypeFromString((*map)[TypeKey]);
      verifyValues(t, sp->componentType(), sp->name());

      verifyValues(name, sp->name(), sp->name());
      verifyValues((*map)[LabelKey], sp->label(), sp->name());
      verifyValues((*map)[DescriptionKey], sp->description(), sp->name());
      verifyValues((qint64)(*map)[DurationMSecsKey].toUInt(),
                    sp->durationMSecs(), sp->name());

      if(sp->componentType() & ~Component::ActionType)
      {
        QSharedPointer<ComponentCollection> spd;
        spd = sp.dynamicCast<ComponentCollection>();

        verifyValues((*map)["children"].toInt(),
                      spd->components().size(),
                      spd->name());

      } else if(sp->componentType() &
         (Component::ActionType & ~Component::RestActionType))
      {
        qint64 spec_delay = (*map)[DelayMSecsKey].toUInt();
        qint64 comp_delay = sp->property("delay").toUInt();

        verifyValues(spec_delay, comp_delay, sp->name());
      }
    }
  }

  void ComponentDomParserTest::componentsTest()
  {

  }

  void ComponentDomParserTest::cleanupTestCase()
  {

  }

}

QTEST_MAIN(kex::ComponentDomParserTest)
