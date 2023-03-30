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
  /// The title is shown not shown.
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
  /// \param[in] position The position (0=top, 1=bottom)
  void addButton(QToolButton *button, int position);

  /// Add a font combo box to the group.
  ///
  /// \param[in] button The button
  /// \param[in] position The position (0=top, 1=bottom)
  void addButton(QFontComboBox *button, int position);

  /// Add a double spin box to the group.
  ///
  /// \param[in] button The button
  /// \param[in] position The position (0=top, 1=bottom)
  void addButton(QSpinBox *button, int position);

  /// Remove a button from the group.
  ///
  /// \param[in] button The button
  /// \param[in] position The position (0=top, 1=bottom)
  void removeButton(QToolButton *button, int position);

private:
  Ui::RibbonSmallButtonsGroup *ui;
  QString m_title; ///< Title of the button group
};


#endif // RIBBONSMALLBUTTONSGROUP_H
