#include "bejsnapwindow.h"
#include "constants.h"
#include "bejsnapapp.h"
#include <QResizeEvent>
#include <QCloseEvent>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

BejSnapWindow::BejSnapWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(new QWidget(this))
    , m_mainLayout(new QVBoxLayout(m_centralWidget))
    , m_captureButton(new QPushButton(tr("Take Screenshot"), this))
    , m_statusLabel(new QLabel(this))
    , m_fileManager(new FileManager(this))
    , m_regionSelector(new RegionSelector(nullptr)) // No parent to allow full-screen
    , m_previewWindow(new PreviewWindow(this))
    , m_settingsDialog(new SettingsDialog(this))
{
    setupUi();
    setupActions();
    createCentralWidget();
    createMenuBar();
    
    // Set up status bar
    statusBar()->addWidget(m_statusLabel, 1);
    updateStatusBar(tr("Ready"));
    
    // Connect signals and slots
    connect(m_captureButton, &QPushButton::clicked, this, &BejSnapWindow::onCaptureClicked);
    connect(m_regionSelector, &RegionSelector::regionSelected, this, &BejSnapWindow::onRegionSelected);
    connect(m_regionSelector, &RegionSelector::selectionCancelled, this, &BejSnapWindow::onSelectionCancelled);
    connect(m_previewWindow, &PreviewWindow::saveRequested, this, &BejSnapWindow::onSaveRequested);
    connect(m_previewWindow, &PreviewWindow::cancelRequested, this, &BejSnapWindow::onCancelRequested);
    connect(m_settingsDialog, &SettingsDialog::savePathChanged, this, &BejSnapWindow::onSavePathChanged);
    connect(m_settingsDialog, &SettingsDialog::darkModeChanged, this, &BejSnapWindow::onDarkModeChanged);
    
    // Initialize settings
    m_settingsDialog->setSavePath(m_fileManager->getSavePath());
    m_settingsDialog->setDarkMode(static_cast<BejSnapApp*>(qApp)->themeManager()->isDarkMode());
    
    // Set window properties
    setWindowTitle(Constants::APP_NAME);
    setMinimumSize(Constants::MIN_WINDOW_SIZE, Constants::MIN_WINDOW_SIZE);
    resize(Constants::DEFAULT_WINDOW_SIZE, Constants::DEFAULT_WINDOW_SIZE);
}

BejSnapWindow::~BejSnapWindow()
{
    // RegionSelector has no parent, so we need to delete it manually
    if (m_regionSelector) {
        delete m_regionSelector;
        m_regionSelector = nullptr;
    }
}

void BejSnapWindow::setupUi()
{
    // Configure capture button
    m_captureButton->setFixedHeight(50);
    m_captureButton->setStyleSheet("font-size: 16px; font-weight: bold;");
    
    // Configure status label
    m_statusLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void BejSnapWindow::setupActions()
{
    m_captureAction = new QAction(tr("&Capture"), this);
    m_captureAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    connect(m_captureAction, &QAction::triggered, this, &BejSnapWindow::onCaptureClicked);
    
    m_settingsAction = new QAction(tr("&Settings"), this);
    m_settingsAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
    connect(m_settingsAction, &QAction::triggered, this, &BejSnapWindow::onSettingsClicked);
    
    m_exitAction = new QAction(tr("E&xit"), this);
    m_exitAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
}

void BejSnapWindow::createCentralWidget()
{
    // Add widgets to main layout
    m_mainLayout->addStretch(1);
    m_mainLayout->addWidget(m_captureButton, 0, Qt::AlignCenter);
    m_mainLayout->addStretch(1);
    
    // Set central widget
    setCentralWidget(m_centralWidget);
}

void BejSnapWindow::createMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(m_captureAction);
    fileMenu->addSeparator();
    fileMenu->addAction(m_settingsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(m_exitAction);
    
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAction = helpMenu->addAction(tr("&About"));
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, tr("About BejSnap"),
            tr("<h3>BejSnap %1</h3>"
               "<p>BejSnap is a square screen capture tool for Linux.</p>"
               "<p>Richard Bejtlich developed BejSnap using VSCodium and Cline on Linux.</p>")
            .arg(Constants::APP_VERSION));
    });
}

void BejSnapWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    ensureSquareWindow();
}

void BejSnapWindow::closeEvent(QCloseEvent *event)
{
    // Additional cleanup if needed
    QMainWindow::closeEvent(event);
}

void BejSnapWindow::ensureSquareWindow()
{
    int size = qMin(width(), height());
    
    if (width() != height()) {
        resize(size, size);
    }
}

void BejSnapWindow::onCaptureClicked()
{
    updateStatusBar(tr("Select a square region..."));
    m_regionSelector->start();
}

void BejSnapWindow::onRegionSelected(QImage capturedImage)
{
    if (capturedImage.isNull()) {
        updateStatusBar(tr("Capture failed"));
        return;
    }
    
    m_currentImage = capturedImage;
    m_previewWindow->setImage(capturedImage);
    m_previewWindow->exec();
}

void BejSnapWindow::onSelectionCancelled()
{
    updateStatusBar(tr("Capture cancelled"));
}

void BejSnapWindow::onSaveRequested()
{
    if (m_currentImage.isNull()) {
        updateStatusBar(tr("No image to save"));
        return;
    }
    
    QString savedPath = m_fileManager->saveImage(m_currentImage);
    if (!savedPath.isEmpty()) {
        updateStatusBar(tr("Image saved to: %1").arg(QFileInfo(savedPath).fileName()));
        
        // Ask if user wants to open the saved image
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, 
            tr("Open Image"),
            tr("Image saved successfully. Would you like to open it?"),
            QMessageBox::Yes | QMessageBox::No
        );
        
        if (reply == QMessageBox::Yes) {
            QDesktopServices::openUrl(QUrl::fromLocalFile(savedPath));
        }
    } else {
        updateStatusBar(tr("Failed to save image"));
    }
}

void BejSnapWindow::onCancelRequested()
{
    m_currentImage = QImage(); // Clear the current image
    updateStatusBar(tr("Ready"));
}

void BejSnapWindow::onSettingsClicked()
{
    m_settingsDialog->exec();
}

void BejSnapWindow::onSavePathChanged(const QString &path)
{
    if (!path.isEmpty()) {
        m_fileManager->setSavePath(path);
        updateStatusBar(tr("Save path updated"));
    }
}

void BejSnapWindow::onDarkModeChanged(bool darkMode)
{
    static_cast<BejSnapApp*>(qApp)->themeManager()->setDarkMode(darkMode);
}

void BejSnapWindow::updateStatusBar(const QString &message)
{
    m_statusLabel->setText(message);
}
