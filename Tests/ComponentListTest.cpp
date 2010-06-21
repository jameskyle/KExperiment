#include "ComponentListTest.h"

namespace kex
{
  ComponentListTest::ComponentListTest() 
  : QObject(),
  _numExamples(3), 
  _numActions(5) // number of types of actions
  {
    
  }

  void ComponentListTest::initTestCase()
  {
  }
  
  void ComponentListTest::cleanupTestCase()
  {
    qDebug() << "called after all tests";
  }

  void ComponentListTest::clearTest()
  {
    QList<ComponentList::Node::Pointer> nodes = componentNodes();
    ComponentList cList;
    
    for (int i =0; i < 2; ++i)
    {
      for (int i = 0; i < nodes.count(); ++i)
      {
        cList.append(nodes[i]);
      }
      
      cList.clear();
      QVERIFY(cList.count() == 0);
      QVERIFY(!cList.back());
      QVERIFY(!cList.front());
      
      qDeleteAll(nodes.begin(), nodes.end());
    }
  }
  
  void ComponentListTest::appendTest()
  {
    ComponentList componentList;
    QList<ComponentList::Node::Pointer> nodes;
    nodes = componentNodes();
    
    // horizontal append
    for (int i = 0; i < nodes.count(); ++i)
    {
      componentList.append(nodes[i]);
      QVERIFY( (i + 1) == componentList.count());
      QVERIFY(nodes[i] == componentList.back());
      QVERIFY(nodes[0] == componentList.front());
    }
    componentList.clear();

    // appending to a parent
    QList<ComponentList::Node::Pointer> a_nodes;
    QList<ComponentList::Node::Pointer> e_nodes;
    QList<ComponentList::Node::Pointer> t_nodes;
    QList<ComponentList::Node::Pointer> ex_nodes;
    
    a_nodes = createTestActionNodes();
    e_nodes = createTestEventNodes();
    t_nodes = createTestTrialNodes();
    ex_nodes = createTestExperimentNodes();
    
    QVERIFY(componentList.count() == 0);
    
    for (int i = 0; i < ex_nodes.count(); ++i)
    {
      componentList.append(ex_nodes[i]);
      ComponentList::iterator it(componentList.begin());
      it = it + i;
      
      ComponentList::Node& np(componentList[i]);
      Q_CHECK_PTR(&np);
      ComponentList::Node::Pointer op = np.next();
      QVERIFY(componentList.back() == ex_nodes[i]);
      QVERIFY(componentList[i].next() == 0);
      if (i) 
      {
        QVERIFY(componentList[i].previous() == &componentList[i-1]);
        QVERIFY(componentList[i].hasPrevious() == true);
      } else
      {
        QVERIFY(componentList[i].hasPrevious() == false);
        QVERIFY(componentList.back() == componentList.front());
      }
      QVERIFY(componentList[i].lastChild() == 0);
      QVERIFY(componentList[i].child() == 0);
      QVERIFY(componentList[i].parentComponent() == 0);
      QVERIFY(componentList[i].durationMSecs() == 0);
      QVERIFY(componentList[i].position() == i);
      QVERIFY(componentList[i].numChildren() == 0);
      QVERIFY(componentList[i].hasChildren() == false);
      QVERIFY(componentList[i].hasNext() == false);
      
      componentList.append(t_nodes[i], &componentList[i]);
      
      componentList.append(e_nodes[i], t_nodes[i]);
      
      int start = i * 5;
      componentList.append(a_nodes[start], e_nodes[i]);
      componentList.append(a_nodes[start + 1], e_nodes[i]);
      componentList.append(a_nodes[start + 2], e_nodes[i]);
      componentList.append(a_nodes[start + 3], e_nodes[i]);
      componentList.append(a_nodes[start + 4], e_nodes[i]);
      
    }
    
    qDeleteAll(a_nodes.begin(), a_nodes.end());
    qDeleteAll(e_nodes.begin(), e_nodes.end());
    qDeleteAll(t_nodes.begin(), t_nodes.end());
    qDeleteAll(ex_nodes.begin(), ex_nodes.end());
  }
  
  void ComponentListTest::nextPreviousNodeTest()
  {
    QList<ComponentList::Node::Pointer> nodes = componentNodes();
    ComponentList componentList;
    
    for (int i = 0; i < nodes.count(); ++i)
    {
      componentList.append(nodes[i]);
    }
    
    // verify that the linking was done correctly
    ComponentList::Node::Pointer node = componentList.front();
    
    // forward traversal; next()
    for (int i = 0; i < componentList.count(); ++i)
    {
      QVERIFY(node == nodes[i]);
      node = node->next();
    }
    
    node = componentList.back();
    // reverse traversal; previous()
    for (int i = nodes.count(); i > 0; --i)
    {
      QVERIFY(node == nodes[i - 1]);
      node = node->previous();
    }
    
    qDeleteAll(nodes.begin(), nodes.end());
  }
  
  void ComponentListTest::insertAfterTest(){}
  void ComponentListTest::insertBeforeTest(){}
  
  void ComponentListTest::findTest()
  {
//    ComponentList::iterator found;
//    ComponentList cList;
//    QList<ComponentList::Node::Pointer> nodes = componentNodes();
//    
//    for (int i = 0; i < nodes.count(); ++i)
//    {
//      cList.append(nodes[i]);
//      
//      
//    }
//    qDeleteAll(cList.begin(), cList.end());
  }
  
  void ComponentListTest::findByNameTest(){}
  
  void ComponentListTest::insertTest(){}
  void ComponentListTest::cloneTest(){}
  void ComponentListTest::removeTest()
  {
    QList<ComponentList::Node::Pointer> nodes = componentNodes();
    ComponentList cList;

    for(int i = 0;i < nodes.count();++i)
    {
      cList.append(nodes[i]);
    }

    while(cList.begin() != cList.end())
    {
      cList.remove(cList.begin());
    }
  }
  
  void ComponentListTest::prependTest(){}
    
  void ComponentListTest::sortComponentListTest(){}
  
  // Operators
  void ComponentListTest::operatorTest()
  {
  }
  
  // iterator methods
  void ComponentListTest::beginTest(){}
  void ComponentListTest::endTest()  
  {
    
  }
  
  void ComponentListTest::iteratorTest()
  {
    QList< ComponentList::Node::Pointer > nodes;
    nodes = componentNodes();
    
    ComponentList cList;
    
    QVERIFY(cList.begin() == cList.end());
    QVERIFY(cList.front() == cList.back());
    
    for (int i = 0; i < nodes.count(); ++i)
    {
      cList.append(nodes[i]);
    }
    QVERIFY(cList.begin() != cList.end());
    QVERIFY(cList.front() != cList.back());
    
    ComponentList::iterator it(cList.begin());
    QVERIFY(it == cList.begin());
    QVERIFY(it != cList.end());
    QVERIFY((*it) == *cList.front());
    QVERIFY((*it) != *cList.back());
    
  }

  QList<ComponentList::Node::Pointer> 
  ComponentListTest::createTestActionNodes() 
  {
    // we have 5 types of actions. we stagger their insertion so we can use 
    // modulus to determine type
    QList<ComponentList::Node::Pointer> cList;
    
    for (int i = 0; i < (_numExamples * 5); ++i)
    {
      QString name("action_%1");
      QString label("label_%1");
      QString desc("desc_%1");
      ComponentList::Node::Pointer node;
      
      int t = (i % 3);
      
      // append rest action
      if (t == 0)
      {
        OutputComponent::SharedPointer sp(new RestAction);
        sp->setName(name.arg(i));
        sp->setLabel(label.arg(i));
        sp->setDescription(desc.arg(i));
        node = new ComponentList::Node(sp);
        
      } else if (t == 1)
      {
        OutputComponent::SharedPointer sp(new TextAction);
        sp->setName(name.arg(i));
        sp->setLabel(label.arg(i));
        sp->setDescription(desc.arg(i));
        node = new ComponentList::Node(sp);
        
      } else if (t == 2)
      {
        OutputComponent::SharedPointer sp(new ImageAction);
        sp->setName(name.arg(i));
        sp->setLabel(label.arg(i));
        sp->setDescription(desc.arg(i));
        node = new ComponentList::Node(sp);
      } else if (t == 3)
      {
        OutputComponent::SharedPointer sp(new AudioAction);
        sp->setName(name.arg(i));
        sp->setLabel(label.arg(i));
        sp->setDescription(desc.arg(i));
        node = new ComponentList::Node(sp);
        
      } else if (t == 4)
      {
        OutputComponent::SharedPointer sp(new VideoAction);
        sp->setName(name.arg(i));
        sp->setLabel(label.arg(i));
        sp->setDescription(desc.arg(i));
        node = new ComponentList::Node(sp);
      }
      
      cList.append(node);
    }
    
    return cList;
  }
  
  QList<ComponentList::Node::Pointer> ComponentListTest::createTestEventNodes()
  {
    QList<ComponentList::Node::Pointer> cList;
    
    for (int i=0; i < _numExamples; ++i)
    {
      OutputComponent::SharedPointer sp(new Event);
      QString name("event_%1");
      QString label("label_%1");
      QString description("desc_%1");
      
      sp->setName(name.arg(i));
      sp->setLabel(label.arg(i));
      sp->setDescription(description.arg(i));
      sp->setMainCategory("Event");
      ComponentList::Node::Pointer node = new ComponentList::Node(sp);
      cList.append(node);
    }
    
    return cList;
  }
  
  QList<ComponentList::Node::Pointer> ComponentListTest::createTestTrialNodes()
  {
    QList<ComponentList::Node::Pointer> cList;
    
    for (int i=0; i < _numExamples; ++i)
    {
      OutputComponent::SharedPointer sp(new Trial);
      QString name("trial_%1");
      QString label("label_%1");
      QString description("desc_%1");
      
      sp->setName(name.arg(i));
      sp->setLabel(label.arg(i));
      sp->setDescription(description.arg(i));
      sp->setMainCategory("Trial");
      ComponentList::Node::Pointer node = new ComponentList::Node(sp);
      cList.append(node);
    }
    
    return cList;
  }
  
  QList<ComponentList::Node::Pointer> 
  ComponentListTest::createTestExperimentNodes()
  {
    QList<ComponentList::Node::Pointer> cList;
    for (int i=0; i < _numExamples; ++i)
    {
      OutputComponent::SharedPointer sp(new Experiment);
      QString name("experiment_%1");
      QString label("label_%1");
      QString description("desc_%1");
      
      sp->setName(name.arg(i));
      sp->setLabel(label.arg(i));
      sp->setDescription(description.arg(i));
      sp->setMainCategory("Event");
      ComponentList::Node::Pointer node = new ComponentList::Node(sp);
      cList.append(node);
    }
    
    return cList;
  }
  
  QList<ComponentList::Node::Pointer> ComponentListTest::componentNodes()
  {
    return (createTestActionNodes() + createTestEventNodes() + 
            createTestTrialNodes() + createTestExperimentNodes());
  }
}
QTEST_MAIN(kex::ComponentListTest)
