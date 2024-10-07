#ifndef ADDTRANSACTIONDIALOG_H
#define ADDTRANSACTIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class AddTransactionDialog : public QDialog {
  Q_OBJECT

 public:
  explicit AddTransactionDialog(QWidget *parent = nullptr);

  QString getValue() const;
  QString getWalletId() const;
  QString getDate() const;

 private:
  QLineEdit *valueInput;
  QLineEdit *walletIdInput;
  QLineEdit *dateInput;
  QPushButton *saveButton;
  QPushButton *cancelButton;

 private slots:
  void onSave();
};

#endif  // ADDTRANSACTIONDIALOG_H
