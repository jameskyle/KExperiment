#include "BaseInformationPage.h"

namespace kex
{
  /**
   * TODO
   */
  BaseInformationPage::BaseInformationPage(QWidget *parent)
    : QWizardPage(parent), 
      nameLabel(tr("&Name:"), this),
      labelLabel(tr("&Label:"), this), 
      descriptionLabel(tr("&Description:"), this),
      selectionLabel(tr("&Selection"), this),
      nameLineEdit(this),
      labelLineEdit(this),
      descriptionTextEdit(this),
      selectionComboBox(this)
      
  {
    setObjectName("BaseInformationPage");
    setLayout(&mainLayout);
    nameLabel.setObjectName("nameLabel");
    nameLineEdit.setObjectName("nameLineEdit");
    nameLabel.setBuddy(&nameLineEdit);
    nameLayout.addWidget(&nameLabel);
    nameLayout.addWidget(&nameLineEdit);
    mainLayout.addLayout(&nameLayout);
    
    labelLabel.setObjectName("labelLabel");
    labelLineEdit.setObjectName("labelLineEdit");
    labelLabel.setBuddy(&labelLineEdit);
    labelLayout.addWidget(&labelLabel);
    labelLayout.addWidget(&labelLineEdit);
    mainLayout.addLayout(&labelLayout);
    
    selectionLabel.setObjectName("selectionLabel");
    selectionComboBox.setObjectName("selectionComboBox");
    selectionLabel.setBuddy(&selectionComboBox);
    selectionComboBoxLayout.addWidget(&selectionLabel);
    selectionComboBoxLayout.addWidget(&selectionComboBox);
    mainLayout.addLayout(&selectionComboBoxLayout);
    
    descriptionLabel.setObjectName("descriptionLabel");
    descriptionTextEdit.setObjectName("descriptionTextEdit");
    descriptionLabel.setBuddy(&descriptionTextEdit);
    descriptionLayout.addWidget(&descriptionLabel);
    descriptionLayout.addWidget(&descriptionTextEdit);
    mainLayout.addLayout(&descriptionLayout);
    
    // register fields
    registerField("name*", &nameLineEdit);
    registerField("selection*", &selectionComboBox);
    registerField("label*", &labelLineEdit);
    registerField("description", &descriptionTextEdit);
  }
    
  void BaseInformationPage::initializePage()
  {
    // first clear the combo box in case
    selectionComboBox.clear();
    if(field("Action").toBool())
    {


    } else if(field("EventCreationType").toBool()) {
      setTitle(tr("Event Information"));
      setSubTitle(tr("Please provide the following details about your new "
        "Event"));
      
      setCategoryList();      
      
    } else if(field("TrialCreationType").toBool()) {
      setTitle(tr("Trial Information"));
      setSubTitle(tr("Please provide the following details about your new "
        "Trial."));

      setCategoryList();      

    } else if(field("ExperimentCreationType").toBool()) {
      setTitle(tr("Experiment Information"));
      setSubTitle(tr("Please provide the following details about your new "
        "Experiment"));

      setCategoryList();      

    }
     else {
      setTitle(tr("Welcome to the K_ Creation Wizard!"));
      setSubTitle(tr("This Wizard allows you to quickly and easily create "
        "K_ Objects"));
    }
  }
  
  void BaseInformationPage::setCategoryList()
  {
    selectionLabel.setText(tr("&Primary Category"));
    selectionLabel.setObjectName("primaryCategoryLabel");
    selectionComboBox.addItem("Choose...");
    selectionComboBox.addItems(
      kex::MetaData::instance().categoryList());
    
    // set tooltips
    QString tip = tr(
    "You may select an existing Catetory or you may enter a new category "
    "\nIf a new category is entered, it will be available for future\n "
    "selection");
    selectionComboBox.setToolTip(tip);
    selectionLabel.setToolTip(tip);
  }
}