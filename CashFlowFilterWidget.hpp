#ifndef CASHFLOWFILTERWIDGET_HPP
#define CASHFLOWFILTERWIDGET_HPP

#include "CashFlowFilter.hpp"

#include <QWidget>
class QCheckBox;
class QDoubleSpinBox;
class QDateEdit;
class QRadioButton;
class QPushButton;

class CashFlowFilterWidget : public QWidget
{
    Q_OBJECT

public:
    CashFlowFilterWidget(QWidget* parent = nullptr, const CashFlowFilter& filter = {});

    const CashFlowFilter& filter() const noexcept;
    const CashFlowFilter& limits() const noexcept;

public slots:
    void setFilter(const CashFlowFilter& filter);
    void setLimits(const CashFlowFilter& limits);

private slots:
    void onApplied();
    void onReset();

signals:
    void applied();
    void reset();

private:
    QCheckBox* m_incomeCheckBox{};
    QCheckBox* m_expenseCheckBox{};

    QDoubleSpinBox* m_lowerAmountLimitSpinBox{};
    QDoubleSpinBox* m_upperAmountLimitSpinBox{};

    QRadioButton* m_allTimeButton{};
    QRadioButton* m_todayButton{};
    QRadioButton* m_dateButton{};
    QRadioButton* m_dateRangeButton{};

    QDateEdit* m_firstDateEdit{};
    QDateEdit* m_lastDateEdit{};

    QPushButton* m_applyButton{};
    QPushButton* m_resetButton{};

    CashFlowFilter m_filter;
    CashFlowFilter m_limits;
};

#endif // CASHFLOWFILTERWIDGET_HPP
