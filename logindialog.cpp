#include "logindialog.h"
#include "ui_logindialog.h"

// Akun yang tersedia (hardcoded, cocok untuk tugas pemula)
// Admin: username=admin, password=admin123
// User:  username=user,  password=user123

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    peranLogin = Peran::User;  // default

    ui->setupUi(this);

    // Tambahkan pilihan role
    ui->cmbRole->addItem("Admin");
    ui->cmbRole->addItem("User");

    // Sembunyikan password
    ui->txtPassword->setEchoMode(QLineEdit::Password);

    // Tampilkan hint username awal
    ui->lblHint->setText("Username: admin | Password: admin123");

    // Atur tombol Enter bisa langsung login
    ui->txtPassword->setPlaceholderText("Masukkan password...");
    ui->txtUsername->setPlaceholderText("Masukkan username...");

    // Nonaktifkan tombol close (paksa pilih login atau batal)
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

// Kembalikan peran yang sudah login
Peran LoginDialog::getPeran() const
{
    return peranLogin;
}

// Tombol Login ditekan
void LoginDialog::on_btnLogin_clicked()
{
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPassword->text();
    int roleIndex    = ui->cmbRole->currentIndex();  // 0=Admin, 1=User

    // Validasi tidak boleh kosong
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Gagal", "Username dan password tidak boleh kosong!");
        return;
    }

    // Cek kredensial berdasarkan role yang dipilih
    if (roleIndex == 0) {
        // Cek akun Admin
        if (username == "admin" && password == "admin123") {
            peranLogin = Peran::Admin;
            QMessageBox::information(this, "Login Berhasil",
                                     "Selamat datang, Admin!\nAnda memiliki akses penuh.");
            accept();  // Tutup dialog dengan status Accepted
        } else {
            QMessageBox::warning(this, "Login Gagal",
                                 "Username atau password Admin salah!");
            ui->txtPassword->clear();
            ui->txtPassword->setFocus();
        }
    } else {
        // Cek akun User
        if (username == "user" && password == "user123") {
            peranLogin = Peran::User;
            QMessageBox::information(this, "Login Berhasil",
                                     "Selamat datang, User!\nAnda hanya bisa melihat dan mencari data.");
            accept();
        } else {
            QMessageBox::warning(this, "Login Gagal",
                                 "Username atau password User salah!");
            ui->txtPassword->clear();
            ui->txtPassword->setFocus();
        }
    }
}

// Tombol Batal: keluar dari aplikasi
void LoginDialog::on_btnBatal_clicked()
{
    reject();  // Tutup dialog dengan status Rejected
}

// Ketika pilihan role berubah, update hint
void LoginDialog::on_cmbRole_currentIndexChanged(int index)
{
    ui->txtUsername->clear();
    ui->txtPassword->clear();

    if (index == 0) {
        ui->lblHint->setText("Username: admin | Password: admin123");
    } else {
        ui->lblHint->setText("Username: user  | Password: user123");
    }
}
