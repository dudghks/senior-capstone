#ifndef RIBBONSMALLBUTTONSGROUP_H
#define RIBBONSMALLBUTTONSGROUP_H

#include <QWidget>
#include <QToolButton>
#include <QFontComboBox>
#include <QSpinBox>

namespace Ui {
class RibbonSmallButtonsGroup;
}

class RibbonSmallButtonsGroup : public QWidget
{
  Q_OBJECT

public:
  explicit RibbonSmallButtonsGroup(QWidget *parent = 0);
  virtual ~RibbonSmallButtonsGroup();

  /// Set the title of the button group.
  ///
  /// \param[in] title The title
  void setTitle(const QString &title);

  /// Get the title of the button group.
  ///
  /// \return The title
  QString title() const;

  /// Get the number of buttons in the button group.
  ///
  /// \return The number of buttons
  int buttonCount() const;

  /// Add a tool button to the group.
  ///
  /// \param[in] button The button
  /// \param[in] row The row
  /// \param[in] column The column
  void addButton(QToolButton *button, int row, int column);

  /// Add a font combo box to the group.
  ///
  /// \param[in] button The button
  /// \param[in] row The row
  /// \param[in] column The column
  void addButton(QFontComboBox *button, int row, int column);

  /// Add a double spin box to the group.
  ///
  /// \param[in] button The button
  /// \param[in] row The row
  /// \param[in] column The column
  void addButton(QSpinBox *button, int row, int column);

  /// Remove a button from the group.
  ///
  /// \param[in] button The button
  void removeButton(QToolButton *button);
  void removeButton(QFontComboBox *button);
  void removeButton(QSpinBox *button);

private:
  Ui::RibbonSmallButtonsGroup *ui;
  QString m_title; ///< Title of the button group
};


#endif // RIBBONSMALLBUTTONSGROUP_H
