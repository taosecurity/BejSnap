#ifndef REGIONSELECTOR_H
#define REGIONSELECTOR_H

#include <QWidget>
#include <QRect>
#include <QPoint>
#include <QScreen>
#include <QPixmap>
#include <QImage>

class RegionSelector : public QWidget
{
    Q_OBJECT

public:
    explicit RegionSelector(QWidget *parent = nullptr);
    ~RegionSelector();

    QImage captureRegion();
    void start();
    
signals:
    void regionSelected(QImage capturedImage);
    void selectionCancelled();
    
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void updateSelectionRect(const QPoint &pos);
    QRect ensureSquareRect(const QRect &rect) const;
    QRect getCurrentScreen() const;
    QRect m_selectionRect;
    QPoint m_startPos;
    QPoint m_endPos;
    bool m_isSelecting;
    QPixmap m_screenPixmap;
    
    // Background dim settings
    QColor m_dimColor;
    int m_dimOpacity;
};

#endif // REGIONSELECTOR_H
