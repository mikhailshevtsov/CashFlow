#include "CashFlowReportWidget.hpp"

#include <QFormLayout>
#include <QLabel>

CashFlowReportWidget::CashFlowReportWidget(QWidget* parent, const CashFlowReport& report)
    : QWidget(parent)
{
    m_incomesCountLabel = new QLabel;
    m_minimumIncomeLabel = new QLabel;
    m_maximumIncomeLabel = new QLabel;
    m_totalIncomeLabel = new QLabel;

    m_expensesCountLabel = new QLabel;
    m_minimumExpenseLabel = new QLabel;
    m_maximumExpenseLabel = new QLabel;
    m_totalExpenseLabel = new QLabel;

    m_balanceLabel = new QLabel;

    setReport(report);

    QFormLayout* layout = new QFormLayout;

    layout->addRow(tr("Incomes count\t"), m_incomesCountLabel);
    layout->addRow(tr("Minimum income\t"), m_minimumIncomeLabel);
    layout->addRow(tr("Maximum income\t"), m_maximumIncomeLabel);
    layout->addRow(tr("Total income\t"), m_totalIncomeLabel);

    layout->addRow(tr("Expenses count\t"), m_expensesCountLabel);
    layout->addRow(tr("Minimum expense\t"), m_minimumExpenseLabel);
    layout->addRow(tr("Maximum expense\t"), m_maximumExpenseLabel);
    layout->addRow(tr("Total expense\t"), m_totalExpenseLabel);

    layout->addRow(tr("Balance\t"), m_balanceLabel);

    setLayout(layout);
}

const CashFlowReport& CashFlowReportWidget::report() const noexcept
{
    return m_report;
}

void CashFlowReportWidget::setReport(const CashFlowReport& report) noexcept
{
    m_report = report;

    m_incomesCountLabel->setText(QString::number(report.incomesCount));
    m_minimumIncomeLabel->setText(QString::number(report.minimumIncome));
    m_maximumIncomeLabel->setText(QString::number(report.maximumIncome));
    m_totalIncomeLabel->setText(QString::number(report.totalIncome));

    m_expensesCountLabel->setText(QString::number(report.expensesCount));
    m_minimumExpenseLabel->setText(QString::number(report.minimumExpense));
    m_maximumExpenseLabel->setText(QString::number(report.maximumExpense));
    m_totalExpenseLabel->setText(QString::number(report.totalExpense));

    m_balanceLabel->setText(QString::number(report.balance));
}
