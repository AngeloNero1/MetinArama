#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SATIR 500
#define MAX_KELIME 100

int bos_mu(char metin[]);
int esit_mi_buyuk_kucuk_harf_duyarsiz(char a[], char b[]);
int satirda_kelime_sayisi(char satir[], char kelime[]);

int main()
{
    FILE *girisDosyasi;
    FILE *cikisDosyasi;

    char girisDosyaAdi[] = "metin.txt";
    char cikisDosyaAdi[] = "sonuc.txt";
    char videoYolu[] = "video.mp4";

    char kelime[MAX_KELIME];
    char satir[MAX_SATIR];

    int satirNo = 0;
    int toplamAdet = 0;
    int gecenSatirSayisi = 0;
    int satirdakiAdet;

    girisDosyasi = fopen(girisDosyaAdi, "r");

    if (girisDosyasi == NULL)
    {
        printf("metin.txt dosyasi bulunamadi!\n");
        return 1;
    }

    printf("Aranacak kelimeyi girin: ");
    fgets(kelime, MAX_KELIME, stdin);

    kelime[strcspn(kelime, "\n")] = '\0';

    if (bos_mu(kelime))
    {
        printf("Gecerli bir giris yapmadiniz!\n");
        fclose(girisDosyasi);
        return 1;
    }

    if (esit_mi_buyuk_kucuk_harf_duyarsiz(kelime, "let it happen"))
    {
        FILE *videoKontrol = fopen(videoYolu, "r");

        if (videoKontrol != NULL)
        {
            fclose(videoKontrol);
            system("start video.mp4");
            printf("Video acildi.\n");
        }
        else
        {
            printf("video.mp4 dosyasi bulunamadi!\n");
        }

        fclose(girisDosyasi);
        return 0;
    }

    cikisDosyasi = fopen(cikisDosyaAdi, "w");

    if (cikisDosyasi == NULL)
    {
        printf("sonuc.txt dosyasi olusturulamadi!\n");
        fclose(girisDosyasi);
        return 1;
    }

    fprintf(cikisDosyasi, "=== METIN ARAMA RAPORU ===\n");
    fprintf(cikisDosyasi, "Aranan kelime: %s\n\n", kelime);

    while (fgets(satir, MAX_SATIR, girisDosyasi) != NULL)
    {
        satirNo++;
        satirdakiAdet = satirda_kelime_sayisi(satir, kelime);

        if (satirdakiAdet > 0)
        {
            gecenSatirSayisi++;
            toplamAdet += satirdakiAdet;

            fprintf(cikisDosyasi, "%d. satirda %d kez bulundu.\n", satirNo, satirdakiAdet);
            fprintf(cikisDosyasi, "Satir: %s", satir);

            if (satir[strlen(satir) - 1] != '\n')
            {
                fprintf(cikisDosyasi, "\n");
            }

            fprintf(cikisDosyasi, "\n");
        }
    }

    fprintf(cikisDosyasi, "=== OZET ===\n");
    fprintf(cikisDosyasi, "Kelimenin gectigi satir sayisi: %d\n", gecenSatirSayisi);
    fprintf(cikisDosyasi, "Kelimenin toplam gecis sayisi: %d\n", toplamAdet);

    fclose(girisDosyasi);
    fclose(cikisDosyasi);

    printf("Arama tamamlandi.\n");
    printf("Sonuclar sonuc.txt dosyasina yazildi.\n");

    return 0;
}

int bos_mu(char metin[])
{
    int i;

    for (i = 0; metin[i] != '\0'; i++)
    {
        if (metin[i] != ' ' && metin[i] != '\t')
        {
            return 0;
        }
    }

    return 1;
}

int esit_mi_buyuk_kucuk_harf_duyarsiz(char a[], char b[])
{
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0')
    {
        if (tolower(a[i]) != tolower(b[i]))
        {
            return 0;
        }
        i++;
    }

    if (a[i] == '\0' && b[i] == '\0')
    {
        return 1;
    }

    return 0;
}

int satirda_kelime_sayisi(char satir[], char kelime[])
{
    int i, j;
    int sayac = 0;
    int bulundu;

    for (i = 0; satir[i] != '\0'; i++)
    {
        bulundu = 1;

        for (j = 0; kelime[j] != '\0'; j++)
        {
            if (tolower(satir[i + j]) != tolower(kelime[j]))
            {
                bulundu = 0;
                break;
            }
        }

        if (bulundu == 1 && kelime[0] != '\0')
        {
            sayac++;
            i = i + j - 1;
        }
    }

    return sayac;
}
