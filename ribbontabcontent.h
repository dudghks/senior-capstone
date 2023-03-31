/*
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef RIBBONTABCONTENT_H
#define RIBBONTABCONTENT_H

#include <QWidget>
#include <QToolButton>
#include <QFontComboBox>
#include <QSpinBox>

namespace Ui {
class RibbonTabContent;
}

class RibbonTabContent : public QWidget
{
  Q_OBJECT

public:
  explicit RibbonTabContent(QWidget *parent = 0);
  virtual ~RibbonTabContent();

  /// Add a group to the tab content.
  ///
  /// \param[in] groupName Name of the group
  void addGroup(const QString &groupName);

  /// Remove a group from the tab content.
  ///
  /// \param[in] groupName Name of the group
  void removeGroup(const QString &groupName);

  /// Add a small button group to the tab content.
  ///
  /// \param[in] groupName Name of the group
  void addSmallGroup (const QString &groupName);

  /// Remove a small button group from the tab content.
  ///
  /// \param[in] groupName Name of the group
  void removeSmallGroup(const QString &groupName);

  /// Get the number of button groups in this tab content.
  ///
  /// \return The number of button groups
  int groupCount() const;

  /// Add a button to the specified group.
  /// The group is created if it does not exist.
  ///
  /// \param[in] groupName Name of the group
  /// \param[in] button The button
  void addButton(const QString &groupName, QToolButton *button);

  /// Remove a button from the specified group.
  /// The group is also removed if it's empty.
  ///
  /// \param[in] groupName Name of the group
  /// \param[in] button The button
  void removeButton(const QString &groupName, QToolButton *button);

  /// Add a small button to the specified group.
  /// The group is created if it does not exist.
  /// Must be a QToolButton, QFontComboBox, or QSpinBox
  ///
  /// \param[in] groupName Name of the group
  /// \param[in] button The button
  /// \param[in] row The row
  /// \param[in] column The column
  void addSmallButton(const QString &groupName, QToolButton *button, int row, int column);
  void addSmallButton(const QString &groupName, QFontComboBox *button, int row, int column);
  void addSmallButton(const QString &groupName, QSpinBox *button, int row, int column);

  /// Remove a small button from the specified group.
  /// The group is also removed if it's empty.
  /// Must be a QToolButton, QFontComboBox, or QSpinBox
  ///
  /// \param[in] groupName Name of the group
  /// \param[in] button The button
  void removeSmallButton(const QString &groupName, QToolButton *button);
  void removeSmallButton(const QString &groupName, QFontComboBox *button);
  void removeSmallButton(const QString &groupName, QSpinBox *button);

private:
  Ui::RibbonTabContent *ui;
};

#endif // RIBBONTABCONTENT_H
