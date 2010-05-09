#include <Components/ComponentInterface.h>

namespace kex
{
  ComponentInterface::ComponentInterface() : d(new ComponentDataPrivate)
  {
    d->ref.ref();
  }

  ComponentInterface::~ComponentInterface()
  {
    if (!d->ref.deref())
    {
      delete d;
    }
  }
    
  ComponentInterface::ComponentInterface(const ComponentInterface &component)
  {
    d = component.d;
    d->ref.ref();
  }
  
  ComponentInterface& 
  ComponentInterface::operator=(const ComponentInterface &component)
  {
    qAtomicAssign(d, component.d);
    return *this;
  }
  
  const QString ComponentInterface::toString() const
  {
    QString output;
    
    output.append("\nObject: %1\n");
    output.append("\tName: %2\n");
    output.append("\tDescription: %3\n");
    output.append("\tLabel: %4\n");
    output.append("\tMainCategory: %5\n");
    
    return output.arg(typeid(this).name(), name(), description(), label(), 
                      mainCategory());
  }

  void ComponentInterface::detach()
  {
    // we only perform the operation for references greater than one.
    if (d->ref != 1)
    {
      ComponentDataPrivate *x = new ComponentDataPrivate(
                                    *static_cast<ComponentDataPrivate *>(d));
      if (!d->ref.deref())
      {
        delete d;
      }
      
      x->ref = 1;
      d = x;
    }
  }
  
  const QString ComponentInterface::name() const 
  {
    return d->name;
  }
  
  const QString ComponentInterface::description() const 
  {
    return d->description;
  }

  const QString ComponentInterface::label() const 
  {
    return d->label;
  }
  
  const QString ComponentInterface::mainCategory() const 
  {
    return d->mainCategory;
  }

  void ComponentInterface::setMainCategory(const QString& cat) 
  {
    if (d->mainCategory != cat)
    {
      detach();
      d->mainCategory = cat;
    }
  }
  
  void ComponentInterface::setName(const QString& name) 
  {
    if (d->name != name)
    {
      detach();
      d->name = name;
    }
  }
  
  void ComponentInterface::setDescription(const QString& desc)
  {
    if (d->description != desc)
    {
      detach();
      d->description = desc;
    }
  }

  void ComponentInterface::setLabel(const QString& label)
  {
    if (d->label != label)
    {
      detach();
      d->label = label;
    }
  }

  void ComponentInterface::addCategory(const QString& category) 
  {
    // this function is not copy on write.
    if (!d->categoryList.contains(category))
    {
      d->categoryList << category;
    }
  }

  void ComponentInterface::removeCategory(const QString& category) 
  {
    // this function is not copy on write
    d->categoryList.removeAll(category);
  }
  
  const quint32 ComponentInterface::durationMSecs() const
  {
    return d->durationMSecs;
  }
}