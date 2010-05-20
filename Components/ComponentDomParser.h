#ifndef COMPONENTDOMPARSER_H
#define COMPONENTDOMPARSER_H

#include <QDomElement>
#include <QFile>
#include <QObject>
#include <QList>
#include <QVariant>

#include "OutputComponent.h"
#include "AggregateComponent.h"
#include "ComponentFactory.h"
#include "ComponentList.h"
#include "Common/Logger.h"

namespace kex
{
  /** \brief  Parses an xml file representing a Component definition.  
   * 
   * Copyright 2010 KSpace MRI. All Rights Reserved.
   *
   * \author James Kyle
   * \author $LastBy$
   * \date 2010-5-10
   * \date $LastChangedDate$
   * \version $Rev$  \sa OutputComponent
   **/
  
  class ComponentDomParser
  {
  public:
    ComponentDomParser();
    ComponentDomParser(const QString& fileName);
    
    OutputComponent* readFile(const QString &fileName);
    OutputComponent* readFile();
    
  private:
    QString _fileName;
    bool isValidElement(const QDomElement &root) const;
    void parseHeaderElement(const QDomElement &element, 
                            OutputComponent* component) const;

    void parseElement(const QDomElement &element, 
                      OutputComponent* component) const;
    
    void parseActionElement(const QDomElement &element, 
                            OutputComponent* component) const;
    
    void parseEventElement(const QDomElement &element,
                           OutputComponent* component) const;
    
    void parseTrialElement(const QDomElement &element,
                           OutputComponent* component) const;
    
    void parseExperimentElement(const QDomElement &element,
                                OutputComponent* component) const;

    void setMainCategory(const QDomElement &element,
                         OutputComponent* component) const;
    
    void createChildComponent(const QDomElement &element,
                              OutputComponent *comp) const;
    
    void resolveName(OutputComponent* comp) const;

    OutputComponent* createComponent(const QDomElement& root) const;

    
  };
}
#endif // COMPONENTDOMPARSSER_HisValidElement