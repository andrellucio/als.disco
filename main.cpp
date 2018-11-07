#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include <cctype>
#include <vector>


using namespace std;

int produto_tot;
int maior;
int quantmaior;

struct produto_reg
{
    int regcod;
    string regmarca;
    double regpreco;
    int regquant;
};
vector <produto_reg> produto_vet(100);


class produto
{
public:
    void leitura()
    {
        int ct=0, achei=-1,tt=0;
        int cod;
        string marca;
        double preco;
        int quant;

        ifstream ler;
        ler.open("produto.txt");
        do
        {
            ler>>cod;
            if (cod>=maior)maior=cod;
            ler>>marca;
            ler>>preco;
            ler>>quant;
            if (quant>=quantmaior)quantmaior=quant;
            if (ler)
            {
                produto_vet[ct].regcod=cod;
                produto_vet[ct].regmarca=marca;
                produto_vet[ct].regpreco=preco;
                produto_vet[ct].regquant=quant;
                ct++;
            }
        }
        while ((ler)&&(ct<100));
        ler.close();
        produto_tot=ct;
        coencidencia();
    }
//-----------------------------------------------------------

    void escrita()
    {
        ofstream escrever;
        escrever.open("produto.txt");

        for (int ct=0;ct<produto_tot;ct++)
        {
            escrever<<produto_vet[ct].regcod<<"  ";
            escrever<<produto_vet[ct].regmarca<<"  ";
            escrever<<produto_vet[ct].regpreco<<"  ";
            escrever<<produto_vet[ct].regquant<<endl;
        }

        escrever.close();
    }

//-----------------------------------------------------------
    void coencidencia()
    {
        int cod, achei, tt, ct;
        for (int i=1;i<=100;i++)
        {
            achei=-1;
            ct=0;
            tt=0;

            for (int j=0; j<=produto_tot; j++)
            {
                if (produto_vet[j].regcod==i) ct++;
            }

            while (ct>=2)
            {
                for (tt=0;tt<=produto_tot;tt++)
                    if (produto_vet[tt].regcod==i) achei=tt;

                if (achei>=0)
                {
                    cout<<"Codigo repetido"<<endl;
                    cabecalho();
                    mostrar(achei);
                    cout      <<endl<<"|------------------------------------------------------------------------|"<<endl;

                    int acheei=0;
                    do
                    {
                        if (acheei==1) cout<<"Produto ja existe na lista!!!!!!"<<endl;
                        cout<<endl<<"Codigo ja existente, digite novo: ";
                        cin>>cod;
                        if (cod>=maior)maior=cod;
                        acheei=0;
                        for (int ct=0;ct<produto_tot;ct++)
                        {
                            if ((cod==produto_vet[ct].regcod))
                            {
                                acheei=1;
                            }
                        }
                    }
                    while (acheei==1);
                    produto_vet[achei].regcod=cod;
                }
                ct--;
            }
        }
        escrita();
    }
//-----------------------------------------------------------------------------------------------

    void mostrar(int achei)
    {
        cout<<endl<<"|   "<<setw(3)<<produto_vet[achei].regcod<<"   "; // setw ->Define a largura do campo a ser usada nas opera��es de sa�da (caracteres). 
        cout<<"|   "<<setw(10)<<left<<produto_vet[achei].regmarca<<"  ";
        cout<<"|   "<<setw(7)<<fixed<<setprecision(2)<<right<<produto_vet[achei].regpreco<<"  ";
        cout<<"|   "<<setw(7)<<right<<produto_vet[achei].regquant<<" |   ";
    }

    void cabecalho()
    {
        cout      <<"|__________________________________________________|";
        cout<<endl<<"| Codigo  |  Produto      |Valor R$    |Quantidade |"<<endl;
        cout      <<"|---------|---------------|------------|-----------|";
    }
//------------------------------------------------------------------


    void listagem()
    {
        cout<<"\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>SISTEM PUCRS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
        cout<<"\n\n Quantidade total incluido na lista: " <<produto_tot<<"."<<endl<<endl;

        cabecalho();
        for (int i=1;i<=maior;i++)
        {
            for (int ct=0; ct<=produto_tot; ct++)
            {
                if (produto_vet[ct].regcod==i) mostrar(ct);
            }
        }

        cout<<endl<<"|__________________________________________________|"<<endl;

        cout<<endl<<"Fim da lista"<<endl<<endl;
        cout<<"_____________________________________________________________________________"<<endl;
    }

//----------------------------------------------------------------------

    void ordemquant()
    {
        cout<<"Listagem dos "<<produto_tot<<" produtos"<<endl<<endl;
        cabecalho();

        for (int i=1;i<=quantmaior;i++)
        {
            for (int ct=0; ct<=produto_tot; ct++)
            {
                if (produto_vet[ct].regquant==i) mostrar(ct);
            }
        }

        cout<<endl<<"|---------------------------------------------------------|"<<endl;
        cout<<endl<<"\nFim da lista"<<endl<<endl;
        cout<<"---------------------------------------------------------"<<endl;
    }

//--------------------------------------------------------------------------

    void ordemvalor()
    {
        cout<<"Listagem dos "<<produto_tot<<" Produto"<<endl<<endl;
        cabecalho();

        for (int i=quantmaior;i>0;i--)
        {
            for (int ct=0; ct<=produto_tot; ct++)
            {
                if (produto_vet[ct].regquant==i) mostrar(ct);
            }
        }

        cout<<endl<<"|------------------------------------------------------------------------|"<<endl;
        cout<<endl<<"Fim da listagem"<<endl<<endl;
        cout<<"--------------------------------------------------------------------------------"<<endl;
    }

//-----------------------------------------------------------------------------

    void excluir()
    {
        int cod2,achei=-1,ct=0, cod=0;
        cout<<"Digite o codigo: ";
        cin>>cod;

        for (ct=0;ct<produto_tot;ct++)
            if (produto_vet[ct].regcod==cod) achei=ct;

        if (achei>=0)
        {
            cod2=achei+1;

            for (int ct=achei;ct<produto_tot;ct++)
            {
                produto_vet[achei].regcod=produto_vet[cod2].regcod;
                produto_vet[achei].regmarca=produto_vet[cod2].regmarca;
                produto_vet[achei].regpreco=produto_vet[cod2].regpreco;
                produto_vet[achei].regquant=produto_vet[cod2].regquant;
                cod2++;
                achei++;
            }
            produto_tot--;
            escrita();
            cout<<endl<<" EXCLUIDA COM SUCESSO!!!"<<endl<<endl;
        }
        else cout<<endl<<"Esse codigo de produto nao existe"<<endl<<endl;
    }

//-----------------------------------------------------------------------------

    void pesquisa()
    {
        int cod, ct, achei=-1, op;
        string valor,red;
        cout<<"\n Digite 1 para pesquisar pelo codigo, e 2 para pesquisar pelo nome: ";
        cin>>op;
        if (op==1)
        {
            cout<<"Digite o codigo: ";
            cin>>cod;

            for (ct=0;ct<=produto_tot;ct++)
                if (produto_vet[ct].regcod==cod) achei=ct;
            if (achei>=0)
            {
                cabecalho();
                mostrar(achei);
                cout<<endl<<"|------------------------------------------------------------------------|"<<endl;

            }
            else
            {
                cout<<endl<<"Codigo nao encontrado"<<endl;
                cout<<"--------------------------------------------------------------------------------"<<endl;
            }

        }

        else
        {
            cout<<"Digite o texto: ";
            cin>>valor;


            cabecalho();
            for (ct=0;ct<=produto_tot;ct++)
            {
                red=produto_vet[ct].regmarca;
                red.resize(valor.size());// sIZE -> Fun��o que retorna o tamanho em caracteres da string.

                int i = red.compare(valor);

                if (i==0)
                {
                    mostrar(ct);
                    cout<<"M";
                }

                red.resize(valor.size());


                i = red.compare(valor);

                if (i==0)
                {
                    mostrar(ct);
                    cout<<"D";
                }
            }
            cout<<endl<<"|------------------------------------------------------------------------|"<<endl;
        }
    }

//-----------------------------------------------------------------------------------

    void adicionar()
    {
        int cod;
        string marca;
        double preco;
        int quant;
        int achei=0;
        do
        {
            if (achei==1) cout<<endl<<"Esse codigo  ja existe!!!!!!"<<endl;
            cout<<endl<<"Digite o codigo: ";
            cin>>cod;
            achei=0;
            for (int ct=0;ct<produto_tot;ct++)
            {
                if ((cod==produto_vet[ct].regcod))
                {
                    achei=1;
                }
            }
        }
        while (achei==1);

        if (maior<cod)maior=cod;
        produto_vet[produto_tot].regcod=cod;
        cout<<"Digite o produto comprado: ";
        cin>>marca;
        produto_vet[produto_tot].regmarca=marca;
        cout<<"Digite o valor do produto: ";
        cin>>preco;
        produto_vet[produto_tot].regpreco=preco;
        cout<<"Digite a quantidade comprada: ";
        cin>>quant;
        produto_vet[produto_tot].regquant=quant;
        cout<<endl<<"PRODUTO ADICIONADO COM SUCESSO!!!"<<endl<<endl;
        produto_tot++;
        escrita();
    }

//-----------------------------------------------------------------------

    void repor()
    {
        int cod, ct, achei=-1,var;
        cout<<"Digite o codigo: ";
        cin>>cod;

        for (ct=0;ct<produto_tot;ct++)
            if (produto_vet[ct].regcod==cod) achei=ct;
        if (achei>=0)
        {
            cout<<endl<<produto_vet[achei].regcod<<" - ";
            cout<<produto_vet[achei].regmarca<<" - ";
            cout<<produto_vet[achei].regpreco<<" - ";
            cout<<"Quantidade: ";
            cin>>var;
            produto_vet[achei].regquant=produto_vet[achei].regquant+var;
            cout<<endl<<"QUANTIDADE ALTERADA COM SUCESSO!!!"<<endl<<endl;
        }
        else cout<<endl<<"Codigo nao encontrado"<<endl<<endl;
        escrita();
    }

//------------------------------------------------------------------------

    void marca()
    {
        int cod, ct, achei=-1,var;
        cout<<"Digite o codigo: ";
        cin>>cod;

        for (ct=0;ct<produto_tot;ct++)
            if (produto_vet[ct].regcod==cod) achei=ct;
        if (achei>=0)
        {
            cout<<endl<<produto_vet[achei].regcod<<" - ";
            cout<<produto_vet[achei].regmarca<<" - ";
            cout<<produto_vet[achei].regpreco<<" - ";
            cout<<produto_vet[achei].regquant<<" - ";
            cout<<"Nova marca: ";
            cin>>produto_vet[achei].regmarca;
            cout<<endl<<"MARCA ALTERADA COM SUCESSO!!!"<<endl<<endl;
        }
        else cout<<endl<<"Codigo nao encontrado";
        escrita();
    }

//--------------------------------------------------------------------------

    void preco()
    {
        int cod, ct, achei=-1,var;
        cout<<"Digite o codigo do produto: ";
        cin>>cod;

        for (ct=0;ct<produto_tot;ct++)
            if (produto_vet[ct].regcod==cod) achei=ct;
        if (achei>=0)
        {
            cout<<endl<<produto_vet[achei].regcod<<" - ";
            cout<<produto_vet[achei].regmarca<<" - ";
            cout<<produto_vet[achei].regquant<<" - ";
            cout<<"Novo preco: ";
            cin>>produto_vet[achei].regpreco;
            cout<<endl<<"PRECO ALTERADO COM SUCESSO!!!"<<endl<<endl;
        }
        else cout<<endl<<"Codigo nao encontrado";
        escrita();
    }

//---------------------------------------------------------------------------

    void cod()
    {
        int cod, ct, achei=-1,var, err,acheii;
        cout<<"Digite o codigo antigo: ";pesquisa
        cin>>cod;
        do
        {
            if (achei==1) cout<<endl<<"produto ja existe!!!!!!"<<endl;
            for (ct=0;ct<produto_tot;ct++)
                if (produto_vet[ct].regcod==cod)
                {
                    acheii=ct;
                    achei=ct;
                }
            if (achei>=0)
            {
                cout<<endl<<produto_vet[acheii].regcod<<" - ";
                cout<<produto_vet[acheii].regmarca<<" - ";
                cout<<produto_vet[acheii].regquant<<" - ";
                cout<<"Novo codigo: ";
                cin>>var;
                err=0;
            }
            else
            {
                cout<<endl<<"Codigo nao encontrado"<<endl<<endl;
                err=1;
            }

            if (err!=1)
            {
                achei=0;
                for (int ct=0;ct<produto_tot;ct++)
                {
                    if ((var==produto_vet[ct].regcod))
                    {
                        achei=1;
                        cout<<"ALTERAR CODIGO"<<endl;
                    }
                }
            }
        }
        while (achei==1);

        if (err!=1)
        {
            produto_vet[acheii].regcod=var;

                maior=0;
                for (int i=0;i<=produto_tot;i++)
                {
                    if (maior<produto_vet[i].regcod) maior=produto_vet[i].regcod;
                }
                if(maior<var) maior=var;
            }

            cout<<endl<<"CODIGO ALTERADO COM SUCESSO!!!"<<endl<<endl;
            escrita();

        }

};

//-----------------------------------------------------------------------------------------------

int main()
{
    int op;
    produto o;
    o.leitura();
    o.listagem();
pesquisa
    while (true)
    {
        cout<<endl<<"                                    OPCOES:\n                        "<<endl<<"                        1- Incluir produtos\n             "<<endl<<"                        2- Pesquisar produtos\n                   "<<endl
        <<"                        3- Alterar quantidade das produtos\n            "<<endl<<"                        4- Apagar produtos\n               "<<endl<<"                        5- Exibir lista completa"<<endl<<"______________________________________________________________________________"
                      <<" "<<endl<<endl<<"                        Digite: ";
        cin>>op;


        switch (op)
        {
        case 1:
            cout<<"\n INCLUIR\n"<<endl;
            o.adicionar();
            break;

        case 2:
            cout<<"\n PESQUISANDO\n"<<endl;
            o.pesquisa();
            break;

        case 3:
            cout<<"\n ALTERACAO\n"<<endl;
            o.repor();
            break;


        case 4:
            cout<<"\n EXCLUIR\n"<<endl;
            o.excluir();
            break;

        case 5:
            o.listagem();
            break;


        default:

            cout<<endl<<"Opcao invalida";
        }
    }
}
