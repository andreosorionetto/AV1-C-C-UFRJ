/*
                PROJETO 2 TMAB
    Andre Osorio Magaldi Netto                118041914
    Joao Paulo Alves Loureiro Da Silva        117196504
    Rodrigo Bagdadi Benoliel                  118031529

*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<stdlib.h>
#include <typeinfo>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <bits/stdc++.h>
#include "funcoesGerais.h"

using namespace std;

void carregaBancoSequencial()
{
    FILE * arq;
    arq = fopen("bancoSequencial.bin","wb");
    ifstream arq_csv;
    arq_csv.open("ghtestes.csv");
    string linha;
    getline(arq_csv,linha);
    vector<Registro> todosRegistros;

    while(!arq_csv.eof())
    {
        getline(arq_csv,linha);
        vector<string> vregistro = split(linha,',');
        Registro novoRegistro;
        novoRegistro.uhe = stoi(vregistro[0],nullptr,10);
        novoRegistro.cenario = stoi(vregistro[1],nullptr,10);
        novoRegistro.estagio = vregistro[2];
        novoRegistro.geracao = stof(vregistro[3],nullptr);
        todosRegistros.push_back(novoRegistro);
    }

    sort( todosRegistros.begin(), todosRegistros.end(), comparaDoisRegistros ); //Ordenada todos os registros lidos para o vetor "todosRegistros"
    unsigned int n=0;
    while( n < todosRegistros.size() )  //Varre o vetor criando blocos de memória e os gravando no arquivo quando cheios.
    {
        Registro bloco_escrito1[fblocagem];
        for(int i=0; i<fblocagem;i++)
        {
            if( n>todosRegistros.size()-1 ){
                    break;
            }
            memcpy(&bloco_escrito1[i],&todosRegistros[n],sizeof(Registro));
            n += 1;
        }
        fwrite((void *)&bloco_escrito1,sizeof(bloco_escrito1),1,arq);
    }
    fclose(arq);
    arq_csv.close();
}


void lerBin(const char * nomeArq){  //Função utilizada para auxiliar na criação do código. Lê um bloco do arquivo binário criado.
    Registro bloco_lido[fblocagem];
    FILE * arqBin;
    if(  arqBin = fopen(nomeArq,"rb")  ){
        int pos = 0;
        fseek(arqBin , pos*sizeof(Registro)*fblocagem, SEEK_CUR);  //Anda até um lugar no arquivo
        fread( (void *)&bloco_lido, sizeof(bloco_lido), 1, arqBin);  // LER UM BLOCO
        fclose(arqBin);
        int p = 0;
        for( unsigned int i = 0; i<sizeof(bloco_lido)/sizeof(Registro); i++ ){
            p+=1;
            cout<<"Numero: "<<p<<"          "<<"uhe: "<<bloco_lido[i].uhe<<"   cenario: "<<bloco_lido[i].cenario<<" Estagio: "<<bloco_lido[i].estagio<<"   geracao: "<<bloco_lido[i].geracao<<endl;
        }
    }else{
    cout<<"Deu ruim"<<endl;
    }
}

Registro procuraMetade(int posAnterior, int posAtual, int key, FILE * arq){  //Função utilizada recursivamente para fazer uma busca binária no arquivo sequencial.
    struct Registro registro_lido;
    cout<<posAnterior<< "  "<< posAtual<<endl;
    fseek(arq, posAtual*sizeof(registro_lido), SEEK_SET);  //Anda até um lugar no arquivo
    fread( (void *)&registro_lido, sizeof(registro_lido), 1, arq);

    if (key == registro_lido.uhe){
        cout<<"Achei:  "<< "uhe: "<<registro_lido.uhe<<"   cenario: "<<
       registro_lido.cenario<<" Estagio: "<<registro_lido.estagio<<"   geracao: "<<registro_lido.geracao<<endl;
        return registro_lido; //Para
    }else if (abs(posAtual-posAnterior) <= 1){
        cout<<"Parei!"<<endl;
        return registro_lido; //Para
    }else if (key < registro_lido.uhe){
        struct Registro r = procuraMetade( posAtual, posAtual - abs(posAnterior-posAtual)/2 , key, arq);
        return r;
    }else{
        struct Registro r = procuraMetade( posAtual, posAtual + abs(posAnterior-posAtual)/2 , key, arq);
        return r;
    }
}

vector <Registro> selectSequencial(int key){
    Registro r;
    vector <Registro> vectorR; //Vetor aonde ficam os registros encontrados.
    FILE * arqBin;
    arqBin = fopen("bancoSequencial.bin","rb");
    fseek(arqBin, 0, SEEK_END); // seek to end of file
    int t = ftell(arqBin)/sizeof(Registro); // get current file pointer
    fseek(arqBin, 0, SEEK_SET);
    int posAtual = t/2;   //Posição do meio do arquivo.
    int posAnterior = 0;
    struct Registro registro_lido;
    int x;
    while(true){
        cout<<posAnterior<< "  "<< posAtual<<endl;
        fseek(arqBin, posAtual*sizeof(registro_lido), SEEK_SET);  //Anda até um lugar no arquivo
        fread( (void *)&registro_lido, sizeof(registro_lido), 1, arqBin);
        if (key == registro_lido.uhe){
            break; //Neste momento ele encontrou um registro com aquela chave e posAtual guarda o local do próprio.
        }else if (abs(posAtual-posAnterior) < 1){
            return vectorR;
        }else if (key < registro_lido.uhe){
            x = posAnterior;
            posAnterior = posAtual;
            posAtual = posAtual - abs(x-posAtual)/2;
        }else{
            x = posAnterior;
            posAnterior = posAtual;
            posAtual = posAtual + abs(x-posAtual)/2;
        }
    }

    //Varremos o arquivo para cima e para baixo para checar se não existem outros registros com a mesma chave.
    int primeira_pos = posAtual;
    while(registro_lido.uhe == key){
        vectorR.push_back(registro_lido);
        posAtual+=1; //Varre para cima.
        fseek(arqBin, (posAtual)*sizeof(registro_lido), SEEK_SET);  //Anda até a próxima posição
        fread( (void *)&registro_lido, sizeof(registro_lido), 1, arqBin);
    }
    posAtual = primeira_pos - 1;
    fseek(arqBin, (posAtual)*sizeof(registro_lido), SEEK_SET);  //Anda até um lugar no arquivo
    fread( (void *)&registro_lido, sizeof(registro_lido), 1, arqBin);

    //Varre a vizinhança e checa se existe outro registro com essa chave:
    while(registro_lido.uhe == key){
        vectorR.push_back(registro_lido);
        posAtual-=1; //Varre para baixo.
        fseek(arqBin, (posAtual)*sizeof(registro_lido), SEEK_SET);  //Anda até a próxima posição
        fread( (void *)&registro_lido, sizeof(registro_lido), 1, arqBin);
   }
    fclose(arqBin);
    return vectorR;
}

void deleteSequencial(int key){ //
    FILE * arqBin; //Arquivo original a ser apagado
    FILE * arqBin2; //Arquivo novo a ser renomeado
    arqBin2 = fopen("bancoSequencialProvisorio.bin","wb");
    Registro bloco_lido[fblocagem];
    if(  arqBin = fopen("bancoSequencial.bin","rb")  ){
        while(!feof(arqBin)){
            fread( (void *)&bloco_lido, sizeof(bloco_lido), 1, arqBin);
            for( unsigned int i = 0; i<sizeof(bloco_lido)/sizeof(Registro); i++ ){ //Itera no bloco inteiro
                if(bloco_lido[i].uhe != key){ //Se a chave primaria for igual, NAO grava o registro no outro arquivo.
                    fwrite((void *)&bloco_lido[i], sizeof(bloco_lido[i]), 1, arqBin2);
                }
            }
        }
    fclose(arqBin);
    fclose(arqBin2);
    //Remove o banco antigo e faz com que o arquivo provisorio se torne o original:
    remove("bancoSequencial.bin");
    rename("bancoSequencialProvisorio.bin.bin","bancoSequencial.bin");
    }else{
    cout<<"Deu ruim"<<endl;
    }
}

void insertSequencial(Registro r){
    FILE * arqBin; //Arquivo original a ser apagado
    FILE * arqBin2; //Arquivo novo a ser renomeado
    arqBin = fopen("bancoSequencial.bin","rb");
    arqBin2 = fopen("bancoSequencialProvisorio.bin","wb");
    struct Registro registro_lido;
    bool inserido = false; //Nos diz se o registro ja foi inserido
    while(!feof(arqBin)){
        fread( (void *)&registro_lido, sizeof(registro_lido), 1, arqBin);
        if(registro_lido.uhe < r.uhe){ //Se o registro for menor ele coloca direto no arquivo, ou seja, ainda não chegou a hora do nosso registro ser inserido.
            fwrite( (void *)&registro_lido, sizeof(registro_lido), 1, arqBin2 );
        }else{ //Chegou a hora do registro ser inserido.
            if(!inserido){ //Se o registro ainda não foi inserido, nós o inserimos no  arquivo, caso contrário, ele continua colocando os outros.
                fwrite( (void *)&r, sizeof(r), 1, arqBin2 );
                inserido = true;
            }
            fwrite( (void *)&registro_lido, sizeof(registro_lido), 1, arqBin2 );
        }
    }
    cout<<"SAI!!"<<endl;
    fclose(arqBin2);
    fclose(arqBin);
    remove("bancoSequencial.bin");
    rename("bancoSequencialProvisorio.bin.bin","bancoSequencial.bin");
}


