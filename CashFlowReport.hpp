#ifndef CASHFLOWREPORT_HPP
#define CASHFLOWREPORT_HPP

#include <QtGlobal>

struct CashFlowReport
{
    quint64 incomesCount = 0;
    qreal minimumIncome = 0;
    qreal maximumIncome = 0;
    qreal totalIncome = 0;

    quint64 expensesCount = 0;
    qreal minimumExpense = 0;
    qreal maximumExpense = 0;
    qreal totalExpense = 0;

    qreal balance = 0;
};

#endif // CASHFLOWREPORT_HPP
