#include <bits/stdc++.h>
using namespace std;

ifstream f("date.in");
ofstream g("date.out");

map <char,int> L; // bijectie intre alfabet si numarul de litere
char alphabet[100];
int nr_stari,nr_litere;

set <int> operator* (set <int> M1, set <int> M2){
    set <int> intersect;
    set <int> :: iterator i,j;
    for(i = M1.begin(); i != M1.end(); i++)
        for(j = M2.begin();j != M2.end(); j++)
        	if (*i == *j)
        intersect.insert(*i);
    return intersect;
}

void parcurgere (int *viz, int stare, int *automat, int nr_lit, int &nr_fin);
int main(){
    f >> nr_stari >> nr_litere;
    set <int> fin,nefin;
    int automat[nr_stari+1][nr_litere];
    for(int i=0;i<nr_litere;i++){
        f >> alphabet[i];
        L[alphabet[i]]=i;
    }
    int start;
    f>>start;
    int nr_fin;
    f>>nr_fin;
    int finale[nr_stari+1];
    for(int i=1;i<=nr_stari;i++) finale[i]=0;
    for(int i=1;i<=nr_fin;i++){
        int x;
        f>>x;
        finale[x]=1;

    }
    int color[nr_stari+1];
    for(int i=1;i<=nr_stari;i++) if(finale[i]) fin.insert(i);
                                 else nefin.insert(i);

    int nr_tranzitii;
    f>>nr_tranzitii;
    for(int i=1;i<=nr_tranzitii;i++){
        int x,y; char c;
        f>>x>>c>>y;
        automat[x][L[c]]=y;
    }
    set < set<int> > P,Q;
    if(nefin.size())
        Q.insert(nefin);
    Q.insert(fin);
    int col=0;
    for(set< set<int> >::iterator it=Q.begin();it!=Q.end();it++){
             col++;
             for(set <int> ::iterator e=it->begin();e!=it->end();e++)
                color[*e]=col;
         }
    int nr_color = Q.size();
    P=Q;
    for(int x=0;x<nr_litere;x++){
	    set <int> q[nr_color+1];
            for(int i=1;i<=nr_stari;i++)
                q[color[automat[i][x]]].insert(i);
            set < set<int> > L;
            for(set < set<int> >::iterator it = P.begin(); it!=P.end(); it++)
                for(int l=1; l<=nr_color; l++){
                    set<int> M = (*it) * q[l];
        if(M.size())
                L.insert(M);
             }
          P=L;
    }
    col = 0;
    for(set< set<int> >::iterator it=P.begin();it!=P.end();it++){
             col++;
             for(set<int>::iterator e=it->begin();e!=it->end();e++)
                color[*e]=col;
         }
    while(P!=Q)  {
        Q=P;
        nr_color=Q.size();
      for(int x=0;x<nr_litere;x++){
                set<int> q[nr_color+1];
                for(int i=1;i<=nr_stari;i++)
                    q[color[automat[i][x]]].insert(i);
                set< set<int> > L;
                for(set< set<int> >::iterator it=P.begin();it!=P.end();it++)
                    for(int l=1;l<=nr_color;l++){
                          set<int>M=(*it)*q[l];
                          if(M.size())
                          L.insert(M);
                        }
             P=L;
        }
        col=0;
        for(set< set<int> >::iterator it=P.begin();it!=P.end();it++)0{
             ++col;
             for(set<int>::iterator e=it->begin();e!=it->end();e++)
                color[*e]=col;
         }

}

    int nr_stari2 = P.size();
    int  auto_min[nr_stari2+1][nr_litere];
    int finale2[nr_stari2+1];
    for(int i=1;i<=nr_stari2;i++)finale2[i]=0;
   int stare=0,nr_finale=0;
    for(set< set<int> >::iterator it=P.begin();it!=P.end();it++)
    {
        ++stare;
        if(finale[*(it->begin())])
         finale2[stare]=1;
        for(int x=0;x<nr_litere;x++)
            auto_min[stare][x]=color[automat[*(it->begin())][x]];
    }

    int viz[nr_stari2+1];
    for(int i=1;i<=nr_stari2;i++) viz[i]=0;
    int nr_stari3=0;
    int start_min=color[start];
    parcurg(viz,start_min,(int*)auto_min,nr_litere,nr_stari3);
    if(!viz[start_min]) {viz[start_min]=1; ++nr_stari3;}
    g<<nr_stari3<<endl;
    for(int i=1;i<=nr_stari2;i++)
        if(viz[i])
            g<<i<<' ';
    g<<endl<<nr_litere<<endl;
    for(int i=0;i<nr_litere;i++)
        g<<alphabet[i]<<' ';
    g<<endl;
    g<<start_min<<endl;
    for(int i=1;i<=nr_stari2;i++)
        if(viz[i]&&finale2[i])
        ++nr_finale;
    g<<nr_finale<<endl;
    for(int i=1;i<=nr_stari2;i++)
        if(finale2[i]&&viz[i])
        g<<i<<' ';
    g<<endl;
    g<<nr_stari3*nr_litere<<endl;
    for(int i=1;i<=nr_stari2;i++)
        for(int x=0;x<nr_litere;x++)
        if(viz[i])
        g<<i<<' '<<alphabet[x]<<' '<<auto_min[i][x]<<endl;

    return 0;
}
void parcurgere (int *viz, int stare, int *automat, int nr_lit, int &nr_fin)
{
    for (int i=0; i<nr_lit; i++)
     if (viz[*((automat + stare * nr_lit)+i)]==0) {
         nr_fin++;
         viz[*((automat+stare*nr_lit)+i)]=1;
         parcurg(viz,*((automat+stare*nr_lit)+i),automat,nr_lit,nr_fin);
     }
}
