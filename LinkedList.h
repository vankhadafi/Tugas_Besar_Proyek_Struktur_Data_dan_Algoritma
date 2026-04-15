#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <QList>

// Kelas LinkedList untuk mengelola semua data playbook
class LinkedList {
private:
    Node* head;  // Pointer ke node pertama
    int jumlah;  // Menyimpan jumlah node

public:
    LinkedList();
    ~LinkedList();

    // Tambah playbook baru di akhir list
    void tambah(Playbook p);

    // Hapus playbook berdasarkan nama
    bool hapus(QString nama);

    // Edit playbook berdasarkan nama lama
    bool edit(QString namaLama, Playbook baru);

    // Cari playbook berdasarkan nama atau strategi
    QList<Playbook> cari(QString keyword);

    // Ambil semua data playbook
    QList<Playbook> semua();

    // Cek apakah nama sudah ada (untuk validasi duplikat)
    bool sudahAda(QString nama);

    // Ambil jumlah data
    int getJumlah();
};

#endif // LINKEDLIST_H
