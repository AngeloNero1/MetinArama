#include<stdio.h>
#include<string.h>
#include<ctype.h>



int main(){

    char hedef_kelime[15];
    char dosya_adi[15];
    char satir[333];
    int satirNo=0,tekrar_sayisi=0;



    printf("Aramak istediginiz kelimeyi giriniz:");
    scanf("%s",hedef_kelime);

    printf("Hangi dosyada ariyorsunuz?");
    scanf("%s",dosya_adi);




    ///Bu kisim aranacak kelimenin harflerini kuculten dongu...
    for(int i=0;hedef_kelime[i]!='\0';i++){
        hedef_kelime[i]=tolower(hedef_kelime[i]);

    }
    FILE *file=fopen(dosya_adi,"r");



    if (file == NULL) {
        printf("Hata: Dosya bulunamadi veya acilamadi!\n");
        return 1;
    }
    while (fgets(satir, sizeof(satir), file) != NULL) {/// buradaki fgets o satirdaki tum herseyi yakalar bosluk, noktalama dahil bizim kodda bunu satir[] dizisine aktariyor...
        satirNo++;// oldugumuz satir sayisini gostermemizde fayda saglicak...



        ///Bu kisim satirdakinleri kucuk harfe gecirme islemi...
        for(int i=0;satir[i]!='\0';i++){

            satir[i]=tolower(satir[i]);



        }



        char *ptr=strstr(satir,hedef_kelime);
        while(ptr!=NULL){
            tekrar_sayisi++;// toplam tekrar sayisini yaazdirdigimizda bu kisim yazilacak...
            printf("Kelime %d. satirda bulundu!\n",satirNo);

            ptr = strstr(ptr + strlen(hedef_kelime), hedef_kelime);/// buldugumuz kelime uzunlugu kadar ileri atliyor oradan okumaya deva ediyor dongu herseyy bitince bitmis oluyor...
        }



    }
    fclose(file);



    // bura raporlama yapacagimiz eksstra dosya...
    printf("Aranan kelime toplam %d kez bulundu.\n", tekrar_sayisi);
    FILE *raporlama = fopen("rapor.txt", "w"); 
    if (raporlama != NULL) {
        fprintf(raporlama, "Aranan kelime toplam %d kez bulundu.\n", tekrar_sayisi);
        fclose(raporlama);
        
    }





    return 0;
}
