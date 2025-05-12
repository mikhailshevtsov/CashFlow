#include "CashFlowWindow.hpp"

#include "CashFlowDialog.hpp"
#include "CashFlowReportWidget.hpp"
#include "CashFlowFilterWidget.hpp"

#include <QFile>
#include <QStyleFactory>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include <QGridLayout>
#include <QDate>

CashFlowWindow::CashFlowWindow(QWidget* parent)
    : QWidget(parent)
{
    setupWindow();
    setupTableModel();
    setupTableView();
    setupButtons();
    setupDialog();
    setupReportWidget();
    setupFilterWidget();
    setupLayout();
    setupConnections();
}

void CashFlowWindow::setupWindow()
{
    setWindowTitle("CashFlow");
    setWindowIcon(QIcon(":/images/icon"));
    resize(1000, 600);

    QFile file(":/styles/style");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();
    setStyleSheet(styleSheet);
    setStyle(QStyleFactory::create("Fusion"));
}

void CashFlowWindow::setupTableModel()
{
    m_tableModel = new QSqlTableModel(this, m_database.getDatabase());
    m_tableModel->setTable("CashFlow");
    m_tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_tableModel->select();
    m_tableModel->setHeaderData(1, Qt::Horizontal, tr("Date"));
    m_tableModel->setHeaderData(2, Qt::Horizontal, tr("Type"));
    m_tableModel->setHeaderData(3, Qt::Horizontal, tr("Amount"));
    m_tableModel->setHeaderData(4, Qt::Horizontal, tr("Description"));

    m_sortFilterTableModel = new QSortFilterProxyModel(this);
    m_sortFilterTableModel->setSourceModel(m_tableModel);
}

void CashFlowWindow::setupTableView()
{
    m_tableView = new QTableView;
    m_tableView->setModel(m_tableModel);
    m_tableView->hideColumn(0); // don't show the id
    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    m_tableView->setMinimumWidth(width() * 0.8);
}

void CashFlowWindow::setupButtons()
{
    m_addButton = new QPushButton(tr("Add"));
    m_removeButton = new QPushButton(tr("Remove"));
    m_editButton = new QPushButton(tr("Edit"));
}

void CashFlowWindow::setupDialog()
{
    m_dialog = new CashFlowDialog(this);
}

void CashFlowWindow::setupReportWidget()
{
    m_reportWidget = new CashFlowReportWidget(this, m_database.getReport());
}

void CashFlowWindow::setupFilterWidget()
{
    m_filterWidget = new CashFlowFilterWidget(this, m_database.getFilter());
    m_filterWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

void CashFlowWindow::setupLayout()
{
    QGridLayout* leftLayout = new QGridLayout;
    leftLayout->addWidget(m_tableView, 0, 0, 6, 12);
    leftLayout->addWidget(m_addButton, 6, 0, 1, 4);
    leftLayout->addWidget(m_removeButton, 6, 4, 1, 4);
    leftLayout->addWidget(m_editButton, 6, 8, 1, 4);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_filterWidget);
    rightLayout->addWidget(m_reportWidget);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addLayout(leftLayout, 1);
    layout->addLayout(rightLayout);
    setLayout(layout);
}

void CashFlowWindow::setupConnections()
{
    connect(m_addButton, &QPushButton::clicked, this, &CashFlowWindow::addCashFlow);
    connect(m_removeButton, &QPushButton::clicked, this, &CashFlowWindow::removeCashFlow);
    connect(m_editButton, &QPushButton::clicked, this, &CashFlowWindow::editCashFlow);
    connect(m_dialog, &QDialog::accepted, this, &CashFlowWindow::acceptDialog);

    connect(m_filterWidget, &CashFlowFilterWidget::applied, this, &CashFlowWindow::onFilterApplied);
    connect(m_filterWidget, &CashFlowFilterWidget::reset, this, &CashFlowWindow::onFilterReset);
}

int CashFlowWindow::getSelectedId() const
{
    if (!m_tableView->selectionModel()->hasSelection())
        return -1;

    auto selectedRow = m_tableView->selectionModel()->selection().indexes().first().row();
    return m_tableModel->record(selectedRow).field(0).value().toInt();
}


// Slots

void CashFlowWindow::addCashFlow()
{
    m_dialog->set(CashFlowDialog::Mode::Add);
    m_dialog->exec();
}

void CashFlowWindow::editCashFlow()
{
    // Get the id of the currently edited item
    m_editedId = getSelectedId();
    if (m_editedId < 0)
        return;

    m_dialog->set(CashFlowDialog::Mode::Edit, m_database.getCashFlow(m_editedId));
    m_dialog->exec();
}

void CashFlowWindow::acceptDialog()
{
    CashFlow cashFlow = m_dialog->cashFlow();

    CashFlowDialog::Mode mode = m_dialog->mode();
    switch (mode)
    {
        case CashFlowDialog::Mode::Add:
            m_database.addCashFlow(cashFlow);
            break;

        case CashFlowDialog::Mode::Edit:
            m_database.updateCashFlow(m_editedId, cashFlow);
            break;
    }

    m_tableModel->submitAll();
    m_reportWidget->setReport(m_database.getReport());
}

void CashFlowWindow::removeCashFlow()
{
    int removedId = getSelectedId();
    if (removedId < 0)
        return;

    m_database.removeCashFlow(removedId);

    m_tableModel->submitAll();
    m_reportWidget->setReport(m_database.getReport());
}

void CashFlowWindow::onFilterApplied()
{
    CashFlowFilter filter = m_filterWidget->filter();
    m_tableModel->setFilter(CashFlowDatabase::getFilterString(filter));
    m_reportWidget->setReport(m_database.getReport());
}

void CashFlowWindow::onFilterReset()
{
    CashFlowFilter filter = m_database.getFilter();
    m_tableModel->setFilter("");
    m_reportWidget->setReport(m_database.getReport());
    m_filterWidget->setFilter(filter);
}

