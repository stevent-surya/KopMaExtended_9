#include "Mahasiswa.h"
#include <iostream>
#include <iomanip> // Untuk std::fixed dan std::setprecision
#include <numeric> // Untuk std::accumulate
#include <limits>

// Constructor
Mahasiswa::Mahasiswa(std::string nim, std::string nama, std::string jurusan)
    : nim(nim), nama(nama), jurusan(jurusan), totalPenarikan(0.0) {
    this->tabungan.fill(0.0); // Inisialisasi semua tabungan dengan 0
}

// Setter
void Mahasiswa::setNama(std::string nama) { this->nama = nama; }
void Mahasiswa::setJurusan(std::string jurusan) { this->jurusan = jurusan; }
void Mahasiswa::setTotalPenarikan(double jumlah) { this->totalPenarikan = jumlah; }


// Getter
std::string Mahasiswa::getNIM() const { return nim; }
std::string Mahasiswa::getNama() const { return nama; }
std::string Mahasiswa::getJurusan() const { return jurusan; }
double Mahasiswa::getTotalPenarikan() const { return totalPenarikan; }
const std::array<double, 6>& Mahasiswa::getRincianTabungan() const { return tabungan; }

// Fungsi untuk input tabungan 6 bulan
void Mahasiswa::inputTabungan() {
    const std::string namaBulan[] = { "Januari", "Februari", "Maret", "April", "Mei", "Juni" };
    std::cout << "Masukkan Tabungan untuk " << nama << " (NIM: " << nim << "):\n";
    for (int i = 0; i < 6; ++i) {
        std::cout << "Tabungan bulan " << namaBulan[i] << ": Rp ";
        std::cin >> tabungan[i];
        while (std::cin.fail() || tabungan[i] < 0) {
            std::cout << "Input tidak valid. Masukkan angka positif: Rp ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> tabungan[i];
        }
    }
}

// Menghitung total setoran tabungan
double Mahasiswa::getJumlahTabungan() const {
    return std::accumulate(tabungan.begin(), tabungan.end(), 0.0);
}

// Menghitung saldo akhir
double Mahasiswa::getTotalSaldo() const {
    return getJumlahTabungan() - totalPenarikan;
}

void Mahasiswa::tarikUang() {
    double jumlah;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Saldo Anda saat ini: Rp " << getTotalSaldo() << std::endl;
    std::cout << "Masukkan jumlah yang ingin ditarik: Rp ";
    std::cin >> jumlah;

    while (std::cin.fail() || jumlah < 0) {
        std::cout << "Input tidak valid. Masukkan jumlah positif: Rp ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> jumlah;
    }

    if (jumlah > getTotalSaldo()) {
        std::cout << "\nError: Saldo tidak mencukupi untuk penarikan.\n";
    }
    else {
        totalPenarikan += jumlah;
        std::cout << "\nSukses! Penarikan sebesar Rp " << jumlah << " berhasil.\n";
        std::cout << "Sisa saldo Anda: Rp " << getTotalSaldo() << std::endl;
    }
}

// Menampilkan data dasar mahasiswa
void Mahasiswa::tampilkanData() const {
    std::cout << "NIM      : " << nim << std::endl;
    std::cout << "Nama     : " << nama << std::endl;
    std::cout << "Jurusan  : " << jurusan << std::endl;
}

// Menampilkan data mahasiswa beserta rincian saldo
void Mahasiswa::tampilkanDataDenganSaldo() const {
    const std::string namaBulan[] = { "Januari", "Februari", "Maret", "April", "Mei", "Juni" };
    tampilkanData();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nRincian Tabungan:\n";
    for (int i = 0; i < 6; ++i) {
        std::cout << "- " << std::setw(10) << std::left << namaBulan[i] << ": Rp " << tabungan[i] << std::endl;
    }
    std::cout << "-------------------------------------\n";
    std::cout << "Total Setoran    : Rp " << std::setw(10) << std::right << getJumlahTabungan() << std::endl;
    std::cout << "Total Penarikan  : Rp " << std::setw(10) << std::right << getTotalPenarikan() << std::endl;
    std::cout << "=====================================\n";
    std::cout << "SALDO AKHIR      : Rp " << std::setw(10) << std::right << getTotalSaldo() << std::endl;
}