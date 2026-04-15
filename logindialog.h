#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

// Enum untuk jenis peran pengguna
enum class Peran {
    Admin,  // Bisa tambah, edit, hapus
    User    // Hanya bisa lihat dan cari
};

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    // Ambil peran yang berhasil login
    Peran getPeran() const;

private slots:
    void on_btnLogin_clicked();
    void on_btnBatal_clicked();

    // Slot ketika pilihan role di combo berubah
    void on_cmbRole_currentIndexChanged(int index);

private:
    Ui::LoginDialog *ui;
    Peran peranLogin;  // Menyimpan hasil peran setelah login berhasil
};

#endif // LOGINDIALOG_H
