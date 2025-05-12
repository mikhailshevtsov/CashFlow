#include "CashFlowDatabase.hpp"

#include <QSqlQuery>
#include <QSqlError>
#include <QDate>

CashFlowDatabase::CashFlowDatabase()
{
    // Opening the connection
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("CashFlow");

    if (!m_database.open())
    {
        qDebug() << m_database.lastError().text() << Qt::endl;
        return;
    }

    // Creating the table if it isn't exists
    QSqlQuery query;    
    bool ok = query.exec(R"(
        CREATE TABLE IF NOT EXISTS CashFlow (
            id          INTEGER PRIMARY KEY AUTOINCREMENT,
            date        STRING  NOT NULL,
            type        STRING  NOT NULL,
            amount      REAL    NOT NULL,
            description STRING  NOT NULL
        );
        )");
    if (!ok)
    {
        qDebug() << query.lastError().text() << Qt::endl;
        return;
    }
}

int CashFlowDatabase::addCashFlow(const CashFlow& cashFlow)
{
    QSqlQuery query;
    query.prepare("INSERT INTO CashFlow (date, type, amount, description) "
                  "VALUES (:date, :type, :amount, :description);");

    query.bindValue(":date", QDate::currentDate().toString("yyyy-MM-dd"));
    query.bindValue(":type", CashFlow::typeString(cashFlow.type));
    query.bindValue(":amount", cashFlow.amount);
    query.bindValue(":description", cashFlow.description);

    if (!query.exec())
        qDebug() << "Failed to insert data: " << query.lastError().text() << Qt::endl;

    return query.lastInsertId().toInt();
}

void CashFlowDatabase::updateCashFlow(int id, const CashFlow& cashFlow)
{
    QSqlQuery query;
    query.prepare("UPDATE CashFlow "
                  "SET date = :date, type = :type, amount = :amount, description = :description "
                  "WHERE id = :id;");

    query.bindValue(":date", cashFlow.date.toString("yyyy-MM-dd"));
    query.bindValue(":type", CashFlow::typeString(cashFlow.type));
    query.bindValue(":amount", cashFlow.amount);
    query.bindValue(":description", cashFlow.description);
    query.bindValue(":id", id);

    if (!query.exec())
        qDebug() << "Failed to update data: " << query.lastError().text() << Qt::endl;
}

void CashFlowDatabase::removeCashFlow(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CashFlow "
                  "WHERE id = :id;");

    query.bindValue(":id", id);

    if (!query.exec())
        qDebug() << "Failed to remove data: " << query.lastError().text() << Qt::endl;
}

CashFlow CashFlowDatabase::getCashFlow(int id)
{
    QSqlQuery query;
    query.prepare("SELECT date, type, amount, description FROM CashFlow "
                  "WHERE id = :id;");

    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Failed to select data: " << query.lastError().text() << Qt::endl;
        return {};
    }

    CashFlow cashFlow;

    query.first();

    cashFlow.date = QDate::fromString(query.value("date").toString(), "yyyy-MM-dd");

    QString type = query.value("type").toString();
    if (type == "Income")
        cashFlow.type = CashFlow::Type::Income;
    else if (type == "Expense")
        cashFlow.type = CashFlow::Type::Expense;

    cashFlow.amount = query.value("amount").toDouble();
    cashFlow.description = query.value("description").toString();

    return cashFlow;
}

quint64 CashFlowDatabase::getCount(CashFlow::Type type) const
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CashFlow "
                  "WHERE type = :type;");
    query.bindValue(":type", CashFlow::typeString(type));

    if (!query.exec())
    {
        qDebug() << "Failed to count: " << query.lastError().text() << Qt::endl;
        return -1;
    }
    query.first();

    return query.value(0).toInt();
}

quint64 CashFlowDatabase::getCount() const
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CashFlow;");

    if (!query.exec())
    {
        qDebug() << "Failed to count: " << query.lastError().text() << Qt::endl;
        return -1;
    }
    query.first();

    return query.value(0).toInt();
}

qreal CashFlowDatabase::getMinimum(CashFlow::Type type) const
{
    QSqlQuery query;
    query.prepare("SELECT MIN(amount) FROM CashFlow "
                  "WHERE type = :type;");
    query.bindValue(":type", CashFlow::typeString(type));

    if (!query.exec())
    {
        qDebug() << "Failed to get minimum: " << query.lastError().text() << Qt::endl;
        return -1;
    }
    query.first();

    return query.value(0).toDouble();
}

qreal CashFlowDatabase::getMinimum() const
{
    QSqlQuery query;
    query.prepare("SELECT MIN(amount) FROM CashFlow;");

    if (!query.exec())
    {
        qDebug() << "Failed to get minimum: " << query.lastError().text() << Qt::endl;
        return -1;
    }
    query.first();

    return query.value(0).toDouble();
}

qreal CashFlowDatabase::getMaximum(CashFlow::Type type) const
{
    QSqlQuery query;
    query.prepare("SELECT MAX(amount) FROM CashFlow "
                  "WHERE type = :type;");
    query.bindValue(":type", CashFlow::typeString(type));

    if (!query.exec())
    {
        qDebug() << "Failed to get maximum: " << query.lastError().text() << Qt::endl;
        return -1;
    }
    query.first();

    return query.value(0).toDouble();
}

qreal CashFlowDatabase::getMaximum() const
{
    QSqlQuery query;
    query.prepare("SELECT MAX(amount) FROM CashFlow;");

    if (!query.exec())
    {
        qDebug() << "Failed to get maximum: " << query.lastError().text() << Qt::endl;
        return -1;
    }
    query.first();

    return query.value(0).toDouble();
}

qreal CashFlowDatabase::getTotal(CashFlow::Type type) const
{
    QSqlQuery query;
    query.prepare("SELECT SUM(amount) FROM CashFlow "
                  "WHERE type = :type;");
    query.bindValue(":type", CashFlow::typeString(type));

    if (!query.exec())
    {
        qDebug() << "Failed to get total: " << query.lastError().text() << Qt::endl;
        return -1;
    }
    query.first();

    return query.value(0).toDouble();
}

qreal CashFlowDatabase::getTotal() const
{
    QSqlQuery query;
    query.prepare("SELECT SUM(amount) FROM CashFlow;");

    if (!query.exec())
    {
        qDebug() << "Failed to get total: " << query.lastError().text() << Qt::endl;
        return -1;
    }
    query.first();

    return query.value(0).toDouble();
}

QDate CashFlowDatabase::getFirstDate() const
{
    QSqlQuery query;
    query.prepare("SELECT MIN(date) FROM CashFlow;");

    if (!query.exec())
    {
        qDebug() << "Failed to get date: " << query.lastError().text() << Qt::endl;
        return QDate();
    }
    query.first();

    return query.value(0).toDate();
}

QDate CashFlowDatabase::getLastDate() const
{
    QSqlQuery query;
    query.prepare("SELECT MAX(date) FROM CashFlow;");

    if (!query.exec())
    {
        qDebug() << "Failed to get date: " << query.lastError().text() << Qt::endl;
        return QDate();
    }
    query.first();

    return query.value(0).toDate();
}

CashFlowReport CashFlowDatabase::getReport() const
{
    CashFlowReport report;

    report.incomesCount = getCount(CashFlow::Type::Income);
    report.minimumIncome = getMinimum(CashFlow::Type::Income);
    report.maximumIncome = getMaximum(CashFlow::Type::Income);
    report.totalIncome = getTotal(CashFlow::Type::Income);

    report.expensesCount = getCount(CashFlow::Type::Expense);
    report.minimumExpense = getMinimum(CashFlow::Type::Expense);
    report.maximumExpense = getMaximum(CashFlow::Type::Expense);
    report.totalExpense = getTotal(CashFlow::Type::Expense);

    report.balance = report.totalIncome - report.totalExpense;

    return report;
}

CashFlowFilter CashFlowDatabase::getFilter() const
{
    CashFlowFilter filter;

    filter.lowerAmountLimit = getMinimum();
    filter.upperAmountLimit = getMaximum();

    filter.firstDate = getFirstDate();
    filter.lastDate = getLastDate();

    return filter;
}

const QSqlDatabase& CashFlowDatabase::getDatabase() const
{
    return m_database;
}

QString CashFlowDatabase::getFilterString(const CashFlowFilter& filter)
{
    QString filterString = "amount >= %1 AND amount <= %2 "
                           "AND date >= \'%3\' AND date <= \'%4\' ";
    filterString = filterString
        .arg(QString::number(filter.lowerAmountLimit))
        .arg(QString::number(filter.upperAmountLimit))
        .arg(filter.firstDate.toString("yyyy-MM-dd"))
        .arg(filter.lastDate.toString("yyyy-MM-dd"));

    if (!filter.income != !filter.expense) // xor
    {
        filterString.append("AND type = ");
        if (filter.income)
            filterString.append("\'Income\'");
        else
            filterString.append("\'Expense\'");
    }

    return filterString;
}
