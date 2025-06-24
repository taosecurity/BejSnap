#ifndef BEJSNAPWINDOW_H
#define BEJSNAPWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QAction>
#include <QMenu>
#include <QStatusBar>

#include "filemanager.h"
#include "regionselector.h"
#include "previewwindow.h"
#include "settingsdialog.h"

class BejSnapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BejSnapWindow(QWidget *parent = nullptr);
    ~BejSnapWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onCaptureClicked();
    void onRegionSelected(QImage capturedImage);
    void onSelectionCancelled();
    void onSaveRequested();
    void onCancelRequested();
    void onSettingsClicked();
    void onSavePathChanged(const QString &path);
    void onDarkModeChanged(bool darkMode);
    void updateStatusBar(const QString &message = QString());

private:
    void setupUi();
    void setupActions();
    void createCentralWidget();
    void createMenuBar();
    void ensureSquareWindow();

    // UI components
    QWidget *m_centralWidget;
    QVBoxLayout *m_mainLayout;
    QPushButton *m_captureButton;
    QLabel *m_statusLabel;
    
    // Actions
    QAction *m_captureAction;
    QAction *m_settingsAction;
    QAction *m_exitAction;
    
    // Core components
    FileManager *m_fileManager;
    RegionSelector *m_regionSelector;
    PreviewWindow *m_previewWindow;
    SettingsDialog *m_settingsDialog;
    
    // State variables
    QImage m_currentImage;
};

#endif // BEJSNAPWINDOW_H
