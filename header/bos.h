#ifndef BOS_INCLUDE
#define BOS_INCLUDE

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class Bos {
private:
    char c;
    int i;
public:
    Bos(){
    }
    void inputKaryawan(){
        system("cls");
        std::string nama, nik = "";
        char c;
        std::cout << "Masukkan nama karyawan: "; std::getline(std::cin >> std::ws, nama);
        do {
            std::cout << "Masukkan nik karyawan (harus 4 digit) : "; std::cin >> nik;
        } while (nik.length() != 4);
        std::cout << "Yakin ingin menambah karyawan? "; std::cin >> c;
        if (c == 'y' || c == 'Y'){
            std::fstream file("data/karyawan.dt");
            file.seekp(0, std::ios::end);
            file << "\n" << nama << ":" << nik;
            file.close();
        }
    }
    void cetakKaryawan(){
        system("cls");
        std::string line, nama, nik;
        std::cout << "Daftar Karyawan:\n";
        std::cout << "NAMA\t\tNIK\n";
        std::fstream file("data/karyawan.dt");
        while (getline(file, line)){
            std::stringstream iss(line);
            std::getline(iss, nama, ':');
            std::getline(iss, nik, '\n');
            std::cout << nama << "\t" << nik << "\n";
        }
        std::cout << std::endl;
        file.close();
    }
    void hasilKerja(){
        system("cls");
        cetakKaryawan();
        std::string nama;
        std::cout << "Pilih nama karyawan: "; std::getline(std::cin >> std::ws, nama);
    }
    void tambahTugas(){
        system("cls");
        std::string tugas, dl, target;
        std::cout << "Masukkan Tugas 	: "; std::getline(std::cin >> std::ws, tugas);
		std::cout << "Masukkan Deadline	: "; std::getline(std::cin >> std::ws, dl);
		std::cout << "Masukkan Target	: "; std::getline(std::cin >> std::ws, target);
		std::cout << "Yakin ingin menambahkan tugas? "; std::cin >> c;
		if (c == 'y' || c == 'Y'){
            return;
		}
    }
    void kesimpulanKerja(){
        system("cls");
        //isi tampilan mau gimana
    }
};

#endif
