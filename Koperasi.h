#ifndef KOPERASI_H
#define KOPERASI_H

#include "Mahasiswa.h"
#include <vector>
#include <string>

class Koperasi {
private:
    std::vector<Mahasiswa> daftarAnggota;
    const std::string NAMA_FILE_DATA = "data_koperasi.dat";

    // Mengembalikan indeks jika ditemukan, -1 jika tidak.
    int cariIndeksAnggotaByNIM(const std::string& nim);

public:
    // Constructor akan otomatis memuat data
    Koperasi();
    // Destructor akan otomatis menyimpan data
    ~Koperasi();

    // Fungsi untuk memuat dan menyimpan data ke file persisten
    void muatDataDariFile();
    void simpanDataKeFile();

    // Mengembalikan pointer ke objek Mahasiswa jika ditemukan, nullptr jika tidak.
    Mahasiswa* cariAnggotaByNIM(const std::string& nim);

    // Menu Admin
    void tambahAnggota();
    void tampilkanSemuaAnggota();
    void ubahAnggota();
    void inputTabunganAnggota();
    void tampilkanTotalSaldoAnggota();
    void exportTotalSaldoKeTxt();
    void hapusAnggota();
};

#endif // KOPERASI_H