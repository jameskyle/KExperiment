#include "ComponentDomParserTest.h"

namespace kex
{
  ComponentDomParserTest::ComponentDomParserTest() : 
  m_componentFiles(),
  m_names(),
  m_labels(),
  m_descriptions(),
  m_types(),
  m_childrenCount(),
  m_durationMSecs(),
  m_dom()
  {
    Config::ApplicationDataDirectoryTypes t;
    
    t = Config::ActionDirectory;
    m_componentFiles << QStringList(Utilities::xmlFileComponentList(t));
    
    t = Config::EventDirectory;
    m_componentFiles << QStringList(Utilities::xmlFileComponentList(t));
    
    t = Config::TrialDirectory;
    m_componentFiles << QStringList(Utilities::xmlFileComponentList(t));
    
    t = Config::ExperimentDirectory;
    m_componentFiles << QStringList(Utilities::xmlFileComponentList(t));
   
    // Action template one: Rest 10 Seconds
    m_labels << "Pauses for 10 seconds.";
    m_descriptions << ("When this action is inserted into a Event, a 10 pause "
                       "is performed at the point of its insertion.");
    m_types.append(OutputComponent::RestActionType);
    m_durationMSecs.append(10000);
    m_childrenCount.append(0);
    
    // Action template two: Rest 30 Seconds
    m_labels << "Pauses for 30 seconds.";
    m_descriptions << ("When this action is inserted into a Event, a 30s pause "
                      "is performed at the point of its insertion.");
    m_types.append(OutputComponent::RestActionType);
    m_durationMSecs.append(30000);
    m_childrenCount.append(0);
    
    // Action template three: Rest 60 Seconds
    m_labels << "Pauses for 60 seconds.";
    m_descriptions << ("When this action is inserted into a Event, a 60s "
                       "pause is performed at the point of its insertion.");
    m_types.append(OutputComponent::RestActionType);
    m_durationMSecs.append(60000);
    m_childrenCount.append(0);

    // Event template one: Bar
    m_labels << "Bar";
    m_descriptions << "described";
    m_types.append(OutputComponent::EventType);
    m_durationMSecs.append(90000);
    m_childrenCount.append(2);
    
    // Event template two
    m_labels << "";
    m_descriptions << "";
    m_types.append(OutputComponent::EventType);
    m_durationMSecs.append(30000);
    m_childrenCount.append(1);
    
    // Trial template one:
    m_labels << "An amazing trial.";
    m_descriptions << "A truly amazing example of a trial";
    m_types.append(OutputComponent::TrialType);
    m_durationMSecs.append(120000);
    m_childrenCount.append(2);
    
    // Trial template two:
    m_labels << "";
    m_descriptions << "";
    m_types.append(OutputComponent::TrialType);
    m_durationMSecs.append(90000);
    m_childrenCount.append(1);
  
    // Experiment template one:
    m_labels << "An example experiment.";
    m_descriptions << "Description for the example experiment.";
    m_types.append(OutputComponent::ExperimentType);
    m_durationMSecs.append(120000);
    m_childrenCount.append(1);
    
    // Experiment template two:
    m_labels << "An second example experiment.";
    m_descriptions << "Description for the example experiment.";
    m_types.append(OutputComponent::ExperimentType);
    m_durationMSecs.append(120000);
    m_childrenCount.append(1);
  }
  
  void ComponentDomParserTest::initTestCase()
  {
  }
  
  void ComponentDomParserTest::readFileTest()
  {
    boost::function<QString (const QString&)> getName;
    getName = &Utilities::componentNameFromFilePath;
    
    ComponentList::Node::Pointer node;

    for (int i = 0; i < m_componentFiles.size(); ++i)
    {
      m_dom.readFile(m_componentFiles[i]);
      node = m_dom.components().back();
      
      QVERIFY(m_dom.components().size() == (i + 1));
      QVERIFY(node->component()->componentType() & m_types[i]);
      QVERIFY(node->component()->name() == getName(m_componentFiles[i]));
      QVERIFY(node->component()->label() == m_labels[i]);
      QVERIFY(node->component()->description() == m_descriptions[i]);
      QVERIFY(node->durationMSecs() == m_durationMSecs[i]);
      QVERIFY(node->children().size() == m_childrenCount[i]);
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
