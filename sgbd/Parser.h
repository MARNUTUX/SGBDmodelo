#include <iostream>  
#include<cstdlib>
#include<cstdio>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string>

class Parser
{
    public:       
        Parser();
        bool insertando(std::string); 
        bool borrando(std::string);
        bool actualizando(std::string);
        bool selecteando(std::string);    
        bool creando(std::string);    
        ~Parser();
        
    private:
        //regexes
        regex_t ins;
        regex_t del;
        regex_t upd;
        regex_t sel;  
        regex_t cre;
        //ayudas
        std::string tipoDato;  
        std::string name;
        std::string declaracion;   
        //patrones para regexes
        std::string patInsert; 
        std::string patDelete;
        std::string patCreate;
        std::string patSelect;
        std::string patUpdate;
};