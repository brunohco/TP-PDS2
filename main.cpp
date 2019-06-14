#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include <sstream>
#include <vector>
#include <math.h>
#include <locale>

#include "buscador.h"
using namespace std;

int main() {
    int cont_files=0;
    string ans, token;
    map<string, map <string, int > > inverted_index;
    vector<string> files = armazena_arquivo(cont_files);
    locale loc;
    cout << "CARREGANDO ARQUIVOS E SEU CONTEÚDO." << endl << endl << endl << endl;
    cout << "-----------------------------------------------------------" << endl << endl << endl << endl;
    
    //Lendo os arquivos e separando cada palavra uma por uma.
    //Adicionando as palavras no índice invertido e zerando o tf de cada uma.
    ifstream inFile;
    for (auto it=files.begin(); it!=files.end(); it++) {
        inFile.open(*it);
        while (getline(inFile, token)) {
            istringstream line(token);
            while (line >> token) {
                for(string::size_type cont_=0; cont_<token.length(); cont_++) {
                    token[cont_]=tolower(token[cont_], loc);
                    if (token[cont_]<'a' || token[cont_]>'z') {
                        token.erase(token.begin()+cont_);
                    }
                }
                inverted_index[token][*it]=0;
            }
        }
        inFile.close();
    }
    
    //Aqui esta sendo feita a contabilização de quantas vezes
    //cada palavra aparece em cada arquivo e também a padronização de cada palavra.
    for (auto it=files.begin(); it!=files.end(); it++) {
        inFile.open(*it);
        while (getline(inFile, token)) {
            istringstream line(token);
            while (line >> token) {
                for(string::size_type cont_=0; cont_<token.length(); cont_++) {
                    token[cont_]=tolower(token[cont_], loc);
                    if (token[cont_]<'a' || token[cont_]>'z') {
                        token.erase(token.begin()+cont_);
                    }
                }
                if(inverted_index.find(token)!=inverted_index.end()) {
                    inverted_index[token][*it]++;
                }
            }
        }
        inFile.close();
    }
    map <string, double> idf = soma_palavras_arquivo(inverted_index, files);
    
    //Aqui o map idf está sendo preenchido com um contador.
    //Soma um para cada arquivo que a palavra existe,
    //Aqui a conta do idf de cada palavra (Dado) está sendo feita.
    for (auto it=idf.begin(); it!=idf.end(); it++) {
        idf[it->first]=log(cont_files/(idf[it->first]));
    }
    
    //Criando um map de coordenadas para cada documento
    map <string, map<string, float>  > doc_coordenate;
    
    //Preenchedo o map de cada documento com as coordenadas.
    for (auto it=inverted_index.begin(); it!=inverted_index.end(); it++) {
        for (auto it2=files.begin(); it2!=files.end(); it2++) {
            doc_coordenate[*it2][it->first]=(inverted_index[it->first][*it2])*(idf[it->first]);
        }
    }
    
    //Criando um map de coordenadas para a consulta.
    map <string, float > doc_coordenate_query;
    
    //Criando um índice invertido para a consulta.
    map <string, int> inverted_index_query;
    
    //Aqui os tokens da consulta serão armazenados.
    vector <string> query_tokens;
    float numerator=0.0, denominator1=0.0, denominator2=0.0;
    
    //Map ranking coseno.
    map <string, float > cosine_ranking;
    string teste;
    cout<<"Digite a sua consulta (quais palavras você deseja achar nos documentos): ";
    cin.ignore();
    getline(cin,teste);
    query_tokens = separa(teste, ' ');
    cout << endl << endl << endl;
    
    //Zerando o índice invertido da consulta, mesmo procedimento do índice invertido dos docs.
    for (auto it=inverted_index.begin(); it!=inverted_index.end(); it++) {
        inverted_index_query[it->first]=0;
    }
    //...
    for (auto it=query_tokens.begin(); it!=query_tokens.end(); it++) {
        if (inverted_index_query.find(*it)!=inverted_index_query.end()) {
            inverted_index_query[*it]++;
        }
    }
    
    //Preenchendo as coordenadas da consulta.
    for (auto it=inverted_index_query.begin(); it!=inverted_index_query.end(); it++) {
        doc_coordenate_query[it->first]=idf[it->first]*inverted_index_query[it->first];
    }
    
    //chamando a função para o ranking coseno
    cosine_ranking = ranking_co(cosine_ranking, numerator, denominator1, denominator2, query_tokens,doc_coordenate_query,doc_coordenate,files);
    return 0;
}

