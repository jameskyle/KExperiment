#include "Event.h"

namespace kex
{
  Event::~Event()
  {
    while(!_actionList.isEmpty()) {
      delete _actionList.takeFirst();
    }
  }
}