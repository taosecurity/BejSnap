#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QApplication>
#include <QPalette>
#include <QFile>
#include <QSettings>

class ThemeManager : public QObject
{
    Q_OBJECT

public:
    explicit ThemeManager(QObject *parent = nullptr);
    ~ThemeManager();

    bool isDarkMode() const;
    void applyTheme();
    void toggleTheme();
    void setDarkMode(bool darkMode);
    
private:
    void loadStyleSheet(const QString &path);
    QPalette createDarkPalette() const;
    QPalette createLightPalette() const;
    void saveSetting();
    void loadSetting();

    bool m_darkMode;
    QSettings m_settings;
};

#endif // THEMEMANAGER_H
