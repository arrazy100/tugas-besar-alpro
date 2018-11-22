#ifndef BOS_INCLUDE
#define BOS_INCLUDE

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>

class Bos {
private:
    char c;
    int i;
    std::string tugas_, dl_, selesai;
    std::vector<std::string> nama_;
    std::vector<std::string> nik_;
public:
    Bos(){
        dataKaryawan();
    }
    void inputKaryawan(){
        system("cls");
        std::string nama, nik = "", username;
        char c;
        std::cout << "Masukkan nama karyawan                : "; std::getline(std::cin >> std::ws, nama);
        std::cout << "Masukkan username karyawan            : "; std::cin >> username;
        do {
            std::cout << "Masukkan kode karyawan (harus 4 digit): "; std::cin >> nik;
        } while (nik.length() != 4);
        std::cout << "Yakin ingin menambah karyawan? "; std::cin >> c;
        if (c == 'y' || c == 'Y'){
            //tambah data karyawan
            std::fstream file("data/karyawan.dt");
            file.seekp(0, std::ios::end);
            file << "\n" << nama << ":" << nik;
            file.close();
            nama_.push_back(nama);
            nik_.push_back(nik);
            //tambah akun karyawan
            std::replace(nama.begin(), nama.end(), ' ', '_');
            std::fstream data("data/data.dt");
            data.seekp(0, std::ios::end);
            data << "\n" << nama << " " << username << " " << nik << " karyawan";
            data.close();
        }
        return;
    }
    void dataKaryawan(){
        std::fstream file("data/karyawan.dt");
        std::string line, nama, nik;
        while (getline(file, line)){
            std::stringstream iss(line);
            std::getline(iss, nama, ':');
            std::getline(iss, nik, '\n');
            nama_.push_back(nama);
            nik_.push_back(nik);
        }
        file.close();
        return;
    }
    void dataTugas(std::string namat, std::string *var, std::string data){
        *var = "";
        dl_ = "";
        std::fstream file(data);
        std::string line, nama, tugas, dl;
        bool tambah = false;
        while (std::getline(file, line)){
            std::stringstream iss(line);
            std::getline(iss, nama, ':');
            if ( (std::find(nama_.begin(), nama_.end(), nama) != nama_.end()) && (namat == nama) ){
                std::getline(iss, tugas, ',');
                std::getline(iss, dl, '\n');
                tambah = true;
            }
            if (tambah){
                *var = *var + tugas + "/";
                dl_ = dl_ + dl + '_';
                tambah = false;
            }
        }
        file.close();
        return;
    }
    int cetakTugas(std::string nama, std::string *var, std::string data){
        dataTugas(nama, var, data);
        std::stringstream t(*var), u(dl_);
        std::string ltugas, ldl;
        int n = 0;
        //cetak daftar tugas
        if (std::find(nama_.begin(), nama_.end(), nama) != nama_.end()){
            std::cout << "Data :\n";
            if (*var == ""){
                std::cout << "Daftar tidak ada!" << std::endl;
            }
            else {
                while (std::getline(t, ltugas, '/') && std::getline(u, ldl, '_')){
                    std::cout << n+1 << ". " << ltugas << "( " << ldl << " )" << std::endl;
                    n++;
                }
            }
        }
        else std::cout << "Nama karyawan tidak ada!" << std::endl;
        return n;
    }
    void cetakKaryawan(){
        system("cls");
        //pengurutan
        for (int a=0; a<nik_.size(); a++){
            for (int b = a+1; b<nik_.size(); b++){
                if (nik_.at(a) >= nik_.at(b)){
                    std::swap(nama_.at(a), nama_.at(b));
                    std::swap(nik_.at(a), nik_.at(b));
                }
            }
        }
        //ukuran nama terpanjang
        int len_s = 0;
        for (int a=0; a<nik_.size(); a++){
            if (nama_.at(a).length() > len_s){
                len_s = nama_.at(a).length();
            }
        }
        //cetak
        int panjang;
        std::string b(len_s + 12, '=');
        std::cout << "Daftar Karyawan (terurut sesuai kode) :\n";
        std::cout << b << "\n";
        std::cout.width(len_s / 2 + 1); std::cout << "NAMA"; std::cout.width(len_s + 1); std::cout << "NIK\n";
        std::cout << b << "\n";
        for (int a=0; a<nik_.size(); a++){
            panjang = (len_s + (len_s + 2) / 2) - nama_.at(a).length();
            std::cout << " " << nama_.at(a); std::cout.width(panjang); std::cout << nik_.at(a) << std::endl;
        }
        std::cout << b << "\n";
        std::cout << std::endl;

        return;
    }
    void daftarKerja(std::string status){
        system("cls");
        cetakKaryawan();
        std::string nama;
        int len;
        std::cout << "Pilih nama karyawan: "; std::getline(std::cin >> std::ws, nama);
        if (status == "belum"){
            len = cetakTugas(nama, &tugas_, "data/tugas.dt");
        }
        else {
            len = cetakTugas(nama, &selesai, "data/tugas_selesai.dt");
            if (len != 0) verifikasiTugas(nama, len);
        }
        std::cout << "\n";
        system("pause");
        return;
    }
    void tambahTugas(){
        system("cls");
        cetakKaryawan();
        std::string tugas, dl = "", target = "";
        do {
            std::cout << "Masukkan Tugas (tanpa : dan ,)    : "; std::getline(std::cin >> std::ws, tugas);
        } while (std::any_of(tugas.begin(), tugas.end(), [](char x){return (':' == x) || (',' == x);}));
        do {
            std::cout << "Masukkan Deadline (angka hari)    : "; std::getline(std::cin >> std::ws, dl);
        } while (! (std::all_of(dl.begin(), dl.end(), ::isdigit)) );
        do {
            std::cout << "Masukkan Target                   : "; std::getline(std::cin >> std::ws, target);
        } while (! (std::find(nama_.begin(), nama_.end(), target) != nama_.end()) );
		std::cout << "Yakin ingin menambahkan tugas? "; std::cin >> c;
		if ( !(std::find(nama_.begin(), nama_.end(), target) != nama_.end()) ){
            return;
		}
		if (c == 'y' || c == 'Y'){
            std::fstream file("data/tugas.dt");
            file.seekp(0, std::ios::end);
            file << "\n" << target << ":" << tugas << "," << dl;
            file.close();
		}
		return;
    }
    void laporanKerja(){
        system("cls");
        //isi tampilan mau gimana
        return;
    }
    void verifikasi(std::string nama, int i){
        //verifikasi tugas
        std::string tugas__;
        dataTugas(nama, &tugas__, "data/tugas_selesai.dt");
        std::stringstream line_(tugas__);
        std::stringstream ldl_(dl_);
        std::string tugas, dl;
        for (int j=0; j<i; j++){
            std::getline(line_, tugas, '/');
            std::getline(ldl_, dl, '_');
        }
        std::fstream file("data/tugas_selesai.dt");
        std::ofstream tmp("data/temp2.dt");
        std::fstream out("data/tugas_verify.dt");
        dataTugas(nama, &tugas__, "data/tugas");
        std::string ln;
        tugas = nama + ":" + tugas + "," + dl;
        while(std::getline(file, ln)){
            out.seekp(0, std::ios::end);
            out << "\n" << ln;
            if (ln.compare(tugas) != 0){
                tmp << ln << std::endl;
            }
        }
        file.close();
        tmp.close();
        out.close();
        remove("data/tugas_selesai.dt");
        rename("data/temp2.dt", "data/tugas_selesai.dt");
        //hapus tugas
        dataTugas(nama, &tugas__, "data/tugas.dt");
        std::stringstream line(tugas__);
        std::stringstream ldl(dl_);
        for (int j=0; j<i; j++){
            std::getline(line, tugas, '/');
            std::getline(ldl, dl, '_');
        }
        tugas = nama + ":" + tugas + "," + dl;
        std::ifstream dtugas("data/tugas.dt");
        std::ofstream temp("data/temp.dt");
        while (std::getline(dtugas, ln)){
            if (ln.compare(tugas) != 0){
                temp << ln << std::endl;
            }
        }
        dtugas.close();
        temp.close();
        remove("data/tugas.dt");
        rename("data/temp.dt", "data/tugas.dt");
        return;
    }
    void verifikasiTugas(std::string nama, int n){
        std::cout << "Verifikasi Tugas? "; std::cin >> c;
        if (c == 'y' || c == 'Y'){
            do {
                std::cout << "Pilih tugas nomor? "; std::cin >> i;
            } while (i>n);
            std::cout << "Yakin? "; std::cin >> c;
            if (c == 'y' || c == 'Y') verifikasi(nama, i);
        }
        return;
    }
};

#endif
