#include "filemanager.h"
#include "constants.h"
#include <QDateTime>
#include <QDebug>
#include <QFileInfo>

FileManager::FileManager(QObject *parent)
    : QObject(parent)
    , m_settings(Constants::APP_NAME, Constants::APP_NAME)
{
    loadSetting();
    ensureSavePathExists();
}

FileManager::~FileManager() = default;

QString FileManager::getSavePath() const
{
    return m_savePath;
}

void FileManager::setSavePath(const QString &path)
{
    if (m_savePath != path) {
        m_savePath = path;
        saveSetting();
        ensureSavePathExists();
    }
}

QString FileManager::saveImage(const QImage &image)
{
    if (!ensureSavePathExists()) {
        qWarning() << "Failed to create save directory";
        return QString();
    }

    QString fileName = generateFileName();
    QString filePath = m_savePath + "/" + fileName;
    
    if (image.save(filePath, Constants::FILE_FORMAT.toUtf8())) {
        qDebug() << "Image saved successfully to:" << filePath;
        return filePath;
    } else {
        qWarning() << "Failed to save image to:" << filePath;
        return QString();
    }
}

QString FileManager::generateFileName() const
{
    QDateTime currentDate = QDateTime::currentDateTime();
    QString dateStr = currentDate.toString("yyyyMMdd");
    int number = getNextFileNumber();
    
    return QString("%1-%2%3.%4")
        .arg(Constants::FILE_PREFIX)
        .arg(dateStr)
        .arg(number, 3, 10, QChar('0'))
        .arg(Constants::FILE_FORMAT);
}

bool FileManager::ensureSavePathExists()
{
    QDir dir(m_savePath);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "Failed to create directory:" << m_savePath;
            return false;
        }
    }
    return true;
}

int FileManager::getNextFileNumber() const
{
    QDateTime currentDate = QDateTime::currentDateTime();
    QString dateStr = currentDate.toString("yyyyMMdd");
    QString prefix = QString("%1-%2").arg(Constants::FILE_PREFIX).arg(dateStr);
    
    QDir dir(m_savePath);
    QStringList filters;
    filters << prefix + "*.png";
    dir.setNameFilters(filters);
    
    QStringList files = dir.entryList(QDir::Files, QDir::Name);
    
    if (files.isEmpty()) {
        return 1;
    }
    
    int maxNum = 0;
    for (const QString &file : files) {
        QString numStr = file.mid(prefix.length(), 3);
        bool ok;
        int num = numStr.toInt(&ok);
        if (ok && num > maxNum) {
            maxNum = num;
        }
    }
    
    return maxNum + 1;
}

void FileManager::saveSetting()
{
    m_settings.setValue("savePath", m_savePath);
}

void FileManager::loadSetting()
{
    m_savePath = m_settings.value("savePath", Constants::DEFAULT_SAVE_PATH).toString();
}
