#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib> // untuk system("cls") dan system("pause")
using namespace std;

// Struktur data untuk Stasiun Kereta Api
struct Stasiun {
    string nama;
    string kota;
    int jumlahPeron;
    Stasiun* next;
};
// Struktur data untuk Penumpang
struct Penumpang {
    string nama;
    string tujuan;
};
// Struktur data untuk antrean penumpang
 struct NodeAntrean {
    Penumpang data;
    NodeAntrean* next;
};
NodeAntrean* depan = nullptr;
NodeAntrean* belakang = nullptr;
NodeAntrean* topRiwayat = nullptr;

// Pointer untuk antrean penumpang
void tambahAntrean() {
    Penumpang p;
    cout << "Nama Penumpang: ";
    // cin.ignore();
    getline(cin, p.nama);
    cout << "Tujuan: ";
    getline(cin, p.tujuan);

    NodeAntrean* baru = new NodeAntrean{p, nullptr};
    if (!belakang) {
        depan = belakang = baru;
    } else {
        belakang->next = baru;
        belakang = baru;
    }
    cout << "Penumpang berhasil masuk ke antrean.\n";
}
// Fungsi untuk melayani penumpang dari antrean
void layaniPenumpang() {
    if (!depan) {
        cout << "Tidak ada penumpang dalam antrean.\n";
        return;
    }

    NodeAntrean* temp = depan;
    Penumpang p = temp->data;
    depan = depan->next;
    if (!depan) belakang = nullptr;

    NodeAntrean* riwayatBaru = new NodeAntrean{p, topRiwayat};
    topRiwayat = riwayatBaru;

    delete temp;
    cout << "Penumpang " << p.nama << " dengan tujuan " << p.tujuan << " telah dilayani.\n";
}
// Fungsi untuk menampilkan antrean penumpang
void tampilkanAntrean() {
    if (!depan) {
        cout << "Antrean kosong.\n";
        return;
    }
    cout << "Daftar Penumpang Dalam Antrean:\n";
    NodeAntrean* curr = depan;
    int no = 1;
    while (curr) {
        cout << no++ << ". " << curr->data.nama << " -> " << curr->data.tujuan << endl;
        curr = curr->next;
    }
}
// Fungsi untuk menampilkan riwayat penumpang yang telah dilayani
void tampilkanRiwayat() {
    if (!topRiwayat) {
        cout << "Belum ada penumpang yang dilayani.\n";
        return;
    }
    cout << "Riwayat Penumpang Yang Telah Dilayani:\n";
    NodeAntrean* curr = topRiwayat;
    int no = 1;
    while (curr) {
        cout << no++ << ". " << curr->data.nama << " -> " << curr->data.tujuan << endl;
        curr = curr->next;
    }
}
// Fungsi untuk membatalkan antrean penumpang
void batalkanAntreanDepan() {
    if (!depan) {
        cout << "Tidak ada penumpang dalam antrean untuk dibatalkan.\n";
        return;
    }

    NodeAntrean* temp = depan;
    Penumpang p = temp->data;
    depan = depan->next;
    if (!depan) belakang = nullptr;

    delete temp;

    cout << "Penumpang " << p.nama << " dengan tujuan " << p.tujuan << " telah dibatalkan dari antrean.\n";
}
// Fungsi untuk membatalkan antrean penumpang dari belakang
void batalkanAntreanBelakang() {
    if (!depan) {
        cout << "Tidak ada penumpang dalam antrean untuk dibatalkan.\n";
        return;
    }

    if (depan == belakang) {
        // Hanya ada satu penumpang
        cout << "Penumpang " << belakang->data.nama << " dengan tujuan " << belakang->data.tujuan << " telah dibatalkan dari antrean (belakang).\n";
        delete belakang;
        depan = belakang = nullptr;
        return;
    }

    // Lebih dari satu node
    NodeAntrean* curr = depan;
    while (curr->next != belakang) {
        curr = curr->next;
    }

    cout << "Penumpang " << belakang->data.nama << " dengan tujuan " << belakang->data.tujuan << " telah dibatalkan dari antrean (belakang).\n";
    delete belakang;
    belakang = curr;
    belakang->next = nullptr;
}
// Fungsi untuk membuat stasiun baru
Stasiun* buatStasiun(string nama, string kota, int jumlahPeron) {
    Stasiun* stasiunBaru = new Stasiun;
    stasiunBaru->nama = nama;
    stasiunBaru->kota = kota;
    stasiunBaru->jumlahPeron = jumlahPeron;
    stasiunBaru->next = nullptr;
    return stasiunBaru;
}

// Fungsi untuk menambah stasiun di akhir list
void tambahStasiun(Stasiun*& head, string nama, string kota, int jumlahPeron) {
    Stasiun* stasiunBaru = buatStasiun(nama, kota, jumlahPeron);
    if (head == nullptr) {
        head = stasiunBaru;
    } else {
        Stasiun* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = stasiunBaru;
    }
}

// Fungsi untuk menampilkan semua stasiun
void tampilkanStasiun(Stasiun* head) {
    Stasiun* temp = head;
    int idx = 1;
    while (temp != nullptr) {
        cout << "Stasiun ke-" << idx++ << endl;
        cout << "Nama        : " << temp->nama << endl;
        cout << "Kota        : " << temp->kota << endl;
        cout << "Jumlah Peron: " << temp->jumlahPeron << endl;
        cout << "--------------------------" << endl;
        temp = temp->next;
    }
}

// Fungsi untuk mencari stasiun berdasarkan nama
Stasiun* cariStasiun(Stasiun* head, string namaCari) {
    Stasiun* temp = head;
    while (temp != nullptr) {
        if (temp->nama == namaCari) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Fungsi untuk sorting stasiun berdasarkan nama (Bubble Sort pada linked list)
void sortingStasiun(Stasiun*& head) {
    if (!head || !head->next) return;
    bool swapped;
    do {
        swapped = false;
        Stasiun* curr = head;
        while (curr->next != nullptr) {
            if (curr->nama > curr->next->nama) {
                // Swap data
                swap(curr->nama, curr->next->nama);
                swap(curr->kota, curr->next->kota);
                swap(curr->jumlahPeron, curr->next->jumlahPeron);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

// Fungsi untuk menyimpan data ke file (tanpa fstream, gunakan FILE* dari C)
void simpanKeFile(Stasiun* head, const string& filename) {
    FILE* file = fopen(filename.c_str(), "w");
    if (!file) {
        cout << "Gagal membuka file untuk menulis.\n";
        return;
    }
    Stasiun* temp = head;
    while (temp != nullptr) {
        fprintf(file, "%s,%s,%d\n", temp->nama.c_str(), temp->kota.c_str(), temp->jumlahPeron);
        temp = temp->next;
    }
    fclose(file);
    cout << "Data berhasil disimpan ke file.\n";
}

// Fungsi untuk membaca data dari file (tanpa fstream, gunakan FILE* dari C)
void bacaDariFile(Stasiun*& head, const string& filename) {
    FILE* file = fopen(filename.c_str(), "r");
    if (!file) {
        cout << "File tidak ditemukan.\n";
        return;
    }
    char nama[100], kota[100];
    int jumlahPeron;
    while (fscanf(file, "%99[^,],%99[^,],%d\n", nama, kota, &jumlahPeron) == 3) {
        tambahStasiun(head, nama, kota, jumlahPeron);
    }
    fclose(file);
    cout << "Data berhasil dibaca dari file.\n";
}


// Fungsi untuk menghapus semua stasiun (menghindari memory leak)
void hapusSemuaStasiun(Stasiun*& head) {
    while (head != nullptr) {
        Stasiun* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Stasiun* head = nullptr;
    int pilihan;
    string nama, kota;
    int jumlahPeron;
    string filename = "stasiun.txt";

    do {
    cout << setw(30) << setfill('=') << " " << endl;
    cout << setfill(' ') << setw(21) << right << "|STASIUN KERETA 'SIIUU'     |" << endl;
    cout << setw(30) << setfill('=') << " " << endl ;        
        cout << "1. Tambah Stasiun\n";
        cout << "2. Tampilkan Stasiun\n";
        cout << "3. Cari Stasiun\n";
        cout << "4. Urutkan Stasiun (berdasarkan nama)\n";
        cout << "5. Simpan ke File\n";
        cout << "6. Baca dari File\n";
         cout <<"7. Tambah Antrean Penumpang\n";
        cout << "8. Layani Penumpang\n";
        cout << "9. Tampilkan Antrean\n";
        cout << "10. Tampilkan Riwayat\n";
        cout << "11. Batalkan Antrean Pertama\n";
        cout << "12. Batalkan Antrean Belakang\n";
        cout << "13. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
        cout << setw(39) << setfill('=') << " " << endl;
        cout << setfill(' ') << setw(21) << right << "TAMBAH STASIUN" << endl;
        cout << setw(39) << setfill('=') << " " << endl ;
                cout << "Nama Stasiun: ";
                getline(cin, nama);
                cout << "Kota: ";
                getline(cin, kota);
                cout << "Jumlah Peron: ";
                cin >> jumlahPeron;
                cin.ignore();
                tambahStasiun(head, nama, kota, jumlahPeron);
                break;
            case 2:
    cout << setw(39) << setfill('=') << " " << endl;
    cout << setfill(' ') << setw(21) << right << "STASIUN :" << endl;
    cout << setw(39) << setfill('=') << " " << endl ;
                tampilkanStasiun(head);
                break;
            case 3:
    cout << setw(39) << setfill('=') << " " << endl;
    cout << setfill(' ') << setw(21) << right << "CARI STASIUN" << endl;
    cout << setw(39) << setfill('=') << " " << endl ;
                cout << "Masukkan nama stasiun yang dicari: ";
                getline(cin, nama);
                {
                    Stasiun* hasil = cariStasiun(head, nama);
                    if (hasil) {
                        cout << "Ditemukan!\n";
                        cout << "Nama        : " << hasil->nama << endl;
                        cout << "Kota        : " << hasil->kota << endl;
                        cout << "Jumlah Peron: " << hasil->jumlahPeron << endl;
                    } else {
                        cout << "Stasiun tidak ditemukan.\n";
                    }
                }
                break;
            case 4:
    cout << setw(39) << setfill('=') << " " << endl;
    cout << setfill(' ') << setw(21) << right << "URUTAN STASIUN" << endl;
    cout << setw(39) << setfill('=') << " " << endl ;
                sortingStasiun(head);
                cout << "Data stasiun telah diurutkan berdasarkan nama.\n";
                break;
            case 5:
                simpanKeFile(head, filename);
                break;
            case 6:
                hapusSemuaStasiun(head); // Bersihkan sebelum baca ulang
                bacaDariFile(head, filename);
                break;
            case 7: tambahAntrean(); break;
            case 8: layaniPenumpang(); break;
            case 9: tampilkanAntrean(); break;
            case 10: tampilkanRiwayat(); break;
            case 11: batalkanAntreanDepan(); break;
            case 12: batalkanAntreanBelakang(); break;
            case 13: hapusSemuaStasiun(head); break;
    cout << setw(30) << setfill('=') << " " << endl;
    cout << setfill(' ') << setw(21) << right << " TERIMA KASIH " << endl;
    cout << setw(30) << setfill('=') << " " << endl ;
            break;               
            default:
            cout << "Pilihan tidak valid.\n";
        }   
    } while (pilihan != 13);

    return 0;
}