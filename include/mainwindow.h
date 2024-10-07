#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <addtransactiondialog.h>
#include <openssl/evp.h>
#include <transaction.h>
#include <openssl/aes.h>

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
const QByteArray KEY =
    "94b362469d7e670e52221841c895b7ac130940e50fa8de825c6a8ab0654e134";  // 32 байта (AES-256)
const QByteArray IV_CBC = "1234567812345678";

// Объявление пространства имен для пользовательского интерфейса
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  // Метод для получения хеша транзакции
  int getHash(QByteArray &hash);

  // Метод для добавления новой транзакции
  void addTransaction(const QString &value, const QString &walletId,
                      const QString &date);

  // Метод для проверки валидности транзакции
  bool isValidTransaction(const QString &value, const QString &walletId,
                          const QString &date);

  // Метод для сохранения транзакций в файл
  void saveToFile();

  // Метод для отображения списка транзакций
  void displayTransactions();

  QByteArray encryptData(const QByteArray &data);

  QByteArray decryptData(const QByteArray &data);

  // Указатель на пользовательский интерфейс
  Ui::MainWindow *ui;

  // Вектор для хранения транзакций
  QVector<Transaction> transactions;

  // Флаг, указывающий, было ли это первое открытие файла
  bool firstOpen = true;

 private slots:
  // Слот, обрабатывающий нажатие на кнопку "Добавить"
  void onAddButtonClicked();

  // Метод для загрузки данных из файла
  void loadFile();
};

#endif  // MAINWINDOW_H
