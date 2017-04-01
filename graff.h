
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string.h>
#include <numeric>
using namespace std;





class dugum
{

public :

    int satir;
    int sutun;
    int dugumrengi;
    dugum *sonraki;


};

class liste
{

public :
    dugum *bas;
    dugum *son;

    void sona_ekle(int,int,int);
    liste(){
    bas=NULL;
    son=NULL;
    };


};

void liste::sona_ekle(int x, int y, int z) {

    dugum * yeni = new  dugum();
	yeni->satir = x;
	yeni->sutun= y;
	yeni->dugumrengi= z;


	if (bas == NULL) {
		// listede eleman yoksa, ilk elemani ekliyoruz
		yeni->sonraki = NULL;
		bas = son = yeni;
	} else {
		// listede eleman varsa
		son->sonraki = yeni;
		yeni->sonraki = NULL;
		son = yeni;
	}
}

class uzaklik
{
public :

    int ilkdugum;
    int ikincidugum;
    int arauzaklik;
    uzaklik *sonraki;

};
class listeuzaklik
{


    public :
        uzaklik *bas;
        uzaklik *son;

        void sona_ekle1(int,int,int);
        void yazdir();
        listeuzaklik(){
        bas=NULL;
        son=NULL;
        };


};
void listeuzaklik::yazdir(){
    uzaklik *tmp  = bas;
    while(tmp != NULL){
        cout <<tmp->ilkdugum<<"-"<<tmp->ikincidugum<<" arasi mesafe : "<<tmp->arauzaklik << endl;
        tmp = tmp->sonraki;
    }
    free(tmp);
}
void listeuzaklik::sona_ekle1(int x, int y, int z) {

    uzaklik * yeni = new  uzaklik();
	yeni->ilkdugum = x;
	yeni->ikincidugum = y;
	yeni->arauzaklik = z;


	if (bas == NULL) {
		// listede eleman yoksa, ilk elemani ekliyoruz
		yeni->sonraki = NULL;
		bas = son = yeni;
	} else {
		// listede eleman varsa
		son->sonraki = yeni;
		yeni->sonraki = NULL;
		son = yeni;
	}
}



void buton_tiklama(Gtk::Entry* boyut_entry,Gtk::Entry* dugum_entry,
                   Gtk::Label* hata_mesaji,Gtk::Label* kruskal_mesaj,Gtk::TextView* kruskal_text)
{





    int boyut= stoi(boyut_entry->get_text());
    int dugumsayisi=boyut;
    if(dugumsayisi>400){
        hata_mesaji->set_text("HATA!!!!!\n400 düğümden fazla girdiniz!!!!");
        return;

    }
    else{
        hata_mesaji->set_text("");
    }



    int i=0,j=0;

    string matris = dugum_entry->get_text();


    int gec[dugumsayisi*2];

    vector<vector<int> > maliyet(dugumsayisi,vector<int>(3));


    istringstream as( matris );
    int a=0;
    int index=0;
    while(as >> a){

        gec[index]=a;
        index++;

    }

    for(i=0;i<index;i++){
        if(gec[i]>19){
            hata_mesaji->set_text("HATA!!!!!!\nKoordinatlar 20x20 aralığında olmalı!!!");
            return;
        }
        else{
            hata_mesaji->set_text("");
        }
    }




    int z=0;

    liste bagliliste = liste();


    for(i=0;i<dugumsayisi*2;i++){

        bagliliste.sona_ekle(gec[i],gec[i+1],z);

        maliyet[z][0]=bagliliste.son->satir;
        maliyet[z][1]=bagliliste.son->sutun;

        z++;
        i++;

    }


    dugum* dugum1[dugumsayisi-1];

    dugum *tmp = bagliliste.bas;

    for(i=0;i<dugumsayisi;i++){

        dugum1[i]=tmp;
        tmp=tmp->sonraki;

    }

    free(tmp);


    int x=0,y=0;

    listeuzaklik duzaklik = listeuzaklik();

    for(i=0;i<dugumsayisi;i++){

        for(j=i+1;j<dugumsayisi;j++){

            x=abs(maliyet[i][0]-maliyet[j][0]);
            y=abs(maliyet[i][1]-maliyet[j][1]);

            duzaklik.sona_ekle1(i,j,x+y);

        }

    }

    duzaklik.yazdir();

    cout<<endl<<endl;

    int kenarsayisi=0;

    kenarsayisi=(dugumsayisi*(dugumsayisi-1))/2;


    uzaklik *duzaklik1 [kenarsayisi];

    uzaklik *tmp1 = duzaklik.bas;


    for(i=0;i<kenarsayisi;i++){
        duzaklik1[i]=tmp1;
        tmp1=tmp1->sonraki;
    }

    free(tmp1);



    for(i=0;i<kenarsayisi-1;i++){

        for(j=0;j<kenarsayisi-1-i;j++){

                if(duzaklik1[j]->arauzaklik > duzaklik1[j+1]->arauzaklik){
                    uzaklik *gecici=duzaklik1[j];
                    duzaklik1[j]=duzaklik1[j+1];
                    duzaklik1[j+1]=gecici;

                }
        }
    }


    listeuzaklik sirali ;



     for(i=0;i<kenarsayisi;i++){

        sirali.sona_ekle1(duzaklik1[i]->ilkdugum,duzaklik1[i]->ikincidugum,duzaklik1[i]->arauzaklik);
    }

    sirali.yazdir();



    cout<<endl;


    cout<<"-------Eklenilen kenarlar----------"<<endl;


    uzaklik *duzaklikek [kenarsayisi];




    int it=0,deneme=0;

    for(i=0;i<kenarsayisi;i++){

        if(dugum1[duzaklik1[i]->ilkdugum]->dugumrengi != dugum1[duzaklik1[i]->ikincidugum]->dugumrengi){

            deneme=dugum1[duzaklik1[i]->ikincidugum]->dugumrengi;

            for(j=0;j<dugumsayisi;j++){

                if(deneme == dugum1[j]->dugumrengi){

                    dugum1[j]->dugumrengi = dugum1[duzaklik1[i]->ilkdugum]->dugumrengi;
                }

            }

          duzaklikek[it]=duzaklik1[i];
          it++;

        }


    }

    int enkisatoplam=0;

    for(i=0;i<it;i++){

        cout<<duzaklikek[i]->ilkdugum<<"-"<<duzaklikek[i]->ikincidugum<<" arasi mesafe : "<<duzaklikek[i]->arauzaklik<<endl;
        enkisatoplam+=duzaklikek[i]->arauzaklik;

    }
    cout<<enkisatoplam;

    string kruskal="";
    for(i=0;i<it;i++){

        kruskal+="D"+std::to_string(duzaklikek[i]->ilkdugum)+"-D"+std::to_string(duzaklikek[i]->ikincidugum)+" arasi mesafe : "+std::to_string(duzaklikek[i]->arauzaklik )+"\n";

    }
    kruskal=kruskal+"En kısa yolun toplamı = "+std::to_string(enkisatoplam);

    kruskal_mesaj->set_text(kruskal);


    int el=0;
    vector <string> yazdir;
    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            bool varmi = false;

            for(int k = 0; k < dugumsayisi; k++ ){
                if(dugum1[k]->satir == i and dugum1[k]->sutun == j){
                    varmi = true;
                    el=k;

                }
            }

            if(varmi){
               yazdir.push_back(" D"+std::to_string(el)+"  ");


            }else{
                yazdir.push_back("     ");
            }
        }
        yazdir.push_back("\n");
    }



    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            for(int k=0;k<it;k++){

                    if(((i>dugum1[duzaklikek[k]->ilkdugum]->satir and i<dugum1[duzaklikek[k]->ikincidugum]->satir) or (i<dugum1[duzaklikek[k]->ilkdugum]->satir and i>dugum1[duzaklikek[k]->ikincidugum]->satir)) and j==dugum1[duzaklikek[k]->ilkdugum]->sutun){
                            const string::size_type yer = yazdir[i*20+j+i].find("D");
                            if(yer == string::npos){
                                yazdir[i*20+j+i]="  :  ";

                            }


                    }

                    if(((j>=dugum1[duzaklikek[k]->ilkdugum]->sutun and j<dugum1[duzaklikek[k]->ikincidugum]->sutun) or (j<dugum1[duzaklikek[k]->ilkdugum]->sutun and j>=dugum1[duzaklikek[k]->ikincidugum]->sutun)) and i == dugum1[duzaklikek[k]->ikincidugum]->satir){
                           const string::size_type yer = yazdir[i*20+j+i].find("D");
                            if(yer == string::npos){
                                yazdir[i*20+j+i]="  ...";

                            }


                    }

            }

        }
    }

    string str = accumulate(yazdir.begin(),yazdir.end(),string(""));


    Glib::RefPtr<Gtk::TextBuffer> buffer = Gtk::TextBuffer::create();
    buffer->set_text(str);
    kruskal_text->set_buffer(buffer);






}


