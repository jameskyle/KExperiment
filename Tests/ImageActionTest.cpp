#include "ImageActionTest.h"

namespace kex
{
  ImageActionTest::ImageActionTest() : QObject(0), m_categories(), m_action()
  {
    m_categories.insert(QString("Cat1"));
    m_categories.insert(QString("Cat2"));
    m_categories.insert(QString("Cat3"));
  }

  void ImageActionTest::initTestCase()
  {
  }

  void ImageActionTest::cleanupTestCase()
  {
  }

  void ImageActionTest::constructorTest()
  {
    // Default constructor
    ImageAction im;
    QVERIFY(im.parent() == 0);
    QVERIFY(im.parentComponent() == 0);
    QVERIFY(im.name() == "");
    QVERIFY(im.description() == "");
    QVERIFY(im.label() == "");
    QVERIFY(im.categories().empty());
    QVERIFY(im.durationMSecs() == 0);
    QVERIFY(im.delayMSecs() == 0);
    QVERIFY(im.imagePath() == "");
    QVERIFY(im.xoffset() == 0);
    QVERIFY(im.yoffset() == 0);
    QVERIFY(im.position() == Component::DefaultPosition);
    // we test component type for both equivalence and masking
    QVERIFY(im.componentType() == Component::ImageActionType);
    QVERIFY(im.componentType() & Component::ImageActionType);


    ImageAction im2(&im, &im, "A Name", "A Description", "A Label", m_categories,
                    200, 500, "/path/to/image", 5, 5, Component::CenterPosition);
    QVERIFY(im2.parent() == &im);
    QVERIFY(im2.parentComponent() == &im);
    QVERIFY(im2.name() == "A Name");
    QVERIFY(im2.description() == "A Description");
    QVERIFY(im2.label() == "A Label");
    QVERIFY(im2.categories().size() == m_categories.size());
    QVERIFY(im2.categories() == m_categories);
    QVERIFY(im2.durationMSecs() == 200);
    QVERIFY(im2.delayMSecs() == 500);
    QVERIFY(im2.imagePath() == "/path/to/image");
    QVERIFY(im2.xoffset() == 5);
    QVERIFY(im2.yoffset() == 5);
    QVERIFY(im2.position() == Component::CenterPosition);
    // we test component type for both equivalence and masking
    QVERIFY(im2.componentType() == Component::ImageActionType);
    QVERIFY(im2.componentType() & Component::ImageActionType);
  }

  void ImageActionTest::cloneTest()
  {
    ImageAction im(0, 0, "A Name", "A Description", "A Label", m_categories,
                    200, 500, "/path/to/image", 5, 5, Component::CenterPosition);
    ImageAction::Pointer im2 = im.clone();

    QVERIFY(im == *im2);

    ImageAction::Pointer im3(im2->clone());

    QVERIFY(*im2 == *im3);
    QVERIFY(im2 != im3);

  }

  void ImageActionTest::nameTest()
  {
    m_action.setName("A New Name");
    QVERIFY(m_action.name() == "A New Name");

    m_action.setName("Another Name");
    QVERIFY(m_action.name() == "Another Name");
  }

  void ImageActionTest::descriptionTest()
  {
    m_action.setDescription("A Description");
    QVERIFY(m_action.description() == "A Description");

    m_action.setDescription("Another Description");
    QVERIFY(m_action.description() == "Another Description");
  }

  void ImageActionTest::labelTest()
  {
    m_action.setLabel("A Label");
    QVERIFY(m_action.label() == "A Label");

    m_action.setLabel("Another Label");
    QVERIFY(m_action.label() == "Another Label");
  }

  void ImageActionTest::categoriesTest()
  {
    QVERIFY(m_action.categories().size() == 0);
    m_action.addCategory("Cat1");
    QVERIFY(m_action.categories().size() == 1);
    QVERIFY(m_action.categories().contains("Cat1"));

    m_action.addCategory("Cat2");
    QVERIFY(m_action.categories().size() == 2);
    QVERIFY(m_action.categories().contains("Cat1"));
    QVERIFY(m_action.categories().contains("Cat2"));

    m_action.removeCategory("Cat1");
    QVERIFY(m_action.categories().size() == 1);
    QVERIFY(!m_action.categories().contains("Cat1"));
    QVERIFY(m_action.categories().contains("Cat2"));
  }

  void ImageActionTest::toStringTest()
  {
    ImageAction im;
    QString temp;
    QString output;
    temp.append("Object: %1");
    temp.append("\nName: %2");
    temp.append("\nDescription: %3");
    temp.append("\nLabel: %4");
    temp.append("\nMainCategory: %5");
    temp.append("\nDurationMSecs: %6");
    temp.append("\nDelayMSecs: %7");
    temp.append("\nxoffset: %8");
    temp.append("\nyoffset: %9");
    temp.append("\nimagePath: %10");

    output = temp.arg(ImageAction::componentTypeToString(
                        Component::ImageActionType)).arg(
                        "").arg("").arg("").arg("ImageAction").arg(0).arg(0).arg(
                        0).arg(0).arg("");

    QVERIFY(output == im.toString());

    im.setName("A Name");
    output = temp.arg(ImageAction::componentTypeToString(
                        Component::ImageActionType)).arg(
                        "A Name").arg("").arg("").arg("ImageAction").arg(0).arg(
                        0).arg(0).arg(0).arg("");

    QVERIFY(output == im.toString());

    im.setDescription("A Description");
    output = temp.arg(ImageAction::componentTypeToString(
                        Component::ImageActionType)).arg(
                        "A Name").arg("A Description").arg("").arg(
                        "ImageAction").arg(0).arg(0).arg(0).arg(0).arg("");

    QVERIFY(output == im.toString());

    im.setLabel("A Label");
    output = temp.arg(ImageAction::componentTypeToString(
                        Component::ImageActionType)).arg(
                        "A Name").arg("A Description").arg("A Label").arg(
                        "ImageAction").arg(0).arg(0).arg(0).arg(0).arg("");

    QVERIFY(output == im.toString());

    im.setDurationMSecs(1000);
    output = temp.arg(ImageAction::componentTypeToString(
                        Component::ImageActionType)).arg(
                        "A Name").arg("A Description").arg("A Label").arg(
                        "ImageAction").arg(1000).arg(0).arg(0).arg(0).arg("");

    QVERIFY(output == im.toString());

    im.setDelayMSecs(2000);
    output = temp.arg(ImageAction::componentTypeToString(
                      Component::ImageActionType)).arg(
                      "A Name").arg("A Description").arg("A Label").arg(
                      "ImageAction").arg(1000).arg(2000).arg(0).arg(0).arg("");
    QVERIFY(output == im.toString());

    im.setXoffset(500);
    output = temp.arg(ImageAction::componentTypeToString(
                      Component::ImageActionType)).arg(
                      "A Name").arg("A Description").arg("A Label").arg(
                      "ImageAction").arg(1000).arg(2000).arg(500).arg(0).arg("");
    QVERIFY(output == im.toString());

    im.setYoffset(600);
    output = temp.arg(ImageAction::componentTypeToString(
                      Component::ImageActionType)).arg(
                      "A Name").arg("A Description").arg("A Label").arg(
                      "ImageAction").arg(1000).arg(2000).arg(500).arg(600).arg("");
    QVERIFY(output == im.toString());


     im.setImagePath("/path/to/some/image.png");
    output = temp.arg(ImageAction::componentTypeToString(
                      Component::ImageActionType)).arg(
                      "A Name").arg("A Description").arg("A Label").arg(
                      "ImageAction").arg(1000).arg(2000).arg(500).arg(
                      600).arg("/path/to/some/image.png");
    QVERIFY(output == im.toString());

  }

  void ImageActionTest::componentTypeTest()
  {
    ImageAction im;
    QVERIFY(im.componentType() == Component::ImageActionType);
  }

  void ImageActionTest::durationMSecsTest()
  {
    ImageAction im;
    QVERIFY(im.durationMSecs() == 0);

    im.setDurationMSecs(200);
    QVERIFY(im.durationMSecs() == 200);

    im.setDurationMSecs(10000);
    QVERIFY(im.durationMSecs() == 10000);

    try {
      im.setDurationMSecs(Component::MAX_DURATION + 1);
      QFAIL("InvalidDurationValue exception expected, but not thrown.");

    } catch (InvalidDurationValue) {}

    try {
      im.setDurationMSecs(-1);
      QFAIL("InvalidDurationValue exception expected, but not thrown.");

    } catch (InvalidDurationValue) {}

  }

  void ImageActionTest::componentTypeToStringTest()
  {
    QString st = Component::componentTypeToString(Component::ImageActionType);
    ImageAction im;
    QCOMPARE(Component::componentTypeToString(im.componentType()), st);
  }

  void ImageActionTest::componentTypeFromStringTest()
  {
    Component::ComponentTypes c_type;
    ImageAction im;

    c_type = Component::componentTypeFromString("ImageActionType");

    QCOMPARE(im.componentType(), c_type);

  }

  void ImageActionTest::operatorEqualsTest()
  {
    ImageAction im1;
    ImageAction im2;

    QCOMPARE(im1, im2);
    QCOMPARE(im1.durationMSecs(), im2.durationMSecs());
    QVERIFY(im1.image() == im2.image());
    QCOMPARE(im1.xoffset(), im2.xoffset());
    QCOMPARE(im1.yoffset(), im2.yoffset());
    QCOMPARE(im1.position(), im2.position());

  }

  void ImageActionTest::parentComponentTest()
  {
      ImageAction *im1 = new ImageAction;
      QVERIFY(im1->parentComponent() == 0);

      ImageAction im2(0, im1);
      QVERIFY(im2.parentComponent() == im1);
  }
}

QTEST_MAIN(kex::ImageActionTest)
