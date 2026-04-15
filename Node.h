#ifndef NODE_H
#define NODE_H

#include <QString>

// Struktur data untuk satu playbook
struct Playbook {
    QString nama;       // Nama playbook
    QString strategi;   // Jenis strategi (Menyerang, Bertahan, dll)
    QString formasi;    // Formasi tim (4-3-3, 4-4-2, dll)
    QString deskripsi;  // Deskripsi singkat
};

// Node untuk linked list
struct Node {
    Playbook data;   // Data playbook yang disimpan
    Node* next;      // Pointer ke node berikutnya

    // Constructor untuk memudahkan pembuatan node baru
    Node(Playbook p) {
        data = p;
        next = nullptr;
    }
};

#endif // NODE_H
