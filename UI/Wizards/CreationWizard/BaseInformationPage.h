#ifndef INFORMATIONPAGE_H
#define INFORMATIONPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Common.h"
#include "Action.h"

namespace kex
{
  class BaseInformationPage : public QWizardPage
  {
    Q_OBJECT
  public:
    BaseInformationPage(QWidget *parent = 0);
    virtual ~BaseInformationPage() {}
    
    void registerFields();
    
    /** \brief Intializes the page according to which CreationType was chosen.
    * 
    * The initialize() method expects a creationtype to be specified in a 
    * previous page. In order for the wizard to support the type, any special
    * page configurations (removal or addition) must be set in this method.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \sa QWizardPage CreationSelectionPage CreationWizard
    **/
    void initializePage();
    
  protected:
    /** \brief Populates the selection combo box with Action categories
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * 
    * \sa Action::categoryList()
    * 
    **/
    void setCategoryList();
    
    QLabel      nameLabel;
    QLabel      labelLabel;      
    QLabel      descriptionLabel;
    QLabel      selectionLabel;
    
    QLineEdit   nameLineEdit;
    QLineEdit   labelLineEdit;
    
    QTextEdit   descriptionTextEdit;
    QComboBox   selectionComboBox;
    
    QVBoxLayout mainLayout;
    QHBoxLayout nameLayout;
    QHBoxLayout labelLayout;
    QHBoxLayout selectionComboBoxLayout;
    QVBoxLayout descriptionLayout;
  };
}
#endif