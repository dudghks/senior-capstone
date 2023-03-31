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
  ui->label->setText(m_title);
}

QString RibbonSmallButtonsGroup::title() const
{
  return m_title;
}

int RibbonSmallButtonsGroup::buttonCount() const
{
  return ui->groupGridLayout->count();
}

void RibbonSmallButtonsGroup::addButton(QToolButton *button, int row, int column)
{
  button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  button->setMinimumSize(28, 28);
  button->setAutoRaise(true);
  button->setIconSize(QSize(27,27));
  ui->groupGridLayout->addWidget(button, row, column);
}

void RibbonSmallButtonsGroup::addButton(QFontComboBox *button, int row, int column)
{
  /// \todo add default stuff for this
  button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  button->setMinimumSize(118, 24);
  button->setMaximumSize(153, 28);
  ui->groupGridLayout->addWidget(button, row, column, 1, 4);
}

void RibbonSmallButtonsGroup::addButton(QSpinBox *button, int row, int column)
{
  /// \todo add default stuff for this
  button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
  button->setMinimumSize(28, 24);
  button->setMaximumSize(41, 28);
  ui->groupGridLayout->addWidget(button, row, column);
}

void RibbonSmallButtonsGroup::removeButton(QToolButton *button)
{
  /// \todo What happens if button is not part of the layout?
  ui->groupGridLayout->removeWidget(button);
}

void RibbonSmallButtonsGroup::removeButton(QFontComboBox *button)
{
  /// \todo What happens if button is not part of the layout?
  ui->groupGridLayout->removeWidget(button);

}

void RibbonSmallButtonsGroup::removeButton(QSpinBox *button)
{
  /// \todo What happens if button is not part of the layout?
  ui->groupGridLayout->removeWidget(button);
}
