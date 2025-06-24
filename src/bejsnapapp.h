#ifndef BEJSNAPAPP_H
#define BEJSNAPAPP_H

#include <QApplication>
#include "thememanager.h"

class BejSnapWindow;

class BejSnapApp : public QApplication
{
    Q_OBJECT

public:
    BejSnapApp(int &argc, char **argv);
    ~BejSnapApp();

    int run();
    ThemeManager* themeManager() const;

private:
    BejSnapWindow *m_mainWindow;
    ThemeManager *m_themeManager;
};

#endif // BEJSNAPAPP_H
