/*
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef RIBBONTABWIDGET_H
#define RIBBONTABWIDGET_H

#include <QTabWidget>
#include <QToolButton>
#include <QFontComboBox>
#include <QSpinBox>

class Ribbon : public QTabWidget
{
  Q_OBJECT
public:
  explicit Ribbon(QWidget *parent = 0);

  /// Add a tab to the ribbon.
  ///
  /// \param[in] tabName Name of the tab
  void addTab(const QString &tabName);

  /// Add a tab to the ribbon.
  ///
  /// \param[in] tabIcon Icon of the tab
  /// \param[in] tabName Name of the tab
  void addTab(const QIcon &tabIcon, const QString &tabName);

  /// Remove a tab from the ribbon.
  ///
  /// \param[in] tabName Name of the tab
  void removeTab(const QString &tabName);

  /// Add a group to the specified tab.
  /// The specified tab is created if it does not exist.
  ///
  /// \param[in] tabName Name of the tab
  /// \param[in] groupName Name of the group
  void addGroup(const QString &tabName, const QString &groupName);

  /// Add a small button group to the specified tab.
  /// The specified tab is created if it does not exist.
  ///
  /// \param[in] tabName Name of the tab
  /// \param[in] groupName Name of the group
  void addSmallGroup(const QString &tabName, const QString &groupName);

  /// Add a button to the specified group.
  /// The specified group and tab are created if they do not exist.
  ///
  /// \param[in] tabName Name of the tab
  /// \param[in] groupName Name of the group
  /// \param[in] button The button
  void addButton(const QString &tabName, const QString &groupName, QToolButton *button);

  /// Remove a button from the specified group.
  /// Do nothing if the button, group or tab doesn't exist.
  /// The button group and tab are also removed if they become empty due to
  /// the removal of the button.
  ///
  /// \param[in] tabName Name of the tab
  /// \param[in] groupName Name of the group
  /// \param[in] button The button
  void removeButton(const QString &tabName, const QString &groupName, QToolButton *button);

  /// Add a small button to the specified small button group.
  /// The specified group and tab are created if they do not exist.
  /// Must be a QToolButton, QFontComboBox, or QSpinBox
  ///
  /// \param[in] tabName Name of the tab
  /// \param[in] groupName Name of the group
  /// \param[in] button The button
  /// \param[in] row The row
  /// \param[in] column The column
  void addSmallButton(const QString &tabName, const QString &groupName, QToolButton *button, int row, int column);
  void addSmallButton(const QString &tabName, const QString &groupName, QFontComboBox *button, int row, int column);
  void addSmallButton(const QString &tabName, const QString &groupName, QSpinBox *button, int row, int column);

  /// Remove a small button from the specified small button group.
  /// Do nothing if the button, group or tab doesn't exist.
  /// The button group and tab are also removed if they become empty due to
  /// the removal of the button.
  /// Must be a QToolButton, QFontComboBox, or QSpinBox
  ///
  /// \param[in] tabName Name of the tab
  /// \param[in] groupName Name of the group
  void removeSmallButton(const QString &tabName, const QString &groupName, QToolButton *button);
  void removeSmallButton(const QString &tabName, const QString &groupName, QFontComboBox *button);
  void removeSmallButton(const QString &tabName, const QString &groupName, QSpinBox *button);
};

#endif // RIBBONTABWIDGET_H
