#ifndef ADDTRANSACTIONDIALOG_H
#define ADDTRANSACTIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

// Класс для диалогового окна добавления транзакции
class AddTransactionDialog : public QDialog {
  Q_OBJECT

 public:
  explicit AddTransactionDialog(QWidget *parent = nullptr);

  // Метод для получения значения транзакции
  QString getValue() const;
  // Метод для получения номера кошелька
  QString getWalletId() const;
  // Метод для получения даты транзакции
  QString getDate() const;

 private:
  QLineEdit *valueInput;  // Поле для ввода суммы транзакции
  QLineEdit *walletIdInput;  // Поле для ввода номера кошелька
  QLineEdit *dateInput;  // Поле для ввода даты транзакции
  QPushButton *saveButton;  // Кнопка для сохранения транзакции
  QPushButton *cancelButton;  // Кнопка для отмены добавления транзакции

 private slots:
    // Слот, обрабатывающий нажатие на кнопку "Сохранить"
    void onSave();
};

#endif  // ADDTRANSACTIONDIALOG_H
