#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_KELIME 100
#define MAX_DOSYA_ADI 100
#define MAX_SATIR 1000

void kucukHarfeCevir(char *yazi)
{
	int i;
    for (i = 0; yazi[i] != '\0'; i++)
    {
        yazi[i] = tolower((unsigned char)yazi[i]);
    }
}

int satirdaGecisSayisi(const char *satir, const char *hedef)
{
    int sayac = 0;
    const char *ptr = satir;
    int hedefUzunluk = strlen(hedef);

    while ((ptr = strstr(ptr, hedef)) != NULL)
    {
        sayac++;
        ptr += hedefUzunluk;
    }

    return sayac;
}

int main()
{
    char hedef_kelime[MAX_KELIME];
    char dosya_adi[MAX_DOSYA_ADI];
    char satir[MAX_SATIR];
    char satirKopya[MAX_SATIR];

    int satirNo = 0;
    int toplamTekrar = 0;
    int gecenSatirSayisi = 0;

    printf("Aramak istediginiz kelime veya cumleyi giriniz: ");
    fgets(hedef_kelime, sizeof(hedef_kelime), stdin);
    hedef_kelime[strcspn(hedef_kelime, "\n")] = '\0';

    if (strlen(hedef_kelime) == 0)
    {
        printf("Bos giris yapildi!\n");
        return 1;
    }

    if (strcmp(hedef_kelime, "let it happen") == 0)
    {
        system("start video.mp4");
        return 0;
    }

    printf("Hangi dosyada ariyorsunuz? ");
    scanf("%99s", dosya_adi);

    FILE *file = fopen(dosya_adi, "r");
    if (file == NULL)
    {
        printf("Hata: Dosya bulunamadi veya acilamadi!\n");
        return 1;
    }

    FILE *rapor = fopen("rapor.txt", "w");
    if (rapor == NULL)
    {
        printf("Hata: rapor.txt olusturulamadi!\n");
        fclose(file);
        return 1;
    }

    char hedefKopya[MAX_KELIME];
    strcpy(hedefKopya, hedef_kelime);
    kucukHarfeCevir(hedefKopya);

    fprintf(rapor, "=== METIN ARAMA RAPORU ===\n");
    fprintf(rapor, "Aranan ifade: %s\n\n", hedef_kelime);

    while (fgets(satir, sizeof(satir), file) != NULL)
    {
        satirNo++;

        strcpy(satirKopya, satir);
        kucukHarfeCevir(satirKopya);

        int adet = satirdaGecisSayisi(satirKopya, hedefKopya);

        if (adet > 0)
        {
            gecenSatirSayisi++;
            toplamTekrar += adet;

            fprintf(rapor, "%d. satirda %d kez bulundu.\n", satirNo, adet);
            fprintf(rapor, "Satir: %s", satir);

            if (satir[strlen(satir) - 1] != '\n')
            {
                fprintf(rapor, "\n");
            }

            fprintf(rapor, "\n");
        }
    }

    fprintf(rapor, "=== OZET ===\n");
    fprintf(rapor, "Ifadenin gectigi satir sayisi: %d\n", gecenSatirSayisi);
    fprintf(rapor, "Ifadenin toplam tekrar sayisi: %d\n", toplamTekrar);

    fclose(file);
    fclose(rapor);

    printf("Arama tamamlandi.\n");
    printf("Sonuclar rapor.txt dosyasina yazildi.\n");

    return 0;
}
