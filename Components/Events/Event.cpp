#include "Event.h"

namespace kex
{
  Event::~Event()
  {
    qDeleteAll(_actionList.begin(), _actionList.end());
  }
}