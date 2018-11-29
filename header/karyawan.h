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
        tugas_ = ""; dl_ = "";
        //data tugas
        std::ifstream f;
        std::fstream file("data/tugas.dt");
        std::string line, nama, tugas, dl;
        bool tambah = false;
        while (std::getline(file, line)){
            std::stringstream iss(line);
            std::getline(iss, nama, ':');
            if (namat == nama){
                std::getline(iss, tugas, ',');
                if (line.find(">") != std::string::npos) continue;
                std::getline(iss, dl, '<');
                tambah = true;
            }
            if (namat == nama && tambah){
                tugas_ = tugas_ + tugas + "/";
                dl_ = dl_ + dl + '_';
                tambah = false;
            }
        }
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
            std::cout << "Mau input tugas? "; tangkapError(&c);
            if (c == 'y' || c == 'Y'){
                do {
                    std::cout << "Pilih nomor tugas : "; tangkapError(&i);
                } while (i>n);
                std::cout << "Nama file tugas (Drag & Drop File ke Console) : "; std::getline(std::cin >> std::ws, nf);
                nf.erase(0, 1);
                nf.pop_back();
                f.open(nf.c_str());
                if (f.is_open()){
                    if (dl == "") return;
                    file.close();
                    f.close();
                    inputTugas(namat, nf, i);
                }
                else {
                    std::cout << "File tidak ada" << std::endl;
                    file.close();
                    f.close();
                }
            }
        }
        system("pause");
        return;
    }
    void inputTugas(std::string nama, std::string nf, int index){
        //copy file ke folder tugas
        std::string nama_s = nama;
        nama_s.erase(std::remove_if(nama_s.begin(), nama_s.end(), ::isspace), nama_s.end());
        std::string ext = nf.substr(nf.find_last_of("."));
        std::string k = nf.substr(nf.find_last_of(".")-5, 5);
        std::string path = "tugas/" + nama_s + "_" + k + ext;
        std::ifstream source(nf.c_str(), std::ios::binary);
        std::ofstream to(path.c_str(), std::ios::binary);
        to << source.rdbuf();
        source.close();
        to.close();
        //edit tugas.dt
        std::stringstream line(tugas_);
        std::string tugas, output, cari, dl, ln, namat, tugast;
        for (int j=0; j<index; j++){
            std::getline(line, tugas, '/');
        }
        std::ifstream dtugas("data/tugas.dt");
        std::ofstream temp("data/temp.dt");
        while(std::getline(dtugas, ln)){
            std::stringstream iss(ln);
            std::getline(iss, namat, ':');
            std::getline(iss, tugast, ',');
            std::getline(iss, dl, '<');
            if (namat == nama && tugast == tugas){
                cari = nama + ":" + tugas + "," + dl;
                temp << cari << ">" << std::endl;
            }
            else {
                temp << ln << std::endl;
            }
        }
        dtugas.close();
        temp.close();
        remove("data/tugas.dt");
        rename("data/temp.dt", "data/tugas.dt");
        //tulis ke tugas_selesai.dt
        output = nama + ":" + tugas + "," + nama_s + "_" + k + ext + ">";
        std::fstream file("data/tugas_selesai.dt");
        file.seekp(0, std::ios::end);
        file << output << "\n";
        file.close();
        return;
    }
    void tugasDone(std::string namat){
        system("cls");
        std::ifstream file("data/tugas_verify.dt");
        std::string nama, tugas, ln;
        int n = 0;
        std::cout << "Tugas Terverifikasi : " << std::endl;
        while(std::getline(file, ln)){
            std::stringstream iss(ln);
            std::getline(iss, nama, ':');
            std::getline(iss, tugas, ',');
            if (namat == nama){
                std::cout << n+1 << ". " << tugas << std::endl;
                n++;
            }
        }
        file.close();
        system("pause");
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
