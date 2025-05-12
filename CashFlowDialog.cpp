#include "CashFlowDialog.hpp"

#include <QFormLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QDialogButtonBox>

CashFlowDialog::CashFlowDialog(QWidget* parent, Mode mode, const CashFlow& cashFlow)
    : QDialog(parent)
{
    // Setup type input widget
    QGroupBox* typeInputWidget = new QGroupBox;
    m_incomeButton = new QRadioButton(tr("Income"));
    m_expenseButton = new QRadioButton(tr("Expense"));

    QHBoxLayout* typeInputWidgetLayout = new QHBoxLayout;
    typeInputWidgetLayout->addWidget(m_incomeButton);
    typeInputWidgetLayout->addWidget(m_expenseButton);
    typeInputWidget->setLayout(typeInputWidgetLayout);

    QButtonGroup* typeButtons = new QButtonGroup(this);
    typeButtons->addButton(m_incomeButton);
    typeButtons->addButton(m_expenseButton);


    // Setup amount input widget
    m_amountInputWidget = new QDoubleSpinBox;
    m_amountInputWidget->setMinimum(0);
    m_amountInputWidget->setMaximum(1'000'000'000'000);


    // Setup description input widget
    m_descriptionInputWidget = new QLineEdit;


    // Setup buttons
    QDialogButtonBox* dialogButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);


    // Setup layout
    QFormLayout* layout = new QFormLayout;
    layout->addRow(tr("Type"), typeInputWidget);
    layout->addRow(tr("Amount"), m_amountInputWidget);
    layout->addRow(tr("Description"), m_descriptionInputWidget);
    layout->addWidget(dialogButtons);
    setLayout(layout);

    // Setup state
    set(mode, cashFlow);

    // Setup connections
    connect(dialogButtons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(dialogButtons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(this, &QDialog::accepted, this, &CashFlowDialog::onAccepted);
}

CashFlowDialog::Mode CashFlowDialog::mode() const noexcept
{
    return m_mode;
}

const CashFlow& CashFlowDialog::cashFlow() const noexcept
{
    return m_cashFlow;
}

void CashFlowDialog::set(Mode mode, const CashFlow& cashFlow)
{
    m_mode = mode;
    m_cashFlow = cashFlow;

    m_incomeButton->setChecked(m_cashFlow.type == CashFlow::Type::Income);
    m_expenseButton->setChecked(m_cashFlow.type == CashFlow::Type::Expense);

    m_amountInputWidget->setValue(m_cashFlow.amount);
    m_descriptionInputWidget->setText(m_cashFlow.description);
}


void CashFlowDialog::onAccepted()
{
    if (m_incomeButton->isChecked())
        m_cashFlow.type = CashFlow::Type::Income;
    else
        m_cashFlow.type = CashFlow::Type::Expense;

    m_cashFlow.amount = m_amountInputWidget->value();

    m_cashFlow.description = m_descriptionInputWidget->text();
}
