#include "BaseInformationPage.h"

namespace kex
{
  /**
   * TODO
   */
  BaseInformationPage::BaseInformationPage(QWidget *parent)
    : QWizardPage(parent),
      _nameLabel(tr("&Name:"), this),
      _labelLabel(tr("&Label:"), this),
      _descriptionLabel(tr("&Description:"), this),
      _nameLineEdit(this),
      _labelLineEdit(this),
      _descriptionTextEdit(this)

  {
    setObjectName("BaseInformationPage");
    setLayout(&_mainLayout);
    _nameLabel.setObjectName("nameLabel");
    _nameLineEdit.setObjectName("nameLineEdit");
    _nameLabel.setBuddy(&_nameLineEdit);
    _nameLayout.addWidget(&_nameLabel);
    _nameLayout.addWidget(&_nameLineEdit);
    _mainLayout.addLayout(&_nameLayout);

    _labelLabel.setObjectName("labelLabel");
    _labelLineEdit.setObjectName("labelLineEdit");
    _labelLabel.setBuddy(&_labelLineEdit);
    _labelLayout.addWidget(&_labelLabel);
    _labelLayout.addWidget(&_labelLineEdit);
    _mainLayout.addLayout(&_labelLayout);

    _descriptionLabel.setObjectName("descriptionLabel");
    _descriptionTextEdit.setObjectName("descriptionTextEdit");
    _descriptionLabel.setBuddy(&_descriptionTextEdit);
    _descriptionLayout.addWidget(&_descriptionLabel);
    _descriptionLayout.addWidget(&_descriptionTextEdit);
    _mainLayout.addLayout(&_descriptionLayout);

    // register fields
    registerField("name*", &_nameLineEdit);
    registerField("label*", &_labelLineEdit);
    registerField("description", &_descriptionTextEdit);
  }

}
