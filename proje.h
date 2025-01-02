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


#ifndef PROJE_H
#define PROJE_H

struct Calisan {
    char *calisanAdi;
    char *calisanSoyadi;
    unsigned short int birimKodu;
    float maas;
    int girisYili;
};

struct Birim {
    char *birimAdi;
    unsigned short int birimKodu;
    struct Calisan *birimCalisanlar;
    
};



struct Birim birimOlustur(char *birimAdi, unsigned short int birimKodu);
struct Calisan calisanOlustur(char *calisanAdi, char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili);
void birimleriDiziyeEkle(struct Birim birim, struct Birim *birimler);
void calisanYazdir(struct Calisan calisan);
void birimYazdir(struct Birim birim);
float maasOrtalama(struct Birim birim);
void maasOrtalamaUstuAlanlar(struct Birim birim);  
void enYuksekMaas(struct Birim* birim, int birimSayisi);
void onYildanFazlaCalisanlar(struct Birim *birimler, int birimSayisi, int maas);
void dinamikBirimCalisanYazdir(struct Birim *birimler);
void calisanlariOku(struct Birim *birimler, int birimSayisi, const char *calisanDosyaAdi);
int birimleriOku(struct Birim *birimler, int maxBirimSayisi, const char *birimDosyaAdi);
void dosyayaYaz(struct Birim *birimler, const char *birimDosyaAdi, const char *calisanDosyaAdi);


#endif
