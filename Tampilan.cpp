#include "Tampilan.h"
#include <iostream>
#include <cstdlib> // Untuk system("cls") dan system("pause")
#include <limits>  // Untuk cin.ignore

void UI::bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UI::jeda() {
    std::cout << "\nTekan Enter untuk melanjutkan...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void UI::header(const std::string& judul) {
    std::cout << "======================================================\n";
    std::cout << "          " << judul << "           \n";
    std::cout << "======================================================\n\n";
}

void UI::menuLogin() {
    UI::bersihkanLayar();
    std::cout << "======================================================\n";
    std::cout << "      SELAMAT DATANG DI SISTEM KOPERASI MAHASISWA     \n";
    std::cout << "======================================================\n";
    std::cout << R"(
         /\\       //\\
  _______))\\_____//((________
 /---------SISTEM KOPMA--------\\
/________________________________\\

LOGIN SISTEM
)";
    std::cout << "======================================================\n";
}


void UI::menuAdmin() {
    UI::bersihkanLayar();
    header("MENU ADMINISTRATOR");
    std::cout << "1. Tambah Peserta Koperasi\n";
    std::cout << "2. Tampilkan Data Peserta Koperasi\n";
    std::cout << "3. Ubah Data Peserta Koperasi\n";
    std::cout << "4. Input Tabungan Peserta (Januari - Juni)\n";
    std::cout << "5. Tampilkan Total Saldo Peserta\n";
    std::cout << "6. Export Total Saldo ke File (.txt)\n";
    std::cout << "7. Hapus Peserta Koperasi\n";
    std::cout << "0. Logout (Kembali ke Menu Login)\n";
    std::cout << "======================================================\n";
    std::cout << "Masukkan pilihan Anda: ";
}

void UI::menuMahasiswa(const std::string& namaMahasiswa) {
    UI::bersihkanLayar();
    header("MENU MAHASISWA");
    std::cout << "Selamat Datang, " << namaMahasiswa << "!\n\n";
    std::cout << "1. Tampilkan Rincian Tabungan & Saldo\n";
    std::cout << "2. Tampilkan Saldo Total\n";
    std::cout << "3. Tarik Uang\n";
    std::cout << "0. Logout (Kembali ke Menu Login)\n";
    std::cout << "======================================================\n";
    std::cout << "Masukkan pilihan Anda: ";
}