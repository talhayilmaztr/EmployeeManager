
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

#include <stdio.h>
#include <stdlib.h>
#include "proje.h"

#include <stdlib.h>
#include <stdio.h>
#include "proje.h"

int main(int argc, char *argv[])
{
    // Command line parametre kontrolü
    if (argc < 3)
    {
        printf("Kullanım: %s <birimDosyaAdi> <calisanDosyaAdi>\n", argv[0]);
        return 1;
    }

    const char *birimDosya = argv[1];  
    const char *calisanDosya = argv[2]; 

    struct Birim *birimler = (struct Birim *)calloc(20, sizeof(struct Birim));
    if (birimler == NULL)
    {
        printf("Bellek tahsisi başarısız oldu.\n");
        return 1;
    }

    // 1. Dosyalardan verileri oku
    printf("**Dosyalardan Veriler Okunuyor**\n");
    int birimSayisi = birimleriOku(birimler, 20, birimDosya);
    calisanlariOku(birimler, birimSayisi, calisanDosya);

    // Eğer dosyalar boşsa veya hiç veri yoksa, örnek birimler ve çalışanlar oluştur
    if (birimSayisi == 0)
    {
        printf("Dosyalarda veri bulunamadı. Örnek birimler ve çalışanlar oluşturuluyor...\n");

        birimler[0] = birimOlustur("Muhasebe", 100);
        birimler[0].birimCalisanlar[0] = calisanOlustur("Ali", "Yılmaz", 100, 5000.0, 2010);
        birimler[0].birimCalisanlar[1] = calisanOlustur("Ayşe", "Demir", 100, 7000.0, 2015);
        birimler[0].birimCalisanlar[2] = calisanOlustur("Mehmet", "Kaya", 100, 4000.0, 2008);

        birimler[1] = birimOlustur("IT", 101);
        birimler[1].birimCalisanlar[0] = calisanOlustur("Zeynep", "Kara", 101, 8000.0, 2012);
        birimler[1].birimCalisanlar[1] = calisanOlustur("Ahmet", "Çelik", 101, 3500.0, 2020);

        birimler[2] = birimOlustur("Satış", 102);
        birimler[2].birimCalisanlar[0] = calisanOlustur("Fatma", "Kara", 102, 7000.0, 2011);
        birimler[2].birimCalisanlar[1] = calisanOlustur("Hasan", "Çelik", 102, 5000.0, 2018);

        struct Birim birimNew =birimOlustur("Finans", 103); 
        birimNew.birimCalisanlar[1] = calisanOlustur("Fatih", "Yıldız", 103, 5000.0, 2011);
        birimleriDiziyeEkle(birimNew, birimler); //Oluşturulan birimi diziye ekler

      
    }

    // 2. Verileri işle ve yazdır
    printf("\n**Birim ve Çalışan Bilgileri**\n");
    for (int i = 0; i < 20; i++)
    {
        if (birimler[i].birimAdi != NULL)
        {
            birimYazdir(birimler[i]);
        }
    }

    printf("\n**Maaş Ortalamaları**\n");
    for (int i = 0; i < 20; i++)
    {
        if (birimler[i].birimAdi != NULL)
        {
            float ortalama = maasOrtalama(birimler[i]);
            printf("%s Birimi Maaş Ortalaması: %.2f\n", birimler[i].birimAdi, ortalama);
        }
    }

    printf("\n**Maaş Ortalamasını Geçen Çalışanlar**\n");
    for (int i = 0; i < 20; i++)
    {
        if (birimler[i].birimAdi != NULL)
        {
            printf("Birim: %s\n", birimler[i].birimAdi);
            maasOrtalamaUstuAlanlar(birimler[i]);
            printf("\n");
        }
    }

    printf("\n**En Yüksek Maaşlı Çalışanlar**\n");
    enYuksekMaas(birimler, 20);

    // 3. 10 yıldan fazla çalışanların maaşını güncelle
    printf("\n**10 Yıldan Fazla Çalışanların Maaşını Güncelleme (6000)**\n");
    onYildanFazlaCalisanlar(birimler, 20, 6000);
    for (int i = 0; i < 20; i++)
    {
        if (birimler[i].birimAdi != NULL)
        {
            birimYazdir(birimler[i]);
        }
    }
    printf("\n");

    // 4. Güncellenmiş verileri dosyalara yaz
    printf("**Güncellenmiş Veriler Dosyalara Yazılıyor**\n");
    dosyayaYaz(birimler, birimDosya, calisanDosya);
    printf("Bilgiler dosyalara yazıldı: %s, %s\n", birimDosya, calisanDosya);
    printf("\n");

    // 5. Dosyalardan okunan güncellenmiş verileri yazdır
    printf("**Dosyalardan Okunan Güncellenmiş Bilgiler**\n");
    birimSayisi = birimleriOku(birimler, 20, birimDosya);
    calisanlariOku(birimler, birimSayisi, calisanDosya);
    for (int i = 0; i < 20; i++)
    {
        if (birimler[i].birimAdi != NULL)
        {
            birimYazdir(birimler[i]);
        }
    }
    printf("\n");

    // Belleği temizle
    free(birimler);

    return 0;
}
