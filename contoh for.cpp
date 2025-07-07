#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Produk {
    char kode[10];
    char nama[30];
    int harga;
    int stok;
};

Produk data[100];
int jumlahData = 0;

// Membaca data dari file
void bacaFile() {
    ifstream file("produk.txt");
    if (file.is_open()) {
        file >> jumlahData;
        for (int i = 0; i < jumlahData; i++) {
            file >> data[i].kode >> data[i].nama >> data[i].harga >> data[i].stok;
        }
        file.close();
    }
}

// Menyimpan data ke file
void simpanFile() {
    ofstream file("produk.txt");
    file << jumlahData << endl;
    for (int i = 0; i < jumlahData; i++) {
        file << data[i].kode << " " << data[i].nama << " " << data[i].harga << " " << data[i].stok << endl;
    }
    file.close();
}

// Menampilkan laporan
void tampilkanLaporan() {
    cout << "\n=== LAPORAN DATA PRODUK ===\n";
    cout << "Kode\tNama\t\tHarga\tStok\n";
    for (int i = 0; i < jumlahData; i++) {
        cout << data[i].kode << "\t" << data[i].nama << "\t\t" << data[i].harga << "\t" << data[i].stok << endl;
    }
}

// Menambahkan data
void tambahProduk() {
    cout << "Masukkan kode: "; cin >> data[jumlahData].kode;
    cout << "Masukkan nama: "; cin >> data[jumlahData].nama;
    cout << "Masukkan harga: "; cin >> data[jumlahData].harga;
    cout << "Masukkan stok: "; cin >> data[jumlahData].stok;
    jumlahData++;
    simpanFile();
    cout << "Produk berhasil ditambahkan!\n";
}

// Sorting berdasarkan nama
void sortingProduk() {
    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if (strcmp(data[j].nama, data[j + 1].nama) > 0) {
                Produk temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
    cout << "Data berhasil diurutkan berdasarkan nama.\n";
    simpanFile();
}

// Searching by kode
int cariProduk(const char kodeCari[]) {
    for (int i = 0; i < jumlahData; i++) {
        if (strcmp(data[i].kode, kodeCari) == 0) {
            return i;
        }
    }
    return -1;
}

// Update produk
void updateProduk() {
    char kodeCari[10];
    cout << "Masukkan kode produk yang ingin diupdate: ";
    cin >> kodeCari;
    int idx = cariProduk(kodeCari);
    if (idx != -1) {
        cout << "Data lama: " << data[idx].nama << " - " << data[idx].harga << " - " << data[idx].stok << endl;
        cout << "Masukkan harga baru: "; cin >> data[idx].harga;
        cout << "Masukkan stok baru: "; cin >> data[idx].stok;
        simpanFile();
        cout << "Produk berhasil diupdate.\n";
    } else {
        cout << "Produk tidak ditemukan.\n";
    }
}

// Hapus produk
void hapusProduk() {
    char kodeCari[10];
    cout << "Masukkan kode produk yang ingin dihapus: ";
    cin >> kodeCari;
    int idx = cariProduk(kodeCari);
    if (idx != -1) {
        for (int i = idx; i < jumlahData - 1; i++) {
            data[i] = data[i + 1];
        }
        jumlahData--;
        simpanFile();
        cout << "Produk berhasil dihapus.\n";
    } else {
        cout << "Produk tidak ditemukan.\n";
    }
}

int main() {
    bacaFile();
    int pilihan;
    do {
        cout << "\n=== MENU SUPERMARKET ===\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Tampilkan Laporan\n";
        cout << "3. Sorting Berdasarkan Nama\n";
        cout << "4. Update Produk\n";
        cout << "5. Hapus Produk\n";
        cout << "6. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahProduk(); break;
            case 2: tampilkanLaporan(); break;
            case 3: sortingProduk(); break;
            case 4: updateProduk(); break;
            case 5: hapusProduk(); break;
            case 6: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}
