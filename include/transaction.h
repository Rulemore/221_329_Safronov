#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <QByteArray>
#include <QCryptographicHash>
#include <QDebug>
#include <QString>
#include <QStringList>

struct Transaction {
  Transaction();
  Transaction(const QString &text);

  QString value;     // Сумма транзакции (7 цифр)
  QString walletId;  // Номер кошелька (6 цифр)
  QString date;  // Дата в формате YYYY.mm.dd_HH:MM:SS (19 символов)
  QString hash;  // Хеш транзакции (SHA-256)

  // Метод для получения строкового представления транзакции
  QString toString() const;

  // Метод для проверки корректности хеша транзакции
  bool validateHash(QByteArray previousHash);
};
#endif  // TRANSACTION_H
