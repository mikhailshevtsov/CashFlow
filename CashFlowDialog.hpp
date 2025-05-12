#ifndef CASHFLOWDIALOG_HPP
#define CASHFLOWDIALOG_HPP

#include "CashFlow.hpp"

#include <QDialog>
class QRadioButton;
class QDoubleSpinBox;
class QLineEdit;

class CashFlowDialog : public QDialog
{
    Q_OBJECT

public:
    enum class Mode { Add, Edit };

    CashFlowDialog(QWidget* parent = nullptr, Mode mode = Mode::Add, const CashFlow& cashFlow = {});

    Mode mode() const noexcept;
    const CashFlow& cashFlow() const noexcept;

public slots:
    void set(Mode mode = Mode::Add, const CashFlow& cashFlow = {});

private slots:
    void onAccepted();

private:
    QRadioButton* m_incomeButton{};
    QRadioButton* m_expenseButton{};

    QDoubleSpinBox* m_amountInputWidget{};
    QLineEdit* m_descriptionInputWidget{};

    Mode m_mode = Mode::Add;
    CashFlow m_cashFlow;
};

#endif // CASHFLOWDIALOG_HPP
