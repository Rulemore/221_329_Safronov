#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <addtransactiondialog.h>
#include <openssl/evp.h>
#include <transaction.h>

#include <QByteArray>
#include <QClipboard>
#include <QCryptographicHash>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>

const QString DATA_FILE_PATH = "transactions.csv";

namespace Ui {
class MainWindow;
}

enum State { Unauthorized };

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  int getHash(QByteArray &hash);

  void addTransaction(const QString &value, const QString &walletId,
                      const QString &date);
  bool isValidTransaction(const QString &value, const QString &walletId,
                          const QString &date);
  void saveToFile();
  void displayTransactions();

  Ui::MainWindow *ui;
  QVector<Transaction> transactions;
  State state;
  bool firstOpen = true;

 private slots:
  void onAddButtonClicked();
  void loadFile();
};

#endif  // MAINWINDOW_H
