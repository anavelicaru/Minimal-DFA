#include <bits/stdc++.h>
using namespace std;

ifstream f("date.in");
ofstream g("date.out");

map <char,int> L; // bijectie intre alfabet si numarul de litere
char alphabet[100];
int nStari,nLitere;

void parcurgere (int *viz, int stare, int *automat, int nLit, int &nFin);
set <int> operator* (set <int> M1, set <int> M2){
    set <int> intersect;
    set <int> :: iterator i,j;
    for(i = M1.begin(); i != M1.end(); i++)
        for(j = M2.begin();j != M2.end(); j++)
        	if (*i == *j)
        intersect.insert(*i);
    return intersect;
}

int main(){
    f >> nStari >> nLitere;
    set <int> fin,nefin;
    int automat[nStari+1][nLitere];
    int start;
    f>>start;
    int nFin;
    f>>nFin;
    int finale[nStari+1];
    for(int i=0;i<nLitere;i++){
        f >> alphabet[i];
        L[alphabet[i]]=i;
    }
    for(int i=1;i<=nStari;i++) finale[i]=0;
    for(int i=1;i<=nFin;i++){
        int x;
        f>>x;
        finale[x]=1;

    }
    int color[nStari+1];
    for(int i=1;i<=nStari;i++) if(finale[i]) fin.insert(i);
                                 else nefin.insert(i);

    int nArcs; //tranzitii
    f>>nArcs;
    for(int i=1;i<=nArcs;i++){
        int x,y;
        char c;
        f >> x >> c >> y;
        automat[x][L[c]]=y;}
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
    int nColors = Q.size();
    P=Q; //aplicam macar o data algoritmul
    for(int x=0; x < nLitere; x++){
	    set <int> q[nColors+1];
            for(int i=1;i<=nStari;i++)
                q[color[automat[i][x]]].insert(i);
            set < set<int> > L;
            for(set < set<int> >::iterator it = P.begin(); it!=P.end(); it++)
                for(int l=1; l<=nColors; l++){
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
        nColors=Q.size();
      for(int x=0; x<nLitere; x++){
                set<int> q[nColors+1];
                for (int i=1;i<=nStari;i++)
                    q[color[automat[i][x]]].insert(i);
                set< set<int> > L;
                for(set< set<int> >::iterator it=P.begin();it!=P.end();it++)
                    for(int l=1;l<=nColors;l++){
                          set<int>M=(*it)*q[l];
                          if(M.size())
                            L.insert(M);
                        }
             P=L;
        }

        col=0;
        for(set< set<int> >::iterator it = P.begin(); it != P.end(); it++){
             ++col;
             for(set<int>::iterator e=it->begin();e!=it->end();e++)
                color[*e]=col;
         }

}
//ramane sa eliminam nodurile inutile
    int nStari2 = P.size();
    int minimal[nStari2+1][nLitere];
    int finale2[nStari2+1];

    for(int i=1;i<=nStari2;i++)
        finale2[i]=0;
    int stare=0,nFinale=0;
    for(set< set<int> >::iterator it=P.begin();it!=P.end();it++){
        stare++;
        if (finale[*(it->begin())])
         finale2[stare]=1;
        for(int x=0;x<nLitere;x++)
            minimal[stare][x]=color[automat[*(it->begin())][x]];
    }

    int viz[nStari2+1];
    for(int i=1;i<=nStari2;i++)
        viz[i]=0;

    int nStari3=0;
    int start_min = color[start];

    parcurgere(viz,start_min,(int*)minimal,nLitere,nStari3);

    if(!viz[start_min]){
            viz[start_min]=1;
            nStari3++;}
    g<<nStari3<<endl;
    for(int i=1;i<=nStari2;i++)
        if(viz[i])
            g<<i<<' ';
    g<<endl<<nLitere<<endl;
    for(int i=0;i<nLitere;i++)
        g<<alphabet[i]<<' ';

    g<<endl;
    g<<start_min<<endl;

    for(int i=1;i<=nStari2;i++)
        if(viz[i]&&finale2[i])
        ++nFinale;
    g<<nFinale<<endl;
    for(int i=1;i<=nStari2;i++)
        if(finale2[i]&&viz[i])
        g<<i<<' ';
    g<<endl;
    g<<nStari3*nLitere<<endl;
    for(int i=1;i<=nStari2;i++)
        for(int x=0;x<nLitere;x++)
        if(viz[i])
        g<<i<<' '<<alphabet[x]<<' '<<minimal[i][x]<<endl;

    return 0;
}
void parcurgere (int *viz, int stare, int *automat, int nr_lit, int &nFin)
{
    for (int i=0; i<nr_lit; i++)
     if (viz[*((automat + stare * nr_lit)+i)]==0) {
         nFin++;
         viz[*((automat+stare*nr_lit)+i)]=1;
         parcurgere(viz,*((automat+stare*nr_lit)+i),automat,nr_lit,nFin);
     }
}
