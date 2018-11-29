#ifndef MENU_INCLUDE
#define MENU_INCLUDE

#include <iostream>
#include "main.h"
#include "bos.h"
#include "karyawan.h"

class Menu {
private:
    Bos atasan;
    Karyawan bawahan;
    Init* init_;
    int i;
public:
    Menu(Init *init) {
        init_ = init;
    }
    void bos() {
        system("cls");
        std::string nama = init_->getNama();
        std::cout << "Selamat datang, " << nama << "\n\n";
        std::cout << "====== MENU ATASAN ======" << std::endl;
        std::cout << "1. Tambah Karyawan \n";
        std::cout << "2. Tampilkan Karyawan \n";
        std::cout << "3. Tambah Tugas Karyawan \n";
        std::cout << "4. Daftar Kerja Karyawan \n";
        std::cout << "5. Verifikasi Kerja Karyawan \n";
        std::cout << "6. Ganti Password \n";
        std::cout << "0. Logout \n";
        std::cout << "Pilih menu: "; init_->tangkapError(&i);
        switch(i){
        case 0: init_->setTrue(true); init_->awal(); break;
        case 1: atasan.inputKaryawan(); break;
        case 2: atasan.cetakKaryawan(); system("pause"); break;
        case 3: atasan.tambahTugas(); break;
        case 4: atasan.daftarKerja("belum"); break;
        case 5: atasan.daftarKerja("sudah"); break;
        case 6: atasan.gantiPassword(nama); break;
        default: salah(); break;
        }
    }
    void karyawan() {
        system("cls");
        std::string nama = init_->getNama();
        std::cout << "Selamat datang, " << nama << "\n\n";
        std::cout << "====== MENU KARYAWAN ======" << std::endl;
        std::cout << "1. Tampilkan Daftar Tugas" << std::endl;
        std::cout << "2. Tugas Terverifikasi" << std::endl;
        std::cout << "3. Ganti Password" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cout << "Pilih menu : "; init_->tangkapError(&i);
        switch(i){
        case 0: init_->setTrue(true); init_->awal(); break;
        case 1:	bawahan.daftarTugas(nama); break;
        case 2: bawahan.tugasDone(nama); break;
        case 3: bawahan.gantiPassword(nama); break;
        default: salah(); break;
        }
    }
    void salah(){
        std::cout << "Menu tidak terdefinisi" << std::endl;
        system("pause");
        return;
    }
};

#endif
