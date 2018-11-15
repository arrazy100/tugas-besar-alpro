#include "header/menu.h"
#include "header/main.h"
#include "header/bos.h"

int main(){
    Init init;
    Menu menu(&init);
    init.awal();

    while (init.isTrue()){
        if (init.getStatus("bos")){
            menu.bos();
        }
        else if (init.getStatus("karyawan")){
            menu.karyawan();
        }
    }

    system("pause");
    return 0;
}
