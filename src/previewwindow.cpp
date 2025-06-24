#include "previewwindow.h"
#include "constants.h"
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>
#include <QShortcut>
#include <QDebug>

PreviewWindow::PreviewWindow(QWidget *parent)
    : QDialog(parent)
    , m_imageLabel(new QLabel(this))
    , m_saveButton(new QPushButton(tr("Save"), this))
    , m_cancelButton(new QPushButton(tr("Cancel"), this))
    , m_mainLayout(new QVBoxLayout(this))
    , m_buttonLayout(new QHBoxLayout())
    , m_saveShortcut(new QShortcut(QKeySequence(Constants::SAVE_SHORTCUT), this))
{
    setupUi();
    
    // Connect signals and slots
    connect(m_saveButton, &QPushButton::clicked, this, &PreviewWindow::onSaveClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &PreviewWindow::onCancelClicked);
    connect(m_saveShortcut, &QShortcut::activated, this, &PreviewWindow::onSaveClicked);
    
    // Set window properties
    setWindowTitle(tr("BejSnap - Preview"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setMinimumSize(300, 300);
    
    // Make the window square
    int size = Constants::DEFAULT_WINDOW_SIZE;
    resize(size, size);
}

PreviewWindow::~PreviewWindow() = default;

void PreviewWindow::setupUi()
{
    // Configure image label
    m_imageLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setMinimumSize(200, 200);
    m_imageLabel->setStyleSheet("background-color: #222; border: 1px solid #444;");
    
    // Configure buttons
    m_saveButton->setDefault(true);
    m_saveButton->setFocus();
    
    // Set up layouts
    m_buttonLayout->addWidget(m_saveButton);
    m_buttonLayout->addWidget(m_cancelButton);
    
    m_mainLayout->addWidget(m_imageLabel, 1);
    m_mainLayout->addLayout(m_buttonLayout);
    
    setLayout(m_mainLayout);
}

void PreviewWindow::setImage(const QImage &image)
{
    m_originalImage = image;
    updatePreview();
}

QImage PreviewWindow::getImage() const
{
    return m_originalImage;
}

void PreviewWindow::updatePreview()
{
    if (m_originalImage.isNull()) {
        return;
    }
    
    QSize previewSize = calculatePreviewSize();
    QPixmap scaledPixmap = QPixmap::fromImage(
        m_originalImage.scaled(previewSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)
    );
    
    m_imageLabel->setPixmap(scaledPixmap);
}

QSize PreviewWindow::calculatePreviewSize() const
{
    // Calculate the maximum size for the preview, leaving space for buttons and padding
    int maxDimension = qMin(width(), height()) - Constants::PREVIEW_WINDOW_PADDING * 2;
    
    // Ensure the image stays square
    return QSize(maxDimension, maxDimension);
}

void PreviewWindow::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    
    // Keep the window square
    int size = qMin(width(), height());
    
    if (width() != height()) {
        resize(size, size);
        return;
    }
    
    updatePreview();
}

void PreviewWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        onCancelClicked();
    } else {
        QDialog::keyPressEvent(event);
    }
}

void PreviewWindow::onSaveClicked()
{
    emit saveRequested();
    accept();
}

void PreviewWindow::onCancelClicked()
{
    emit cancelRequested();
    reject();
}
