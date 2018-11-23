#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

int produto_tot;
int maior;
int quantmaior;

class prod
{
    public:
      int regcod;
      string regmarca;
      double regpreco;
      int regquant;

      prod( int regcod, string regmarca, double regpreco, int regquant)
      {
        this->regcod = regcod;
        this->regmarca = regmarca;
        this->regpreco = regpreco;
        this->regquant = regquant;
      }
};

/*class produto
{
public:*/
    void leitura(vector<prod> dados)    //leitura do arquivo txt
    {
        int ct=0, achei=-1;
        int cod;
        string marca;
        double preco;
        int quant;

        ifstream ler;
        ler.open("produto.txt");
        do{
            ler>>cod;
            if (cod>=maior)maior=cod;   //coloca os codigos de produtos em ordem crescente
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
        }while ((ler)&&(ct<100));
        ler.close();
        produto_tot=ct;
    }
//-----------------------------------------------------------
    void escrita()          //escrever no arquivo txt
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
    void mostrar(int achei)     //mostra a lista de produtos
    {
        cout<<endl<<"    "<<setw(3)<<produto_vet[achei].regcod<<"   "; // setw ->Define a largura do campo a ser usada nas operações de saída (caracteres). 
        cout<<"    "<<setw(10)<<left<<produto_vet[achei].regmarca<<"  ";
        cout<<"    "<<setw(7)<<fixed<<setprecision(2)<<right<<produto_vet[achei].regpreco<<"  ";
        cout<<"    "<<setw(7)<<right<<produto_vet[achei].regquant<<"     ";
    }
//------------------------------------------------------------------------
    void cabecalho()      //imprime o cabeçalho
    {
        cout<<endl<<"  Codigo     Produto       Valor R$     Quantidade  "<<endl;
        cout      <<"|---------|---------------|------------|-----------|";
    }
//------------------------------------------------------------------
    void listagem()       //organiza os produtos abaixo do cabeçalho
    {
        cabecalho();
        for (int i=1;i<=maior;i++)
        {
            for (int ct=0; ct<=produto_tot; ct++)
            {
                if (produto_vet[ct].regcod==i) mostrar(ct);
            }
        }
    }
//----------------------------------------------------------------------
    void excluir()        //exclui produtos
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
    void adicionar()          //adiciona produtos à lista
    {
        int cod;
        string marca;
        double preco;
        int quant;
        int achei=0;
        do{
            if (achei==1) cout<<endl<<"Esse codigo  ja existe!!!!!!"<<endl;   //verifica se já existe o codigo digitado
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
        }while (achei==1);

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
/*};*/
//-----------------------------------------------------------------------------------------------
int main()
{
    vector<int> dados;
    
    int op;
    leitura();
    listagem();

    while ( op!= 4 )
    {
        cout<<endl<<endl<<"                                    OPCOES:\n                        "<<endl<<"                        1- Incluir produtos\n             "<<endl<<"                        2- Apagar produtos\n               "<<endl<<"                        3- Exibir lista completa\n"<<endl<<"                        4- Encerrar tarefa\n             "<<endl<<endl<<"  Digite: ";
        cin>>op;

      switch (op)
        {
        case 1:
            cout<<"\n INCLUIR\n"<<endl;
            adicionar();
            break;

        case 2:
            cout<<"\n EXCLUIR\n"<<endl;
            excluir();
            break;

        case 3:
            listagem();
            break;

        case 4:
            cout<<endl<<"Programa encerrado."<<endl;
            break;

        default:
            cout<<endl<<"Opcao invalida";
        }
    }
}