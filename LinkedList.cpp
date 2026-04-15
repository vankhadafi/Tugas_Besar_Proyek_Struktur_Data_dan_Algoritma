#include "LinkedList.h"

// Constructor: inisialisasi linked list kosong
LinkedList::LinkedList() {
    head = nullptr;
    jumlah = 0;
}

// Destructor: hapus semua node dari memori
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* berikut = current->next;
        delete current;
        current = berikut;
    }
}

// Tambah playbook baru di akhir linked list
void LinkedList::tambah(Playbook p) {
    Node* baru = new Node(p);  // Buat node baru

    if (head == nullptr) {
        // Jika list masih kosong, node baru jadi head
        head = baru;
    } else {
        // Cari node terakhir lalu sambungkan
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = baru;
    }
    jumlah++;
}

// Hapus node berdasarkan nama playbook
bool LinkedList::hapus(QString nama) {
    if (head == nullptr) return false;  // List kosong

    // Kalau node pertama yang mau dihapus
    if (head->data.nama == nama) {
        Node* hapusan = head;
        head = head->next;
        delete hapusan;
        jumlah--;
        return true;
    }

    // Cari node sebelum yang mau dihapus
    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->data.nama == nama) {
            Node* hapusan = current->next;
            current->next = hapusan->next;
            delete hapusan;
            jumlah--;
            return true;
        }
        current = current->next;
    }

    return false;  // Nama tidak ditemukan
}

// Edit data playbook berdasarkan nama lama
bool LinkedList::edit(QString namaLama, Playbook baru) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.nama == namaLama) {
            current->data = baru;  // Ganti data lama dengan data baru
            return true;
        }
        current = current->next;
    }
    return false;  // Tidak ditemukan
}

// Cari playbook berdasarkan keyword (nama atau strategi)
QList<Playbook> LinkedList::cari(QString keyword) {
    QList<Playbook> hasil;
    Node* current = head;

    // Ubah keyword ke huruf kecil agar pencarian tidak case-sensitive
    QString kw = keyword.toLower();

    while (current != nullptr) {
        bool cocok = current->data.nama.toLower().contains(kw) ||
                     current->data.strategi.toLower().contains(kw) ||
                     current->data.formasi.toLower().contains(kw);
        if (cocok) {
            hasil.append(current->data);
        }
        current = current->next;
    }
    return hasil;
}

// Ambil semua data playbook dalam bentuk QList
QList<Playbook> LinkedList::semua() {
    QList<Playbook> hasil;
    Node* current = head;
    while (current != nullptr) {
        hasil.append(current->data);
        current = current->next;
    }
    return hasil;
}

// Cek apakah nama playbook sudah ada (mencegah duplikat)
bool LinkedList::sudahAda(QString nama) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.nama.toLower() == nama.toLower()) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Kembalikan jumlah data yang tersimpan
int LinkedList::getJumlah() {
    return jumlah;
}
