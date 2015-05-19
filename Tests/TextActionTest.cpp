#include "TextActionTest.h"

// TODO Implement tests for TextAction class

namespace kex
{
  TextActionTest::TextActionTest()
  {
  }

  void TextActionTest::categoriesTest()
  {
    TextAction action;
    QStringList list;
    list << "Cat1" << "Cat2" << "Cat3";

    QVERIFY(action.categories().size() == 0);
    QVERIFY(action.categories().empty());

    for (int i = 0; i < list.size(); ++i) {
      QVERIFY(action.categories().size() == i);
      action.addCategory(list[i]);
      QVERIFY(action.categories().contains(list[i]));
      QVERIFY(action.categories().size() == (i + 1));
    }
  }

  void TextActionTest::cleanupTestCase()
  {

  }

  void TextActionTest::cloneTest()
  {
    TextAction action(0,0, "A Name", "A Description", "A Label");
    TextAction::Pointer pt = action.clone();

    QVERIFY(action == *pt);

    TextAction *pt2 = pt->clone();

    QVERIFY(*pt2 == *pt);
    QVERIFY(pt2 != pt);
  }

  void TextActionTest::componentTypeFromStringTest()
  {
    Component::ComponentTypes c_type;

    c_type = Component::componentTypeFromString("TextActionType");
    QVERIFY(c_type == Component::TextActionType);
    QVERIFY(c_type & Component::TextActionType);
    QVERIFY(c_type & Component::ActionType);
  }

  void TextActionTest::componentTypeTest()
  {
    TextAction action;

    QVERIFY(action.componentType() == Component::TextActionType);
    QVERIFY(action.componentType() & Component::TextActionType);
  }

  void TextActionTest::componentTypeToStringTest()
  {
    QString s_type = "TextAction";
    TextAction action;

    QVERIFY(s_type == Component::componentTypeToString(action.componentType()));
  }

  void TextActionTest::constructorTest()
  {
    QSet<QString> categories;
    categories.insert(QString("Cat1"));
    categories.insert(QString("Cat2"));
    categories.insert(QString("Cat3"));

    // Default constructor
    TextAction action;
    QVERIFY(action.parent() == 0);
    QVERIFY(action.parentComponent() == 0);
    QVERIFY(action.name() == "");
    QVERIFY(action.description() == "");
    QVERIFY(action.label() == "");
    QVERIFY(action.categories().empty());
    QVERIFY(action.durationMSecs() == 0);
    QVERIFY(action.delayMSecs() == 0);
    QVERIFY(action.text() == "");
    QVERIFY(action.family() == "Helvetica");
    QVERIFY(action.pointSize() == 12);
    QVERIFY(action.xoffset() == 0);
    QVERIFY(action.yoffset() == 0);
    QVERIFY(action.position() == Component::DefaultPosition);

    // we test component type for both equivalence and masking
    QVERIFY(action.componentType() == Component::TextActionType);
    QVERIFY(action.componentType() & Component::TextActionType);


    TextAction action2(&action,         // parent
                       &action,         // parentComponent
                       "A Name",        // name
                       "A Description", // descriptioin
                       "A Label",       // label
                       categories,      // categories
                       200,             // duration
                       500,             // delay
                       "the text",      // text
                       "Monaco",     // family
                       14,              // font size
                       QColor("white"), // foreground
                       QColor("black"), // background
                       5,               // xoffset
                       5,               // yoffset
                       Component::CenterPosition); // position

    QVERIFY(action2.parent() == &action);
    QVERIFY(action2.parentComponent() == &action);
    QVERIFY(action2.name() == "A Name");
    QVERIFY(action2.description() == "A Description");
    QVERIFY(action2.label() == "A Label");
    QVERIFY(action2.categories().size() == categories.size());
    QVERIFY(action2.categories() == categories);
    QVERIFY(action2.durationMSecs() == 200);
    QVERIFY(action2.delayMSecs() == 500);
    QVERIFY(action2.text() == "the text");
    QVERIFY(action2.family() == "Monaco");
    QVERIFY(action2.pointSize() == 14);
    QVERIFY(action2.foreground() == QColor("white"));
    QVERIFY(action2.background() == QColor("black"));
    QVERIFY(action2.xoffset() == 5);
    QVERIFY(action2.yoffset() == 5);
    QVERIFY(action2.position() == Component::CenterPosition);
    // we test component type for both equivalence and masking
    QVERIFY(action2.componentType() == Component::TextActionType);
    QVERIFY(action2.componentType() & Component::TextActionType);
  }

  void TextActionTest::delayMSecsTest()
  {
    TextAction action;
    QVERIFY(action.delayMSecs() == 0);

    action.setDelayMSecs(1000);
    QVERIFY(action.delayMSecs() == 1000);

    action.setDelayMSecs(Component::MAX_DURATION);
    QVERIFY(action.delayMSecs() == Component::MAX_DURATION);

    try {
      action.setDelayMSecs(-1);
      QFAIL("Expected InvalidDelayValue exception, but none was thrown");
    } catch (InvalidDelayValue) {}

    try {
      action.setDelayMSecs(Component::MAX_DURATION + 1);
      QFAIL("Expected InvalidDelayValue exception, but none was thrown");
    } catch (InvalidDelayValue) {}
  }

  void TextActionTest::descriptionTest()
  {
    TextAction action;
    QVERIFY(action.description() == "");

    action.setDescription("Desc");
    QVERIFY(action.description() == "Desc");
    QVERIFY(action.description() == QString("Desc"));

    action.setDescription(QString("Desc2"));
    QVERIFY(action.description() == "Desc2");

  }

  void TextActionTest::durationMSecsTest()
  {

  }

  void TextActionTest::equalityTest()
  {

  }

  void TextActionTest::initTestCase()
  {

  }

  void TextActionTest::labelTest()
  {

  }

  void TextActionTest::nameTest()
  {

  }

  void TextActionTest::parentComponentTest()
  {

  }

  void TextActionTest::setDelayMSecsTest()
  {

  }

  void TextActionTest::setSourceTest()
  {

  }

  void TextActionTest::sourceTest()
  {

  }

  void TextActionTest::textTest()
  {

  }

  void TextActionTest::toStringTest()
  {

  }
}

QTEST_MAIN(kex::TextActionTest)
