#ifndef BOS_INCLUDE
#define BOS_INCLUDE

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Bos {
private:
    char c;
    int i;
    std::string tugas_, dl_;
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
    }
    void dataTugas(std::string namat){
        tugas_ = "";
        dl_ = "";
        std::fstream file("data/tugas.dt");
        std::string line, nama, tugas, dl;
        bool tambah = false;
        while (std::getline(file, line)){
            std::stringstream iss(line);
            std::getline(iss, nama, ':');
            if ( (std::find(nama_.begin(), nama_.end(), nama) != nama_.end()) && (namat == nama) ){
                std::getline(iss, tugas, ',');
                std::getline(iss, dl, '.');
                tambah = true;
            }
            if (tambah){
                tugas_ = tugas_ + tugas + "/";
                dl_ = dl_ + dl + '.';
                tambah = false;
            }
        }
        file.close();
    }
    void cetakTugas(std::string nama){
        dataTugas(nama);
        std::stringstream t(tugas_), u(dl_);
        std::string ltugas, ldl;
        int n = 1;
        //cetak daftar tugas
        if (std::find(nama_.begin(), nama_.end(), nama) != nama_.end()){
            std::cout << "Daftar Tugas Belum Selesai:" << std::endl;
            if (tugas_ == ""){
                std::cout << "Tugas tidak ada!" << std::endl;
            }
            else {
                while (std::getline(t, ltugas, '/') && std::getline(u, ldl, '.')){
                    std::cout << n << ". " << ltugas << "( " << ldl << " hari" << " )" << std::endl;
                    n++;
                }
                verifikasiTugas(nama, n);
            }
        }
        else std::cout << "Nama karyawan tidak ada!" << std::endl;
    }
    void cetakKaryawan(){
        system("cls");
        std::cout << "Daftar Karyawan (terurut sesuai kode) :\n";
        std::cout << "NAMA\t\tNIK\n";

        for (int a=0; a<nik_.size(); a++){
            for (int b = a+1; b<nik_.size(); b++){
                if (nik_.at(a) >= nik_.at(b)){
                    std::swap(nama_.at(a), nama_.at(b));
                    std::swap(nik_.at(a), nik_.at(b));
                }
            }
        }

        for (int a=0; a<nik_.size(); a++){
            std::cout << nama_.at(a) << "\t" << nik_.at(a) << std::endl;
        }
        std::cout << std::endl;
    }
    void hasilKerja(){
        system("cls");
        cetakKaryawan();
        std::string nama;
        std::cout << "Pilih nama karyawan: "; std::getline(std::cin >> std::ws, nama);
        cetakTugas(nama);
        system("pause");
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
    }
    void kesimpulanKerja(){
        system("cls");
        //isi tampilan mau gimana
    }
    void verifikasi(std::string nama, int i){
        std::stringstream line(tugas_);
            std::string tugas;
            for (int j=0; j<i; j++){
                std::getline(line, tugas, '/');
            }
            std::ifstream file("data/tugas.dt");
            std::ofstream filetmp("data/temp.dt");
            std::ofstream temp("data/tugas_selesai.dt");
            std::string ln;
            while(std::getline(file, ln)){
                if (ln.find(tugas) != std::string::npos){
                    temp << ln << std::endl;
                }
                else {
                    filetmp << ln << std::endl;
                }
            }
            file.close();
            filetmp.close();
            temp.close();
            remove("data/tugas.dt");
            rename("data/temp.dt", "data/tugas.dt");
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
    }
};

#endif
