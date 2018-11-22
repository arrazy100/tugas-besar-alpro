#ifndef MAIN_INCLUDE
#define MAIN_INCLUDE

#include "bos.h"

class Init {
private:
    int i;
    char c;
    std::string usr, pass;
    std::string namalengkap, username = "", password = "", status;
    bool is_bos;
    bool is_true;
    Bos bos;
public:
    Init(){
    }
    void awal(){
        is_true = true;
        usr = "";
        pass = "";
        system("cls");
        std::cout << "====== SOFTWARE PERUSAHAAN PT TUNGGAL IKA ======" << std::endl;
        std::cout << "1. Login \n";
        std::cout << "0. Keluar \n";
        std::cout << "Pilih menu: "; std::cin >> i;
        switch(i){
        case 0: is_true = false; break;
        case 1: login(); break;
        }
    }
    void login(){
        system("cls");
        std::cout << "====== LOGIN SESSION ======\n";
        std::cout << "Username: "; std::getline(std::cin >> std::ws, usr);
        std::cout << "Password: "; std::getline(std::cin >> std::ws, pass);
        if (!log(usr, pass)){
            std::cout << "Username/ password salah\n";
            std::cout << "Coba lagi? "; std::cin >> c;
            if (c == 'y' || c == 'Y') login();
            else {
                std::cout << "Kembali ke menu utama? "; std::cin >> c;
                if (c == 'y' || c == 'Y') awal();
            }
        }
    }
    bool log(std::string user, std::string pass){
        std::ifstream file("data/data.dt");
        while (!file.eof()){
            file >> namalengkap;
            file >> username;
            file >> password;
            file >> status;
            if (username == user && password == pass){
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    std::string getNama(){
        std::replace(namalengkap.begin(), namalengkap.end(), '_', ' ');
        return namalengkap;
    }
    bool getStatus(std::string jabatan){
        return (status == jabatan);
    }
    bool isTrue(){
        return is_true;
    }
    void setTrue(bool status){
       is_true = status;
    }
};

#endif
