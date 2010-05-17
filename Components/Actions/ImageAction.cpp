#include "ImageAction.h"

namespace kex
{
  /**
   * TODO
   */
  ImageAction::ImageAction(QObject *parent) : Action(parent)
  {
  }

  /**
   * TODO
   */
  ImageAction::~ImageAction()
  {
    
  }

  /**
   * TODO
   */
  void ImageAction::begin()
  {
    
  }
  
  /*
  * TODO
  */
  void ImageAction::abort()
  {
    
  }
  
  bool ImageAction::setFile(const QString& filePath)
  {
    bool success(true);
    _imageFile.setFileName(filePath);
    
    if (!_imageFile.exists())
    {
      success = false;
    }
    
    return success;
  }

}