#include <iostream>
#include <fstream>

using namespace std;

struct nod
{
    int value,ech;
    nod *left,*right;
};

nod *root;

void drumMaxim(nod *root,int &maxx,int lung)
{
    if(root)
    {
        drumMaxim(root->left,maxx,lung+1);
        if(root->left==NULL && root->right==NULL && lung>maxx)
            maxx=lung;
        drumMaxim(root->right,maxx,lung+1);
    }
}

void calcul_ech(nod *root)
{
    int hLeft=1,hRight=1;
    if(root->left)
        drumMaxim(root->left,hLeft,1);
    else
        hLeft=0;
    if(root->right)
        drumMaxim(root->right,hRight,1);
    else
        hRight=0;
    root->ech=hLeft-hRight;
}

void rot_L(nod *&root)
{
    nod *aux;
    aux=root->right;
    root->right=aux->left;
    aux->left=root;
    calcul_ech(root);
    calcul_ech(aux);
    root=aux;
}

void rot_R(nod *&root)
{
    nod *aux;
    aux=root->left;
    root->left=aux->right;
    aux->right=root;
    calcul_ech(root);
    calcul_ech(aux);
    root=aux;
}

void rot_LR(nod *&root)
{
    rot_L(root->left);
    rot_R(root);
}

void rot_RL(nod *&root)
{
    rot_R(root->right);
    rot_L(root);
}

void echilibrare(nod *&root)
{
    nod *aux;
    calcul_ech(root);
    if(root->ech==-2)
    {
        aux=root->right;
        if(aux->ech==(-1))
            rot_L(root);
        else if(aux->ech==1)
            rot_RL(root);
    }
    else if(root->ech==2)
    {
        aux=root->left;
        if(aux->ech==1)
            rot_R(root);
        else if(aux->ech==(-1))
            rot_LR(root);
    }
}

void inserare(nod *&root,int val)
{
    if(root==NULL)
    {
        nod *nou=new nod;
        nou->value=val;
        nou->ech=0;
        nou->left=NULL;
        nou->right=NULL;
        root=nou;
    }
    else
    {

        if(val<root->value)
            inserare(root->left,val);
        else if(val>root->value)
            inserare(root->right,val);
    }
    echilibrare(root);
}

void SRD(nod *r)
{
    if(r)
    {
        SRD(r->left);
        cout<<r->value<<' ';
        SRD((r->right));
    }
}

void RSD(nod *r)
{
    if(r)
    {
        cout<<r->value<<' ';
        RSD(r->left);
        RSD(r->right);
    }
}

int cautare(nod *r,int val)
{
    nod *aux=root;
    while(aux)
    {
        if(aux->value==val)
            return 1;
        if(val<aux->value)
            aux=aux->left;
        else if(val>aux->value)
            aux=aux->right;
    }
    return 0;
}

int maxx(nod *r)
{
    nod *aux=root;
    while(aux->right)
    {
        aux=aux->right;
    }
    return aux->value;
}

nod *maxx_nod(nod *r)
{
    nod *aux=r;
    while(aux->right)
        aux=aux->right;
    return aux;
}

void stergere(nod *&root, int val)
{
    if (root == NULL)
    {
        return;
    }
    if (val < root->value)
    {
        stergere(root->left, val);
    }
    else if (val > root->value)
    {
        stergere(root->right, val);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        else if (root->left == NULL)
        {
            nod *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            nod *temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            nod *temp = maxx_nod(root->left);
            root->value = temp->value;
            stergere(root->left, temp->value);
        }
    }
}

void meniu()
{
    int opt;
    while(true)
    {
        cout<<"1. Cauta x in arbore\n2. Afiseaza maximul din arbore\n3. Sterge valoarea x\n4. Afiseaza in ordine crescatoare cheile din arbore\n5. Exit\n";
        do
        {
            cin>>opt;
        }
        while(opt<1 && opt>4);
        switch(opt)
        {
        case 1:
        {
            int x;
            cout<<"Dati valoarea cautata: ";
            cin>>x;
            cout<<cautare(root,x)<<endl;
            break;
        }
        case 2:
        {
            cout<<"Maximul din arbore: "<<maxx(root)<<endl;
            break;
        }
        case 3:
        {
            int sters;
            cout<<"Dati valoarea de sters: ";
            cin>>sters;
            stergere(root,sters);
            break;
        }
        case 4:
        {
            SRD(root);
            cout<<endl;
            break;
        }
        case 5:
            return;
        }
    }

}

int main()
{
    ifstream f("date.in");
    int x;
    while(f>>x)
        inserare(root,x);
    //meniu();
    RSD(root);
    f.close();
    return 0;
}
