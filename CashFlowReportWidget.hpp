#ifndef CASHFLOWREPORTWIDGET_HPP
#define CASHFLOWREPORTWIDGET_HPP

#include "CashFlowReport.hpp"

#include <QWidget>
class QFormLayout;
class QLabel;

class CashFlowReportWidget : public QWidget
{
public:
    CashFlowReportWidget(QWidget* parent = nullptr, const CashFlowReport& report = {});

    const CashFlowReport& report() const noexcept;

public slots:
    void setReport(const CashFlowReport& report) noexcept;

private:
    QFormLayout* m_layout{};

    QLabel* m_incomesCountLabel{};
    QLabel* m_minimumIncomeLabel{};
    QLabel* m_maximumIncomeLabel{};
    QLabel* m_totalIncomeLabel{};

    QLabel* m_expensesCountLabel{};
    QLabel* m_minimumExpenseLabel{};
    QLabel* m_maximumExpenseLabel{};
    QLabel* m_totalExpenseLabel{};

    QLabel* m_balanceLabel{};

    CashFlowReport m_report;
};

#endif // CASHFLOWREPORTWIDGET_HPP
