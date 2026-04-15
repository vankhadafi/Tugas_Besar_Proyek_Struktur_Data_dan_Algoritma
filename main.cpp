#include <QApplication>
#include "logindialog.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Playbook Sepak Bola");

    // Tampilkan dialog login terlebih dahulu
    LoginDialog loginDlg;

    // Jika user menekan Batal / menutup dialog, keluar dari aplikasi
    if (loginDlg.exec() != QDialog::Accepted) {
        return 0;  // Keluar aplikasi
    }

    // Ambil peran yang sudah login
    Peran peranLogin = loginDlg.getPeran();

    // Buka jendela utama dengan peran yang sesuai
    MainWindow w(peranLogin);
    w.show();

    return a.exec();
}
