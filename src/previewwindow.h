#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QDialog>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QShortcut>

class PreviewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewWindow(QWidget *parent = nullptr);
    ~PreviewWindow();

    void setImage(const QImage &image);
    QImage getImage() const;

signals:
    void saveRequested();
    void cancelRequested();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    void setupUi();
    void updatePreview();
    QSize calculatePreviewSize() const;

    QLabel *m_imageLabel;
    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_buttonLayout;
    QImage m_originalImage;
    QShortcut *m_saveShortcut;
};

#endif // PREVIEWWINDOW_H
