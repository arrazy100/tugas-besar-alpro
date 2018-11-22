#include "header/menu.h"
#include "header/main.h"
#include "header/bos.h"

int main(){
    Init init;
    init.awal();
    Menu menu(&init);

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
