
/**
* @file C_proje
* @description :Bu proje, birimlerin ve çalışanların yönetimini sağlayan bir
yazılım geliştirmeyi amaçlamaktadır. Sistem; birim ve çalışan bilgilerini bellekte
tutar, kullanıcıdan gelen verileri işler, istatistiksel hesaplamalar yapar, verileri 
dosyalara yazar ve dosyalardan okuyarak bilgileri yeniden yükler.
* @assignment 1
* @date 22/12/2024
* @author Talha Yılmaz - talha_yilmaz@stu.fsm.edu.tr - 2221221041
*/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "proje.h"


//Birim oluşturur ve gerekli bellek tahsislerini yapar.

struct Birim birimOlustur(char *birimAdi, unsigned short int birimKodu)
{
    struct Birim yeniBirim;
    yeniBirim.birimAdi = (char *)calloc(30, sizeof(char)); // Birim adını tutmak için bellek tahsis et
    strcpy(yeniBirim.birimAdi, birimAdi);
    yeniBirim.birimKodu = birimKodu;
    yeniBirim.birimCalisanlar = (struct Calisan *)calloc(20, sizeof(struct Calisan)); // Çalışanlar dizisini oluştur
    return yeniBirim;
}


//Çalışan oluşturur ve gerekli bellek tahsislerini yapar.

struct Calisan calisanOlustur(char *calisanAdi, char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili)
{
    struct Calisan yeniCalisan;
    yeniCalisan.calisanAdi = (char *)calloc(30, sizeof(char)); // Çalışan adını tutmak için bellek tahsis et
    strcpy(yeniCalisan.calisanAdi, calisanAdi);
    yeniCalisan.calisanSoyadi = (char *)calloc(30, sizeof(char)); // Çalışan soyadını tutmak için bellek tahsis et
    strcpy(yeniCalisan.calisanSoyadi, calisanSoyadi);
    yeniCalisan.birimKodu = birimKodu;
    yeniCalisan.maas = maas;
    yeniCalisan.girisYili = girisYili;
    return yeniCalisan;
}


//Bir çalışanın bilgilerini yazdırır.
 
void calisanYazdir(struct Calisan calisan)
{
    printf("%s,%s,%d,%.2f,%hd", calisan.calisanAdi, calisan.calisanSoyadi, calisan.girisYili, calisan.maas, calisan.birimKodu);
    printf("\n");
}

//Birimin bilgilerini ve çalışanlarını yazdırır.

void birimYazdir(struct Birim birim)
{
    if (birim.birimAdi != NULL)
    {
        printf("%s,%hd\n", birim.birimAdi, birim.birimKodu);

        for (size_t i = 0; i < 20; i++)
        {
            if (birim.birimCalisanlar[i].calisanAdi != NULL)
            {
                calisanYazdir(birim.birimCalisanlar[i]);
                printf("\n");
            }
        }
    }
}


//Birimi diziye ekler, eğer aynı birim kodu varsa eklemez.

void birimleriDiziyeEkle(struct Birim birim, struct Birim *birimler)
{
    // Birimin zaten var olup olmadığını kontrol et
    for (size_t i = 0; i < 20; i++)
    {
        if (birimler[i].birimKodu == birim.birimKodu)
        {
            printf("%d zaten mevcut ekleyemen\n", birim.birimKodu);
            return;
        }
    }

    // Boş bir yer bul ve ekle
    for (int i = 0; i < 20; i++)
    {
        if (birimler[i].birimAdi == NULL)
        {
            birimler[i] = birim;
            return;
        }
    }
    printf("dizi dolu \n");
}


//Tüm birimleri ve çalışanlarını yazdırır.
 
void dinamikBirimCalisanYazdir(struct Birim *birimler)
{
    for (int i = 0; i < 20; i++)
    {
        birimYazdir(birimler[i]);
    }
}

//Birimdeki çalışanların maaş ortalamasını hesaplar.
 
float maasOrtalama(struct Birim birim)
{
    float sum = 0;
    int count = 0;
    for (int i = 0; i < 20; i++)
    {
        if (birim.birimCalisanlar[i].calisanAdi != NULL)
        {
            sum += birim.birimCalisanlar[i].maas;
            count++;
        }
    }
    if (count == 0)
    {
        return 0;
    }
    return sum / count;
}

//Maaşı birim ortalamasının üzerinde olan çalışanları yazdırır.
void maasOrtalamaUstuAlanlar(struct Birim birim)
{
    float maasOrt = maasOrtalama(birim);
    for (size_t i = 0; i < 20; i++)
    {
        if (birim.birimCalisanlar[i].calisanAdi != NULL)
        {
            if (birim.birimCalisanlar[i].maas > maasOrt)
            {
                calisanYazdir(birim.birimCalisanlar[i]);
            }
        }
    }
}


//Her birimdeki en yüksek maaşlı çalışanı bulur ve yazdırır.
void enYuksekMaas(struct Birim *birimler, int birimSayisi)
{
    for (int i = 0; i < birimSayisi; i++)
        if (birimler[i].birimAdi != NULL)
        {
            {
                int maxIndex = -1;
                float maxMaas = 0;

                // Birimdeki en yüksek maaşlı çalışanı bul
                for (int j = 0; j < 20; j++)
                {
                    if (birimler[i].birimCalisanlar[j].calisanAdi != NULL)
                    {
                        if (maxIndex == -1 || birimler[i].birimCalisanlar[j].maas > maxMaas)
                        {
                            maxMaas = birimler[i].birimCalisanlar[j].maas;
                            maxIndex = j;
                        }
                    }
                }

                // Bulunan çalışanı yazdır
                if (maxIndex != -1 && birimler[i].birimCalisanlar[maxIndex].calisanAdi != NULL)
                {
                    printf("Birim: %s - En yuksek maasli calisan: %s %s - Maas: %.2f\n",
                           birimler[i].birimAdi,
                           birimler[i].birimCalisanlar[maxIndex].calisanAdi,
                           birimler[i].birimCalisanlar[maxIndex].calisanSoyadi,
                           birimler[i].birimCalisanlar[maxIndex].maas);
                }
            }
        }
}

//On yıldan fazla süredir çalışan ve maaşı verilen değerden düşük olan çalışanların maaşını artırır.
void onYildanFazlaCalisanlar(struct Birim *birimler, int birimSayisi, int maas)
{
    int suankiYil = 2024;
    for (int i = 0; i < birimSayisi; i++)
        if (birimler[i].birimAdi != NULL)
        {
            {
                for (int j = 0; j < 20; j++)
                {
                    if (birimler[i].birimCalisanlar[j].calisanAdi != NULL)
                    {
                        if (birimler[i].birimCalisanlar[j].maas < maas && suankiYil - birimler[i].birimCalisanlar[j].girisYili > 10)
                        {
                            birimler[i].birimCalisanlar[j].maas = maas;
                        }
                    }
                }
            }
        }
}

//Tüm birim ve çalışan bilgilerini verilen dosyalara yazdırır.
void dosyayaYaz(struct Birim *birimler, const char *birimDosyaAdi, const char *calisanDosyaAdi)
{
    FILE *birimFp = fopen(birimDosyaAdi, "w");
    FILE *calisanFp = fopen(calisanDosyaAdi, "w");

    if (birimFp == NULL || calisanFp == NULL)
    {
        printf("Dosyalardan biri açilamadi: %s veya %s\n", birimDosyaAdi, calisanDosyaAdi);
        if (birimFp != NULL)
            fclose(birimFp);
        if (calisanFp != NULL)
            fclose(calisanFp);
        return;
    }

    // Dizideki her birimi ve çalışanları ilgili dosyalara yaz
    for (int i = 0;; i++)
    {
        if (birimler[i].birimAdi == NULL)
        {
            break;
        }

        fprintf(birimFp, "%s,%d\n", birimler[i].birimAdi, birimler[i].birimKodu);

        for (int j = 0; j < 20; j++)
        {
            if (birimler[i].birimCalisanlar[j].calisanAdi != NULL)
            {
                fprintf(calisanFp, "%s,%s,%.2f,%d,%d\n",
                        birimler[i].birimCalisanlar[j].calisanAdi,
                        birimler[i].birimCalisanlar[j].calisanSoyadi,
                        birimler[i].birimCalisanlar[j].maas,
                        birimler[i].birimCalisanlar[j].girisYili,
                        birimler[i].birimCalisanlar[j].birimKodu);
            }
        }
    }

    fclose(birimFp);
    fclose(calisanFp);
    printf("Bilgiler ayrı dosyalara yazıldı: %s (Birimler), %s (Çalışanlar)\n", birimDosyaAdi, calisanDosyaAdi);
}


//Verilen dosyadan birim bilgilerini okur ve diziye ekler.
int birimleriOku(struct Birim *birimler, int maxBirimSayisi, const char *birimDosyaAdi)
{
    FILE *fp = fopen(birimDosyaAdi, "r");
    if (fp == NULL)
    {
        printf("Dosya açılamadı: %s\n", birimDosyaAdi);
        return 0;
    }

    int birimSayisi = 0;

    while (birimSayisi < maxBirimSayisi)
    {
        char birimAdi[30];
        int birimKodu;

        int result = fscanf(fp, "%[^,],%d\n", birimAdi, &birimKodu);
        if (result == 2)
        {
            int mevcut = 0;
            for (int i = 0; i < birimSayisi; i++)
            {
                if (birimler[i].birimKodu == birimKodu)
                {
                    mevcut = 1;
                    printf("aynı birim kodlu %d %s birimi eklenemez\n", birimler[i].birimKodu, birimler[i].birimAdi);
                    break;
                }
            }

            if (!mevcut)
            {
                birimler[birimSayisi] = birimOlustur(birimAdi, birimKodu);
                birimSayisi++;
            }
        }
        else
        {
            break;
        }
    }

    fclose(fp);
    return birimSayisi;
}

//Verilen dosyadan çalışan bilgilerini okur ve ilgili birimlere ekler.
void calisanlariOku(struct Birim *birimler, int birimSayisi, const char *calisanDosyaAdi)
{
    FILE *fp = fopen(calisanDosyaAdi, "r");
    if (fp == NULL)
    {
        printf("Dosya açılamadı: %s\n", calisanDosyaAdi);
        return;
    }

    while (1)
    {
        char calisanAdi[30], calisanSoyadi[30];
        int birimKodu, girisYili;
        float maas;

        int result = fscanf(fp, "%[^,],%[^,],%f,%d,%d\n", calisanAdi, calisanSoyadi, &maas, &girisYili, &birimKodu);
        if (result == 5)
        {
            struct Calisan yeniCalisan = calisanOlustur(calisanAdi, calisanSoyadi, birimKodu, maas, girisYili);

            int bulundu = 0;
            for (int i = 0; i < birimSayisi; i++)
            {
                if (birimler[i].birimKodu == birimKodu)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if (birimler[i].birimCalisanlar[j].calisanAdi == NULL)
                        {
                            birimler[i].birimCalisanlar[j] = yeniCalisan;
                            bulundu = 1;
                            break;
                        }
                    }
                    break;
                }
            }

            if (!bulundu)
            {
                printf("HATA: %d kodlu birim bulunamadı! Çalışan eklenemedi: %s %s\n", birimKodu, calisanAdi, calisanSoyadi);
            }
        }
        else
        {
            break;
        }
    }

    fclose(fp);
}
