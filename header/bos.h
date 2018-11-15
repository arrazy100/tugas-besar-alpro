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
    std::vector<std::string> nama_;
    std::vector<std::string> nik_;
public:
    Bos(){
        dataKaryawan();
    }
    void inputKaryawan(){
        system("cls");
        std::string nama, nik = "";
        char c;
        std::cout << "Masukkan nama karyawan: "; std::getline(std::cin >> std::ws, nama);
        do {
            std::cout << "Masukkan kode karyawan (harus 4 digit) : "; std::cin >> nik;
        } while (nik.length() != 4);
        std::cout << "Yakin ingin menambah karyawan? "; std::cin >> c;
        if (c == 'y' || c == 'Y'){
            std::fstream file("data/karyawan.dt");
            file.seekp(0, std::ios::end);
            file << "\n" << nama << ":" << nik;
            file.close();
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
    void cetakKaryawan(){
        system("cls");
        std::cout << "Daftar Karyawan (terurut sesuai kode) :\n";
        std::cout << "NAMA\t\tNIK\n";

        for (auto a=0; a<nik_.size(); a++){
            for (auto b = a+1; b<nik_.size(); b++){
                if (nik_.at(a) >= nik_.at(b)){
                    std::swap(nama_.at(a), nama_.at(b));
                    std::swap(nik_.at(a), nik_.at(b));
                }
            }
        }

        for (auto a=0; a<nik_.size(); a++){
            std::cout << nama_.at(a) << "\t" << nik_.at(a) << std::endl;
        }
        std::cout << std::endl;
        system("pause");
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
