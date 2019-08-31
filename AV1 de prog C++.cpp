/*
                TRABALHO 1:

    Disciplina:  Tópicos de mat. apl. B ( C/C++ e BD )
    Professor:   Milton Ramos Ramirez

    Integrantes do grupo e DRE:     Andre Osorio Magaldi Netto   118041914
                                    Joao Paulo Alves Loureiro da Silva    117196504
                                    Rodrigo Bagdadi Benoliel    118031529



O programa recebe um arquivo estruturado da seguinte forma:


NOME                                              DRE                      TELEFONE                    NASCIMENTO
Andre Osorio Magaldi Netto                        118041914                986259629                   19981204
Joao Paulo Alves
****************                                  117114327                959872452                   20001206
.
.
.
Rodrigo Bagdadi Benoliel                          118056378                945434565                   19991216


*SEM NENHUMA LINHA VAZIA NO FINAL*.


Cada atributo de um aluno possui um tamanho máximo fixo.

O NASCIMENTO esta na forma ano+mes+dia, para que a ordenação possa ser feita de forma mais prática.

O objetivo principal deste código é a função ordenar(). Essa função recebe 4 argumentos iniciais: algo, path, campo de ordenação e campo de projeção.

A função ordenar() abre o arquivo contido no path (O nosso "banco de dados") , cria um vetor de structs (cada struct é um aluno), ordena esse vetor de
acordo com o algoritmo especificado (bubble ou merge), mostra na tela a lista do campo de projeção ordenada de acorodo com o campo de ordenação, e escreve no arquivo
as linhas ordenadas de forma correta.


No algoritmo merge sort nos usamos os conceitos de vetor da esquerda e vetor da direita apenas para facilitar na escrita do código.

Para medir o tempo gasto pelos dois algoritmos nos utilizamos a biblioteca time.h e a funcao clock().
O algoritmo BUBBLE sort se mostrou muito mais fácil de implementar, porém, muito mais devagar que o MERGE.


Para um arquivo pequeno e que não esta ordenado, os dois algoritmos ordenaram quase no mesmo tempo, mas a medida que aumentamos o tamanho do arquivo
o bubble sort se tornou muito mais LENTO que o merge sort.

Por outro lado, para um arquivo já ordenado o bubble sort foi muito mais rápido que o merge sort. Isso provavelmente ocorre porque com o arquivo ja ordenado
o bubble sort não troca nada e simplismente percorre o vetor checando condicoes, enquanto o merge sort ainda tem que dividir e juntar o vetor.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream> //Para a leitura do arquivo
#include <map>
#include <time.h>

using namespace std;


struct Aluno{ // Encontramos dificuldade para chamar um atributo de aluno a partir de uma string ( na função ordenar() ). Por esse motivo, nos criamos um dicionário (map) onde todas as
              // chaves são strings (DRE, nome etc...).
    string linha;
    map<string,string> atributos;

};


struct Aluno create_aluno(string linha)  // Essa função cria um struct Aluno baseado nos dados contidos em cada linha do nosso "Banco de dados"(O arquivo .txt).
{
    Aluno a1;
    a1.linha = linha;
    a1.atributos["nome"] = linha.substr(0,50);   //Todos os valores de cada chave do map (atributos) são strings. Isso foi feito para que não seja necessário especificar
    a1.atributos["DRE"] = linha.substr(50,25);   // se as variáveis que vamos ordenar são do tipo int (DRE) ou string (nome).
    a1.atributos["tel"] = linha.substr(75, 27);  // Além disso, os operadores < e > (Necessários para o merge_sort e no bubble_sort) funcionam para strings da mesma forma que funcionam para inteiros.
    a1.atributos["nascimento"] = linha.substr(103,9);
    return a1;
};



vector<Aluno> bubble_sort_struct(vector<Aluno> vetor, string campo_de_ord) //Implementação do algoritmo bubble sort.
{
	bool troca = false; //Essa variável diz se é preciso continuar trocando elementos de lugar.
	do{
		troca = false; //Iniciamos assumindo que a lista a esta ordenada. Caso não existirem elementos desordenados então essa variável não mudará de valor e o loop encerrará.
		for(int i=0; i<vetor.size()-1; i++)
        {
			if(vetor[i].atributos[campo_de_ord]>vetor[i+1].atributos[campo_de_ord]) //Se encontrar um par de elementos consecutivos e ordenados de forma errada, os dois trocam de lugar.
            {   // Trocamos os dois valores de posição:
				Aluno elem1 = vetor[i];
				vetor[i] = vetor[i+1];
                vetor[i+1] = elem1;
				troca = true;
			}
		}
	}while(troca);
	return vetor;
}


// Para criar a função merge sort nos primeiro criamos uma função que parte o vetor pela metade:

vector<vector<Aluno> > splitstruct (vector<Aluno> vetor){  //Essa funcao parte um vetor de structs ao meio e retorna um novo vetor que contém as duas metades.
                                                          // A maior das duas metades é sempre colocada na esquerda (De acordo com o algoritmo).
    vector<Aluno> vetorEsquerda;
    vector<Aluno> vetorDireita;
    int lim = (vetor.size()+1)/2;  //Armazena a posição aonde a lista é divida.
    for(int i = 0;i < vetor.size();i++ ){
        if(i < lim){
            vetorEsquerda.push_back(vetor[i]); //Todos antes de lim, são adicionados ao da esquerda.
        }else{
        vetorDireita.push_back(vetor[i]); //Todos depois de lim, são adicionados ao da direita.
        }
    }
    vector<vector<Aluno> > ret;
    ret.push_back(vetorEsquerda); //O da esquerda vem antes.
    ret.push_back(vetorDireita);
    return(ret);
}


vector<Aluno> merge_sort_struct(vector<Aluno> vetor, string campo_de_ord){ //Essa função ordenada um vetor de structs de acordo com um campo de ordenação (atributo de cada aluno) dado.
                                                                           // Esse campo de ordenação pode ser "DRE", "nome", "nascimento" ou "tel".

    if(vetor.size()==1){ // CASO TRIVIAL.
        return vetor; }

    vector<Aluno> vetorEsquerda = merge_sort_struct(splitstruct(vetor)[0], campo_de_ord);
    vector<Aluno> vetorDireita = merge_sort_struct(splitstruct(vetor)[1],campo_de_ord);

    //Quando o programa chega neste ponto, significa que a recursão acima retornou alguma coisa, ou seja, chegamos ao caso trivial e não é possível quebrar o vetor ainda mais.
    //A partir desse momento, a função ira começar a adicionar os novos elementos, de forma ordenada, ao vetorOrd.



    vector<Aluno> vetorOrd; // Vetor de tamanho variavel que contem os elementos ordenados.

    int partida = 0; //Parametro para guardarmos em qual posição a iteração anterior parou.
    for(int i = 0; i < vetorEsquerda.size(); i++){ //Para cada numero do vetor da esquerda nos o comparamos com todos da direita.
        for(int j = partida; j < vetorDireita.size(); j++){ // Iteramos a da direita. A partir do elemento que paramos na última iteração.

            if(vetorEsquerda[i].atributos[campo_de_ord] < vetorDireita[j].atributos[campo_de_ord]){   // Compara o atributo dos dois structs, o que tiver menor, fica na esquerda.
                vetorOrd.push_back(vetorEsquerda[i]); // Nos adicionamos o struct na esquerda.
                partida = j;// Para não repetir structs que ja colocamos no vetor, a proxima iteração
                            // deve começar de onde paramos na ultima, por isso guardamos o inteiro partida, pois , indica de onde deve começar na próxima iteração.

                if(i == vetorEsquerda.size()-1){ // Se for satisfeita significa que ja foram adicionados todos os elementos do vetor da esquerda, logo, só falta botar o que resta do vetor da direita.
                    for(int n = j;n<vetorDireita.size();n++){ //Adiciona o resto do elementos do vetor da direita.
                        vetorOrd.push_back(vetorDireita[n]);
                    }
                }
                break; //Quebramos o loop, pois a condiçao ja foi satisfeita, ou seja, ja adicionamos um struct ao novo vetor.
            }


            vetorOrd.push_back(vetorDireita[j]); // Como vetorEsquerda[i] >= vetorDireita[j] o da direita entra no vectorOrd.

            if(j == vetorDireita.size()-1){  // Se essa condição for satisfeita significa que ja foram colocados todos os elementos
                            // do vetor da direita, ou seja, só falta colocar em vectorOrd o resto dos structs da esquerda.

                for(int n = i;n<vetorEsquerda.size();n++){ //Adiciona os structs restantes da esquerda.
                    vetorOrd.push_back(vetorEsquerda[n]);
                }
                i = vetorEsquerda.size(); // Para que encerre o loop de fora pois ja foram colocados todos os elementos.
            }
        }
    }
    return vetorOrd; //Retorna o vetor ordenado.
}


//A PRINCIPAL:
void ordenar(string algo, string path, string campo_de_ordenacao, string campo_de_projecao ) // O primeiro argumento, algo, diz se ele usará bubble sort ou merge sort para fazer a ordenação.
 {                                                                                           // ( "bubble" para bubble-sort e "merge" para merge-sort )

    vector<Aluno> vetor_de_alunos;
    ifstream arquivo;
    arquivo.open(path); //Abrimos o arquivo que esta no path.

    string line; //irá armazenar o texto de uma linha inteira.

    getline(arquivo, line); //Pula a primeira linha pois é a que contém somente o nome das colunas.
    string primeira_linha = line; //Armazena a primeira linha com o titulo das colunas.

    while(getline(arquivo, line)) // Enquanto existirem novas linhas para ler leia a linha
    {
        Aluno a1 = create_aluno(line); // Cria um novo struct Aluno baseado na linha lida anteriormente.
        vetor_de_alunos.push_back(a1); // Coloca o novo aluno no vetor de alunos.
    }


    clock_t tempo = clock(); //Para medir o tempo gasto pelo algoritmo.

    //Escolhe qual o tipo de algoritmo e ordena:
    if(algo == "bubble"){vetor_de_alunos = bubble_sort_struct(vetor_de_alunos,campo_de_ordenacao);}
    if(algo == "merge") {vetor_de_alunos = merge_sort_struct(vetor_de_alunos,campo_de_ordenacao);}

    tempo = clock() - tempo;
    double tempo_gasto = ((double)tempo)/CLOCKS_PER_SEC; //Tempo gasto em segundos.

    //Projeta na tela a coluna do argumento campo_de_projeção:
    for(int i=0; i<vetor_de_alunos.size();i++){    cout<<vetor_de_alunos[i].atributos[campo_de_projecao]<<endl;    }

    arquivo.close();

    //Ordenamos o arquivo de acordo com o campo de ordenação. ESCREVE NO ARQUIVO
    ofstream file;
    file.open(path);
    file<< primeira_linha <<endl;
    for(int i=0; i<vetor_de_alunos.size();i++){    file<< vetor_de_alunos[i].linha <<endl;    }
    file.close();

    cout<< "Tamanho do arquivo: "<< vetor_de_alunos.size()<<" linhas."<<endl ;
    printf("Tempo do sort: %f segundos.\n", tempo_gasto);

}



int main(){

    ordenar("merge","table.txt","nascimento","nome");      //  Os campos aceitos são: "DRE", "nome", "nascimento", "tel".

    return 0;
}

