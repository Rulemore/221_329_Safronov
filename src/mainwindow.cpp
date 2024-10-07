#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QString>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->stackedWidget->setCurrentIndex(1);
  ui->plainTextEdit->setReadOnly(true);
  state = State::Unauthorized;

  connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::loadFile);
  connect(ui->addButton, &QPushButton::clicked, this,
          &MainWindow::onAddButtonClicked);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loadFile() {
  QString fileName;
  if (!firstOpen) {
    fileName =
        QFileDialog::getOpenFileName(this, "Загрузить транзакции", "",
                                     "CSV Files (*.csv);;Text Files (*.txt)");
    if (fileName.isEmpty()) {
      return;
    }
  } else {
    fileName = DATA_FILE_PATH;
    firstOpen = false;
  }

  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
    return;
  }

  QTextStream in(&file);
  transactions.clear();
  while (!in.atEnd()) {
    QString line = in.readLine();
    if (!line.isEmpty()) {
      QStringList fields = line.split(',');
      if (fields.size() == 4) {
        QString value = fields[0].trimmed();
        QString walletId = fields[1].trimmed();
        QString date = fields[2].trimmed();
        QString hash = fields[3].trimmed();

        Transaction transaction;
        transaction.value = value;
        transaction.walletId = walletId;
        transaction.date = date;
        transaction.hash = hash;

        transactions.append(transaction);
      } else {
        qDebug() << "Неверный формат строки: " << line;
      }
    }
  }
  file.close();
  displayTransactions();
}

void MainWindow::displayTransactions() {
  ui->plainTextEdit->clear();
  for (const Transaction &e : transactions) {
    ui->plainTextEdit->appendPlainText(e.value + "," + e.walletId + "," +
                                       e.date + "," + e.hash);
  }
}

void MainWindow::onAddButtonClicked() {
  AddTransactionDialog dialog(this);

  if (dialog.exec() == QDialog::Accepted) {
    QString value = dialog.getValue();
    QString walletId = dialog.getWalletId();
    QString date = dialog.getDate();

    addTransaction(value, walletId, date);
  }
}

void MainWindow::addTransaction(const QString &value, const QString &walletId,
                                const QString &date) {
  if (!isValidTransaction(value, walletId, date)) {
    QMessageBox::warning(this, "Ошибка", "Некорректные данные транзакции.");
    return;
  }

  QByteArray previousHash =
      (transactions.isEmpty() ? QByteArray()
                              : transactions.last().hash.toUtf8());
  QString hash =
      QString(QCryptographicHash::hash(value.toUtf8() + walletId.toUtf8() +
                                           date.toUtf8() + previousHash,
                                       QCryptographicHash::Sha256)
                  .toHex());

  Transaction newTrx;
  newTrx.value = value;
  newTrx.walletId = walletId;
  newTrx.date = date;
  newTrx.hash = hash;

  transactions.append(newTrx);
  displayTransactions();
  saveToFile();
}

bool MainWindow::isValidTransaction(const QString &value,
                                    const QString &walletId,
                                    const QString &date) {
  return (value.length() == 7 && value.toInt() >= 0) &&
         (walletId.length() == 6 && walletId.toInt() >= 0) &&
         (date.length() == 19);
}

void MainWindow::saveToFile() {
  QFile file("transactions.csv");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
    return;
  }

  QTextStream out(&file);
  for (const Transaction &e : transactions) {
    out << e.value << "," << e.walletId << "," << e.date << "," << e.hash
        << "\n";
  }
  file.close();
}
