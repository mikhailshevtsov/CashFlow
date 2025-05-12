#ifndef CASHFLOWDATABASE_HPP
#define CASHFLOWDATABASE_HPP

#include "CashFlow.hpp"
#include "CashFlowReport.hpp"
#include "CashFlowFilter.hpp"

#include <QSqlDatabase>
#include <QDate>

class CashFlowDatabase
{
public:
    CashFlowDatabase();

    // Manipulation with cashflow data
    int addCashFlow(const CashFlow& cashFlow);
    void updateCashFlow(int id, const CashFlow& cashFlow);
    void removeCashFlow(int id);
    CashFlow getCashFlow(int id);

    // Report
    quint64 getCount(CashFlow::Type type) const;
    quint64 getCount() const;
    qreal getMinimum(CashFlow::Type type) const;
    qreal getMinimum() const;
    qreal getMaximum(CashFlow::Type type) const;
    qreal getMaximum() const;
    qreal getTotal(CashFlow::Type type) const;
    qreal getTotal() const;

    CashFlowReport getReport() const;
    CashFlowFilter getFilter() const;

    QDate getFirstDate() const;
    QDate getLastDate() const;

    const QSqlDatabase& getDatabase() const;

    static QString getFilterString(const CashFlowFilter& filter);

private:
    QSqlDatabase m_database;
};

#endif // CASHFLOWDATABASE_HPP
