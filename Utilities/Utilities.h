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

#include <Common/Global.h>
#include <Components/ComponentRegister.h>

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


    /** \brief  Registers the comonents with the ComponentRegister
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * Each class should be registered with the ComponentRegister. As new classes
     * are created, their factory methods and metadata can be set here. The
     * metadata ensures the application can properly find class related materials
     * such as QResource templates.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-13
     * \date $LastChangedDate$
     * \version $Rev$  \sa ComponentRegister
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


   };

}
#endif
