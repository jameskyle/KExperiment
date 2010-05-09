#include "VideoAction.h"

namespace kex
{
  /**
   * TODO
   */
  VideoAction::VideoAction(QObject *parent) : OutputComponent(parent), Action()
  {
  }

  /**
   * TODO rewrite this for proper media file handling
   */
  bool VideoAction::setFile(const QString& filePath)
  {
    bool success(true);
    _videoFile.setFileName(filePath);
    
    if (!_videoFile.exists())
    {
      success = false;
    }
    
    return success;
  }
  
  /**
   * TODO
   */
  VideoAction::~VideoAction()
  {
    
  }

  /**
   * TODO
   */
  void VideoAction::begin()
  {
    
  }
  
  /*
  * TODO
  */
  void VideoAction::abort()
  {
    
  }
}