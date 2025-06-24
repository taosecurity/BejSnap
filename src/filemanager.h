#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QImage>
#include <QSettings>

class FileManager : public QObject
{
    Q_OBJECT

public:
    explicit FileManager(QObject *parent = nullptr);
    ~FileManager();

    QString getSavePath() const;
    void setSavePath(const QString &path);
    QString saveImage(const QImage &image);
    QString generateFileName() const;
    bool ensureSavePathExists();

private:
    int getNextFileNumber() const;
    void saveSetting();
    void loadSetting();

    QString m_savePath;
    QSettings m_settings;
};

#endif // FILEMANAGER_H
