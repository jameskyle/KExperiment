#ifndef UTILITIES_H
#define UTILITIES_H

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QResource>
#include <QVariant>
#include <QXmlSchemaValidator>
#include <QStringList>

#include "Common/Config.h"
#include "Components/ComponentFactory.h"
#include "Components/Component.h"

namespace kex
{
  namespace Utilities
  {
    void setupAppStorageEnvironment();
    void configureApplication();

    /** \brief Writes out the default template files.
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * If one of the default template files is missing, writes out that template
     * file into the user's data directory. If a file by the same name already
     * exists, nothing is done.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-12
     * \date $LastChangedDate$
     * \version $Rev$
     **/
    void writeTemplateFiles();


    /** \brief  Registers the components with the ComponentFactory
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * Each class should be registered with the ComponentFactory. As new classes
     * are created, their factory methods and metadata can be set here. The
     * metadata ensures the application can properly find class related materials
     * such as QResource templates.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-13
     * \date $LastChangedDate$
     * \version $Rev$  \sa ComponentFactory
     **/
    void registerComponents();

    /** \brief Sets any application specific variables.
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * Application specific variables are set here. For example, organization
     * and application names.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-13
     * \date $LastChangedDate$
     * \version $Rev$  \sa Config
     **/
    void configureApplication();

    /** \brief  Validates the provided file using the specified validator.
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * Returns true if file conforms to the validator schema.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-3
     * \date $LastChangedDate$
     * \param file the file to be validated
     * \prarm validator validator used to validate
     * \version $Rev$
     **/
    bool isValidXml(QFile *file, const QXmlSchemaValidator *validator);

    /** \brief  Translates the given fileName string to a valid compnent name.
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * Al underscores in a comoponent name are converted to spaces
     * and the .xml extension is removed. Also, camelcase names are expanded
     * inserting a space before each capital letter.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-4
     * \date $LastChangedDate$
     * \param fileName a string representing the component's template file name
     * \return QString the component name
     * \version $Rev$
     **/
    QString componentNameFromBaseName(const QString& fileName);
    
    QString componentNameFromFilePath(const QString& path);
    
    /** \brief  Deletes all the items in the range [begin, end)  
     *  
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     * 
     * Delets all the items in the range [begin, end] using the C++ delete 
     * operator. The item type must be a pointer type.
     *
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-4
     * \date $LastChangedDate$
     * \param begin an STL forward iterator representing the start point
     * \param end an STL forward iterator representing the stop point
     * \version $Rev$
     **/
    template <class ForwardIterator>
    void deleteAll(ForwardIterator begin, ForwardIterator end)
    {
      while(begin != end) 
      {
        delete *(begin++);
      }
    }

    /** \brief  Deletes all the items in the container
     *  
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     * 
     * Delets all the items in the container. The container must have a begin()
     * and end() method that returns an STL iterator.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-4
     * \date $LastChangedDate$
     * \param list container that provides begin() and end() iterators
     * \version $Rev$
     **/
    template <class Container>
    void deleteAll(Container c)
    {
      deleteAll(c.begin(), c.end());
    }
    
    
    // a find method. For some reason the boost::iterator_facade iterators is
    // throwing a compile error in std::find for the value. When that is 
    // addressed, std::find can be replaced for this method
    template<class ForwardIterator, class ValueType>
    ForwardIterator find(ForwardIterator begin, ForwardIterator end, 
                         ValueType value)
    {
      while (begin != end)
      {
        if ((*begin) == value)
        {
          break;
        }
        ++begin;
      }
      
      return begin;
    }
    
    bool sortComponentQList(const Component::Pointer c1,
                            const Component::Pointer *c2);
  };

}
#endif
