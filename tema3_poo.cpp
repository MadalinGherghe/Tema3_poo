#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
ifstream f("date.in");
ifstream g("destinatii.in");
class turist
{
protected:
    char nume[20],prenume[30],activitate_preferata[100],sex;
    int varsta;
    bool masina_personala;
public:
    void set_nume(char s[]);
    char *get_nume();
    void set_prenume(char s[]);
    char *get_prenume();
    void set_activitate(char s[]);
    char *get_activitate();
    void set_sex(char s);
    char get_sex();
    void set_varsta(int);
    int get_varsta();
    void set_masina(bool);
    bool get_masina();

    turist(const turist&);
    turist(){};
    virtual ~turist();
    friend istream& operator>>(istream&, turist&);
    friend ostream& operator<<(ostream&, turist&);
};
istream& operator>>(istream& in, turist& t)
{
    in.get();
    in.get(t.nume,20);
    in.get();
    in.get(t.prenume,30);
    in.get();
    in>>t.sex>>t.varsta;
    in.get();
    in.get(t.activitate_preferata,100);
    in.get();
    in>>t.masina_personala;
}
ostream& operator<<(ostream& out,turist &t){
    out<<t.nume<<" "<<t.prenume<<"\nSex: "<<t.sex<<"\nVarsta: "<<t.varsta<<" ani\n";
    out<<"Activitate preferata: "<<t.activitate_preferata<<"\nDetine masina personala: ";
    if(t.masina_personala)out<<"Da\n";
      else cout<<"Nu\n";
}
turist::~turist()
{
    delete []nume;
    delete []prenume;
    delete []activitate_preferata;
}

turist::turist(const turist &t){
    strcpy(nume,t.nume);
    strcpy(prenume,t.prenume);
    sex=t.sex;
    varsta=t.varsta;
    strcpy(activitate_preferata,t.activitate_preferata);
    masina_personala=t.masina_personala;
}
void turist::set_masina(bool x){
    masina_personala=x;
}
bool turist::get_masina(){
    return masina_personala;
}
void turist::set_nume(char s[]){
    strcpy(nume,s);
}
char *turist::get_nume(){
    return nume;
}
void turist::set_prenume(char s[]){
    strcpy(prenume,s);
}
char *turist::get_prenume(){
    return prenume;
}
void turist::set_activitate(char s[]){
    strcpy(activitate_preferata,s);
}
char *turist::get_activitate(){
    return activitate_preferata;
}
void turist::set_sex(char s){
    sex=s;
}
char turist::get_sex(){
    return sex;
}
void turist::set_varsta(int v){
    varsta=v;
}
int turist::get_varsta(){
   return varsta;
}


class activitate
{
protected:
    char nume_activitate[30];
    int importanta;
    float durata,distanta;
    bool vehicul_necesar,accepta_minori;

public:
    activitate(){importanta=0;}
    activitate(const activitate&);
    virtual ~activitate(){
       delete []nume_activitate;
         }
    virtual int getImportanta()
    {
        return importanta;
    }
    void setImportanta(int x)
    {
        importanta=x;
    }
    friend istream& operator>>(istream&,activitate&);
    friend ostream& operator<<(ostream&, activitate&);
    virtual void c_importanta(turist *,int n);
    virtual float getDurata(){return durata;}
};

activitate::activitate(const activitate& a)
{
    strcpy(nume_activitate,a.nume_activitate);
    importanta=a.importanta;
    durata=a.durata;
    distanta=a.distanta;
    vehicul_necesar=a.vehicul_necesar;
    accepta_minori=a.accepta_minori;
}

istream& operator>>(istream& in,activitate& a){
    in.get();in.get();
    in.get(a.nume_activitate,30);
    in.get();
    in>>a.durata>>a.distanta>>a.accepta_minori;
    if(a.distanta>2)
        a.vehicul_necesar=1;
       else a.vehicul_necesar=0;
}

ostream& operator<<(ostream& out,activitate& a){
    out<<"Nume activitate: "<<a.nume_activitate;
    out<<"\nDurata activitate: "<<a.durata<<" zi(le)\n";
    out<<"Distanta parcursa: "<<a.distanta<<" km\n";
    if(a.vehicul_necesar)out<<"Vehicul necesar pentru transport\n";
}

void activitate::c_importanta(turist *x,int n)
{
  for(int i=1;i<=n;i++){
    if(strstr(x[i].get_activitate(),nume_activitate))importanta++;
  }
}

class plaja:public activitate
{
   protected:
   char tip_plaja[30],nume_plaja[30];
public:
    plaja(){
        strcpy(nume_plaja,"-");
        strcpy(tip_plaja,"-");
        strcpy(nume_activitate,"-");
        durata=0;distanta=0;
        vehicul_necesar=0;accepta_minori=0;
        importanta=0;
    }
     virtual ~plaja(){
       delete []nume_activitate;
       delete []tip_plaja;
       delete []nume_plaja;
         }
    plaja(const plaja&);
    friend istream& operator>>(istream&,plaja&);
    friend ostream& operator<<(ostream&,plaja&);
    void c_importanta(turist *,int n);
};
void plaja::c_importanta(turist *x,int n)
{
  for(int i=1;i<=n;i++){
    if(strstr(x[i].get_activitate(),"plaja"))importanta++;
    if(strstr(x[i].get_activitate(),tip_plaja))importanta++;
  }
}

plaja::plaja(const plaja& p){
    strcpy(tip_plaja,p.tip_plaja);
    strcpy(nume_plaja,p.nume_plaja);
    strcpy(nume_activitate,p.nume_activitate);
    durata=p.durata;
    importanta=p.importanta;
    distanta=p.distanta;
    vehicul_necesar=p.vehicul_necesar;
    accepta_minori=p.accepta_minori;
}

istream& operator>>(istream& in,plaja& p){
    strcpy(p.nume_activitate,"plaja");
    in.get();in.get();
    in.get(p.nume_plaja,30);
    in.get();
    in.get(p.tip_plaja,30);
    in.get();
    in>>p.durata>>p.distanta>>p.accepta_minori;
    if(p.distanta>2)p.vehicul_necesar=1;
       else p.vehicul_necesar=0;
}

ostream& operator<<(ostream& out,plaja& p){
    out<<"Tip activitate: Relaxare pe plaja "<<p.nume_plaja;
    out<<"\nTip plaja: "<<p.tip_plaja;
    if(p.accepta_minori==0)out<<" (Interzis accesul minorilor - Acestia pot petrece timpul pe o alta plaja din apropiere insotiti de parinti)";
    out<<"\nDurata activitate: "<<p.durata<<" zi(le)\n";
    out<<"Distanta parcursa: "<<p.distanta<<" km\n";
    if(p.vehicul_necesar)out<<"Vehicul necesar pentru transport\n";
}

class munte:public activitate
{
protected:
    char nume_munte[20],nume_manastire[30];
    int tip_traseu;         //1-usor 2-mediu 3-greu
    bool oprire_manastire,accepta_femei,ghid_montan;
public:
    munte(){
        strcpy(nume_munte,"-");
     strcpy(nume_manastire,"-");
     tip_traseu=0;
     oprire_manastire=accepta_femei=ghid_montan=0;
     importanta=0;
    }
    virtual ~munte(){
       delete []nume_activitate;
       delete []nume_manastire;
       delete[]nume_munte;
         }
    munte(const munte&);
    friend istream& operator>>(istream&,munte&);
    friend ostream& operator<<(ostream&,munte&);
    void c_importanta(turist *,int);
};

void munte::c_importanta(turist *x,int n)
{
    importanta=0;
    for(int i=1;i<=n;i++){
    if(strstr(x[i].get_activitate(),"munte")||strstr(x[i].get_activitate(),"drumetie"))importanta++;
    if(strstr(x[i].get_activitate(),"traseu usor")&&tip_traseu==1)importanta++;
      else if(strstr(x[i].get_activitate(),"traseu mediu")&&tip_traseu==2)importanta++;
            else if(strstr(x[i].get_activitate(),"traseu greu")&&tip_traseu==3)importanta++;
  }
}

munte::munte(const munte& m){
    strcpy(nume_munte,m.nume_munte);
    strcpy(nume_manastire,m.nume_manastire);
    tip_traseu=m.tip_traseu;
    oprire_manastire=m.oprire_manastire;
    accepta_femei=m.accepta_femei;
    ghid_montan=m.ghid_montan;
    strcpy(nume_activitate,m.nume_activitate);
    durata=m.durata;
    importanta=m.importanta;
    distanta=m.distanta;
    vehicul_necesar=m.vehicul_necesar;
    accepta_minori=m.accepta_minori;
}

istream& operator>>(istream& in, munte& m){
    strcpy(m.nume_activitate,"Tip activitate: drumetie pe munte");
    in.get();in.get();
    in.get(m.nume_munte,20);
    in.get();
    in>>m.tip_traseu;
    if(m.tip_traseu==3)m.accepta_minori=0;
      else m.accepta_minori=1;
    in>>m.durata>>m.distanta;
    if(m.distanta>2)m.vehicul_necesar=1;
       else m.vehicul_necesar=0;
    in>>m.oprire_manastire;
    if(m.oprire_manastire)
    {
        in.get();
        in.get(m.nume_manastire,30);
        in.get();
        in>>m.accepta_femei;
    }
    in>>m.ghid_montan;
}

ostream& operator<<(ostream& out, munte& m){
    out<<"Drumetie pe Muntele/Muntii: "<<m.nume_munte<<"\nTraseu ";
    if(m.tip_traseu==1)out<<"usor\n";
      else if(m.tip_traseu==2)out<<"mediu\n";
            else if(m.tip_traseu==3)out<<"greu (interzis minorilor si persoanelor in varsta)\n";
    if(m.oprire_manastire){
        out<<"Traseul include oprire la "<<m.nume_manastire;
        if(!m.accepta_femei)out<<" care nu accepta vizitatori femei";
        out<<"\n";
    }
    if(m.ghid_montan)out<<"Turistii vor fi insotiti de un ghid montan local\n";
    out<<"Durata activitate: "<<m.durata<<" zi(le)\n";
    out<<"Distanta parcursa: "<<m.distanta<<" km\n";
    if(m.vehicul_necesar)out<<"Vehicul necesar pentru transport\n";
}

class muzeu:public activitate{
protected:
    char nume_muzeu[30],tip_muzeu[20];
    bool accepta_femei;
public:
    muzeu(){
    strcpy(nume_muzeu,"-");
    strcpy(tip_muzeu,"-");
    accepta_femei=0;
    importanta=0;
    }
    virtual ~muzeu(){
       delete []nume_activitate;
       delete []nume_muzeu;
       delete []tip_muzeu;
         }
    muzeu(const muzeu&);
    friend istream& operator>>(istream&,muzeu&);
    friend ostream& operator<<(ostream&,muzeu&);
    void c_importanta(turist *,int);
};

muzeu::muzeu(const muzeu& m)
{
    strcpy(nume_activitate,m.nume_activitate);
    durata=m.durata;
    importanta=m.importanta;
    distanta=m.distanta;
    vehicul_necesar=m.vehicul_necesar;
    accepta_minori=m.accepta_minori;
    strcpy(nume_muzeu,m.nume_muzeu);
    strcpy(tip_muzeu,m.tip_muzeu);
    accepta_femei=m.accepta_femei;
}

istream& operator>>(istream& in,muzeu& m){
    strcpy(m.nume_activitate,"Vizitare muzeu");
    in.get();in.get();
    in.get(m.nume_muzeu,30);
    in.get();
    in.get(m.tip_muzeu,20);
    in.get();
    if(strstr(m.tip_muzeu,"stiintific"))
        in>>m.accepta_femei;
    in>>m.durata>>m.distanta;
    if(m.distanta>2)m.vehicul_necesar=1;
       else m.vehicul_necesar=0;
    m.accepta_minori=1;
}

ostream& operator<<(ostream& out,muzeu& m){
    out<<"Tip activitate: Vizita la muzeu ("<<m.nume_muzeu<<")\nTip muzeu: "<<m.tip_muzeu;
    if(!m.accepta_femei)out<<"\nMuzeul nu accepta vizitatori femei\n";
    out<<"Durata activitate: "<<m.durata<<" zi(le)\n";
    out<<"Distanta parcursa: "<<m.distanta<<" km\n";
    if(m.vehicul_necesar)out<<"Vehicul necesar pentru transport\n";
}

void muzeu::c_importanta(turist *x,int n)
{
  for(int i=1;i<=n;i++){
    if(strstr(x[i].get_activitate(),"muzeu"))importanta++;
    if(strstr(x[i].get_activitate(),tip_muzeu))importanta++;
  }
}

class sauna:public activitate{
protected:
    char nume_locatie[30],tip_sauna[20];
public:
    sauna(){
    strcpy(nume_locatie,"-");
    strcpy(tip_sauna,"-");
    importanta=0;
    }
    virtual ~sauna(){
       delete []nume_activitate;
       delete []nume_locatie;
       delete []tip_sauna;
         }
    sauna(const sauna&);
    friend istream& operator>>(istream&, sauna&);
    friend ostream& operator<<(ostream&, sauna&);
    void c_importanta(turist *,int);
};

sauna::sauna(const sauna& s){
    strcpy(nume_locatie,s.nume_locatie);
    strcpy(tip_sauna,s.tip_sauna);
    strcpy(nume_activitate,s.nume_activitate);
    durata=s.durata;
    importanta=s.importanta;
    distanta=s.distanta;
    vehicul_necesar=s.vehicul_necesar;
    accepta_minori=s.accepta_minori;
}
istream& operator>>(istream& in, sauna& s){
    strcpy(s.nume_activitate,"Sauna si Spa");
    in.get();in.get();
    in.get(s.nume_locatie,30);
    in.get();
    in.get(s.tip_sauna,20);in.get();
    in>>s.durata>>s.distanta;
    if(s.distanta>2)s.vehicul_necesar=1;
       else s.vehicul_necesar=0;
    s.accepta_minori=1;
}
ostream& operator<<(ostream& out, sauna& s){
    out<<"Tip activitate: Sauna si Spa\n";
    out<<"In cadrul locatiei -"<<s.nume_locatie<<"- doamnele se vor bucura de Spa, iar domnii  de sauna "<<s.tip_sauna<<"\n";
    out<<"Durata activitate: "<<s.durata<<" zi(le)\n";
    out<<"Distanta parcursa: "<<s.distanta<<" km\n";
    if(s.vehicul_necesar)out<<"Vehicul necesar pentru transport\n";
}

void sauna::c_importanta(turist *x,int n)
{
  for(int i=1;i<=n;i++){
    if(strstr(x[i].get_activitate(),"sauna"))importanta++;
    if(strstr(x[i].get_activitate(),tip_sauna))importanta++;
  }
}

class seara:public activitate{
protected:
    char nume_club[30],nume_restaurant[30];
public:
    seara(){
    strcpy(nume_club,"-");
    strcpy(nume_restaurant,"-");
    importanta=0;
    }
    virtual ~seara(){
       delete []nume_activitate;
       delete []nume_club;
       delete []nume_restaurant;
         }
    seara(const seara&);
    friend istream& operator>>(istream&, seara&);
    friend ostream& operator<<(ostream&, seara&);
    void c_importanta(turist *,int);
};

seara::seara(const seara& s){
    strcpy(nume_club,s.nume_club);
    strcpy(nume_restaurant,s.nume_restaurant);
    strcpy(nume_activitate,s.nume_activitate);
    durata=s.durata;
    importanta=s.importanta;
    distanta=s.distanta;
    vehicul_necesar=s.vehicul_necesar;
    accepta_minori=s.accepta_minori;
}
istream& operator>>(istream& in,seara& s){
    strcpy(s.nume_activitate,"Cina");
    in.get();in.get();
    in.get(s.nume_restaurant,30);
    in.get();in.get(s.nume_club,30);
    in.get();
    in>>s.durata>>s.distanta;
    if(s.distanta>2)s.vehicul_necesar=1;
       else s.vehicul_necesar=0;
    s.accepta_minori=1;
}
ostream& operator<<(ostream& out, seara& s){
    out<<"Tip activitate: Cina\n";
    out<<"Domnii si doamnele vor lua o cina de lux in restaurantul -"<<s.nume_restaurant<<"- in timp ce tinerii vor petrece o noapte de neuitat la -"<<s.nume_club<<"-,clubul din apropierea restaurantului\n";
    out<<"Durata activitate: "<<s.durata<<" zi(le)\n";
    out<<"Distanta parcursa: "<<s.distanta<<" km\n";
    if(s.vehicul_necesar)out<<"Vehicul necesar pentru transport\n";
}
void seara::c_importanta(turist *x,int n)
{
  for(int i=1;i<=n;i++){
    if(strstr(x[i].get_activitate(),"club")||strstr(x[i].get_activitate(),"cina")||strstr(x[i].get_activitate(),"restaurant"))importanta++;
  }
}

class destinatie
{
protected:
    int importanta_t,nr_activitati,n_plaja,n_munte,n_muzeu,n_sauna,n_seara,n_activitate_noua;
    float durata_totala;
    char nume[30];
public:
     plaja *v1;
    munte *v2;
    muzeu *v3;
    sauna *v4;
    seara *v5;
    activitate *v6;
    destinatie(){importanta_t=0;}
    virtual ~destinatie(){
       delete []v1;
       delete []v2;
       delete []v3;
       delete []v4;
       delete []v5;
       delete []v6;
         }
    friend istream& operator>>(istream&,destinatie&);
    friend ostream& operator<<(ostream&, destinatie&);
    void calc_importanta();
    int getPlaja(){return n_plaja;}
    int getMunte(){return n_munte;}
    int getMuzeu(){return n_muzeu;}
    int getSauna(){return n_sauna;}
    int getSeara(){return n_seara;}
    int getActivitataNoua(){return n_activitate_noua;}
    int getimportanta(){return importanta_t;}
};

void destinatie::calc_importanta()
{
    int i;
    importanta_t=0;durata_totala=0;
    for(i=1;i<=n_plaja;i++)
        {importanta_t+=v1[i].getImportanta();durata_totala+=v1[i].getDurata();}
    for(i=1;i<=n_munte;i++)
       {importanta_t+=v2[i].getImportanta();durata_totala+=v2[i].getDurata();}
    for(i=1;i<=n_muzeu;i++)
        {importanta_t+=v3[i].getImportanta();durata_totala+=v3[i].getDurata();}
    for(i=1;i<=n_sauna;i++)
        {importanta_t+=v4[i].getImportanta();durata_totala+=v4[i].getDurata();}
    for(i=1;i<=n_seara;i++)
        {importanta_t+=v5[i].getImportanta();durata_totala+=v5[i].getDurata();}
    for(i=1;i<=n_activitate_noua;i++)
        {importanta_t+=v6[i].getImportanta();durata_totala+=v6[i].getDurata();}
}

istream& operator>>(istream& in, destinatie& d){
    in.get();in.get();
    in.get(d.nume,30);
    in.get();
    int i,j;
    in>>d.n_plaja;
    d.v1=new plaja[d.n_plaja+1];
    for(i=1;i<=d.n_plaja;i++)
        in>>d.v1[i];
    in>>d.n_munte;
    d.v2=new munte[d.n_munte+1];
    for(i=1;i<=d.n_munte;i++)
        in>>d.v2[i];
    in>>d.n_muzeu;
    d.v3=new muzeu[d.n_muzeu+1];
    for(i=1;i<=d.n_muzeu;i++)
        in>>d.v3[i];
    in>>d.n_sauna;
    d.v4=new sauna[d.n_sauna+1];
    for(i=1;i<=d.n_sauna;i++)
        in>>d.v4[i];
    in>>d.n_seara;
    d.v5=new seara[d.n_seara+1];
    for(i=1;i<=d.n_seara;i++)
        in>>d.v5[i];
    in>>d.n_activitate_noua;
    d.v6=new activitate[d.n_activitate_noua+1];
    for(i=1;i<=d.n_activitate_noua;i++)
        in>>d.v6[i];
    d.nr_activitati=d.n_activitate_noua+d.n_munte+d.n_muzeu+d.n_plaja+d.n_sauna+d.n_seara;
}

ostream& operator<<(ostream& out,destinatie& d){
    int index,index_vect,n=14,i,j,x=int(d.durata_totala+0.5);
    if(x<n)n=x;
    j=1;
    while(j<=n)
    {
        cout<<"Ziua "<<j<<"\n";
        int maximp=-1;
    for(i=1;i<=d.n_plaja;i++)
        if(d.v1[i].getImportanta()>maximp){maximp=d.v1[i].getImportanta();index=i;index_vect=1;}
    for(i=1;i<=d.n_munte;i++)
      if(d.v2[i].getImportanta()>maximp){maximp=d.v2[i].getImportanta();index=i;index_vect=2;}
    for(i=1;i<=d.n_muzeu;i++)
       if(d.v3[i].getImportanta()>maximp){maximp=d.v3[i].getImportanta();index=i;index_vect=3;}
    for(i=1;i<=d.n_sauna;i++)
       if(d.v4[i].getImportanta()>maximp){maximp=d.v4[i].getImportanta();index=i;index_vect=4;}
    for(i=1;i<=d.n_seara;i++)
        if(d.v5[i].getImportanta()>maximp){maximp=d.v5[i].getImportanta();index=i;index_vect=5;}
    for(i=1;i<=d.n_activitate_noua;i++)
        if(d.v6[i].getImportanta()>maximp){maximp=d.v6[i].getImportanta();index=i;index_vect=6;}


    switch(index_vect)
    {
        case 1:  cout<<d.v1[index];cout<<"\n";
                 d.v1[index].setImportanta(-2);
                 j+=int(d.v1[index].getDurata()+0.5);
                 break;
        case 2:  cout<<d.v2[index];cout<<"\n";
                 d.v2[index].setImportanta(-2);
                 j+=int(d.v2[index].getDurata()+0.5);
                 break;
        case 3:  cout<<d.v3[index];cout<<"\n";
                 d.v3[index].setImportanta(-2);
                 j+=int(d.v3[index].getDurata()+0.5);
                 break;
        case 4:  cout<<d.v4[index];cout<<"\n";
                 d.v4[index].setImportanta(-2);
                 j+=int(d.v4[index].getDurata()+0.5);
                 break;
        case 5:  cout<<d.v5[index];cout<<"\n";
                 d.v5[index].setImportanta(-2);
                 j+=int(d.v5[index].getDurata()+0.5);
                 break;
        case 6:  cout<<d.v6[index];cout<<"\n";
                 d.v6[index].setImportanta(-2);
                 j+=int(d.v6[index].getDurata()+0.5);
                 break;
    }
    }
}

int main()
{
    turist *t;
    int i,j,nr_turisti,nr_destinatii;
    f>>nr_turisti;
    t=new turist[nr_turisti+1];
    for(i=1;i<=nr_turisti;i++)
        f>>t[i];

    destinatie *x;
    g>>nr_destinatii;
    x=new destinatie[nr_destinatii+1];
    for(i=1;i<=nr_destinatii;i++)
        g>>x[i];
 int imp=0,index_imp=0;
    for(i=1;i<=nr_destinatii;i++)
    {
        for(j=1;j<=x[i].getPlaja();j++)
            x[i].v1[j].c_importanta(t,nr_turisti);
        for(j=1;j<=x[i].getMunte();j++)
            x[i].v2[j].c_importanta(t,nr_turisti);
        for(j=1;j<=x[i].getMuzeu();j++)
            x[i].v3[j].c_importanta(t,nr_turisti);
        for(j=1;j<=x[i].getSauna();j++)
            x[i].v4[j].c_importanta(t,nr_turisti);
        for(j=1;j<=x[i].getSeara();j++)
            x[i].v5[j].c_importanta(t,nr_turisti);
        for(j=1;j<=x[i].getActivitataNoua();j++)
            x[i].v6[j].c_importanta(t,nr_turisti);
       x[i].calc_importanta();
       if(x[i].getimportanta()>imp){imp=x[i].getimportanta();
                                    index_imp=i;}
    }
      cout<<x[index_imp];
      cout<<"\n***Precizare:***\nExista posibilittea ca la o anumita activitate sa nu poata lua parte toate persoanele(in functie de varsta si sex)\nIn acest caz, pentru persoanele ce nu pot participa, acea activitate va fi inlocuita cu alta pe placul lor";
    return 0;
}
