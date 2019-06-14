#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include <sstream>
#include <vector>
#include <math.h>
#include <locale>
#include <string>
#include "buscador.h"

using namespace std;




vector<string> armazena_arquivo(int &cont_files){
    int verif = 1;
    string ans;
    vector<string> files;
    while(verif == 1){
        cout<< "Digite o nome do arquivo com a extensão txt: ";
        cin>> ans;
        files.push_back(ans);
        cont_files++;
        cout<< endl;
        cout << "Arquivo adicionado com sucesso. Deseja continuar? (1)-Sim (2)-Não: ";
        cin>>verif;
    }
    return files;
}


vector<string> separa(string str, char separador){
    vector<string> internal;
    stringstream ss(str);
    string tok;
    while (getline(ss,tok,separador)) {
        internal.push_back(tok);
    }
    return internal;
}


map <string, double> soma_palavras_arquivo(map<string, map <string, int > > inverted_index,vector<string> files ){
    map <string, double> idf;
    ifstream inFile;
    for (auto it=inverted_index.begin(); it!=inverted_index.end(); it++) {
        for (auto it2=files.begin(); it2!=files.end(); it2++) {
            inFile.open(*it2);
            if (inverted_index[it->first][*it2]!=0) {
                idf[it->first]++;
            }
            inFile.close();
        }
    }
    return idf;
}





map<string,float> ranking_co (map <string, float >cosine_ranking,float &numerator,float &denominator1,float &denominator2,vector<string> &query_tokens,map <string, float > &doc_coordenate_query,map <string, map<string, float>  > doc_coordenate,vector<string>files){
    for (auto it=files.begin(); it!=files.end(); it++) {
        for (auto it2=query_tokens.begin(); it2!=query_tokens.end(); it2++) {
            numerator=(doc_coordenate[*it][*it2]*doc_coordenate_query[*it2]);
            denominator1+=pow(doc_coordenate[*it][*it2], 2);
            denominator2+=pow(doc_coordenate_query[*it2], 2);
        }
        if((denominator1==0) || (denominator2==0)) {
            cosine_ranking[*it]=0;
        }
        else {
            cosine_ranking[*it]=numerator/(sqrt(denominator1)*sqrt(denominator2));
        }
        numerator=0.0;
        denominator1=0.0;
        denominator2=0.0;
    }
    cout << "De acordo com sua consulta e com os documentos fornecidos, o ranking coseno ficou assim: "<<endl;
    for (auto it=cosine_ranking.begin(); it!=cosine_ranking.end(); it++) {
        cout << it->first << "-> " << it->second << endl;
    }
    return cosine_ranking;
}
