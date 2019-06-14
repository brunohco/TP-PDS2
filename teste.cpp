#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN


#include "doctest.h"

#include "procurador.h"




#include <stdio.h>

#include <iostream>

#include <fstream>

#include <map>

#include <cctype>

#include <sstream>

#include <vector>

#include <math.h>

#include <locale>

#include <string>


TEST_SUITE("Procurador"){

    TEST_CASE("armazena_arquivo(int &cont_files"){

        

        vector<string> files = armazena_arquivo(cont_files);

        Check(files[0] = )

    }

    

    

    TEST_CASE("separa(string str, char separador)"){

        str = "testando se separa as palavras";

        CHECK(internal[0] == "testando");

        CHECK(internal[1] == "se");

        CHECK(internal[2] == "separa");

        CHECK(internal[3] == "as");

        CHECK(internal[4] == "palavras");

        str ="";

        CHECK(internal[0 == ]"");

    }

    

    TEST_CASE("soma_palavras_arquivo(map<string, map <string, int > > inverted_index,vector<string> files)"){

        

    }

    

    TEST_CASE("ranking_co (map <string, float >cosine_ranking,float &numerator,float &denominator1,float &denominator2,vector<string> &query_tokens,map <string, float > &doc_coordenate_query,map <string, map<string, float>  > doc_coordenate,vector<string>files)"){

        

        map<string,float> ranking_co (cosine_ranking,numerator,denominator1, denominator2,query_tokens,doc_coordenate_query, doc_coordenate,files);

        CHECK (it->first == "teste.txt");

        map<string,float> ranking_co (cosine_ranking,numerator,denominator1, denominator2,query_tokens,doc_coordenate_query, doc_coordenate,files);

        CHECK(it->first == "teste2.txt");

        map<string,float> ranking_co (cosine_ranking,numerator,denominator1, denominator2,query_tokens,doc_coordenate_query, doc_coordenate,files);


        

    }

    

    

    

}