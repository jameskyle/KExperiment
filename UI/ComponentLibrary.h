#ifndef COMPONENTLIBRARY_H
#define COMPONENTLIBRARY_H
#include <QDockWidget>
#include <QSortFilterProxyModel>
#include <QAction>

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

    void setModel(ComponentModel *model);
    
    QAction* toggleActionAction() {return m_toggleActionAction;}
    QAction* toggleEventAction() {return m_toggleEventAction;}
    QAction* toggleTrialAction() {return m_toggleTrialAction;}
    QAction* toggleExperimentAction() {return m_toggleExperimentAction;}
    QAction* toggleAllComponentsAction() {return m_toggleAllComponentsAction;}
    
    QAbstractItemModel* model(){return componentListView->model();}

  private:
    void toggleComponentFilter(bool checked, OutputComponent::ComponentTypes t);
    
    QAction* m_toggleActionAction;
    QAction* m_toggleEventAction;
    QAction* m_toggleTrialAction;
    QAction* m_toggleExperimentAction;
    QAction* m_toggleAllComponentsAction;
    
  public slots:
    void toggleActions(bool checked);
    void toggleEvents(bool checked);
    void toggleTrials(bool checked);
    void toggleExperiments(bool checked);
    void udpateAllComponentsAction();
    
  signals:
    void selectedIndexChanged(const QModelIndex&);
    
  };
}
#endif
