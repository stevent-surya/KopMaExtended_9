#ifndef MAHASISWA_H
#define MAHASISWA_H

#include <string>
#include <array>

class Mahasiswa {
private:
    std::string nim;
    std::string nama;
    std::string jurusan;
    std::array<double, 6> tabungan; // Indeks 0-5 untuk Januari-Juni
    double totalPenarikan;

public:
    // Constructor
    Mahasiswa(std::string nim, std::string nama, std::string jurusan);

    // Setter
    void setNama(std::string nama);
    void setJurusan(std::string jurusan);
    void setTotalPenarikan(double jumlah); // Untuk memuat data dari file

    // Getter
    std::string getNIM() const;
    std::string getNama() const;
    std::string getJurusan() const;
    double getJumlahTabungan() const; // Hanya total dari setoran
    double getTotalPenarikan() const;
    double getTotalSaldo() const; // Saldo akhir (Tabungan - Penarikan)
    const std::array<double, 6>& getRincianTabungan() const;


    // Fungsi utama
    void inputTabungan();
    void tarikUang();
    void tampilkanData() const;
    void tampilkanDataDenganSaldo() const;
};

#endif // MAHASISWA_H