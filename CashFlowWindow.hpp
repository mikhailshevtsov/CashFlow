#ifndef CASHFLOWWINDOW_HPP
#define CASHFLOWWINDOW_HPP

#include "CashFlowDatabase.hpp"
class CashFlowDialog;
class CashFlowReportWidget;
class CashFlowFilterWidget;

#include <QWidget>
class QSqlTableModel;
class QSortFilterProxyModel;
class QTableView;
class QPushButton;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class CashFlowWindow : public QWidget
{
    Q_OBJECT

public:
    CashFlowWindow(QWidget* parent = nullptr);

private:
    CashFlowDatabase m_database;

    QSqlTableModel* m_tableModel{};
    QSortFilterProxyModel* m_sortFilterTableModel{};
    QTableView* m_tableView{};

    QPushButton* m_addButton{};
    QPushButton* m_removeButton{};
    QPushButton* m_editButton{};

    CashFlowDialog* m_dialog{};

    CashFlowReportWidget* m_reportWidget{};
    CashFlowFilterWidget* m_filterWidget{};

    int m_editedId = -1;

private:
    void setupWindow();
    void setupTableModel();
    void setupTableView();
    void setupButtons();
    void setupDialog();
    void setupReportWidget();
    void setupFilterWidget();
    void setupLayout();
    void setupConnections();

    int getSelectedId() const;

private slots:
    void addCashFlow();
    void editCashFlow();
    void acceptDialog();
    void removeCashFlow();

    void onFilterApplied();
    void onFilterReset();
};
#endif // CASHFLOWWINDOW_HPP
