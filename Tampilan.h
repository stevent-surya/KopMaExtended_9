#ifndef TAMPILAN_H
#define TAMPILAN_H

#include <string>

// Namespace untuk mengelompokkan fungsi-fungsi terkait tampilan/UI
namespace UI {
    // Membersihkan layar konsol
    void bersihkanLayar();

    // Jeda program, menunggu pengguna menekan Enter
    void jeda();

    // Menampilkan header dengan judul yang diformat
    void header(const std::string& judul);

    // Menampilkan berbagai menu
    void menuLogin();
    void menuAdmin();
    void menuMahasiswa(const std::string& namaMahasiswa);
}

#endif // TAMPILAN_H