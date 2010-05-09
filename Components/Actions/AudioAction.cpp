#include "AudioAction.h"

namespace kex
{
  /**
   * TODO
   */
  AudioAction::AudioAction(QObject *parent) : OutputComponent(parent), Action()
  {
  }
  
  /**
   * TODO rewrite this for proper media file handling
   */
  bool AudioAction::setFile(const QString& filePath)
  {
    bool success(true);
    _audioFile.setFileName(filePath);
    
    if (!_audioFile.exists())
    {
      success = false;
    }
    
    return success;
  }
  

  /**
   * TODO
   */
  AudioAction::~AudioAction()
  {
    
  }

  /**
   * TODO
   */
  void AudioAction::begin()
  {
    
  }
  
  /*
  * TODO
  */
  void AudioAction::abort()
  {
    
  }
}