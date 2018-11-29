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
        //input nama karyawan
        do {
            std::cout << "Masukkan nama karyawan                : "; std::getline(std::cin >> std::ws, nama);
            if (std::find(nama_.begin(), nama_.end(), nama) != nama_.end()){
                std::cout << "Nama sudah terdaftar" << std::endl;
                continue;
            }
            else break;
        } while(true);
        //input username karyawan
        std::cout << "Masukkan username karyawan            : "; tangkapError(&username);
        do {
            std::cout << "Masukkan kode karyawan (harus 4 digit): "; tangkapError(&nik);
            if (std::find(nik_.begin(), nik_.end(), nik) != nik_.end()){
                std::cout << "Kode sudah terdaftar" << std::endl;
                continue;
            }
        } while (nik.length() != 4);
        //yakin ingin menambah karyawan?
        std::cout << "Yakin ingin menambah karyawan? "; tangkapError(&c);;
        if (c == 'y' || c == 'Y'){
            //tambah data karyawan
            std::fstream file("data/karyawan.dt");
            file.seekp(0, std::ios::end);
            file << nama << ":" << nik << "\n";
            file.close();
            nama_.push_back(nama);
            nik_.push_back(nik);
            //tambah akun karyawan
            std::replace(nama.begin(), nama.end(), ' ', '_');
            std::fstream data("data/data.dt");
            data.seekp(0, std::ios::end);
            data << nama << " " << username << " " << nik << " karyawan" << "\n";
            data.close();
        }
        return;
    }
    void dataKaryawan(){
        //masukkan data karyawan ke vector (mirip linked list)
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
    void dataTugas(std::string namat, std::string *var, std::string data, char par = '\n'){
        //baca data tugas, masukkan ke string
        *var = "";
        dl_ = "";
        std::fstream file(data);
        std::string line, nama, tugas, dl;
        bool tambah = false;
        while (std::getline(file, line)){
            std::stringstream iss(line);
            std::getline(iss, nama, ':'); //contoh Muhammad Rezal:
            if ( (std::find(nama_.begin(), nama_.end(), nama) != nama_.end()) && (namat == nama) ){
                std::getline(iss, tugas, ','); //contoh buat survei,
                if (line.find(par) != std::string::npos){
                    std::getline(iss, dl, par); //contoh 2<, artinya masih belum dikerjakan
                    tambah = true;
                }
            }
            if (tambah){
                //masukkan string tugas ke pointer var
                *var = *var + tugas + "/";
                //masukkan string deadline ke variabel dl_
                dl_ = dl_ + dl + "?";
                tambah = false;
            }
        }
        file.close();
        return;
    }
    int cetakTugas(std::string nama, std::string *var, std::string data, char par = '\n'){
        //panggil fungsi dataTugas
        dataTugas(nama, var, data, par);
        std::stringstream t(*var), u(dl_); //stringstream digunakan untuk parsing
        std::string ltugas, ldl;
        int n = 0;
        //cetak daftar tugas
        if (std::find(nama_.begin(), nama_.end(), nama) != nama_.end()){ //jika nama karyawan ada
            std::cout << "Data :\n";
            if (*var == ""){ //jika tugas kosong
                std::cout << "Daftar tidak ada!" << std::endl;
            }
            else { //jika tugas ada
                while (std::getline(t, ltugas, '/') && std::getline(u, ldl, '?')){
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
        //pengurutan karyawan berdasarkan nik
        for (unsigned int a=0; a<nik_.size(); a++){
            for (unsigned int b = a+1; b<nik_.size(); b++){
                if (nik_.at(a) >= nik_.at(b)){
                    std::swap(nama_.at(a), nama_.at(b));
                    std::swap(nik_.at(a), nik_.at(b));
                }
            }
        }
        //ukuran nama terpanjang
        unsigned int len_s = 0;
        for (unsigned int a=0; a<nik_.size(); a++){
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
        for (unsigned int a=0; a<nik_.size(); a++){
            panjang = (len_s + (len_s + 2) / 2) - nama_.at(a).length();
            std::cout << " " << nama_.at(a); std::cout.width(panjang); std::cout << nik_.at(a) << std::endl;
        }
        std::cout << b << "\n";
        std::cout << std::endl;

        return;
    }
    void daftarKerja(std::string status){
        system("cls");
        //panggil cetakKaryawan
        cetakKaryawan();
        std::string nama;
        int len;
        std::cout << "Pilih nama karyawan: "; std::getline(std::cin >> std::ws, nama);
        if (status == "belum"){ //untuk tugas yang belum diinput oleh karyawan
            len = cetakTugas(nama, &tugas_, "data/tugas.dt", '<');
        }
        else {
            len = cetakTugas(nama, &selesai, "data/tugas_selesai.dt", '>');
            if (len != 0) verifikasiTugas(nama, len);
        }
        std::cout << "\n";
        system("pause");
        return;
    }
    void tambahTugas(){
        system("cls");
        //panggil cetakKaryawan
        cetakKaryawan();
        std::string tugas, dl = "", target = "";
        do { //masukkan tugas tanpa : , < >
            std::cout << "Masukkan Tugas (tanpa : , < >)    : "; std::getline(std::cin >> std::ws, tugas);
        } while (std::any_of(tugas.begin(), tugas.end(), [](char x){return (':' == x) || (',' == x) || ('<' == x) || ('>' == x);}));
        do { //masukkan deadline hari, hanya angka
            std::cout << "Masukkan Deadline (angka hari)    : "; std::getline(std::cin >> std::ws, dl);
        } while (! (std::all_of(dl.begin(), dl.end(), ::isdigit)) );
        do { //masukkan target pegawai
            std::cout << "Masukkan Target Pegawai           : "; std::getline(std::cin >> std::ws, target);
        } while (! (std::find(nama_.begin(), nama_.end(), target) != nama_.end()) );
        //yakin?
		std::cout << "Yakin ingin menambahkan tugas? "; tangkapError(&c);
		if (c == 'y' || c == 'Y'){
            //tulis tugas ke dalam file tugas.dt
            std::fstream file("data/tugas.dt");
            file.seekp(0, std::ios::end);
            file << target << ":" << tugas << "," << dl << "<" << "\n";
            file.close();
		}
		return;
    }
    void verifikasi(std::string nama, int i){
        //verifikasi tugas
        std::string tugas, dl;
        std::string tugas__;
        dataTugas(nama, &tugas__, "data/tugas_selesai.dt", '>');
        std::stringstream line(tugas__);
        std::stringstream ldl(dl_);
        for (int j=0; j<i; j++){ //untuk mendapatkan tugas dan deadline dari index yang diinput pengguna
            std::getline(line, tugas, '/');
            std::getline(ldl, dl, '?');
        }
        //buka file tugas_selesai.dt, temp2.dt (sebagai temporary), dan tugas_verify.dt
        std::ifstream file("data/tugas_selesai.dt");
        std::ofstream tmp("data/temp2.dt");
        std::fstream out("data/tugas_verify.dt");
        std::string ln;
        tugas = nama + ":" + tugas + "," + dl + ">"; //tugas = nama:tugas,dl
        while(std::getline(file, ln)){
            if (ln != tugas){
                tmp << ln << "\n";
            }
        }
        out.seekp(0, std::ios::end);
        out << tugas << "\n";
        file.close();
        tmp.close();
        out.close();
        remove("data/tugas_selesai.dt"); //hapus file
        rename("data/temp2.dt", "data/tugas_selesai.dt"); //ubah nama file
        //hapus tugas
        dataTugas(nama, &tugas__, "data/tugas.dt", '>');
        std::stringstream tdl(dl_);
        for (int j=0; j<i; j++){ //untuk mendapatkan tugas dan deadline dari index yang diinput pengguna
            std::getline(line, tugas, '/');
            std::getline(tdl, dl, '?');
        }
        tugas = nama + ":" + tugas + "," + dl + ">";
        std::ifstream dtugas("data/tugas.dt");
        std::ofstream temp("data/temp.dt");
        while (std::getline(dtugas, ln)){
            if (ln != tugas){
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
        std::cout << "Verifikasi Tugas? "; tangkapError(&c);
        if (c == 'y' || c == 'Y'){
            do {
                std::cout << "Pilih tugas nomor? "; tangkapError(&i);
            } while (i>n);
            std::cout << "Yakin? "; tangkapError(&c);
            if (c == 'y' || c == 'Y') verifikasi(nama, i);
        }
        return;
    }
    void gantiPassword(std::string nama){
        std::string namat = nama, pw, line;
        std::replace(namat.begin(), namat.end(), ' ', '_');
        std::ifstream file("data/data.dt");
        std::ofstream temp("data/temp.dt");
        system("cls");
        std::cout << "Masukkan password baru: "; tangkapError(&pw);
        temp << "\n";
        while (std::getline(file, line)){
            std::string nama__, username, password, status;
            file >> nama__;
            file >> username;
            file >> password;
            file >> status;
            if (namat == nama__){
                temp << nama__ << " " << username << " " << pw << " " << status << std::endl;
            }
            else {
                temp << nama__ << " " << username << " " << password << " " << status << std::endl;
            }
        }
        file.close();
        temp.close();
        remove("data/data.dt");
        rename("data/temp.dt", "data/data.dt");
        return;
    }
    void tangkapError(int *i){
        try {
            std::cin >> *i;
            if (std::cin.fail()){
                std::cout << "Input error" << std::endl;
            }
        }
        catch(char *error){}
    }
    void tangkapError(char *c){
        try {
            std::cin >> *c;
            if (std::cin.fail()){
                std::cout << "Input error" << std::endl;
            }
        }
        catch(char *error){}
    }
    void tangkapError(std::string *s){
        try {
            std::cin >> *s;
            if (std::cin.fail()){
                std::cout << "Input error" << std::endl;
            }
        }
        catch(char *error){}
    }
};

#endif
