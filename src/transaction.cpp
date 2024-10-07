#include "transaction.h"

Transaction::Transaction() : value(""), walletId(""), date(""), hash("") {}

Transaction::Transaction(const QString &text) {
  QStringList fields = text.split(' ');
  if (fields.size() == 4) {
    value = fields[0].trimmed();
    walletId = fields[1].trimmed();
    date = fields[2].trimmed();
    hash = fields[3].trimmed();
  } else {
    value = "";
    walletId = "";
    date = "";
    hash = "";
  }
}

QString Transaction::toString() const { return value + walletId + date; }

bool Transaction::validateHash(QByteArray previousHash) {
  QByteArray thisHash = QCryptographicHash::hash(
      this->toString().toUtf8() + previousHash, QCryptographicHash::Sha256);
  previousHash = thisHash.toHex();
  qDebug() << hash + " || " + thisHash.toHex();

  if (thisHash.toHex() != hash) return false;
  return true;
}
