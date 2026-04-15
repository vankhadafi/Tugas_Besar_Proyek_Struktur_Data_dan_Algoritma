# Sistem Informasi Playbook Sepak Bola
Sistem Informasi Playbook Sepak Bola adalah aplikasi desktop berbasis **C++** dan **Qt** yang dikembangkan sebagai tugas besar praktikum **PSDA (Pemrograman Struktur Data dan Algoritma)** oleh **Kelompok 5**. Framework Qt mendukung pengembangan aplikasi lintas platform dengan C++ dan umum digunakan untuk membangun antarmuka GUI desktop [web:3][web:5].

## Deskripsi Proyek
Aplikasi ini dirancang untuk membantu pengguna dalam mengelola data playbook sepak bola secara terstruktur, mulai dari menambahkan, menampilkan, mencari, mengubah, hingga menghapus data strategi permainan. Proyek ini juga menjadi implementasi konsep struktur data dan algoritma dalam konteks aplikasi desktop akademik.

## Fitur Utama
- Menambahkan data playbook sepak bola.
- Menampilkan daftar playbook yang tersimpan.
- Mencari data playbook berdasarkan kata kunci tertentu.
- Mengedit informasi playbook.
- Menghapus data playbook.
- Menyediakan antarmuka GUI interaktif menggunakan Qt.
- Mengimplementasikan konsep struktur data dalam pengelolaan data.

## Teknologi yang Digunakan
- **C++** sebagai bahasa pemrograman utama.
- **Qt Framework** untuk pengembangan antarmuka dan aplikasi desktop [web:3][web:5].
- **Qt Creator** sebagai IDE pengembangan.

## Tujuan Proyek
Proyek ini dibuat untuk:
- Memenuhi tugas besar praktikum mata kuliah **PSDA**.
- Menerapkan konsep struktur data dan algoritma dalam program nyata.
- Melatih pembuatan aplikasi desktop berbasis GUI dengan Qt.
- Mengembangkan sistem informasi sederhana bertema playbook sepak bola.

## Struktur Proyek
```bash
Playbook-Sepak-Bola/
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
├── logindialog.ui
├── logindialog.h
├── logindialog.cpp
├── Node.h
├── linkedlist.h
├── linkedlist.cpp
├── PlaybookSepakBola.pro
├── assets/
├── data/
└── README.md
```

## Cara Menjalankan
1. Clone repository ini.
2. Buka project menggunakan **Qt Creator**.
3. Pastikan **Qt kit** dan compiler **C++** sudah terpasang.
4. Build project.
5. Jalankan aplikasi melalui Qt Creator.

## Cara Penggunaan
1. Jalankan aplikasi.
2. Pilih menu atau tombol pada antarmuka utama.
3. Tambahkan data playbook sesuai kebutuhan.
4. Gunakan fitur pencarian untuk menemukan data tertentu.
5. Edit atau hapus data jika diperlukan.

## Konsep PSDA yang Diimplementasikan
- Struktur data dasar untuk penyimpanan data.
- Algoritma pencarian untuk menemukan playbook.
- Pengelolaan data pada aplikasi desktop.
- Integrasi logika program dengan GUI.

## Anggota Kelompok 5
- Muhammad Farel Audrico A (G1A025077)
- Muhammad Rikza Zalfanara (G1A025058)
- Ivan Khadafi (G1A025088)
- Muhammad Rifqi Pratama (G1A025096)

## Pengembangan Lanjutan
Beberapa pengembangan yang dapat dilakukan:
- Menambahkan database seperti SQLite.
- Menambahkan autentikasi pengguna.
- Menyimpan data secara permanen.
- Memperbaiki tampilan antarmuka.
- Menambahkan visualisasi formasi dan strategi.

## Lisensi
Proyek ini dibuat untuk keperluan akademik dan pembelajaran.