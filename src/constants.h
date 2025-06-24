#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QDir>

namespace Constants {
    // Application information
    const QString APP_NAME = "BejSnap";
    const QString APP_VERSION = "1.0.0";
    
    // File settings
    const QString FILE_PREFIX = "BejCap";
    const QString FILE_FORMAT = "png";
    const QString DEFAULT_SAVE_PATH = QDir::homePath() + "/Pictures/BejSnap";
    
    // UI Constants
    const int DEFAULT_WINDOW_SIZE = 400; // Square window size (width = height)
    const int MIN_WINDOW_SIZE = 300;
    const int PREVIEW_WINDOW_PADDING = 20;
    
    // Theme constants
    const bool DEFAULT_DARK_MODE = true;
    const QString DARK_THEME_STYLE = ":/styles/dark.qss";
    const QString LIGHT_THEME_STYLE = ":/styles/light.qss";
    
    // Shortcut keys
    const QString SAVE_SHORTCUT = "Ctrl+S";
    const QString CANCEL_SHORTCUT = "Esc";
}

#endif // CONSTANTS_H
