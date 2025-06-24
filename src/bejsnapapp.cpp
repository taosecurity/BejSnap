#include "bejsnapapp.h"
#include "bejsnapwindow.h"
#include "constants.h"
#include <QMessageBox>
#include <QDebug>

BejSnapApp::BejSnapApp(int &argc, char **argv)
    : QApplication(argc, argv)
    , m_mainWindow(nullptr)
    , m_themeManager(nullptr)
{
    // Set application information
    setApplicationName(Constants::APP_NAME);
    setApplicationVersion(Constants::APP_VERSION);
    setOrganizationName(Constants::APP_NAME);
    
    // Initialize theme manager
    m_themeManager = new ThemeManager(this);
    
    // Create and show main window
    m_mainWindow = new BejSnapWindow();
}

BejSnapApp::~BejSnapApp()
{
    if (m_mainWindow) {
        delete m_mainWindow;
        m_mainWindow = nullptr;
    }
}

int BejSnapApp::run()
{
    if (!m_mainWindow) {
        QMessageBox::critical(nullptr, tr("Error"), tr("Failed to initialize application."));
        return 1;
    }
    
    m_mainWindow->show();
    return exec();
}

ThemeManager* BejSnapApp::themeManager() const
{
    return m_themeManager;
}
