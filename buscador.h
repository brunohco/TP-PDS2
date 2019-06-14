#ifndef buscador_h
#define buscador_h
using namespace std;
#include <stdio.h>


//função responsáveis por inserir os arquivos ".txt"
vector<string> armazena_arquivo(int &cont_files);

//função responsável por separar as frases em palavras
vector<string> separa(string str, char separador);

//função que preenche o map idf  com um contador.
//Soma um para cada arquivo que a palavra existe, se não, nada acontece.
map <string, double> soma_palavras_arquivo(map<string, map <string, int > > inverted_index,vector<string> files);

//função responsável por criar o ranking oseno e imprimir seu resultado
map<string,float> ranking_co (map <string, float >cosine_ranking,float &numerator,float &denominator1,float &denominator2,vector<string> &query_tokens,map <string, float > &doc_coordenate_query,map <string, map<string, float>  > doc_coordenate,vector<string>files);


#endif
