#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    QString getSavePath() const;
    void setSavePath(const QString &path);
    
    bool getDarkMode() const;
    void setDarkMode(bool darkMode);

signals:
    void savePathChanged(const QString &path);
    void darkModeChanged(bool darkMode);

private slots:
    void onBrowseClicked();
    void onOkClicked();
    void onCancelClicked();
    void onDarkModeToggled(bool checked);

private:
    void setupUi();
    
    QLineEdit *m_savePathEdit;
    QPushButton *m_browseButton;
    QCheckBox *m_darkModeCheckBox;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
    
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_pathLayout;
    QHBoxLayout *m_buttonLayout;
};

#endif // SETTINGSDIALOG_H
