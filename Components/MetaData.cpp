#include "MetaData.h"

namespace kex
{
  MetaData::MetaData()
  {
    _categoryList << "Motor" << "Language" << "Memory";
    _tagList << "Block" << "Event" << _categoryList;
  }
  
  MetaData&  MetaData::instance()
  {
    static MetaData _instance;
    return _instance;
  }
  
  void MetaData::addCategory(QString& category)
  {
    if(!_categoryList.contains(category))
    {
      _categoryList << category;
    }
  }

  void MetaData::addTag(QString& tag)
  {
    if(!_tagList.contains(tag))
    {
      _tagList << tag;
    }
  }

  void MetaData::removeTag(QString& tag)
  {
    _tagList.removeAll(tag);
  }

  void MetaData::removeCategory(QString& category)
  {
    _categoryList.removeAll(category);
  }
  
  void MetaData::addCategories(QList<QString>& categories)
  {
    _categoryList.append(categories);
  }
}
