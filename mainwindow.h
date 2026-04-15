#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "LinkedList.h"
#include "logindialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor menerima peran pengguna yang sudah login
    MainWindow(Peran peran, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnTambah_clicked();
    void on_btnHapus_clicked();
    void on_btnEdit_clicked();
    void on_btnCari_clicked();
    void on_btnTampilSemua_clicked();
    void on_btnBersihkanForm_clicked();
    void on_btnLogout_clicked();
    void on_tableWidget_itemClicked();

private:
    Ui::MainWindow *ui;
    LinkedList* daftarPlaybook;
    Peran peranAktif;  // Simpan peran yang sedang login

    void tampilkanData(QList<Playbook> list);
    void bersihkanForm();
    bool validasiInput();

    // Atur tampilan sesuai peran (admin/user)
    void aturTampilanPeran();
};

#endif // MAINWINDOW_H
