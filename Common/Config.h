#ifndef GLOBAL_H
#define GLOBAL_H
#include <vector>

#include <QString>
#include <QMultiMap>
#include <QDesktopServices>
#include <QMessageBox>
#include <QVariant>
#include <QDir>

#include "Components/Components.h"
#include "Common/Uncopyable.h"

#include "Common/Logger.h"

namespace kex
{
    /** \brief  Holds common configuration valus for application
   *
   * Copyright 2010 KSpace MRI. All Rights Reserved.
   *
   * \author James Kyle
   * \author $LastChangedBy$
   * \date 2010-4-8
   * \date $LastChangedDate$
   * \version $Rev$  \sa Types.h Config.h
   **/
  class Config : private Uncopyable
  {
    Q_FLAGS(ApplicationDataDirectoryType ApplicationDataDirectoryTypes)
  public:
    static Config& instance();


    enum MetaDataType {
      TemplateResourcePaths      = 0x1,
      CustomDirectoryPath        = 0x1 << 1,
    };

    enum ApplicationDataDirectoryType {
      LogDirectory                = 0x1,
      ActionDirectory             = 0x1 << 1,
      ExperimentDirectory         = 0x1 << 2,
      EventDirectory              = 0x1 << 3,
      TrialDirectory              = 0x1 << 4,
      AllDataDirectories          = (LogDirectory | ActionDirectory |
                                     ExperimentDirectory | EventDirectory |
                                     TrialDirectory),
    };
    Q_DECLARE_FLAGS(ApplicationDataDirectoryTypes, ApplicationDataDirectoryType)

    /** \brief  Returns the storage location path for this application
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-10
     * \date $LastChangedDate$
     * \param directoryType the type of directory
     * \return QString holds the path tot he directory
     * \version $Rev$  \sa Component::DataDirectoryType
     **/
    const QString
    dataDirectoryPath(const ApplicationDataDirectoryTypes directoryType) const;

    /** \brief  Returns a list of all data directories
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * The application uses several data directories for holding templates,
     * user defined components, and cache data. This method returns a list of all
     * these directories.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-10
     * \date $LastChangedDate$
     * \version $Rev$
     * \sa Component::DataDirectoryType
     * \sa Utilities::setupAppStorageEnvironment
     **/
    const QStringList dataDirectoryList(ApplicationDataDirectoryTypes dt) const;

    /** \brief  Registers metadata associated with the requested class.
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * Each class has an associated set of metadata such as the lcoation of its
     * xml template file. This registers that metadata and allows lookups based
     * on the registered classes identifier.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-13
     * \date $LastChangedDate$
     * \param classid id of the class to set the metadata for
     * \prarm metadata a map of metadata values for this class
     * \return bool true if the class is found in the register list, false if not
     * \version $Rev$  \sa ComonentRegister()
     **/
//    bool registerComponentMetaData(const QString& classid,
//                                   QMap<Config::MetaDataType,
//                                   QVariant> metadata);

    /** \brief  Returns the metadata for a class
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * Each registered class has a metadtat type that stores class specific
     * application data.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-15
     * \date $LastChangedDate$
     * \param key a string specifying the registered class
     * \version $Rev$
     **/
   // const QMap<Config::MetaDataType, QVariant> metaData(QString& key) const;

    const QString organizationName() const {return m_organizationName;}
    const QString domainName() const {return m_domainName;}
    const QString applicationName() const {return m_applicationName;}
    const QString storageLocation() const {return m_storageLocation;}
    const QString componentSchemaFile() const { return m_componentSchemaFile;}
    const QStringList templates(ApplicationDataDirectoryTypes t) const;
    void addTemplate(ApplicationDataDirectoryTypes storagePath, QString temp);
    /** \brief  Returns a list of paths to the component xml definition files
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-3
     * \date $LastChangedDate$
     * \version $Rev$  \sa validateXml()
     **/
    QStringList xmlFileComponentList(kex::Config::ApplicationDataDirectoryTypes t =
                                     kex::Config::ApplicationDataDirectoryTypes(
                                     kex::Config::ActionDirectory |
                                     kex::Config::EventDirectory |
                                     kex::Config::TrialDirectory |
                                     kex::Config::ExperimentDirectory));

  private:
    QString m_organizationName;
    QString m_domainName;
    QString m_applicationName;
    QString m_storageLocation;
    QList<ApplicationDataDirectoryTypes> m_dataDirectoryList;
    QMultiMap<ApplicationDataDirectoryTypes, QString> m_templates;
    QString m_componentSchemaFile;

    //!< map of class's application metadata
    //QMap<QString, QMap<MetaDataType, QVariant> > _componentMetaDataMap;

    // map between an ApplicationDataDirectoryTypes and its name
    QMap<ApplicationDataDirectoryTypes, QString> m_directoryTypeList;

    Config();
    ~Config() {}
  };
  // FIXME http://tinyurl.com/2ga3sdx
  //Q_DECLARE_OPERATORS_FOR_FLAGS(Config::ApplicationDataDirectoryTypes)
};

#endif
