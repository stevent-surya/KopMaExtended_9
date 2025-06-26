#include "Sistem.h"
#include "Tampilan.h"
#include <iostream>
#include <limits>
#include <iomanip>

Sistem::Sistem() : penggunaAktif(TipePengguna::NONE), mahasiswaLogin(nullptr) {}

void Sistem::jalankan() {
    while (true) {
        login(); // Tampilkan layar login

        if (penggunaAktif == TipePengguna::ADMIN) {
            jalankanMenuAdmin();
        }
        else if (penggunaAktif == TipePengguna::MAHASISWA) {
            jalankanMenuMahasiswa();
        }
        else {
            // Jika penggunaAktif == NONE (misal dari logout)
            // Loop akan berlanjut dan menampilkan menu login lagi
        }
    }
}

void Sistem::login() {
    std::string username, password;
    UI::menuLogin();
    std::cout << "Username : ";
    std::cin >> username;
    std::cout << "Password : ";
    std::cin >> password;

    if (username == "admin" && password == "12345") {
        penggunaAktif = TipePengguna::ADMIN;
        std::cout << "\nLogin sebagai Admin berhasil!" << std::endl;
        UI::jeda();
    }
    else {
        mahasiswaLogin = koperasi.cariAnggotaByNIM(username);
        if (mahasiswaLogin != nullptr && mahasiswaLogin->getNIM() == password) {
            penggunaAktif = TipePengguna::MAHASISWA;
            std::cout << "\nLogin berhasil!" << std::endl;
            UI::jeda();
        }
        else {
            penggunaAktif = TipePengguna::NONE;
            mahasiswaLogin = nullptr;
            std::cout << "\nLogin gagal. Username atau Password salah." << std::endl;
            UI::jeda();
        }
    }
}

void Sistem::jalankanMenuAdmin() {
    int pilihan = -1;
    char yt;
    do {
        UI::menuAdmin();
        std::cin >> pilihan;

        while (std::cin.fail()) {
            std::cout << "Input tidak valid! Harap masukkan angka menu: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> pilihan;
        }

        UI::bersihkanLayar();
        switch (pilihan) {
        case 1: koperasi.tambahAnggota(); break;
        case 2: koperasi.tampilkanSemuaAnggota(); break;
        case 3: koperasi.ubahAnggota(); break;
        case 4: koperasi.inputTabunganAnggota(); break;
        case 5: koperasi.tampilkanTotalSaldoAnggota(); break;
        case 6: koperasi.exportTotalSaldoKeTxt(); break;
        case 7: koperasi.hapusAnggota(); break;
        case 0:
            penggunaAktif = TipePengguna::NONE;
            std::cout << "Logout berhasil.\n";
            break;
        default:
            std::cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

        if (pilihan != 0) {
            std::cout << "\n\nLakukan aksi lain (y/n)? ";
            std::cin >> yt;
            if (yt == 'N' || yt == 'n') {
                pilihan = 0; // Set pilihan ke 0 untuk keluar dari loop
                penggunaAktif = TipePengguna::NONE;
                std::cout << "Logout berhasil.\n";
            }
        }

        if (pilihan != 0) UI::jeda();

    } while (pilihan != 0);
}

void Sistem::jalankanMenuMahasiswa() {
    int pilihan = -1;
    char yt;
    do {
        UI::menuMahasiswa(mahasiswaLogin->getNama());
        std::cin >> pilihan;

        while (std::cin.fail()) {
            std::cout << "Input tidak valid! Harap masukkan angka menu: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> pilihan;
        }

        UI::bersihkanLayar();
        switch (pilihan) {
        case 1:
            UI::header("RINCIAN TABUNGAN & SALDO");
            mahasiswaLogin->tampilkanDataDenganSaldo();
            break;
        case 2:
            UI::header("SALDO TOTAL");
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "Saldo total Anda saat ini adalah: Rp " << mahasiswaLogin->getTotalSaldo() << std::endl;
            break;
        case 3:
            UI::header("TARIK TUNAI");
            mahasiswaLogin->tarikUang();
            break;
        case 0:
            penggunaAktif = TipePengguna::NONE;
            mahasiswaLogin = nullptr;
            std::cout << "Logout berhasil.\n";
            break;
        default:
            std::cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

        if (pilihan != 0) {
            std::cout << "\n\nKembali ke menu mahasiswa (y/n)? ";
            std::cin >> yt;
            if (yt == 'N' || yt == 'n') {
                pilihan = 0; // Set pilihan ke 0 untuk keluar dari loop
                penggunaAktif = TipePengguna::NONE;
                mahasiswaLogin = nullptr;
                std::cout << "Logout berhasil.\n";
            }
        }

        if (pilihan != 0) UI::jeda();

    } while (pilihan != 0);
}