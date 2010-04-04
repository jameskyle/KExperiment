#ifndef METADATA_H
#define METADATA_H
#include <QStringList>

namespace kex
{
  /** \brief  Lists of available metadata for components
  * 
  * Various lists of metadata that can be applied to components for sorting
  * and filtering.
  * 
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-02
  * \date $LastChangedDate$
  * \version $Rev$  \sa
  **/
  
  class MetaData
  {
  public:
    /** \brief Returns a reference to the MetaData object.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \sa ~MetaData()
    **/
    static MetaData&  instance();
    
    /** \brief Returns a reference to the category list.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \return QStringList list of available categories
    **/
    const QStringList& categoryList() {return _categoryList;}
    
    /** \brief Returns a reference to the tag list.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \return QStringList list of available tags.
    * \sa
    **/
    const QStringList& tagList() {return _tagList;}
    
    /** \brief Adds the category to the category list
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \param  category name of the new category to be added
    * \sa removeCategory addTag removeTag
    **/
    void addCategory(QString& category);
    
    /** \brief Adds the tag to the tag list
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \param  tag name of tag to be added
    * \sa removeTag addCategory removeCategory
    **/
    void addTag(QString& tag);
    
    /** \brief Removes the tag from the tag list.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \param  tag name of tag to be removed
    * \sa addTag removeCategory addCategory
    **/
    void removeTag(QString& tag);
    
    /** \brief Removes the category from the category list
     * 
     * \author James Kyle KSpace MRI
     * \date 2010-04-02
     * \param  description of parameter
     * \param  category category name to be removed
     * \sa addCategory addTag removeCategory removeTag
     **/
    void removeCategory(QString& category);
    
    /** \brief Adds a list of new categories.
    * 
    * Once a category is added, it is available in selection menus and as
    * a sort item for all actions and events. New categories must be 
    * added before they can be used.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param  categories a QList of QStrings holding a list of new categories
    * 
    **/
    void addCategories(QList<QString>& categories);

  private:
    /** \brief Contructor for the MetaData class
    * 
    * Instantiates a set of default metadata values.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \sa ~MetaData()
    **/
    MetaData ();
    
    /** \brief Destructor for the MetaData class
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \sa MetaData()
    **/
    ~MetaData () {}
    
    QStringList _categoryList;
    QStringList _tagList;
  };
}
#endif