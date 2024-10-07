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

  QString value;
  QString walletId;
  QString date;
  QString hash;

  QString toString() const;
  bool validateHash(QByteArray previousHash);
};
#endif  // TRANSACTION_H

