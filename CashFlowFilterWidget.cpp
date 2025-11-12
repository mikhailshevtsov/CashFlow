#include "CashFlowFilterWidget.hpp"

#include <QGridLayout>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>

CashFlowFilterWidget::CashFlowFilterWidget(QWidget* parent, const CashFlowFilter& filter)
{
    m_incomeCheckBox = new QCheckBox(tr("Income"));
    m_expenseCheckBox = new QCheckBox(tr("Expense"));

    m_lowerAmountLimitSpinBox = new QDoubleSpinBox;
    m_lowerAmountLimitSpinBox->setDecimals(2);
    m_upperAmountLimitSpinBox = new QDoubleSpinBox;
    m_upperAmountLimitSpinBox->setDecimals(2);

    m_allTimeButton = new QRadioButton(tr("All time"));
    m_todayButton = new QRadioButton(tr("Today"));
    m_dateButton = new QRadioButton(tr("Date"));
    m_dateRangeButton = new QRadioButton(tr("Range"));

    m_allTimeButton->setChecked(true);

    QButtonGroup* buttons = new QButtonGroup(this);
    buttons->addButton(m_allTimeButton);
    buttons->addButton(m_todayButton);
    buttons->addButton(m_dateButton);
    buttons->addButton(m_dateRangeButton);

    m_firstDateEdit = new QDateEdit;
    m_firstDateEdit->setDisplayFormat("yyyy-MM-dd");
    m_lastDateEdit = new QDateEdit;
    m_lastDateEdit->setDisplayFormat("yyyy-MM-dd");

    m_applyButton = new QPushButton(tr("Apply"));
    m_resetButton = new QPushButton(tr("Reset"));

    setLimits(filter);
    setFilter(filter);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(m_incomeCheckBox, 0, 0);
    layout->addWidget(m_expenseCheckBox, 0, 1);
    layout->addWidget(m_lowerAmountLimitSpinBox, 1, 0);
    layout->addWidget(m_upperAmountLimitSpinBox, 1, 1);
    layout->addWidget(m_allTimeButton, 2, 0, 1, 2);
    layout->addWidget(m_todayButton, 3, 0, 1, 2);
    layout->addWidget(m_dateButton, 4, 0, 1, 2);
    layout->addWidget(m_dateRangeButton, 5, 0, 1, 2);
    layout->addWidget(m_firstDateEdit, 6, 0);
    layout->addWidget(m_lastDateEdit, 6, 1);
    layout->addWidget(m_applyButton, 7, 0, 1, 2);
    layout->addWidget(m_resetButton, 8, 0, 1, 2);
    setLayout(layout);

    m_firstDateEdit->setEnabled(false);
    m_lastDateEdit->setEnabled(false);

    connect(m_firstDateEdit, &QDateEdit::dateChanged, m_lastDateEdit, &QDateEdit::setMinimumDate);
    connect(m_lastDateEdit, &QDateEdit::dateChanged, m_firstDateEdit, &QDateEdit::setMaximumDate);

    connect(m_dateButton, &QRadioButton::toggled, m_firstDateEdit, &QDateEdit::setEnabled);
    connect(m_dateButton, &QRadioButton::toggled, m_lastDateEdit, &QDateEdit::setEnabled);

    connect(m_dateButton, &QRadioButton::toggled, [this](bool value)
    {
        if (value)
        {
            connect(m_firstDateEdit, &QDateEdit::dateChanged, m_lastDateEdit, &QDateEdit::setDate);
            connect(m_lastDateEdit, &QDateEdit::dateChanged, m_firstDateEdit, &QDateEdit::setDate);
        }
        else
        {
            disconnect(m_firstDateEdit, &QDateEdit::dateChanged, m_lastDateEdit, &QDateEdit::setDate);
            disconnect(m_lastDateEdit, &QDateEdit::dateChanged, m_firstDateEdit, &QDateEdit::setDate);
        }
    });

    connect(m_dateRangeButton, &QRadioButton::toggled, m_firstDateEdit, &QDateEdit::setEnabled);
    connect(m_dateRangeButton, &QRadioButton::toggled, m_lastDateEdit, &QDateEdit::setEnabled);

    connect(m_todayButton, &QRadioButton::clicked, m_firstDateEdit, [this]()
    {
        m_firstDateEdit->setDate(QDate::currentDate());
    });
    connect(m_todayButton, &QRadioButton::clicked, m_lastDateEdit, [this]()
    {
        m_lastDateEdit->setDate(QDate::currentDate());
    });

    connect(m_dateButton, &QRadioButton::clicked, m_lastDateEdit, [this]()
    {
        m_lastDateEdit->setDate(m_firstDateEdit->date());
    });

    connect(m_applyButton, &QPushButton::clicked, this, &CashFlowFilterWidget::onApplied);
    connect(m_resetButton, &QPushButton::clicked, this, &CashFlowFilterWidget::onReset);
}

const CashFlowFilter& CashFlowFilterWidget::filter() const noexcept
{
    return m_filter;
}

const CashFlowFilter& CashFlowFilterWidget::limits() const noexcept
{
    return m_limits;
}

void CashFlowFilterWidget::setFilter(const CashFlowFilter& filter)
{
    m_filter = filter;

    m_incomeCheckBox->setChecked(filter.income);
    m_expenseCheckBox->setChecked(filter.expense);

    m_lowerAmountLimitSpinBox->setValue(filter.lowerAmountLimit);
    m_upperAmountLimitSpinBox->setValue(filter.upperAmountLimit + 0.01);

    m_firstDateEdit->setDate(filter.firstDate);
    m_lastDateEdit->setDate(filter.lastDate);
}

void CashFlowFilterWidget::setLimits(const CashFlowFilter& limits)
{
    m_limits = limits;

    m_lowerAmountLimitSpinBox->setRange(limits.lowerAmountLimit, limits.upperAmountLimit);
    m_upperAmountLimitSpinBox->setRange(limits.lowerAmountLimit, limits.upperAmountLimit);

    m_firstDateEdit->setDateRange(limits.firstDate, limits.lastDate);
    m_lastDateEdit->setDateRange(limits.firstDate, limits.lastDate);
}

void CashFlowFilterWidget::onApplied()
{
    m_filter.income = m_incomeCheckBox->isChecked();
    m_filter.expense = m_expenseCheckBox->isChecked();

    m_filter.lowerAmountLimit = m_lowerAmountLimitSpinBox->value();
    m_filter.upperAmountLimit = m_upperAmountLimitSpinBox->value();

    m_filter.firstDate = m_firstDateEdit->date();
    m_filter.lastDate = m_lastDateEdit->date();

    emit applied();
}

void CashFlowFilterWidget::onReset()
{
    m_allTimeButton->setChecked(true);

    emit reset();
}
