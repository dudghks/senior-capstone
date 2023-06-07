/*
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#include "ribbontabcontent.h"
#include "ui_ribbontabcontent.h"
#include "ribbonbuttongroup.h"
#include "ribbonsmallbuttonsgroup.h"

RibbonTabContent::RibbonTabContent(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::RibbonTabContent)
{
  ui->setupUi(this);
}

RibbonTabContent::~RibbonTabContent()
{
  delete ui;
}


void RibbonTabContent::addGroup(const QString &groupName)
{
  RibbonButtonGroup *ribbonButtonGroup = new RibbonButtonGroup;
  ribbonButtonGroup->setTitle(groupName);

  ui->ribbonHorizontalLayout->addWidget(ribbonButtonGroup);
}

void RibbonTabContent::removeGroup(const QString &groupName)
{
  // Find ribbon group
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonButtonGroup *group = static_cast<RibbonButtonGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ui->ribbonHorizontalLayout->removeWidget(group); /// \todo :( No effect
      delete group;
      break;
    }
  }

  /// \todo  What if the group still contains buttons? Delete manually?
  // Or automaticly deleted by Qt parent() system.
}

void RibbonTabContent::addSmallGroup (const QString &groupName)
{
    RibbonSmallButtonsGroup *ribbonSmallButtonsGroup = new RibbonSmallButtonsGroup;
    ribbonSmallButtonsGroup->setTitle(groupName);

    ui->ribbonHorizontalLayout->addWidget(ribbonSmallButtonsGroup);
}

void RibbonTabContent::removeSmallGroup(const QString &groupName)
{
  // Find ribbon group
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonSmallButtonsGroup *group = static_cast<RibbonSmallButtonsGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ui->ribbonHorizontalLayout->removeWidget(group); /// \todo :( No effect
      delete group;
      break;
    }
  }

  /// \todo  What if the group still contains buttons? Delete manually?
  // Or automaticly deleted by Qt parent() system.
}

int RibbonTabContent::groupCount() const
{
  return ui->ribbonHorizontalLayout->count();
}

void RibbonTabContent::addButton(const QString &groupName, QToolButton *button)
{
  // Find ribbon group
  RibbonButtonGroup *ribbonButtonGroup = nullptr;
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonButtonGroup *group = static_cast<RibbonButtonGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ribbonButtonGroup = group;
      break;
    }
  }

  if (ribbonButtonGroup != nullptr)
  {
    // Group found
    // Add ribbon button
    ribbonButtonGroup->addButton(button);
  }
  else
  {
    // Group not found
    // Add ribbon group
    addGroup(groupName);

    // Add ribbon button
    addButton(groupName, button);
  }
}

void RibbonTabContent::removeButton(const QString &groupName, QToolButton *button)
{
  // Find ribbon group
  RibbonButtonGroup *ribbonButtonGroup = nullptr;
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonButtonGroup *group = static_cast<RibbonButtonGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ribbonButtonGroup = group;
      break;
    }
  }

  if (ribbonButtonGroup != nullptr)
  {
    // Group found
    // Remove ribbon button
    ribbonButtonGroup->removeButton(button);

    if (ribbonButtonGroup->buttonCount() == 0)
    {
      // Empty button group
      // Remove button group
      removeGroup(groupName);
    }
  }
}

void RibbonTabContent::addSmallButton(const QString &groupName, QToolButton *button, int row, int column)
{
  // Find ribbon group
  RibbonSmallButtonsGroup *ribbonSmallButtonsGroup = nullptr;
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonSmallButtonsGroup *group = static_cast<RibbonSmallButtonsGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ribbonSmallButtonsGroup = group;
      break;
    }
  }

  if (ribbonSmallButtonsGroup != nullptr)
  {
    // Group found
    // Add ribbon button
    ribbonSmallButtonsGroup->addButton(button, row, column);
  }
  else
  {
    // Group not found
    // Add ribbon group
    addSmallGroup(groupName);

    // Add ribbon button
    addSmallButton(groupName, button, row, column);
  }
}

void RibbonTabContent::addSmallButton(const QString &groupName, QFontComboBox *button, int row, int column)
{
  // Find ribbon group
  RibbonSmallButtonsGroup *ribbonSmallButtonsGroup = nullptr;
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonSmallButtonsGroup *group = static_cast<RibbonSmallButtonsGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ribbonSmallButtonsGroup = group;
      break;
    }
  }

  if (ribbonSmallButtonsGroup != nullptr)
  {
    // Group found
    // Add ribbon button
    ribbonSmallButtonsGroup->addButton(button, row, column);
  }
  else
  {
    // Group not found
    // Add ribbon group
    addSmallGroup(groupName);

    // Add ribbon button
    addSmallButton(groupName, button, row, column);
  }
}

void RibbonTabContent::addSmallButton(const QString &groupName, QComboBox *button, int row, int column)
{
  // Find ribbon group
  RibbonSmallButtonsGroup *ribbonSmallButtonsGroup = nullptr;
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonSmallButtonsGroup *group = static_cast<RibbonSmallButtonsGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ribbonSmallButtonsGroup = group;
      break;
    }
  }

  if (ribbonSmallButtonsGroup != nullptr)
  {
    // Group found
    // Add ribbon button
    ribbonSmallButtonsGroup->addButton(button, row, column);
  }
  else
  {
    // Group not found
    // Add ribbon group
    addSmallGroup(groupName);

    // Add ribbon button
    addSmallButton(groupName, button, row, column);
  }
}

void RibbonTabContent::removeSmallButton(const QString &groupName, QToolButton *button)
{
  // Find ribbon group
  RibbonSmallButtonsGroup *ribbonSmallButtonsGroup = nullptr;
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonSmallButtonsGroup *group = static_cast<RibbonSmallButtonsGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ribbonSmallButtonsGroup = group;
      break;
    }
  }

  if (ribbonSmallButtonsGroup != nullptr)
  {
    // Group found
    // Remove ribbon button
    ribbonSmallButtonsGroup->removeButton(button);

    if (ribbonSmallButtonsGroup->buttonCount() == 0)
    {
      // Empty button group
      // Remove button group
      removeGroup(groupName);
    }
  }
}

void RibbonTabContent::removeSmallButton(const QString &groupName, QFontComboBox *button)
{
  // Find ribbon group
  RibbonSmallButtonsGroup *ribbonSmallButtonsGroup = nullptr;
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonSmallButtonsGroup *group = static_cast<RibbonSmallButtonsGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ribbonSmallButtonsGroup = group;
      break;
    }
  }

  if (ribbonSmallButtonsGroup != nullptr)
  {
    // Group found
    // Remove ribbon button
    ribbonSmallButtonsGroup->removeButton(button);

    if (ribbonSmallButtonsGroup->buttonCount() == 0)
    {
      // Empty button group
      // Remove button group
      removeGroup(groupName);
    }
  }
}

void RibbonTabContent::removeSmallButton(const QString &groupName, QComboBox *button)
{
  // Find ribbon group
  RibbonSmallButtonsGroup *ribbonSmallButtonsGroup = nullptr;
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonSmallButtonsGroup *group = static_cast<RibbonSmallButtonsGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ribbonSmallButtonsGroup = group;
      break;
    }
  }

  if (ribbonSmallButtonsGroup != nullptr)
  {
    // Group found
    // Remove ribbon button
    ribbonSmallButtonsGroup->removeButton(button);

    if (ribbonSmallButtonsGroup->buttonCount() == 0)
    {
      // Empty button group
      // Remove button group
      removeGroup(groupName);
    }
  }
}
