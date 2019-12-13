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

void carregaBancoHeap(){

    FILE * arq;
    arq = fopen("bancoHeap.bin","wb");
    ifstream arq_csv;
    arq_csv.open("ghtestes.csv");
    string linha;
    getline(arq_csv,linha);
    while(!arq_csv.eof()){  // Enquanto não chegar ao final do arquivo, cri blocos com tamanho "fblocagem" e os enche com registros.

        Registro bloco_escrito1[fblocagem];

        for(int i=0; i<fblocagem;i++){
                getline(arq_csv,linha);
                vector<string> vregistro = split(linha,',');
                Registro novoRegistro;
                novoRegistro.uhe = stoi(vregistro[0],nullptr,10);
                novoRegistro.cenario = stoi(vregistro[1],nullptr,10);
                novoRegistro.estagio = vregistro[2];
                novoRegistro.geracao = stof(vregistro[3],nullptr);
                memcpy(&bloco_escrito1[i],&novoRegistro,sizeof(novoRegistro)); //Copia para o bloco.
                }
        fwrite((void *)&bloco_escrito1,sizeof(bloco_escrito1),1,arq); //Grava o bloco
        }
    fclose(arq);
    arq_csv.close();

}

vector<Registro> selectHeap(int key){
    vector<Registro> vetorR;
    Registro bloco_lido[fblocagem];
    FILE * arqBin;
    if(  arqBin = fopen("bancoHeap.bin","rb")  ){
        int pos = 0;
        while(!feof(arqBin)){    //Enquanto não chegar ao final do arquivo, checa se o registro bate com a chave indicada.
            fseek(arqBin , pos*sizeof(Registro)*fblocagem, SEEK_SET);  //Anda até um lugar no arquivo
            fread( (void *)&bloco_lido, sizeof(bloco_lido), 1, arqBin);
            pos+=1;
            for( unsigned int i = 0; i<sizeof(bloco_lido)/sizeof(Registro); i++ ){

                if(bloco_lido[i].uhe == key){
                    vetorR.push_back(bloco_lido[i]); //Se for igual, guarda no vetor para ser retornado.
                }
            }
        }
    fclose(arqBin);
    return vetorR;

    }else{
    cout<<"Deu ruim"<<endl;
    }

}

void insertHeap(int uhe, int cenario, string estagio, int geracao ){
    Registro registro_novo = Registro{uhe, cenario, estagio, geracao};
    FILE * arqBin;
    arqBin = fopen("bancoHeap.bin","wb");
    fwrite((void *)&registro_novo, sizeof(registro_novo), 1, arqBin);
    fclose(arqBin);
    cout<<"Registro inserido com sucesso!"<<endl;
}


void deleteHeap(int key ){
    FILE * arqBin;   //Arquivo a ser apagado no final.
    FILE * arqBin2; //Arquivo a ser criado e renomeado.
    arqBin2 = fopen("bancoHeapProvisorio.bin","wb");
    Registro bloco_lido[fblocagem];
    if(  arqBin = fopen("bancoHeap.bin","rb")  ){
        while(!feof(arqBin)){
            fread( (void *)&bloco_lido, sizeof(bloco_lido), 1, arqBin);
            for( unsigned int i = 0; i<sizeof(bloco_lido)/sizeof(Registro); i++ ){  //Itera no bloco lido
                if(bloco_lido[i].uhe != key){ //Se a chave primaria do registro for igual, NAO inlcui ele no outro arquivo.
                    fwrite((void *)&bloco_lido[i], sizeof(bloco_lido[i]), 1, arqBin2);
                }
            }
        }
    fclose(arqBin);
    fclose(arqBin2);
    //Remove o banco antigo e faz com que o arquivo provisorio se torne o original:
    remove("bancoHeap.bin");
    rename("bancoHeapProvisorio.bin","bancoHeap.bin");
    }else{
    cout<<"Deu ruim"<<endl;
    }
}
