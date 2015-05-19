#include "ComponentListTest.h"

namespace kex
{
  ComponentListTest::ComponentListTest() 
  : QObject()
  {
  }

  void ComponentListTest::ComponentListTest::initTestCase()
  {
  }
  
  void ComponentListTest::ComponentListTest::cleanupTestCase()
  {
    qDebug() << "called after all tests";
  }
  
  void ComponentListTest::incrementIteratorTest()
  {
    ComponentList cList;
    QList<ComponentList::Node::Pointer> nList;
    int i(0);
    
    getLists(&cList, &nList);
    ComponentList::iterator it(cList.begin());
    
    while (it != cList.end())
    {
      QVERIFY(*it == nList[i]);
      ++i;
      ++it;
    }
    
    QVERIFY(it == cList.end());
    Utilities::deleteAll(cList);
  }
  
  void ComponentListTest::decrementIteratorTest()
  {
    ComponentList cList;
    QList<ComponentList::Node::Pointer> nList;
    int i(0);
    
    getLists(&cList, &nList);
    
    ComponentList::iterator it(cList.back());
    
    i = (nList.size() - 1);
    while (it != cList.end())
    {
      QVERIFY(*it == nList[i]);
      --i;
      --it;
    }
    Utilities::deleteAll(cList);
  }
  
  void ComponentListTest::randomAccessIteratorTest()
  {
    ComponentList cList;
    QList<ComponentList::Node::Pointer> nList;
    int i(0);
    
    getLists(&cList, &nList);
    
    ComponentList::iterator it(cList.begin());
    
    for (i = 0; i < nList.size(); ++i)
    {
      int reverse = nList.size() - i - 1;
      
      QVERIFY(it[i] == nList[i]);
      QVERIFY(it[reverse] == nList[reverse]);
    }
    
    Utilities::deleteAll(cList);
  }
  
  void ComponentListTest::frontTest()
  {
    
  }
  
  void ComponentListTest::backTest()
  {
    ComponentList cList;
    QList<ComponentList::Node::Pointer> nList;
    int i(0);
    
    getLists(&cList, &nList);
    cList.clear();
    
    for (i = 0; i < nList.size(); ++i)
    {
      cList.push_back(nList[i]);
      QVERIFY(cList.back() == nList[i]);
    }
    cList.clear();
    
    for (i = 0; i < nList.size(); ++i)
    {
      cList.push_front(nList[i]);
      QVERIFY(cList.back() == nList[0]);
    }
    Utilities::deleteAll(cList);
  }
  
  void ComponentListTest::sizeTest()
  {
    ComponentList cList;
    QList<ComponentList::Node::Pointer> nList;
    int i(0);
    
    QVERIFY(cList.size() == 0);
    
    getLists(&cList, &nList);
    QVERIFY(cList.size() == nList.size());
    cList.clear();
    QVERIFY(cList.size() == 0);
    
    for (i = 0; i < nList.size(); ++i)
    {
      cList.push_back(nList[i]);
      QVERIFY(cList.size() == (i + 1));
    }
    
    Utilities::deleteAll(nList);
  }
  
  void ComponentListTest::emptyTest()
  {
    ComponentList cList;
    QList<ComponentList::Node::Pointer> nList;
    
    QVERIFY(cList.empty());
    
    getLists(&cList, &nList);
    
    QVERIFY(!cList.empty());
    
    cList.clear();
    
    QVERIFY(cList.empty());
    
    Utilities::deleteAll(nList);
  }
  
  void ComponentListTest::push_backTest()
  {
    ComponentList cList;
    QList<ComponentList::Node::Pointer> nList;
    int i(0);
    
    getLists(&cList, &nList);
    cList.clear();
    
    for (i = 0; i < nList.count(); ++i)
    {
      cList.push_back(nList[i]);
      QVERIFY(cList.back() == nList[i]);
      QVERIFY(cList.size() == (i + 1));
      if (i != 0) QVERIFY(cList.front() != nList[i]);
      else QVERIFY(cList.front() == cList.back());
      QVERIFY(cList.back() != *cList.end());
    }
    
    Utilities::deleteAll(nList);
  }
    
  void ComponentListTest::push_frontTest()
  {
    ComponentList cList;
    QList<ComponentList::Node::Pointer> nList;
    int i(0);
    
    getLists(&cList, &nList);
    cList.clear();
    
    for (i = 0; i < nList.count(); ++i)
    {
      cList.push_front(nList[i]);
      QVERIFY(cList.front() == nList[i]);
      QVERIFY(cList.size() == (i + 1));
      if (i != 0) QVERIFY(cList.back() != nList[i]);
      else QVERIFY(cList.back() == cList.back());
      QVERIFY(cList.front() == *cList.begin());
    }
    
    Utilities::deleteAll(nList);
  }
    
  void ComponentListTest::beginTest()
  {
    ComponentList cList;
    ComponentList cList2;
    QList<ComponentList::Node::Pointer> nList;
    QList<ComponentList::Node::Pointer> nList2;
    int i(0);
    
    getLists(&cList, &nList);
    getLists(&cList2, &nList2);
    cList.clear();
    cList2.clear();
    
    for (i = 0; i < nList.count(); ++i)
    {
      cList.push_back(nList[i]);
      QVERIFY(*cList.begin() == nList[0]);
      cList2.push_front(nList2[i]);
      QVERIFY(*cList2.begin() == nList2[i]);
      
    }
    
    Utilities::deleteAll(nList);
    Utilities::deleteAll(nList2);
  }
  
  void ComponentListTest::endTest()
  {
    ComponentList cList;
    ComponentList cList2;
    QList<ComponentList::Node::Pointer> nList;
    QList<ComponentList::Node::Pointer> nList2;
    int i(0);
    
    getLists(&cList, &nList);
    getLists(&cList2, &nList2);
    cList.clear();
    cList2.clear();
    
    for (i = 0; i < nList.count(); ++i)
    {
      cList.push_back(nList[i]);
      QVERIFY(*cList.end() == 0);
      cList2.push_front(nList2[i]);
      QVERIFY(*cList2.end() == 0);
      
    }
    
    Utilities::deleteAll(nList);
    Utilities::deleteAll(nList2);
    
  }
  
  void ComponentListTest::clearTest()
  {
    ComponentList cList;
    QList<ComponentList::Node::Pointer> nList;
    
    getLists(&cList, &nList);
    cList.clear();
    
    QVERIFY(cList.size() == 0);
    QVERIFY(*cList.begin() == 0);
    QVERIFY(*cList.end() == 0);
    
    ComponentList::iterator it(cList.begin());
    
    // this should never enter the loop
    while (it != cList.end())
    {
      QVERIFY(false);
    }
    
    Utilities::deleteAll(nList);
  }
  
  void ComponentListTest::removeTest()
  {
    ComponentList cList;
    QList<ComponentList::Node::Pointer> nList;
    int i(0);
    
    getLists(&cList, &nList);

    for (i = 0; i < nList.size(); ++i)
    {
      cList.remove(nList[i]);
      QVERIFY(cList.size() == (nList.size() - (i + 1)));
      
    }
    
    Utilities::deleteAll(nList);
  }
  
  void ComponentListTest::getLists(ComponentList *cList,
                                   QList<ComponentList::Node::Pointer> *nList)
  {
    int i(0);
    for (i = 0; i < 10; ++i)
    {
      nList->append(new ComponentList::Node(new RestAction));
      cList->push_back((*nList)[i]);
    }
  }

}
QTEST_MAIN(kex::ComponentListTest)
