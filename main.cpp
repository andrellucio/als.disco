//Felipe Pereira de Castro
//André Lucio de Souza

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

int produto_tot;
int maior=0;

class prod
{
    public:
      int cod;
      string marca;
      double preco;
      int quant;

      prod( int cod, string marca, double preco, int quant)
      {
        this->cod = cod;
        this->marca = marca;
        this->preco = preco;
        this->quant = quant;
      }
};
//-------------------------------------------------------------------
    void leitura(vector<prod> &dados)    //leitura do arquivo txt
    {
        int ct=0;
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
            if (ler)
            {
                prod p(cod, marca, preco, quant);
                dados.push_back(p);
                
                dados[ct].cod=cod;
                dados[ct].marca=marca;
                dados[ct].preco=preco;
                dados[ct].quant=quant;
                ct++;
            }
        }while (ler);
        ler.close();
        produto_tot=ct;
    }
//-----------------------------------------------------------
    void escrita(vector<prod> dados)          //escrever no arquivo txt
    {
        ofstream escrever;
        escrever.open("produto.txt");
        for (int ct=0;ct<dados.size();ct++)
        {
            escrever<<dados[ct].cod<<"  ";
            escrever<<dados[ct].marca<<"  ";
            escrever<<dados[ct].preco<<"  ";
            escrever<<dados[ct].quant<<endl;
        }
        escrever.close();
    }
//-----------------------------------------------------------
    void mostrar(vector<prod> dados,int ct)     //mostra a lista de produtos
    {
        cout<<endl<<"    "<<setw(3)<<dados[ct].cod<<"   "; // setw ->Define a largura do campo a ser usada nas operações de saída (caracteres). 
        cout<<"    "<<setw(10)<<left<<dados[ct].marca<<"  ";
        cout<<"    "<<setw(7)<<fixed<<setprecision(2)<<right<<dados[ct].preco<<"  ";
        cout<<"    "<<setw(7)<<right<<dados[ct].quant<<"     ";
    }
//------------------------------------------------------------------------
    void cabecalho()      //imprime o cabeçalho
    {
        cout<<endl<<"  Codigo     Produto       Valor R$     Quantidade  "<<endl;
        cout      <<"|---------|---------------|------------|-----------|";
    }
//------------------------------------------------------------------
    void listagem(vector<prod> dados)       //organiza os produtos abaixo do cabeçalho
    {
        cabecalho();
        for (int i=1;i<=maior;i++)
        {
            for (int ct=0; ct<=produto_tot; ct++)
            {
                if (dados[ct].cod==i) mostrar(dados, ct);
            }
        }
    }
//----------------------------------------------------------------------
    void excluir(vector<prod> &dados)        //exclui produtos
    {
        int cod2, achei=-1, ct, cod=0;
        cout<<"Digite o codigo: ";
        cin>>cod;

        for (ct=0;ct<produto_tot;ct++)
            if (dados[ct].cod==cod) achei=ct;

        if (achei>=0)
        {
            cod2=achei+1;
            for (int ct=achei;ct<produto_tot;ct++)
            {
                dados[achei].cod=dados[cod2].cod;
                dados[achei].marca=dados[cod2].marca;
                dados[achei].preco=dados[cod2].preco;
                dados[achei].quant=dados[cod2].quant;
                cod2++;
                achei++;
            }
            produto_tot--;
            escrita(dados);
            cout<<endl<<" EXCLUIDA COM SUCESSO!!!"<<endl<<endl;
        }
        else cout<<endl<<"Esse codigo de produto nao existe"<<endl<<endl;
    }
//-----------------------------------------------------------------------------
    void adicionar(vector<prod> &dados)          //adiciona produtos à lista
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
                if (cod==dados[ct].cod)
                {
                    achei=1;
                }
            }
        }while (achei==1);

        if (maior<cod)maior=cod;
        cout<<"Digite o produto comprado: ";
        cin>>marca;
        cout<<"Digite o valor do produto: ";
        cin>>preco;
        cout<<"Digite a quantidade comprada: ";
        cin>>quant;
        cout<<endl<<"PRODUTO ADICIONADO COM SUCESSO!!!"<<endl<<endl;
        produto_tot++;
        prod p(cod, marca, preco, quant);
        dados.push_back(p);
        escrita(dados);
    }    
//-----------------------------------------------------------------------------------------------
int main()
{
    vector<prod> dados;
    
    int op;
    leitura(dados);
    listagem(dados);

    while ( op!= 4 )
    {
        cout<<endl<<endl<<"                                    OPCOES:\n                        "<<endl<<"                        1- Incluir produtos\n             "<<endl<<"                        2- Apagar produtos\n               "<<endl<<"                        3- Exibir lista completa\n"<<endl<<"                        4- Encerrar tarefa\n             "<<endl<<endl<<"  Digite: ";
        cin>>op;

      switch (op)
        {
        case 1:
            cout<<"\n INCLUIR\n"<<endl;
            adicionar(dados);
            break;

        case 2:
            cout<<"\n EXCLUIR\n"<<endl;
            excluir(dados);
            break;

        case 3:
            listagem(dados);
            break;

        case 4:
            cout<<endl<<"Programa encerrado."<<endl;
            break;

        default:
            cout<<endl<<"Opcao invalida";
        }
    }
}