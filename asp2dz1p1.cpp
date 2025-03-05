#include <iostream>
#include <cmath>
using namespace std;
//fja za ispis niza izmedju zadatih pozicija low i high
void ispisiniz(long long int niz[], int low, int high){
    for (int i = low; i <=high; ++i) {
        cout<<niz[i]<<" ";
    }
    cout<<endl;
}
//ternarna pretraga koja u brPor cuva ukupan broj porednjenja za svaki element koji trazi da bi se posle odredio prosecan broj poredjenja
void ternarnaPretraga(int& brPor, int n, long long int niz[], int x)
{
    int low = 0,high = n-1, br=0;
    while(low<=high)
    {
        int mid1=low+(high-low)/3;
        int mid2=high-(high-low)/3;
        cout<<"low= "<<niz[low]<<" , high= "<<niz[high]<<endl;
        cout<<"mid1= "<<niz[mid1]<<" , mid2= "<<niz[mid2]<<endl;
        if(niz[mid1]!=x )
        {
            br++;
        }
        else
        {
            br++;
            cout<<"Uspesna pretraga! Broj poredjenja do uspesnog rezultata: "<<br<<endl;
            brPor+=br;
            return;
        }
        if(niz[mid2]!=x )
        {
            br++;
        }
        else
        {
            br++;
            brPor+=br;
            cout<<"Uspesna pretraga! Broj poredjenja do uspesnog rezultata: "<<br<<endl;
            return;
        }
        if(x<niz[mid1])
        {
            high=mid1-1;
            cout<<"Deo koji naredno pretrazujemo:"<<endl;
            ispisiniz(niz, low, high);
        }
        else if(x<niz[mid2])
        {
            low=mid1+1;
            high=mid2-1;
            cout<<"Deo koji naredno pretrazujemo:"<<endl;
            ispisiniz(niz, low, high);
        }
        else
        {
            low=mid2+1;
            cout<<"Deo koji naredno pretrazujemo:"<<endl;
            ispisiniz(niz, low, high);
        }
    }
    cout<<"Nespesna pretraga!"<<endl;
}

void interpolacionaPretraga(int&brPor, int n, long long int niz[], int x)
{
    int low = 0,high = n-1, br=0;
    while(low<=high and x >= niz[low] and x<=niz[high])
    {
        int mid=low+(high-low)*(x-niz[low])/(niz[high]-niz[low]);
        cout<<"low= "<<niz[low]<<" , high= "<<niz[high]<<endl;
        cout<<"mid1= "<<niz[mid]<<endl;
        br++;
        if(x==niz[mid]){

            cout<<"Uspesna pretraga! Broj poredjenja do uspesnog rezultata: "<<br<<endl;
            brPor+=br;
            return;
        }
        else if(x<niz[mid]){
            high=mid-1;
            cout<<"Deo koji naredno pretrazujemo:"<<endl;
            ispisiniz(niz, low, high);
        }
        else{
            low=mid+1;
            cout<<"Deo koji naredno pretrazujemo:"<<endl;
            ispisiniz(niz, low, high);
        }
    }
    cout<<"Neuspesna pretraga!"<<endl;
}
//fja koja pronalazi faktorijel broja
long long int fact (int n){
    if(n==0)return 1;
    long long int pro=1;
    for (int i = 1; i <= n; ++i) {
        pro*=i;
    }
    return pro;
}
//fja koja pronalazi binomne koeficijente
long long int nad(int n, int k){
    if(k==0) return 1;
    if(n==0) return 0;
    return fact(n)/(fact(k)*fact(n-k));
}
int main() {
    int brReda,a;
    int brojPorednjenja1=0, brojPoredjenja2=0;
    int ponavlj=0;
    while(true){
        cout<<"Izaberite jednu od ponudjenih opcija:"
              "\n1.Unos broja reda Lozanicevog trougla za pretrazivanje i pocetak pretrage"
              "\n2.Kraj progarama"<<endl;
        cin>>a;
        if(a==1){
            cout<<"Unesite broj reda"<<endl;
            cin>>brReda;
            long long int niz[brReda+1];
            for(int i=0;i<=brReda;i++)
            {
                niz[i]=(nad(brReda,i)+nad(brReda%2,i%2)*nad(floor(brReda/2), floor(i/2)))/2;
            }
            cout<<"Lozanicev red broj "<<brReda<<". je spreman za pretrazivanje"<<endl;
            for (int i = 0; i <=brReda; ++i) {
                cout<<niz[i]<<"  ";
            }
            cout<<endl;
            int klj;
            while(true) {
                cout << "Unesite koji kljuc zelite da trazite:" << endl;
                cin >> klj;
                ponavlj++;
                cout << "Zapocinjemo ternatnu pretragu:" << endl;
                cout << "Deo Lozanicevog reda koji pretrazujemo " << endl;
                for (int i = 0; i < brReda / 2 + 1; ++i) {
                    cout << niz[i] << "  ";
                }
                cout << endl;
                ternarnaPretraga(brojPorednjenja1, brReda / 2 + 1, niz, klj);
                cout << "\nZapocinjemo interpolaconu pretragu:" << endl;
                cout << "Lozanicev red broj " << brReda << "." << endl;
                for (int i = 0; i < brReda / 2 + 1; ++i) {
                    cout << niz[i] << "  ";
                }
                cout << endl;
                interpolacionaPretraga(brojPoredjenja2, brReda / 2 + 1, niz, klj);
                cout<<"Ukoliko zelite da prekinete pretragu na ovom redu Lozanicevog trougla unesite 0:"<<endl;
                int prekid;
                cin>>prekid;
                if(!prekid){
                    cout<<"Prosecan broj pristupa prilikom uspesne TERNARNE pretrage nad datim redom je: "<<(double)brojPorednjenja1/ponavlj<<endl;
                    cout<<"Prosecan broj pristupa prilikom uspesne INTERPOLACIONE pretrage nad datim redom je: "<<(double)brojPoredjenja2/ponavlj<<endl;
                    cout<<"Poredimo performanse: TERNARNA/INTERPOLACIONA: "<< ((double)brojPorednjenja1/ponavlj)/((double)brojPoredjenja2/ponavlj)<<endl;
                    cout<<"Ovo znaci da su performanse bolje kod:";
                    if(((double)brojPorednjenja1/ponavlj)/((double)brojPoredjenja2/ponavlj)<1)cout<<"TERNARNE PRETRAGE"<<endl;
                    else if(((double)brojPorednjenja1/ponavlj)/((double)brojPoredjenja2/ponavlj)==1)cout<<"OBE PRETRAGE"<<endl;
                    else cout<<"INTERPOLACIONE PRETRAGE"<<endl;
                    brojPorednjenja1=0, brojPoredjenja2=0, ponavlj=0;
                    break;
                }
            }
        }
        else if(a==2)
        {
            cout<<"Kraj programa!"<<endl;
            break;
        }
        else
        {
            cout<<"Niste izabrali validnu opciju, pokusajte ponovo\t"<<endl;
        }
    }
    return 0;
}
