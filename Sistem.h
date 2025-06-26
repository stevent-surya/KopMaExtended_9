#ifndef SISTEM_H
#define SISTEM_H

#include "Koperasi.h"

enum class TipePengguna {
    ADMIN,
    MAHASISWA,
    NONE // Untuk status gagal login atau logout
};

class Sistem {
private:
    Koperasi koperasi;
    TipePengguna penggunaAktif;
    Mahasiswa* mahasiswaLogin; // Pointer ke mhs yg sedang login

    void login();
    void jalankanMenuAdmin();
    void jalankanMenuMahasiswa();

public:
    Sistem();
    void jalankan(); // Fungsi utama untuk memulai seluruh program
};

#endif // SISTEM_H