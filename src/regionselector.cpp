#include "regionselector.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

RegionSelector::RegionSelector(QWidget *parent)
    : QWidget(parent)
    , m_isSelecting(false)
    , m_dimColor(Qt::black)
    , m_dimOpacity(120)
{
    // Set up the overlay window
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setCursor(Qt::CrossCursor);
}

RegionSelector::~RegionSelector() = default;

void RegionSelector::start()
{
    // Capture the entire screen
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen) {
        qWarning() << "Failed to get primary screen";
        return;
    }
    
    // Get the virtual screen geometry (all monitors)
    QRect screenGeometry = QGuiApplication::primaryScreen()->virtualGeometry();
    
    // Take a screenshot of the entire virtual screen
    m_screenPixmap = screen->grabWindow(0, 
                                        screenGeometry.x(), 
                                        screenGeometry.y(), 
                                        screenGeometry.width(), 
                                        screenGeometry.height());
    
    // Set the window to cover the entire virtual screen
    setGeometry(screenGeometry);
    
    // Reset selection state
    m_selectionRect = QRect();
    m_isSelecting = false;
    m_startPos = QPoint();
    m_endPos = QPoint();
    
    // Show the overlay
    showFullScreen();
}

QImage RegionSelector::captureRegion()
{
    if (m_selectionRect.isValid()) {
        return m_screenPixmap.copy(m_selectionRect).toImage();
    }
    return QImage();
}

void RegionSelector::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    
    // Draw the screenshot as background
    painter.drawPixmap(rect(), m_screenPixmap);
    
    // Dim the entire screen
    QColor dimColor = m_dimColor;
    dimColor.setAlpha(m_dimOpacity);
    painter.fillRect(rect(), dimColor);
    
    if (m_selectionRect.isValid()) {
        // Clear the dim effect within the selection rectangle
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        painter.fillRect(m_selectionRect, Qt::transparent);
        
        // Draw selection rectangle border
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.setPen(QPen(Qt::white, 2, Qt::SolidLine));
        painter.drawRect(m_selectionRect);
        
        // Display dimensions
        QString dimensions = QString("%1 x %2")
                .arg(m_selectionRect.width())
                .arg(m_selectionRect.height());
        
        // Position the text near the selection
        QPoint textPos = m_selectionRect.bottomRight() + QPoint(10, 20);
        
        // Ensure the text is visible by drawing a background
        QFont font = painter.font();
        font.setBold(true);
        painter.setFont(font);
        
        QRect textRect = painter.fontMetrics().boundingRect(dimensions);
        textRect.adjust(-5, -5, 5, 5);
        textRect.moveTopLeft(textPos);
        
        painter.fillRect(textRect, QColor(0, 0, 0, 180));
        painter.setPen(Qt::white);
        painter.drawText(textPos, dimensions);
    }
}

void RegionSelector::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isSelecting = true;
        m_startPos = event->pos();
        m_endPos = m_startPos;
        updateSelectionRect(m_endPos);
        update();
    }
}

void RegionSelector::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isSelecting) {
        m_endPos = event->pos();
        updateSelectionRect(m_endPos);
        update();
    }
}

void RegionSelector::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isSelecting) {
        m_isSelecting = false;
        m_endPos = event->pos();
        updateSelectionRect(m_endPos);
        
        if (m_selectionRect.isValid() && 
            m_selectionRect.width() > 10 && 
            m_selectionRect.height() > 10) {
            // Capture the selected region
            QImage capturedImage = captureRegion();
            hide();
            emit regionSelected(capturedImage);
        }
        
        update();
    }
}

void RegionSelector::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        // Cancel selection
        hide();
        emit selectionCancelled();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void RegionSelector::updateSelectionRect(const QPoint &pos)
{
    QRect rawRect(m_startPos, pos);
    m_selectionRect = ensureSquareRect(rawRect.normalized());
}

QRect RegionSelector::ensureSquareRect(const QRect &rect) const
{
    // Make the rectangle a square by using the smaller dimension
    int size = qMin(rect.width(), rect.height());
    
    // Create a square rectangle while maintaining the top-left corner
    return QRect(rect.topLeft(), QSize(size, size));
}

QRect RegionSelector::getCurrentScreen() const
{
    // Get the screen containing the cursor
    QPoint globalCursorPos = QCursor::pos();
    QScreen *screen = QGuiApplication::screenAt(globalCursorPos);
    
    if (!screen) {
        // Fallback to primary screen
        screen = QGuiApplication::primaryScreen();
    }
    
    return screen ? screen->geometry() : QRect();
}
