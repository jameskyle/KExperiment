#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QDesktopServices>

#include "Uncopyable.h"

namespace kex
{
  // Contains globally used configuration options for the application
  class Config : private Uncopyable
  {
  public:
    static Config& instance();
    const QString organizationName() const {return _organizationName;}
    const QString organizationDomain() const {return _organizationDomain;}
    const QString storageLocation() const {return _storageLocation;}
    
    
    void setOrganizationDomain(const QString& name) 
      {_organizationDomain = name;}
    void setOrganizationName(const QString& name) 
      {_organizationName = name;}
    
  private:
    Config();
    QString _organizationDomain;
    QString _organizationName;
    QString _storageLocation;
    
  };
}
#endif