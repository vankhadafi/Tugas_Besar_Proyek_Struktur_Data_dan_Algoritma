#include "mainwindow.h"
#include "ui_mainwindow.h"

// Constructor menerima peran login dari main.cpp
MainWindow::MainWindow(Peran peran, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    peranAktif = peran;
    daftarPlaybook = new LinkedList();

    // Lebar kolom tabel
    ui->tableWidget->setColumnWidth(0, 155);
    ui->tableWidget->setColumnWidth(1, 105);
    ui->tableWidget->setColumnWidth(2, 80);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Hubungkan klik tabel ke slot
    connect(ui->tableWidget, &QTableWidget::itemClicked,
            this, &MainWindow::on_tableWidget_itemClicked);

    ui->lblJumlah->setText("Total Playbook: 0");

    // Pilihan strategi
    ui->cmbStrategi->addItem("-- Pilih Strategi --");
    ui->cmbStrategi->addItem("Menyerang");
    ui->cmbStrategi->addItem("Bertahan");
    ui->cmbStrategi->addItem("Pressing");
    ui->cmbStrategi->addItem("Counter Attack");
    ui->cmbStrategi->addItem("Possession");
    ui->cmbStrategi->addItem("Tiki-taka");

    // Pilihan formasi
    ui->cmbFormasi->addItem("-- Pilih Formasi --");
    ui->cmbFormasi->addItem("4-3-3");
    ui->cmbFormasi->addItem("4-4-2");
    ui->cmbFormasi->addItem("4-2-3-1");
    ui->cmbFormasi->addItem("3-5-2");
    ui->cmbFormasi->addItem("5-3-2");
    ui->cmbFormasi->addItem("3-4-3");
    ui->cmbFormasi->addItem("4-1-4-1");

    // Atur tampilan sesuai peran
    aturTampilanPeran();
}

MainWindow::~MainWindow()
{
    delete daftarPlaybook;
    delete ui;
}

// Atur tampilan berdasarkan peran yang login
void MainWindow::aturTampilanPeran()
{
    if (peranAktif == Peran::Admin) {
        // Admin: semua fitur aktif
        setWindowTitle("Sistem Informasi Playbook Sepak Bola  [LOGIN SEBAGAI: ADMIN]");
        ui->lblPeran->setText("Login sebagai: ADMIN");
        ui->lblPeran->setStyleSheet("font-weight: bold; color: white; "
                                    "background-color: #1a5276; padding: 4px; border-radius: 3px;");

        // Aktifkan semua tombol edit
        ui->btnTambah->setEnabled(true);
        ui->btnEdit->setEnabled(true);
        ui->btnHapus->setEnabled(true);
        ui->btnBersihkanForm->setEnabled(true);

        // Form input bisa diisi
        ui->txtNama->setEnabled(true);
        ui->cmbStrategi->setEnabled(true);
        ui->cmbFormasi->setEnabled(true);
        ui->txtDeskripsi->setEnabled(true);

        ui->grpForm->setTitle("Form Input Playbook (Akses Penuh - Admin)");

    } else {
        // User: hanya bisa lihat dan cari
        setWindowTitle("Sistem Informasi Playbook Sepak Bola  [LOGIN SEBAGAI: USER]");
        ui->lblPeran->setText("Login sebagai: USER  (hanya bisa melihat & mencari)");
        ui->lblPeran->setStyleSheet("font-weight: bold; color: white; "
                                    "background-color: #117a65; padding: 4px; border-radius: 3px;");

        // Nonaktifkan semua tombol ubah data
        ui->btnTambah->setEnabled(false);
        ui->btnEdit->setEnabled(false);
        ui->btnHapus->setEnabled(false);
        ui->btnBersihkanForm->setEnabled(false);

        // Form input tidak bisa diisi
        ui->txtNama->setEnabled(false);
        ui->cmbStrategi->setEnabled(false);
        ui->cmbFormasi->setEnabled(false);
        ui->txtDeskripsi->setEnabled(false);

        ui->grpForm->setTitle("Info Playbook (Hanya Lihat - User)");
    }
}

// ==================== TOMBOL TAMBAH ====================
void MainWindow::on_btnTambah_clicked()
{
    if (!validasiInput()) return;

    QString nama = ui->txtNama->text().trimmed();

    if (daftarPlaybook->sudahAda(nama)) {
        QMessageBox::warning(this, "Duplikat",
                             "Nama playbook '" + nama + "' sudah ada!\nGunakan nama yang berbeda.");
        return;
    }

    Playbook p;
    p.nama      = nama;
    p.strategi  = ui->cmbStrategi->currentText();
    p.formasi   = ui->cmbFormasi->currentText();
    p.deskripsi = ui->txtDeskripsi->toPlainText().trimmed();

    daftarPlaybook->tambah(p);
    tampilkanData(daftarPlaybook->semua());
    bersihkanForm();

    QMessageBox::information(this, "Berhasil", "Playbook berhasil ditambahkan!");
}

// ==================== TOMBOL HAPUS ====================
void MainWindow::on_btnHapus_clicked()
{
    QString nama = ui->txtNama->text().trimmed();

    if (nama.isEmpty()) {
        QMessageBox::warning(this, "Perhatian",
                             "Pilih dulu playbook yang ingin dihapus\n(klik baris di tabel).");
        return;
    }

    int konfirmasi = QMessageBox::question(this, "Konfirmasi Hapus",
                                           "Yakin ingin menghapus playbook '" + nama + "'?",
                                           QMessageBox::Yes | QMessageBox::No);
    if (konfirmasi == QMessageBox::No) return;

    if (daftarPlaybook->hapus(nama)) {
        tampilkanData(daftarPlaybook->semua());
        bersihkanForm();
        QMessageBox::information(this, "Berhasil", "Playbook berhasil dihapus!");
    } else {
        QMessageBox::warning(this, "Gagal", "Playbook tidak ditemukan!");
    }
}

// ==================== TOMBOL EDIT ====================
void MainWindow::on_btnEdit_clicked()
{
    QString namaLama = ui->txtNamaAsli->text();

    if (namaLama.isEmpty()) {
        QMessageBox::warning(this, "Perhatian",
                             "Pilih dulu playbook yang ingin diedit\n(klik baris di tabel).");
        return;
    }

    if (!validasiInput()) return;

    Playbook baru;
    baru.nama      = ui->txtNama->text().trimmed();
    baru.strategi  = ui->cmbStrategi->currentText();
    baru.formasi   = ui->cmbFormasi->currentText();
    baru.deskripsi = ui->txtDeskripsi->toPlainText().trimmed();

    if (baru.nama != namaLama && daftarPlaybook->sudahAda(baru.nama)) {
        QMessageBox::warning(this, "Duplikat",
                             "Nama '" + baru.nama + "' sudah digunakan playbook lain!");
        return;
    }

    if (daftarPlaybook->edit(namaLama, baru)) {
        tampilkanData(daftarPlaybook->semua());
        bersihkanForm();
        QMessageBox::information(this, "Berhasil", "Playbook berhasil diperbarui!");
    } else {
        QMessageBox::warning(this, "Gagal", "Playbook tidak ditemukan!");
    }
}

// ==================== TOMBOL CARI ====================
void MainWindow::on_btnCari_clicked()
{
    QString keyword = ui->txtCari->text().trimmed();

    if (keyword.isEmpty()) {
        QMessageBox::warning(this, "Perhatian", "Masukkan kata kunci pencarian terlebih dahulu.");
        return;
    }

    QList<Playbook> hasil = daftarPlaybook->cari(keyword);

    if (hasil.isEmpty()) {
        QMessageBox::information(this, "Hasil Pencarian",
                                 "Tidak ada playbook yang cocok dengan '" + keyword + "'.");
        tampilkanData(daftarPlaybook->semua());
    } else {
        tampilkanData(hasil);
        ui->lblJumlah->setText("Ditemukan: " + QString::number(hasil.size()) + " playbook");
    }
}

// ==================== TOMBOL TAMPIL SEMUA ====================
void MainWindow::on_btnTampilSemua_clicked()
{
    ui->txtCari->clear();
    tampilkanData(daftarPlaybook->semua());

    if (daftarPlaybook->getJumlah() == 0) {
        QMessageBox::information(this, "Info", "Belum ada data playbook yang tersimpan.");
    }
}

// ==================== TOMBOL BERSIHKAN FORM ====================
void MainWindow::on_btnBersihkanForm_clicked()
{
    bersihkanForm();
}

// ==================== TOMBOL LOGOUT ====================
void MainWindow::on_btnLogout_clicked()
{
    int konfirmasi = QMessageBox::question(this, "Logout",
                                           "Yakin ingin logout?\nAnda akan kembali ke halaman login.",
                                           QMessageBox::Yes | QMessageBox::No);
    if (konfirmasi == QMessageBox::No) return;

    // Tutup jendela utama, lalu buka login dialog lagi
    this->close();

    // Buka kembali login
    LoginDialog loginDlg;
    if (loginDlg.exec() == QDialog::Accepted) {
        Peran peranBaru = loginDlg.getPeran();
        MainWindow* mainWin = new MainWindow(peranBaru);
        mainWin->show();
    } else {
        // Jika batal login, keluar dari aplikasi
        QApplication::quit();
    }
}

// ==================== KLIK BARIS DI TABEL ====================
void MainWindow::on_tableWidget_itemClicked()
{
    int baris = ui->tableWidget->currentRow();
    if (baris < 0) return;

    QString nama      = ui->tableWidget->item(baris, 0)->text();
    QString strategi  = ui->tableWidget->item(baris, 1)->text();
    QString formasi   = ui->tableWidget->item(baris, 2)->text();
    QString deskripsi = ui->tableWidget->item(baris, 3)->text();

    // Isi form (untuk admin bisa diedit, untuk user hanya tampil)
    ui->txtNama->setText(nama);
    ui->txtNamaAsli->setText(nama);
    ui->txtDeskripsi->setPlainText(deskripsi);

    int idxStrategi = ui->cmbStrategi->findText(strategi);
    if (idxStrategi >= 0) ui->cmbStrategi->setCurrentIndex(idxStrategi);

    int idxFormasi = ui->cmbFormasi->findText(formasi);
    if (idxFormasi >= 0) ui->cmbFormasi->setCurrentIndex(idxFormasi);
}

// ==================== FUNGSI BANTU ====================

void MainWindow::tampilkanData(QList<Playbook> list)
{
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < list.size(); i++) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(list[i].nama));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(list[i].strategi));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(list[i].formasi));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(list[i].deskripsi));
    }

    ui->lblJumlah->setText("Total Playbook: " + QString::number(daftarPlaybook->getJumlah()));
}

void MainWindow::bersihkanForm()
{
    ui->txtNama->clear();
    ui->txtNamaAsli->clear();
    ui->txtDeskripsi->clear();
    ui->cmbStrategi->setCurrentIndex(0);
    ui->cmbFormasi->setCurrentIndex(0);
    ui->tableWidget->clearSelection();
}

bool MainWindow::validasiInput()
{
    if (ui->txtNama->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validasi", "Nama playbook tidak boleh kosong!");
        ui->txtNama->setFocus();
        return false;
    }

    if (ui->cmbStrategi->currentIndex() == 0) {
        QMessageBox::warning(this, "Validasi", "Silakan pilih jenis strategi!");
        return false;
    }

    if (ui->cmbFormasi->currentIndex() == 0) {
        QMessageBox::warning(this, "Validasi", "Silakan pilih formasi tim!");
        return false;
    }

    if (ui->txtDeskripsi->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validasi", "Deskripsi tidak boleh kosong!");
        ui->txtDeskripsi->setFocus();
        return false;
    }

    return true;
}
