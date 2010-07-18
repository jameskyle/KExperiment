#ifndef LOGGER_H
#define LOGGER_H
#include <QDebug>
#include <QWidget>
#include <QMessageBox>

#include "Common/Uncopyable.h"
namespace kex
{  
  /** \brief  Handles logging for the application
   * 
   * Copyright 2010 KSpace MRI. All Rights Reserved.
   *
   * \author James Kyle
   * \author $LastChangedBy$
   * \date 2010-4-15
   * \date $LastChangedDate$
   * \version $Rev$ 
   **/
  class Logger : private Uncopyable
  {
  public:
    enum LogLevelType   {
      DebugLogLevel      = 0x1,
      WarningLogLevel    = 0x2,
      CriticalLogLevel  = 0x4,
      FatalLogLevel      = 0x8,
    };
    /** \brief  Returns an instance of the Logger class
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-15
     * \date $LastChangedDate$
     * \version $Rev$
     **/
    static Logger& instance();
    
    /** \brief  Logs the provided message for the declared log level.
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-15
     * \date $LastChangedDate$
     * \param msg message to be logged
     * \prarm obj a pointer to the object requesting a log
     * \param level the desired log level [defaut] Debug
     * \version $Rev$  \sa LogLevelType
     **/
    void log(const char* msg, const QObject *obj = 0, 
             LogLevelType level = DebugLogLevel);
    
    /** \brief  Logs the provided message for the declared log level
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-2
     * \date $LastChangedDate$
     * \prarm msg message to be logged
     * \param obj pointer to the object requesting a log
     * \param level the desired log level [defaut] Debug
     * \version $Rev$
     **/
    void log(const QString& msg, const QObject *obj = 0, 
                     Logger::LogLevelType level = DebugLogLevel);
    
  private:
    /** \brief  Default constructor
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     * 
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-15
     * \date $LastChangedDate$
     * \version $Rev$
     **/
    Logger() {}
    
    /** \brief  Default destructor.
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     * 
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-15
     * \date $LastChangedDate$
     * \version $Rev$
     **/
    ~Logger() {}
    
  public slots:
    /** \brief  Displays the given message and info to the user
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     * 
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-15
     * \date $LastChangedDate$
     * \param test the text of the QMessageBox
     * \prarm info The information portionof the QMessageBox
     * \version $Rev$  \sa QMessageBox
     **/
    void displayMessage(const QString& text, 
                        const QString& info = "",
                        QMessageBox::StandardButton button = 
                        QMessageBox::Ok, 
                        Logger::LogLevelType level = DebugLogLevel) const;
  };
}
#endif