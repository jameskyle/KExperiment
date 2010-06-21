#ifndef BASEINFORMATIONPAGE_H
#define BASEINFORMATIONPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Components/Actions/Action.h"

namespace kex
{
  class BaseInformationPage : public QWizardPage
  {
    Q_OBJECT
  public:
    BaseInformationPage(QWidget *parent = 0);
    virtual ~BaseInformationPage() {}

  protected:

    QLabel      _nameLabel;
    QLabel      _labelLabel;
    QLabel      _descriptionLabel;

    QLineEdit   _nameLineEdit;
    QLineEdit   _labelLineEdit;

    QTextEdit   _descriptionTextEdit;

    QVBoxLayout _mainLayout;
    QHBoxLayout _nameLayout;
    QHBoxLayout _labelLayout;
    QVBoxLayout _descriptionLayout;
  };
}
#endif
