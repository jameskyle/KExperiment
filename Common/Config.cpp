#include "Config.h"

namespace kex
{
  /**
   * TODO
   */
  Config::Config()
    : _organizationDomain("kspace-mri.com"),
      _organizationName("KSpace MRI"),
      _storageLocation(
        QDesktopServices::storageLocation(QDesktopServices::DataLocation))
  {
    
  }
  
  /**
   * TODO
   */
  Config& Config::instance()
  {
    static Config _instance;
    return _instance;
  }
}