#ifndef KARYAWAN_INCLUDE
#define KARYAWAN_INCLUDE

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class Karyawan {
private:
    std::string tugas_ = "", dl_ = "";
    char c;
    int i;
public:
    Karyawan(){
    }
    void daftarTugas(std::string namat){
        system("cls");
        //data tugas
        std::fstream file("data/tugas.dt");
        std::string line, nama, tugas, dl;
        bool tambah = false;
        while (std::getline(file, line)){
            std::stringstream iss(line);
            std::getline(iss, nama, ':');
            if (namat == nama){
                std::getline(iss, tugas, ',');
                std::getline(iss, dl, '\n');
                tambah = true;
            }
            if (tambah){
                tugas_ = tugas_ + tugas + "/";
                dl_ = dl_ + dl + '_';
                tambah = false;
            }
        }
        file.close();
        //cetak tugas
        if (tugas_ == ""){
            std::cout << "Tugas tidak ada! \n";
        }
        else {
            std::cout << "Daftar Tugas : \n";
            std::stringstream t(tugas_), u(dl_);
            std::string ltugas, ldl, nf;
            int n = 0;
            while (std::getline(t, ltugas, '/') && std::getline(u, ldl, '_')){
                std::cout << n+1 << ". " << ltugas << "( " << ldl << " )" << std::endl;
                n++;
            }
            std::cout << "Mau input tugas? "; std::cin >> c;
            if (c == 'y' || c == 'Y'){
                do {
                    std::cout << "Pilih nomor tugas : "; std::cin >> i;
                } while (i>n);
                std::cout << "Nama file tugas : "; std::getline(std::cin >> std::ws, nf);
                inputTugas(namat, nf, i);
            }
        }
        system("pause");
        return;
    }
    void inputTugas(std::string nama, std::string nf, int index){
        std::stringstream line(tugas_);
        std::string tugas, output;
        for (int j=0; j<index; j++){
            std::getline(line, tugas, '/');
        }
        output = nama + ":" + tugas + "," + nf;
        std::fstream file("data/tugas_selesai.dt");
        file.seekp(0, std::ios::end);
        file << output << "\n";
        file.close();
    }
    void tugasDone(std::string nama){
        //bikin tampilan
    }
    void laporanBulanan(std::string nama){
        //bikin tampilan
    }
};

#endif
