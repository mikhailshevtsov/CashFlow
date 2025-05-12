#ifndef CASHFLOW_HPP
#define CASHFLOW_HPP

#include <QDate>
#include <QString>

struct CashFlow
{
    enum class Type { Income, Expense };

    CashFlow() noexcept;
    CashFlow(const QDate& date, Type type, const QString& description, qreal amount);

    QDate date;
    Type type = Type::Income;
    QString description;
    qreal amount = 0;

    static QString typeString(Type type) noexcept;
};

#endif // CASHFLOW_HPP
