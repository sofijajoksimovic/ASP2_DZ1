#include <iostream>
#include <queue>
#include <cmath>
#include<stack>
using namespace std;
struct Cvor{
    int info;
    int visina;
    struct Cvor*right;
    struct Cvor*left;
    struct Cvor*parent;
};
//kreiramo prazno stablo
Cvor* kreirajStablo(){
    Cvor*root= nullptr;
    return root;
}
//fja vraca visinu zadatog cvora
int visina(Cvor*t){
    if (t == nullptr)
        return 0;
    return t->visina;
}
int balans(Cvor*t){
    if (t == nullptr)
        return 0;
    return visina(t->left) - visina(t->right);
}
//desna rotacija, updatuje pokazivac na oca, koji mu je prosledjen
Cvor* rightRot(Cvor*x,Cvor*root,Cvor*fp) {
    Cvor *y = x->left;
    Cvor *temp = y->right;
    y->right = x;
    x->left = temp;
    y->parent=fp;
    if(fp!= nullptr){
        if(fp->right==x)fp->right=y;
        else fp->left=y;
    }
    x->visina = max(visina(x->left),visina(x->right)) + 1;
    y->visina = max(visina(y->left),visina(y->right)) + 1;
    if(root==x)root=y;//menjamo pokazivac na koren u slucaju da je on kritican cvor
    return root;
}
//analogno desnoj rotaciji
Cvor* leftRot(Cvor*x,Cvor*root,Cvor*fp) {
    Cvor *y = x->right;
    Cvor *temp = y->left;
    y->left = x;
    x->right = temp;
    y->parent = fp;
    if (fp != nullptr) {
        if (fp->right == x)fp->right = y;
        else fp->left = y;
    }
    x->visina = max(visina(x->left),visina(x->right)) + 1;
    y->visina = max(visina(y->left),visina(y->right)) + 1;
    if (root == x)root = y;
    return root;
}
//fja koja proverava da li je root null, ako jeste umece koren a ako nije trazi kljuc koji zelimo da umetnemo,
// ako ga nismo nasli pravimo novi cvor, postavljamo pokazivace, zatim za svaki element tj njegov predak koji
//stavili na stek na putu do njega updatujemo visinu, proglasavmo ga kriticnim i rotiramo ako je postao debalansiran
Cvor* unesiKljuc(Cvor* root,int k)
{
    if(root== nullptr){
        root=new Cvor;
        root->info=k;
        root->right= nullptr;
        root->left= nullptr;
        root->parent= nullptr;
        root->visina=1;
        return root;
    }
    Cvor*p=root,*q,*fp;
    stack<Cvor*>s;
    while(p!= nullptr)
    {
        s.push(p);
        if(k==p->info)
            return root;
        if (k < p->info) {
            q = p->left;
        }
        else q = p->right;
        fp = p;
        p = q;
    }
    q=new Cvor;
    q->info=k;
    q->left= nullptr;
    q->right= nullptr;
    q->parent=fp;
    if(k<fp->info)fp->left=q;
    else fp->right=q;
    q->visina=1;
    while(!s.empty()) {
        Cvor*curr=s.top();
        s.pop();
        Cvor *fparent;
        if(!s.empty()) {
            fparent = s.top();
            s.pop();
        }
        else fparent= nullptr;
        curr->visina=max(visina(curr->left),visina(curr->right))+1;
        int b= balans(curr);
        if(b==2 and balans(curr->left)==1){
            root=rightRot(curr,root,fparent);
        }
        if(b==2 and balans(curr->left)==-1)
        {
            root=leftRot(curr->left,root,curr);
            root=rightRot(curr,root,fparent);
        }
        if(b==-2 and balans(curr->right)==-1)
        {
            root= leftRot(curr,root,fparent);
        }
        if(b==-2 and balans(curr->right)==1)
        {
            root=rightRot(curr->right,root,curr);
            root=leftRot(curr,root,fparent);
        }
        if(fparent!= nullptr)s.push(fparent);
    }
    return root;
}
//fja koja za svaki clan niza kljuceva koje je korisnik uneo umece cvor u stablo, preko unesiKljuc
Cvor* unesiKljuceve(Cvor*root, int n, int niz[])
{
    for (int i = 0; i < n; ++i) {
        root=unesiKljuc(root,niz[i]);
    }
    return root;
}
//fja koja proverava da li je kljuc u stablu
bool pripadnost(Cvor*root,int k){
    Cvor*p=root;
    while(p!= nullptr){
        if(k==p->info)
            return true;
        else if(k<p->info)
            p=p->left;
        else
            p=p->right;
    }
    return false;
}
void obrisiStablo(Cvor*root){
    if(root== nullptr)
        return;
    queue<Cvor*> q;
    q.push(root);
    Cvor*prvi;
    while (!q.empty())
    {
        prvi = q.front();
        q.pop();
        if (prvi->left!= nullptr) {
            q.push(prvi->left);
        }
        if (prvi->right!= nullptr) {
            q.push(prvi->right);
        }
        delete prvi;
    }
}
//fja koja pronalazi uniju kljuceva dva stabla
int* unijaDvaSkupa(Cvor*r1, Cvor*r2, int &max){
    int*niz=new int[max];//pocetni maksimum je broj cvorova r1 + broj cvorova r2, u slucjau da su vise cvorova zajednicki ovaj broj ce se smanjiti
    int br=0;
    queue<Cvor*> q;
    q.push(r1);
    //prvo sve cvorove iz r1 dodajemo u uniju
    while(!q.empty()){
        Cvor*prvi=q.front();
        q.pop();
        niz[br++]=prvi->info;
        if (prvi->left!= nullptr) {
            q.push(prvi->left);
        }
        if (prvi->right) {
            q.push(prvi->right);
        }
    }
    //zatim u uniju dodajemo samo one cvorove iz r2 koji nisu u r1 tj nisu vec dodati
    q.push(r2);
    while(!q.empty()){
        Cvor*prvi=q.front();
        q.pop();
        if(!pripadnost(r1,prvi->info)){
            niz[br++]=prvi->info;
        }
        if (prvi->left!= nullptr) {
            q.push(prvi->left);
        }
        if (prvi->right) {
            q.push(prvi->right);
        }
    }
    //smanjujemo duzinu niza tj unije
    int *niz1=new int[br];
    for (int i = 0; i < br; ++i) {
        niz1[i]=niz[i];
    }
    delete[] niz;
    max=br;//menjamo max kroz funkciju
    return niz1;
}
//funkcija koju cemo koristiti u ispisiStablo kako bismo ispisali razmake izmedju cvorova
void razmak(Cvor* t,double n)
{   //koliko uvlacimo pre pocetka ispisa cvorova tog nivoa
    for (int i=0; i<n; i++)
    {
        cout << "  ";
    }
    if (t != nullptr)
    {
        cout <<t->info;
    }
    else
    {
        cout <<" ";
    }
}
//funkcija koja ispisuje stablo po nivoima da bi se jasno istakla struktura
void ispisiStablo(Cvor* root)
{
    queue<Cvor*> nivo, sledeci;
    //korisitmo dva reda, jedan trenunti-nivo a jedan sledeci
    nivo.push(root);
    int br = 0;//brojac do kog nivoa smo dosli tj visine
    int vis= visina(root) - 1;//broj nivoa maksimalan
    double n = pow(2, (vis + 1)) - 1;

    while (br <= vis) {
        Cvor* t= nivo.front();
        nivo.pop();

        if (sledeci.empty())//na pocetku ostavljamo vise mesta
        {
            razmak(t,n/ pow(2, br +1));
        }
        else
        {
            razmak(t, n / pow(2, br));
        }
        if (t)
        {
            sledeci.push(t->left);
            sledeci.push(t->right);
        }
        else
        {
            sledeci.push(nullptr);
            sledeci.push(nullptr);

        }
        if (nivo.empty())
        {
            br++;
            cout << "\n\n";
            nivo = sledeci;
            while (!sledeci.empty())
            {
                sledeci.pop();
            }
        }
    }
}
int main() {
    cout<<"Dobrodosli! Da li zelite da kreirate prazno stablo? (1 za DA)"<<endl;
    int a;
    cin>>a;
    if(a==1){
        Cvor *root=kreirajStablo();
        cout<<"Prazno stablo je kreirano!"<<endl;
        cout<<"Unesite broj kljuceva i kljuceve koje zelite da ubacite u stablo:"<<endl;
        int n;
        cin>>n;
        int niz[n];
        for (int i = 0; i < n; ++i) {
            cin>>niz[i];
        }
        root=unesiKljuceve(root, n, niz);
        cout<<"AVL stablo/skup je popunjen!, ovako izgleda:"<<endl;
        ispisiStablo(root);
        while(true) {
            cout << "Izaberite neku od sledecih opcija:\n"
                    "1.Umetanje novog elementa u skup\n"
                    "2.Provera pripadnosti nekog elementa skupu\n"
                    "3.Kreiranje novog skupa i prikaz unije dva zadata skupa\n"
                    "4.Kraj programa" << endl;
            int b;
            cin>>b;
            if(b==1)
            {
                int k;
                cout<<"Unesite kljuc:"<<endl;
                cin>>k;
                root=unesiKljuc(root,k);
                cout<<"Stablo sada izgleda ovako:"<<endl;
                ispisiStablo(root);
                n++;
            }
            else if(b==2)
            {
                int k;
                cout<<"Unesite kljuc:"<<endl;
                cin>>k;
                if(pripadnost(root,k))cout<<"KLJUC JE U SKUPU."<<endl;
                else cout<<"KLJUC NIJE U SKUPU."<<endl;
            }
            else if(b==3)
            {
                Cvor*root2=kreirajStablo();
                cout<<"Novo prazno stablo je kreirano!"<<endl;
                cout<<"Unesite broj kljuceva i kljuceve koje zelite da ubacite u stablo:"<<endl;
                int m;
                cin>>m;
                int niz1[m];
                for (int i = 0; i < m; ++i) {
                    cin>>niz1[i];
                }
                root2=unesiKljuceve(root2, m, niz1);
                cout<<"AVL stablo/skup je popunjen!, ovako izgleda:"<<endl;
                ispisiStablo(root2);
                cout<<"Unija skupova kljuceva ova dva stabla je:"<<endl;
                int max=n+m;
                int *unija;
                unija=unijaDvaSkupa(root,root2,max);
                for (int i = 0; i < max; ++i) {
                    cout<<unija[i]<<" ";
                }
                cout<<endl;
                obrisiStablo(root2);
            }
            else if(b==4)
            {
                obrisiStablo(root);
                cout<<"Stablo je obrisano! Kraj rada programa!"<<endl;
                return 0;
            }
            else{
                cout<<"Izabrali ste nevalidnu opiciju, pokusajte ponovo:"<<endl;
            }
        }
    }
    return 0;
}
