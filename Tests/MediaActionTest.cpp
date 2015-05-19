#include "MediaActionTest.h"

// TODO Implement the following test methods for the MediaAction class
namespace kex
{
  MediaActionTest::MediaActionTest() :
    m_testAudioFile(),
    m_testVideoFile()
  {
    // TODO: Converting this to an auto-generated absolute path when given a
    //       relative project path would be ideal
    QString root("/Users/jkyle/Projects/KExperimentProject/KExperiment/");
    m_testAudioFile.append(root).append("Tests/Data/test.mp3");
    m_testVideoFile.append(root).append("Tests/Data/test.mp4");

    QCoreApplication::setApplicationName(
          kex::Config::instance().applicationName());
    Config::ApplicationDataDirectoryTypes t;
  }

  void MediaActionTest::categoriesTest()
  {
    QStringList list;
    list << "Cat1" << "Cat2" << "Cat3";
    MediaAction action;

    QVERIFY(action.categories().size() == 0);
    QVERIFY(action.categories().empty());

    for (int i = 0; i < list.size(); ++i) {
      QVERIFY(action.categories().size() == i);
      action.addCategory(list[i]);
      QVERIFY(action.categories().contains(list[i]));
      QVERIFY(action.categories().size() == (i + 1));
    }
  }

  void MediaActionTest::cleanupTestCase()
  {
  }

  void MediaActionTest::cloneTest()
  {
    MediaAction im(0,0, "A Name", "A Description", "A Label");
    MediaAction::Pointer pt = im.clone();

    QVERIFY(im == *pt);

    MediaAction *pt2 = pt->clone();

    QVERIFY(*pt2 == *pt);
    QVERIFY(pt2 != pt);
  }

  void MediaActionTest::componentTypeFromStringTest()
  {
    Component::ComponentTypes c_type;

    c_type = Component::componentTypeFromString("MediaActionType");
    QVERIFY(c_type == Component::MediaActionType);

    c_type = Component::componentTypeFromString("AudioActionType");
    QVERIFY(c_type == Component::AudioActionType);

    c_type = Component::componentTypeFromString("VideoActionType");
    QVERIFY(c_type == Component::VideoActionType);

  }

  void MediaActionTest::componentTypeTest()
  {
    MediaAction action;

    QVERIFY(action.componentType() == Component::MediaActionType);

    action.setSource(m_testAudioFile);
    QVERIFY(action.componentType() == Component::AudioActionType);

    action.setSource(m_testVideoFile);
    QVERIFY(action.componentType() == Component::VideoActionType);

    // invalid source
    action.setSource("");
    QVERIFY(action.componentType() == Component::MediaActionType);

  }

  void MediaActionTest::componentTypeToStringTest()
  {
    QString s_type = "MediaAction";
    MediaAction action;

    QVERIFY(s_type == Component::componentTypeToString(action.componentType()));

    s_type = "AudioAction";
    action.setSource(m_testAudioFile);
    QVERIFY(s_type == Component::componentTypeToString(action.componentType()));

    s_type = "VideoAction";
    action.setSource(m_testVideoFile);
    QVERIFY(s_type == Component::componentTypeToString(action.componentType()));

  }

  void MediaActionTest::constructorTest()
  {
    MediaAction action;
    QVERIFY(action.parent() == 0);
    QVERIFY(action.parentComponent() == 0);
    QVERIFY(action.name() == "");
    QVERIFY(action.description() == "");
    QVERIFY(action.label() == "");
    QVERIFY(action.categories().empty());
    QVERIFY(action.durationMSecs() == 0);
    QVERIFY(action.delayMSecs() == 0);
    QVERIFY(action.source() == "");
    // we test component type for both equivalence and masking
    QVERIFY(action.componentType() == Component::MediaActionType);
    QVERIFY(action.componentType() & Component::MediaActionType);



  }

  void MediaActionTest::delayMSecsTest()
  {
    MediaAction action;
    QVERIFY(action.delayMSecs() == 0);

    action.setDelayMSecs(1000);
    QVERIFY(action.delayMSecs() == 1000);

    // negative values should throw an exception
    try {
      action.setDelayMSecs(-1);
      QFAIL("InvalidDealyValue exception expected, but not thrown.");
    } catch (InvalidDelayValue) {}

    try {
      action.setDelayMSecs(Component::MAX_DURATION + 1);
      QFAIL("InvalidDelayValue exception expected, but not thrown.");
    } catch (InvalidDelayValue) {}

    action.setDelayMSecs(Component::MAX_DURATION - 1);
    QVERIFY(action.delayMSecs() == (Component::MAX_DURATION - 1));
  }

  void MediaActionTest::descriptionTest()
  {
    MediaAction action;
    QVERIFY(action.description() == "");

    action.setDescription("New Description");
    QVERIFY(action.description() == "New Description");

    QString s = "Another Description";
    action.setDescription(s);
    QVERIFY(action.description() == s);
  }

  void MediaActionTest::durationMSecsTest()
  {
    MediaAction action;
    QVERIFY(action.durationMSecs() == 0);

    // media actions only update duration times when media is added.
    action.setSource(m_testAudioFile);
    QVERIFY(action.durationMSecs() == 28028);

    action.setSource(m_testVideoFile);
    QVERIFY(action.durationMSecs() == 8400);

  }

  void MediaActionTest::equalityTest()
  {
    MediaAction action1;
    MediaAction action2;

    QVERIFY(action1 == action2);

    action1.setDelayMSecs(100);
    QVERIFY(action1 != action2);

    action2.setDelayMSecs(100);
    QVERIFY(action1 == action2);

    action1.setName("Name");
    action2.setName("Name");
    QVERIFY(action1 == action2);

    action1.setLabel("Label");
    action2.setLabel("Label");
    QVERIFY(action1 == action2);

    action1.setDescription("Description");
    action2.setDescription("Description");
    QVERIFY(action1 == action2);

    action1.addCategory("Cat1");
    QVERIFY(action1 != action2);
    action2.addCategory("Cat1");
    QVERIFY(action1 == action2);

    action1.setSource(m_testAudioFile);
    QVERIFY(action1 != action2);

    action2.setSource(m_testAudioFile);
    QVERIFY(action1 == action2);

    action2.setSource(m_testVideoFile);
    QVERIFY(action1 != action2);

    action2.setParent(&action1);
    QVERIFY(action1 != action2);
    action2.setParent(0);
  }

  void MediaActionTest::initTestCase()
  {
  }

  void MediaActionTest::labelTest()
  {
    MediaAction action;
    QVERIFY(action.label() == "");

    action.setLabel("A Label");
    QVERIFY(action.label() == "A Label");

    action.setLabel("");
    QVERIFY(action.label() == "");

    QString s("A Label");
    action.setLabel(s);
    QVERIFY(action.label() == s);
  }

  void MediaActionTest::nameTest()
  {
    MediaAction action;

    QVERIFY(action.name() == "");
    QVERIFY(action.name().isEmpty());

    action.setName("Some Name");
    QVERIFY(action.name() == "Some Name");
    QVERIFY(!action.name().isEmpty());
    QVERIFY(action.name() == QString("Some Name"));
  }

  void MediaActionTest::parentComponentTest()
  {
    MediaAction action;
    Event event;
    Experiment experiment;
    Trial trial;

    QVERIFY(action.parentComponent() == 0x0);

    action.setParentComponent(&event);
    QVERIFY(action.parentComponent() == &event);

    action.setParentComponent(&experiment);
    QVERIFY(action.parentComponent() == &experiment);

    action.setParentComponent(&trial);
    QVERIFY(action.parentComponent() == &trial);
  }

  void MediaActionTest::sourceTest()
  {
    MediaAction action;
    QVERIFY(action.source() == "");

    action.setSource(m_testAudioFile);
    QVERIFY(action.source() == m_testAudioFile);

    action.setSource(m_testVideoFile);
    QVERIFY(action.source() == m_testVideoFile);

    action.setSource("");
    QVERIFY(action.source() == "");
  }

  void MediaActionTest::toStringTest()
  {
    MediaAction action;

    QString temp;
    QString output;
    temp.append("Object: %1");
    temp.append("\nName: %2");
    temp.append("\nDescription: %3");
    temp.append("\nLabel: %4");
    temp.append("\nMainCategory: %5");
    temp.append("\nDurationMSecs: %6");
    temp.append("\nDelayMSecs: %7");
    temp.append(("\nSource: %8"));

    output = temp.arg("MediaAction").arg("").arg("").arg("").arg("MediaAction").
                  arg(0).arg(0).arg("");
    QVERIFY(action.toString() == output);

    action.setName("A Name");
    output = temp.arg("MediaAction").arg("A Name").arg("").arg("").
                  arg("MediaAction").arg(0).arg(0).arg("");
    QVERIFY(action.toString() == output);

    action.setDescription("A Description");
    output = temp.arg("MediaAction").arg("A Name").arg("A Description").arg("").
                  arg("MediaAction").arg(0).arg(0).arg("");

    action.setLabel("A Label");
    output = temp.arg("MediaAction").arg("A Name").arg("A Description").
                  arg("A Label").arg("MediaAction").arg(0).arg(0).arg("");
    QVERIFY(action.toString() == output);

    action.setDelayMSecs(1000);
    output = temp.arg("MediaAction").arg("A Name").arg("A Description").
                  arg("A Label").arg("MediaAction").arg(0).arg(1000).arg("");
    QVERIFY(action.toString() == output);

    action.setSource(m_testAudioFile);
    output = temp.arg("AudioAction").arg("A Name").arg("A Description").
                  arg("A Label").arg("AudioAction").arg(28028).arg(1000).
                  arg(m_testAudioFile);

    QVERIFY(action.toString() == output);

    action.setSource(m_testVideoFile);
    output = temp.arg("VideoAction").arg("A Name").arg("A Description").
                  arg("A Label").arg("VideoAction").arg(8400).arg(1000).
                  arg(m_testVideoFile);
    QVERIFY(action.toString() == output);
  }
}

QTEST_MAIN(kex::MediaActionTest)

