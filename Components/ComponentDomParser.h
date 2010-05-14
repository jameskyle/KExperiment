#ifndef COMPONENTDOMPARSER_H
#define COMPONENTDOMPARSER_H

#include <QDomElement>
#include <QFile>
#include <QObject>
#include <QList>
#include <QVariant>

#include "ComponentInterface.h"
#include "ComponentList.h"
#include "Common/Logger.h"
#include "AbstractComponent.h"

namespace kex
{
  /** \brief  Parses an xml file representing a Component definition.  
   * 
   * Copyright 2010 KSpace MRI. All Rights Reserved.
   *
   * \author James Kyle
   * \author $LaAbstractComponent* parentstChangedBy$
   * \date 2010-5-10
   * \date $LastChangedDate$
   * \version $Rev$  \sa ComponentInterface
   **/
  
  class ComponentDomParser
  {
  public:
    ComponentDomParser();
    ComponentDomParser(const QString& fileName);
    
    bool readFile(const QString &fileName);
    bool readFile();
    
    AbstractComponent::Pointer component() const {return _rootComponent;}
        
  private:
    AbstractComponent::Pointer _rootComponent;
    QString _fileName;
    bool isValidElement(const QDomElement &root) const;
    void parseHeaderElement(const QDomElement &element, 
                            AbstractComponent* component) const;

    void parseElement(const QDomElement &element, 
                      AbstractComponent* component) const;
    void parseActionElement(const QDomElement &element, 
                            AbstractComponent* component) const;
    void setMainCategory(const QDomElement &element,
                         AbstractComponent* component) const;
    
    void createChildComponent(const QDomElement &element,
                              AbstractComponent *comp) const;

    
  };
}
#endif // COMPONENTDOMPARSSER_HisValidElement