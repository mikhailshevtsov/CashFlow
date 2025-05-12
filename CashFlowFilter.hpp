#ifndef CASHFLOWFILTER_HPP
#define CASHFLOWFILTER_HPP

#include <QtGlobal>
#include <QDate>

struct CashFlowFilter
{
    bool income = true;
    bool expense = true;

    qreal lowerAmountLimit = 0;
    qreal upperAmountLimit = 0;

    QDate firstDate;
    QDate lastDate;
};

#endif // CASHFLOWFILTER_HPP
