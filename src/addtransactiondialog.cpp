#include "addtransactiondialog.h"

#include <QLabel>
#include <QMessageBox>

AddTransactionDialog::AddTransactionDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle("Добавить транзакцию");

  valueInput = new QLineEdit(this);
  walletIdInput = new QLineEdit(this);
  dateInput = new QLineEdit(this);

  valueInput->setPlaceholderText("Сумма (7 цифр)");
  walletIdInput->setPlaceholderText("Номер кошелька (6 цифр)");
  dateInput->setPlaceholderText("Дата (YYYY.mm.dd_HH:MM:SS)");

  saveButton = new QPushButton("Сохранить", this);
  cancelButton = new QPushButton("Отмена", this);

  connect(saveButton, &QPushButton::clicked, this,
          &AddTransactionDialog::onSave);
  connect(cancelButton, &QPushButton::clicked, this,
          &AddTransactionDialog::reject);

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(new QLabel("Сумма:"));
  layout->addWidget(valueInput);
  layout->addWidget(new QLabel("Номер кошелька:"));
  layout->addWidget(walletIdInput);
  layout->addWidget(new QLabel("Дата:"));
  layout->addWidget(dateInput);
  layout->addWidget(saveButton);
  layout->addWidget(cancelButton);

  setLayout(layout);
}

QString AddTransactionDialog::getValue() const { return valueInput->text(); }

QString AddTransactionDialog::getWalletId() const {
  return walletIdInput->text();
}

QString AddTransactionDialog::getDate() const { return dateInput->text(); }

void AddTransactionDialog::onSave() {
  if (valueInput->text().isEmpty() || walletIdInput->text().isEmpty() ||
      dateInput->text().isEmpty()) {
    QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
    return;
  }

  accept();
}
