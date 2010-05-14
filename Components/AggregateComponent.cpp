#include "AggregateComponent.h"

namespace kex
{
  AggregateComponent::~AggregateComponent()
  {
    qDeleteAll(_componentList.begin(), _componentList.end());
  }
}
