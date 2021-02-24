#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dugum
{
    int plakakodu;
    char *sehiradi;
    char *bolge;
    int komsusayisi;
    struct dugum *prev;
    struct dugum *next;
    struct dugum2 *komsu;
};

struct dugum2
{
    int komsuplaka;
    struct dugum2 *next2;
};

struct dugum* YeniDugum(int plakakod,char *sehirad,char *sehirbolge,int komsu_sayi)
{
    struct dugum *Yeni_dugum=(struct dugum*)malloc(sizeof(struct dugum));
    Yeni_dugum->plakakodu=plakakod;
    Yeni_dugum->sehiradi=sehirad;
    Yeni_dugum->bolge=sehirbolge;
    Yeni_dugum->komsusayisi=komsu_sayi;
    Yeni_dugum->next=NULL;
    Yeni_dugum->prev=NULL;
    return Yeni_dugum;
};

struct dugum *baslangic=NULL;
struct dugum *karsilastirma=NULL;
struct dugum *temp=NULL;
struct dugum *silGecici = NULL;
struct dugum *son=NULL;
struct dugum *sil=NULL;

void satirbolme(char *dosyayolu)
{
    FILE *dosya=fopen(dosyayolu,"r");
    char *satir;
    char *kelime;
    // kelime=(char *)calloc(20,sizeof(char));
    char *pointer;
    int sayac=0;
    int komsular=-1;
    int yollananplaka;
    char * yollanankent;
    char *yollananbolge;
    int yollanankomsusayisi;
    pointer=(char *)malloc(100*sizeof(char));
    kelime=(char *)malloc(20*sizeof(char));

    if(!feof(dosya))
    {
        satir=(char *)malloc(100*sizeof(char));
        while(fgets(satir,"%s",dosya)!=NULL)
        {

            pointer=strtok(satir,"\n");
            // printf("%s\n",pointer);

            if(sayac==0)
            {
                kelime=strtok(pointer,",");
                //printf("%s\n",kelime);
                sayac++;
                yollananplaka=atoi(kelime);
            }
            if(sayac==1)
            {
                kelime=strtok(NULL,",");
                //printf("%s\n",kelime);
                sayac++;
                yollanankent=(char *)malloc(20*sizeof(char));
                strcpy(yollanankent, kelime);
            }
            if(sayac==2)
            {
                kelime=strtok(NULL,",");
                // printf("%s\n",kelime);
                sayac++;
                yollananbolge=(char *)malloc(3*sizeof(char));
                strcpy(yollananbolge,kelime);
            }
            while(kelime!=NULL)
            {
                kelime=strtok(NULL,",");
                //printf("%s\n",kelime);
                komsular++;
            }
            if(kelime==NULL)
            {
                yollanankomsusayisi=komsular;
                // printf("%d\n",komsular);
            }
            karsilastirma=YeniDugum(yollananplaka,yollanankent,yollananbolge,yollanankomsusayisi);

            komsular=-1;
            sayac=0;
            sonaEkle(karsilastirma);
        }
    }
    fclose(dosya);
}

void sonaEkle(struct dugum *node)
{
    if(baslangic==NULL)
    {
        baslangic=node;
    }
    else
    {
        temp=baslangic;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }

        node->prev=temp;
        temp->next=node;
    }
}

void Listele()
{
    temp=baslangic;
    while(temp!=NULL)
    {
        printf("\n");
        printf(" Plaka Kodu: %d \n",temp->plakakodu);
        printf(" Sehir Adi: %s \n",temp->sehiradi);
        printf(" Bolge: %s \n",temp->bolge);
        printf(" Komsu Sayisi: %d \n",temp->komsusayisi);
        printf("\n");
        temp=temp->next;
    }
}

void ciktidosyasi()
{
    FILE *cikti = fopen("cikti.txt","a");
    temp=baslangic;
    while(temp!=NULL)
    {
        fprintf(cikti,"\nPlaka Kodu:%d\n",temp->plakakodu);
        fprintf(cikti,"Sehir Adi:%s\n",temp->sehiradi);
        fprintf(cikti,"%Bolge:%s\n",temp->bolge);
        fprintf(cikti,"%Komsu sayisi:%d\n\n",temp->komsusayisi);
        temp=temp->next;
    }
    fclose(cikti);
}

struct dugum *Ara(int x)
{
    struct dugum *ara=(struct dugum*)malloc(sizeof(struct dugum));
    ara=baslangic;
    while(ara!=NULL)
    {
        if(ara->plakakodu==x)
            return ara;
        ara=ara->next;
    }
    return NULL;
}

struct dugum *Arasehiradi(char *x)
{
    struct dugum *ara=(struct dugum*)malloc(sizeof(struct dugum));
    ara=baslangic;
    while(ara!=NULL)
    {
        if(strcmp(ara->sehiradi,x)==0)
            return ara;
        ara=ara->next;
    }
    return NULL;
}

struct dugum *Arabolge(char *x)
{
    struct dugum *ara=(struct dugum*)malloc(sizeof(struct dugum));
    ara=baslangic;

    while(ara!=NULL)
    {
        if(strcmp(ara->bolge,x)==0)
            return ara;
        ara=ara->next;
        return NULL;
    }
}

void silme(char *veri)
{
    int kontrol = 0;
    if(baslangic == NULL)
        kontrol = -1;

    else if(strcmp(baslangic->sehiradi,veri)==0)
    {
        silGecici = baslangic;
        baslangic = baslangic->next;
        free(silGecici);
        kontrol = 1;
    }

    else
    {

        temp = baslangic;

        while(temp->next != NULL)
        {


            if(strcmp(temp->next->sehiradi,veri)==0)
            {
                kontrol = 1;
                silGecici = temp->next;

                if(silGecici == son)
                    son = temp;

                temp->next = sil->next;
                free(silGecici);
                break;

            }

            temp = temp->next;

        }
    }
    if(kontrol == 0)
        printf("Silmek Istediginiz Sehir Listede Yoktur...\n\n");
    else if(kontrol == -1)
        printf("Listede eleman yoktur...\n\n");
    else if(kontrol == 1)
        printf("%s sehiri listeden silinmistir...\n\n",veri);
}

void Sirala()
{
    struct dugum *dolas=(struct dugum*)malloc(sizeof(struct dugum));
    struct dugum *adim=baslangic;
    while(adim!=NULL)
    {
        dolas=baslangic;
        while(dolas!=NULL)
        {
            if(dolas->plakakodu > dolas->next->plakakodu)
            {
                int temp=dolas->plakakodu;
                dolas->plakakodu=dolas->next->plakakodu;
                dolas->next->plakakodu=temp;
            }
            dolas=dolas->next;
        }
        adim=adim->next;
    }
}

int main()
{
    int secim=0;
    char dosyayol[100]="sehirler.txt";
    char ekleneceksehir[100];
    char aranansehir[20];
    FILE *deneme = fopen(dosyayol,"a");
    int arananplaka;
    int yes=0;
    char bolgeAra[2];
    int aranacakkomsusayisi=0;
    char silineceksehir[100];

    satirbolme(dosyayol);
    // Listele();

    struct dugum *bulunan=(struct dugum*)malloc(sizeof(struct dugum));

    printf("1)Yeni bir sehir ekleyin\n");
    printf("2)Sehir arama(plaka koduna gore)\n");
    printf("3)Sehir arama(sehir adina gore)\n");
    printf("4)Sehir silmek\n");
    printf("5)Belirli bir bolgedeki sehirleri listeleme\n");
    printf("6)Komsu sayisina gore sehiri bulma\n");
    printf("7)Cikti.txt olusturma\n");
    printf("8)Cikis\n\n");
    printf("Seciminiz: ");
    scanf("%d",&secim);

    while (secim<8 && secim>0)
    {
        switch(secim)
        {
        case 1:
LOOP:
            printf("Eklenecek sehirin ismini giriniz(Plaka, Sehir ismi, Bolge, Komsular): ");
            scanf("%s",&ekleneceksehir);

            fprintf(deneme,"%s\n",ekleneceksehir);
            fclose(deneme);

            satirbolme(dosyayol);
            //Sirala();
            Listele();


            break;

        case 2:
            printf("Aramak istediginiz plakayi giriniz: ");
            scanf("%d",&arananplaka);
            if(Ara(arananplaka))
            {
                bulunan=Ara(arananplaka);
                printf("\n");
                printf(" Plaka Kodu: %d \n",bulunan->plakakodu);
                printf(" Sehir Adi: %s \n",bulunan->sehiradi);
                printf(" Bolge: %s \n",bulunan->bolge);
                printf(" Komsu Sayisi: %d \n",bulunan->komsusayisi);
                printf("\n");
            }
            else
            {
                printf("sehir listede yok, eklemek ister misiniz?(Evet icin:1 Hayir icin:2");
                scanf("%d",&yes);
                if(yes==1)
                {
                    goto LOOP;
                }
            }
            break;

        case 3:
            printf("Aramak istediginiz sehirin adini giriniz: ");
            scanf("%s",aranansehir);
            if(Arasehiradi(aranansehir))
            {
                bulunan=Arasehiradi(aranansehir);
                printf("\n");
                printf(" Plaka Kodu: %d \n",bulunan->plakakodu);
                printf(" Sehir Adi: %s \n",bulunan->sehiradi);
                printf(" Bolge: %s \n",bulunan->bolge);
                printf(" Komsu Sayisi: %d \n",bulunan->komsusayisi);
                printf("\n");
            }
            else
            {
                printf("sehir listede yok, eklemek ister misiniz?(Evet icin:1 Hayir icin:2");
                scanf("%d",&yes);
                if(yes==1)
                {
                    goto LOOP;
                }
            }

            break;

        case 4:
            printf("Silmek istediginiz sehirin ismini giriniz:");
            scanf("%s",silineceksehir);
            silme(silineceksehir);
            break;

        case 5:
LOOP2:
            printf("Listelemek istediginiz bolgenin kisaltmasini giriniz: ");
            scanf("%s",bolgeAra);

            struct dugum *ara=(struct dugum*)malloc(sizeof(struct dugum));
            ara=baslangic;
            int kontrol=0;

            while(ara!=NULL)
            {
                if(strcmp(ara->bolge,bolgeAra)==0)
                {
                    printf("\n");
                    printf(" Plaka Kodu: %d \n",ara->plakakodu);
                    printf(" Sehir Adi: %s \n",ara->sehiradi);
                    printf(" Bolge: %s \n",ara->bolge);
                    printf(" Komsu Sayisi: %d \n",ara->komsusayisi);
                    printf("\n");
                    kontrol++;
                }
                ara=ara->next;

            }
            if(kontrol==0)
            {
                printf("\nBolge adini yanlis girdiniz..\n(MA,KA,AK,IA,GA,DA,EG)\n\n");
                goto LOOP2;

            }
            else if(kontrol>=1)
                printf("\nBolgede %d adet sehir listelenmistir!\n\n",kontrol);
            kontrol=0;
            break;

        case 6:
            printf("Kac komsusu ve daha fazla olan sehiri aramak istiyorsunuz? ");
            scanf("%d",&aranacakkomsusayisi);
            struct dugum *ara2=(struct dugum*)malloc(sizeof(struct dugum));
            ara2=baslangic;
            while(ara2 != NULL)
            {
                if(ara2->komsusayisi >aranacakkomsusayisi)
                {
                    printf("\n");
                    printf(" Plaka Kodu: %d \n",ara2->plakakodu);
                    printf(" Sehir Adi: %s \n",ara2->sehiradi);
                    printf(" Bolge: %s \n",ara2->bolge);
                    printf(" Komsu Sayisi: %d \n",ara2->komsusayisi);
                    printf("\n");
                }
                ara2=ara2->next;
            }
            break;

        case 7:
            ciktidosyasi();
            printf("cikti.txt olusturuldu\n\n");
            break;

        }

        printf("1)Yeni bir sehir ekleyin\n");
        printf("2)Sehir arama(plaka koduna gore)\n");
        printf("3)Sehir arama(sehir adina gore)\n");
        printf("4)Sehir silmek\n");
        printf("5)Belirli bir bolgedeki sehirleri listeleme\n");
        printf("6)Komsu sayisina gore sehiri bulma\n");
        printf("7)Cikti.txt olusturma\n");
        printf("8)Cikis\n\n");
        printf("Seciminiz: ");
        scanf("%d",&secim);

    }

    return 0;
}



