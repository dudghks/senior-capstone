#include "ribbonsmallbuttonsgroup.h"
#include "ui_ribbonsmallbuttonsgroup.h"

#include <QToolButton>

RibbonSmallButtonsGroup::RibbonSmallButtonsGroup(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::RibbonSmallButtonsGroup)
  , m_title("")
{
  ui->setupUi(this);
}

RibbonSmallButtonsGroup::~RibbonSmallButtonsGroup()
{
  delete ui;
}

void RibbonSmallButtonsGroup::setTitle(const QString &title)
{
  m_title = title;
}

QString RibbonSmallButtonsGroup::title() const
{
  return m_title;
}

int RibbonSmallButtonsGroup::buttonCount() const
{
  return ui->topHorizontalLayout->count() + ui->bottomHorizontalLayout->count();
}

void RibbonSmallButtonsGroup::addButton(QToolButton *button, int pos)
{
  button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  button->setMinimumSize(58, 58);
  button->setAutoRaise(true);
  button->setIconSize(QSize(40,40));
  button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  if(pos == 0) {
      ui->topHorizontalLayout->addWidget(button);
  }
  else if(pos == 1) {
      ui->bottomHorizontalLayout->addWidget(button);
  }
}

void RibbonSmallButtonsGroup::addButton(QFontComboBox *button, int pos)
{
  /// \todo add default stuff for this
  button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  button->setMinimumSize(58, 58);
  if(pos == 0) {
      ui->topHorizontalLayout->addWidget(button);
  }
  else if(pos == 1) {
      ui->bottomHorizontalLayout->addWidget(button);
  }
}

void RibbonSmallButtonsGroup::addButton(QSpinBox *button, int pos)
{
  /// \todo add default stuff for this
  button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  button->setMinimumSize(58, 58);
  if(pos == 0) {
      ui->topHorizontalLayout->addWidget(button);
  }
  else if(pos == 1) {
      ui->bottomHorizontalLayout->addWidget(button);
  }
}

void RibbonSmallButtonsGroup::removeButton(QToolButton *button, int pos)
{
  /// \todo What happens if button is not part of the layout?
    if(pos == 0) {
        ui->topHorizontalLayout->removeWidget(button);
    }
    else if(pos == 1) {
        ui->bottomHorizontalLayout->removeWidget(button);
    }
}
