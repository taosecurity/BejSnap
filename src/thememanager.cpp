#include "thememanager.h"
#include "constants.h"
#include <QStyleFactory>
#include <QDebug>

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent)
    , m_settings(Constants::APP_NAME, Constants::APP_NAME)
{
    loadSetting();
    applyTheme();
}

ThemeManager::~ThemeManager() = default;

bool ThemeManager::isDarkMode() const
{
    return m_darkMode;
}

void ThemeManager::toggleTheme()
{
    m_darkMode = !m_darkMode;
    applyTheme();
    saveSetting();
}

void ThemeManager::setDarkMode(bool darkMode)
{
    if (m_darkMode != darkMode) {
        m_darkMode = darkMode;
        applyTheme();
        saveSetting();
    }
}

void ThemeManager::applyTheme()
{
    QPalette palette;
    
    if (m_darkMode) {
        palette = createDarkPalette();
        loadStyleSheet(Constants::DARK_THEME_STYLE);
    } else {
        palette = createLightPalette();
        loadStyleSheet(Constants::LIGHT_THEME_STYLE);
    }
    
    qApp->setPalette(palette);
    qApp->setStyle(QStyleFactory::create("Fusion"));
}

void ThemeManager::loadStyleSheet(const QString &path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
    } else {
        qWarning() << "Failed to load stylesheet:" << path;
    }
}

QPalette ThemeManager::createDarkPalette() const
{
    QPalette palette;
    
    // Dark color scheme
    QColor darkColor(45, 45, 45);
    QColor darkGray(53, 53, 53);
    QColor gray(128, 128, 128);
    QColor blue(42, 130, 218);
    QColor lightGray(192, 192, 192);
    
    palette.setColor(QPalette::Window, darkColor);
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(18, 18, 18));
    palette.setColor(QPalette::AlternateBase, darkGray);
    palette.setColor(QPalette::ToolTipBase, blue);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, darkGray);
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::Link, blue);
    palette.setColor(QPalette::Highlight, blue);
    palette.setColor(QPalette::HighlightedText, Qt::black);
    
    palette.setColor(QPalette::Active, QPalette::Button, darkGray.darker());
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, gray);
    palette.setColor(QPalette::Disabled, QPalette::WindowText, gray);
    palette.setColor(QPalette::Disabled, QPalette::Text, gray);
    palette.setColor(QPalette::Disabled, QPalette::Light, darkGray);
    
    return palette;
}

QPalette ThemeManager::createLightPalette() const
{
    // Default light palette
    return QPalette();
}

void ThemeManager::saveSetting()
{
    m_settings.setValue("darkMode", m_darkMode);
}

void ThemeManager::loadSetting()
{
    m_darkMode = m_settings.value("darkMode", Constants::DEFAULT_DARK_MODE).toBool();
}
