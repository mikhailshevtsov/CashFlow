#include "CashFlow.hpp"

CashFlow::CashFlow() noexcept {}

CashFlow::CashFlow(const QDate& date, Type type, const QString& description, qreal amount)
    : date(date)
    , type(type)
    , description(description)
    , amount(amount)
{}

QString CashFlow::typeString(Type type) noexcept
{
    switch (type)
    {
        case Type::Income:
            return "Income";
        case Type::Expense:
            return "Expense";
        default:
            return "None";
    }
}
