#include "Koperasi.h"
#include "Tampilan.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <iomanip>

Koperasi::Koperasi() {
    muatDataDariFile();
}

Koperasi::~Koperasi() {
    simpanDataKeFile();
}

void Koperasi::muatDataDariFile() {
    std::ifstream file(NAMA_FILE_DATA, std::ios::binary);
    if (!file) {
        // Jika file tidak ada (pertama kali dijalankan), tidak apa-apa
        return;
    }

    // Hapus data lama di memori sebelum memuat yg baru
    daftarAnggota.clear();

    while (file) {
        size_t nimLen, namaLen, jurusanLen;

        // Baca panjang string
        file.read(reinterpret_cast<char*>(&nimLen), sizeof(nimLen));
        if (file.eof()) break; // Akhir dari file

        char* nimBuffer = new char[nimLen + 1];
        file.read(nimBuffer, nimLen);
        nimBuffer[nimLen] = '\0';
        std::string nim(nimBuffer);
        delete[] nimBuffer;

        file.read(reinterpret_cast<char*>(&namaLen), sizeof(namaLen));
        char* namaBuffer = new char[namaLen + 1];
        file.read(namaBuffer, namaLen);
        namaBuffer[namaLen] = '\0';
        std::string nama(namaBuffer);
        delete[] namaBuffer;

        file.read(reinterpret_cast<char*>(&jurusanLen), sizeof(jurusanLen));
        char* jurusanBuffer = new char[jurusanLen + 1];
        file.read(jurusanBuffer, jurusanLen);
        jurusanBuffer[jurusanLen] = '\0';
        std::string jurusan(jurusanBuffer);
        delete[] jurusanBuffer;

        Mahasiswa mhs(nim, nama, jurusan);

        std::array<double, 6> tabungan;
        file.read(reinterpret_cast<char*>(tabungan.data()), sizeof(tabungan));

        for (int i = 0; i < 6; ++i) mhs.inputTabungan(); // Cara "kasar" untuk set tabungan, perlu refactor Mahasiswa
        // Refactor: Tambahkan setter di Mahasiswa: setRincianTabungan(const std::array<double, 6>&)

        double totalPenarikan;
        file.read(reinterpret_cast<char*>(&totalPenarikan), sizeof(totalPenarikan));
        mhs.setTotalPenarikan(totalPenarikan);

        daftarAnggota.push_back(mhs);
    }
    file.close();
}


void Koperasi::simpanDataKeFile() {
    std::ofstream file(NAMA_FILE_DATA, std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "Error: Tidak bisa membuka file untuk menyimpan data!" << std::endl;
        return;
    }

    for (const auto& mhs : daftarAnggota) {
        std::string nim = mhs.getNIM();
        size_t nimLen = nim.length();
        file.write(reinterpret_cast<const char*>(&nimLen), sizeof(nimLen));
        file.write(nim.c_str(), nimLen);

        std::string nama = mhs.getNama();
        size_t namaLen = nama.length();
        file.write(reinterpret_cast<const char*>(&namaLen), sizeof(namaLen));
        file.write(nama.c_str(), namaLen);

        std::string jurusan = mhs.getJurusan();
        size_t jurusanLen = jurusan.length();
        file.write(reinterpret_cast<const char*>(&jurusanLen), sizeof(jurusanLen));
        file.write(jurusan.c_str(), jurusanLen);

        auto tabungan = mhs.getRincianTabungan();
        file.write(reinterpret_cast<const char*>(tabungan.data()), sizeof(tabungan));

        double totalPenarikan = mhs.getTotalPenarikan();
        file.write(reinterpret_cast<const char*>(&totalPenarikan), sizeof(totalPenarikan));
    }
    file.close();
}


int Koperasi::cariIndeksAnggotaByNIM(const std::string& nim) {
    for (size_t i = 0; i < daftarAnggota.size(); ++i) {
        if (daftarAnggota[i].getNIM() == nim) {
            return i; // Mengembalikan indeks
        }
    }
    return -1; // Tidak ditemukan
}

Mahasiswa* Koperasi::cariAnggotaByNIM(const std::string& nim) {
    for (auto& anggota : daftarAnggota) {
        if (anggota.getNIM() == nim) {
            return &anggota;
        }
    }
    return nullptr;
}


void Koperasi::tambahAnggota() {
    UI::header("TAMBAH PESERTA BARU");
    std::string nim, nama, jurusan;

    std::cout << "Masukkan NIM      : ";
    std::cin >> nim;
    if (cariAnggotaByNIM(nim) != nullptr) {
        std::cout << "\nError: Mahasiswa dengan NIM " << nim << " sudah terdaftar!\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Masukkan Nama     : ";
    std::getline(std::cin, nama);
    std::cout << "Masukkan Jurusan  : ";
    std::getline(std::cin, jurusan);

    daftarAnggota.push_back(Mahasiswa(nim, nama, jurusan));
    std::cout << "\nSukses! Mahasiswa " << nama << " berhasil ditambahkan.\n";
}

void Koperasi::tampilkanSemuaAnggota() {
    UI::header("DATA SEMUA PESERTA KOPERASI");
    if (daftarAnggota.empty()) {
        std::cout << "Belum ada data peserta yang terdaftar.\n";
    }
    else {
        for (size_t i = 0; i < daftarAnggota.size(); ++i) {
            std::cout << "--- Peserta " << i + 1 << " ---\n";
            daftarAnggota[i].tampilkanData();
            std::cout << std::endl;
        }
    }
}

void Koperasi::ubahAnggota() {
    UI::header("UBAH DATA PESERTA");
    if (daftarAnggota.empty()) {
        std::cout << "Belum ada data peserta.\n";
        return;
    }
    std::string nim, namaBaru, jurusanBaru;
    std::cout << "Masukkan NIM peserta yang akan diubah: ";
    std::cin >> nim;

    Mahasiswa* mhs = cariAnggotaByNIM(nim);
    if (mhs == nullptr) {
        std::cout << "\nError: Peserta dengan NIM " << nim << " tidak ditemukan.\n";
    }
    else {
        std::cout << "\nData ditemukan:\n";
        mhs->tampilkanData();
        std::cout << "\nMasukkan data baru (kosongkan jika tidak ingin diubah):\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Nama Baru     : ";
        std::getline(std::cin, namaBaru);
        std::cout << "Jurusan Baru  : ";
        std::getline(std::cin, jurusanBaru);

        if (!namaBaru.empty()) mhs->setNama(namaBaru);
        if (!jurusanBaru.empty()) mhs->setJurusan(jurusanBaru);

        std::cout << "\nSukses! Data peserta berhasil diubah.\n";
    }
}

void Koperasi::inputTabunganAnggota() {
    UI::header("INPUT TABUNGAN PESERTA");
    if (daftarAnggota.empty()) {
        std::cout << "Belum ada data peserta.\n";
        return;
    }
    std::string nim;
    std::cout << "Masukkan NIM peserta: ";
    std::cin >> nim;

    Mahasiswa* mhs = cariAnggotaByNIM(nim);
    if (mhs == nullptr) {
        std::cout << "\nError: Peserta dengan NIM " << nim << " tidak ditemukan.\n";
    }
    else {
        mhs->inputTabungan();
        std::cout << "\nSukses! Data tabungan berhasil diinput.\n";
    }
}

void Koperasi::tampilkanTotalSaldoAnggota() {
    UI::header("TAMPILKAN TOTAL SALDO PESERTA");
    if (daftarAnggota.empty()) {
        std::cout << "Belum ada data peserta.\n";
        return;
    }
    std::string nim;
    std::cout << "Masukkan NIM peserta: ";
    std::cin >> nim;

    Mahasiswa* mhs = cariAnggotaByNIM(nim);
    if (mhs == nullptr) {
        std::cout << "\nError: Peserta dengan NIM " << nim << " tidak ditemukan.\n";
    }
    else {
        std::cout << "\n--- Rincian Saldo ---\n";
        mhs->tampilkanDataDenganSaldo();
    }
}

void Koperasi::exportTotalSaldoKeTxt() {
    UI::header("EXPORT DATA SALDO KE .TXT");
    if (daftarAnggota.empty()) {
        std::cout << "Tidak ada data untuk diexport.\n";
        return;
    }

    std::ofstream file("Laporan_Saldo_Koperasi.txt");
    if (!file.is_open()) {
        std::cout << "Error: Gagal membuka file untuk ditulis.\n";
        return;
    }

    file << "======================================================\n";
    file << "          LAPORAN TOTAL SALDO PESERTA KOPERASI        \n";
    file << "======================================================\n\n";

    file << std::fixed << std::setprecision(2);

    for (const auto& mhs : daftarAnggota) {
        file << "NIM      : " << mhs.getNIM() << "\n";
        file << "Nama     : " << mhs.getNama() << "\n";
        file << "Jurusan  : " << mhs.getJurusan() << "\n";
        file << "Total Saldo: Rp " << mhs.getTotalSaldo() << "\n";
        file << "------------------------------------------------------\n";
    }

    file.close();
    std::cout << "Sukses! Data berhasil diexport ke file 'Laporan_Saldo_Koperasi.txt'.\n";
}


void Koperasi::hapusAnggota() {
    UI::header("HAPUS PESERTA KOPERASI");
    if (daftarAnggota.empty()) {
        std::cout << "Belum ada data peserta.\n";
        return;
    }
    std::string nim;
    std::cout << "Masukkan NIM peserta yang akan dihapus: ";
    std::cin >> nim;

    int index = cariIndeksAnggotaByNIM(nim);
    if (index == -1) {
        std::cout << "\nError: Peserta dengan NIM " << nim << " tidak ditemukan.\n";
    }
    else {
        std::string nama = daftarAnggota[index].getNama();
        char konfirmasi;
        std::cout << "\nAnda yakin ingin menghapus " << nama << " (NIM: " << nim << ")? (y/t): ";
        std::cin >> konfirmasi;
        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            daftarAnggota.erase(daftarAnggota.begin() + index);
            std::cout << "\nSukses! Peserta " << nama << " telah dihapus.\n";
        }
        else {
            std::cout << "\nPenghapusan dibatalkan.\n";
        }
    }
}