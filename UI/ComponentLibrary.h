#ifndef COMPONENTLIBRARY_H
#define COMPONENTLIBRARY_H
#include <QDockWidget>
#include <QSortFilterProxyModel>

#include "Models/ComponentModel.h"
#include "Models/ComponentSortFilterProxyModel.h"
#include "ui_LibraryDockWidget.h"

namespace kex
{
  /** \brief  Displays the specific component library
   *
   * Copyright 2010 KSpace MRI. All Rights Reserved.
   *
   * \author James Kyle
   * \author $LastChangedBy$
   * \date 2010-4-7
   * \date $LastChangedDate$
   * \version $Rev$
   **/
  class ComponentLibrary : public QDockWidget, private Ui::LibraryDockWidget
  {
    Q_OBJECT
  public:
    /** \brief  Constructor for initializing library with a given window title
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-7
     * \date $LastChangedDate$
     * \param title the title text
     * \prarm parent the parent widget
    * \version $Rev$  \sa QDockWidget
    **/
    ComponentLibrary(QWidget *parent = 0);

    /** \brief  Default destructor for the ComponentLibrary
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-7
     * \date $LastChangedDate$
     * \version $Rev$
     **/
    ~ComponentLibrary();

    void setModel(QAbstractItemModel *model, 
                  OutputComponent::ComponentTypes c_type = 
                  OutputComponent::AllComponents);

  };
}
#endif
