#include "settingsdialog.h"
#include "constants.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , m_savePathEdit(new QLineEdit(this))
    , m_browseButton(new QPushButton(tr("Browse..."), this))
    , m_darkModeCheckBox(new QCheckBox(tr("Dark Mode"), this))
    , m_okButton(new QPushButton(tr("OK"), this))
    , m_cancelButton(new QPushButton(tr("Cancel"), this))
    , m_mainLayout(new QVBoxLayout(this))
    , m_pathLayout(new QHBoxLayout())
    , m_buttonLayout(new QHBoxLayout())
{
    setupUi();
    
    // Connect signals and slots
    connect(m_browseButton, &QPushButton::clicked, this, &SettingsDialog::onBrowseClicked);
    connect(m_okButton, &QPushButton::clicked, this, &SettingsDialog::onOkClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &SettingsDialog::onCancelClicked);
    connect(m_darkModeCheckBox, &QCheckBox::toggled, this, &SettingsDialog::onDarkModeToggled);
    
    // Set window properties
    setWindowTitle(tr("BejSnap - Settings"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(400, 200);
}

SettingsDialog::~SettingsDialog() = default;

void SettingsDialog::setupUi()
{
    // Create and configure widgets
    QLabel *savePathLabel = new QLabel(tr("Save Path:"), this);
    
    // Configure layouts
    m_pathLayout->addWidget(savePathLabel);
    m_pathLayout->addWidget(m_savePathEdit, 1);
    m_pathLayout->addWidget(m_browseButton);
    
    m_buttonLayout->addStretch(1);
    m_buttonLayout->addWidget(m_okButton);
    m_buttonLayout->addWidget(m_cancelButton);
    
    m_mainLayout->addLayout(m_pathLayout);
    m_mainLayout->addWidget(m_darkModeCheckBox);
    m_mainLayout->addStretch(1);
    m_mainLayout->addLayout(m_buttonLayout);
    
    setLayout(m_mainLayout);
    
    // Set OK as the default button
    m_okButton->setDefault(true);
    
    // Set placeholder text for path edit
    m_savePathEdit->setPlaceholderText(tr("Select a directory to save screenshots"));
}

QString SettingsDialog::getSavePath() const
{
    return m_savePathEdit->text();
}

void SettingsDialog::setSavePath(const QString &path)
{
    m_savePathEdit->setText(path);
}

bool SettingsDialog::getDarkMode() const
{
    return m_darkModeCheckBox->isChecked();
}

void SettingsDialog::setDarkMode(bool darkMode)
{
    m_darkModeCheckBox->setChecked(darkMode);
}

void SettingsDialog::onBrowseClicked()
{
    QString dir = QFileDialog::getExistingDirectory(
        this, 
        tr("Select Save Directory"),
        m_savePathEdit->text().isEmpty() ? Constants::DEFAULT_SAVE_PATH : m_savePathEdit->text(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );
    
    if (!dir.isEmpty()) {
        m_savePathEdit->setText(dir);
        emit savePathChanged(dir);
    }
}

void SettingsDialog::onOkClicked()
{
    emit savePathChanged(m_savePathEdit->text());
    accept();
}

void SettingsDialog::onCancelClicked()
{
    reject();
}

void SettingsDialog::onDarkModeToggled(bool checked)
{
    emit darkModeChanged(checked);
}
