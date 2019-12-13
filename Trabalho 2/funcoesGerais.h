/*
                PROJETO 2 TMAB
    Andre Osorio Magaldi Netto                118041914
    Joao Paulo Alves Loureiro Da Silva        117196504
    Rodrigo Bagdadi Benoliel                  118031529

*/


#pragma once  // Para não conflitar quando chamamos os arquivos no main.cpp

#include <iostream>
#include <sstream>
#include <vector>
#include<stdlib.h>
#include <typeinfo>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

unsigned const int fblocagem = 102;  //Fator de blocagem

struct Registro{   //Registro do banco
    unsigned int        uhe;
    unsigned int    cenario;
    string         estagio;
    double          geracao;
};


bool comparaDoisRegistros(Registro r1, Registro r2){  //Função utilizada para ordenar os registros do banco Sequencial.
        return r1.uhe < r2.uhe;
}

vector<string> split(string str,char c){   //Parser da string. Faz o split da string em um caracter específico.
    vector<string> vetor;
    string temp;
    istringstream ss(str);
    while (std::getline(ss, temp, c)) {
        vetor.push_back( temp);}
    return vetor;
}


