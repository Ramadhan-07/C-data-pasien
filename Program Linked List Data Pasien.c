#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<ctype.h>
#define YA 1    // to define that ya is equals to 1
#define TIDAK 0 // to define that tidak equals to 0
#define NULL 0  // to define that null equals to 0

struct catatan_pasien // define the struct
{
    char nama[15];
    char penyakit[21];
    char asal[15];
    unsigned long nopas;
    char ruang[14];
    struct catatan_pasien *next;
};

struct catatan_pasien *awal;
struct catatan_pasien *catat(struct catatan_pasien *tampung, struct catatan_pasien *ujung)
{
    printf("Nomor Pasien    : "); // display nomor pasien
    scanf("%lu", &ujung->nopas);  // to give input to nomor pasien in variable ujung->nopas
    printf("Nama Pasien     : ");
    scanf("%s", &ujung->nama);
    printf("Nama Ruangan    : ");
    scanf("%s", &ujung->ruang);
    printf("Menderita Sakit : ");
    scanf("%s", &ujung->penyakit);
    printf("Alamat Asal     : ");
    scanf("%s", &ujung->asal);
    printf("\n");
    ujung->next=NULL;

    if(tampung==NULL)
    {
        tampung = ujung;
    }
    else
    {
        tampung->next = ujung;
        tampung = ujung;
    }
    return(tampung);
};

disajikan_ya_tidak()
{
    char jawab;
    int j;
    printf("Dilanjutkan?  (Y/T)\n");
    if((toupper(jawab=getche()))=='T')
        j=0;
    else if(toupper(jawab)=='Y')
        j=1;
    else
    {
        printf("\nJawaban Harus (Y,y) atau (T,t)\n");
        j=1;
    }
    printf("\n");
    return(j);
}

void sajikan_hasil(struct catatan_pasien *ujung) //define function sajikan_hasil
{
    char *p;
    printf(">>>>>>>>>>>>>>>>>|| Data Pasien Rumah Sakit Cepet Sehat ||<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("=================================================================================\n");
    printf("|No Pasien |  Nama Pasien  | Nama Ruangan |  Penyakit diderita  |  Alamat Asal  |\n");
    printf("=================================================================================\n");
    ujung=awal;

    while(ujung!=NULL)
    {
        p=&(ujung->nama[0]);
        printf("|%-10lu|%-10s     |%-10s    |%-10s           |%-10s     |\n", ujung->nopas, p, ujung->ruang, ujung->penyakit, ujung->asal);
        ujung = ujung->next;
    }
}

void sisipkan_1_catatan(struct catatan_pasien *tampung)
{
    unsigned long h;
    struct catatan_pasien *p;
    printf("\n\rDisisipkan Setelah Nomor(?) ");
    scanf("%lu", &h);
    p=awal;

    while(p!=NULL)
    {
        if(p->nopas==h)
        {
            tampung = (struct catatan_pasien*)malloc(sizeof(*tampung)); // to allocate catatan_pasien to variable tampung
            printf("\nData Pasien Yang Disisipkan\n");
            printf("Nomor Pasien    : ");
            scanf("%lu", &tampung->nopas);
            printf("Nama Pasien     : ");
            scanf("%s", &tampung->nama);
            printf("Nama Ruangan    : ");
            scanf("%s", &tampung->ruang);
            printf("Menderita Sakit : ");
            scanf("%s", &tampung->penyakit);
            printf("Alamat Asal     : ");
            scanf("%s", &tampung->asal);
            printf("\n");
            tampung->next = p->next;
            p->next = tampung;
            p = tampung;
        }
        p=p->next;
    }
}

hapus_1_catatan(struct catatan_pasien *ujung) // function to delete one data from catatan_pasien
{
    unsigned long h;
    struct catatan_pasien *p;
    struct catatan_pasien *tampung;
    printf("\nNo Pasien yang akan dihapus(?)\n");
    scanf("%lu", &h);
    if(awal->nopas==h)
    {
        p = awal->next;
        free(awal);
        awal = p;
    }
    else
    {
        p = awal;
        p = tampung;
        while(p!=NULL)
        {
            ujung = p;
            p = p->next;
            if(p->nopas==h)
            {
                ujung->next = p->next;
                free(p);
                p = ujung->next;
            }
        }
    }
    return 0;
}

menu_sisip_hapus()
{
    printf("\nSilahkan Pilih Menu \n");
    printf("PILIHAN: \n");

    printf("   H atau h : Hapus Satu Data\n");

    printf("   S atau s : Sisipkan satu Data\n");

    printf("   E atau e : Selesai atau exit\n");

    return 0;
}

void pilihan(struct catatan_pasien *ujung)
{
    char p;
    while((toupper(p=getche()))!='e')
    {
        switch (p)
        {
            case 's' :
            {
                sisipkan_1_catatan(ujung);
                sajikan_hasil(ujung);
                menu_sisip_hapus();
                break;
            }

            case 'h' :
            {
                hapus_1_catatan(ujung);
                sajikan_hasil(ujung);
                menu_sisip_hapus();
                break;
            }

            case 'e' :
            {
                printf("\nPilihan sisip hapus selesai\n");
                getche();
                break;
            }

            default :
            {
                printf("\njawaban harus (H,h) atau (S,s) atau (E,e\n");
                break;
            }
        }
    }
}

main()
{
    struct catatan_pasien *tampung;
    struct catatan_pasien *ujung;
    int jawab;
    printf("||||||||||||  RUMAH SAKIT CEPET SEHAT |||||||||||||\n");
    printf("\n");
    printf("Masukkan Data Pasien \n");
    awal = NULL;
    tampung = NULL;
    jawab = YA;
    while(jawab==YA)
    {
        ujung=(struct catatan_pasien *)malloc(sizeof(struct catatan_pasien));
        if(awal==NULL)
        {
            awal = catat(tampung,ujung);
            tampung = awal;
        }
        else
            tampung = catat(tampung, ujung);
        jawab = disajikan_ya_tidak();
    }
    printf("Hasil Masukkan Disajikan Kembali Di Layar: \n");
    sajikan_hasil(ujung);
    menu_sisip_hapus();
    pilihan(tampung);
}
