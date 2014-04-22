#include"Parser.h"       

Parser::Parser()
{  
    this->tipoDato = "(int|varchar\\([[:digit:]]+\\)|float|double|text|date)";   
    this->name = "[[:alpha:]][[:alnum:]]*"; 
    this->declaracion = name+" "+tipoDato;   
    this->patInsert = "insert into "+name+" values\\( [[:alnum:]]+(,[[:alnum:]]+)* \\);"; 
    this->patDelete = "delete from "+name+"( where "+name+" = [[:alnum:]]+( and "+name+" = [[:alnum:]]+)*)*;";
    this->patCreate = "create table "+name+"\\( "+declaracion+"( , "+declaracion+")* \\);";
    this->patSelect = "select (\\*|"+name+"(, "+name+")*) from "+name+";"; 
    this->patUpdate = "update "+name+" set "+name+" = [[:alnum:]]+( ,"+name+" = [[:alnum:]]+)*( where "+name+" = [[:alnum:]]+( and "+name+" = [[:alnum:]]+)*)*;";
}

bool Parser::insertando(std::string input)
{
    int rc;
    printf("%s\n%s\n", patInsert.c_str(),input.c_str());
    if(0 == (rc = regcomp(&ins, patInsert.c_str(),REG_EXTENDED)))
    {
        printf("%s\n", "okok");
        return (0 == regexec(&ins, input.c_str(), 0, NULL, 0));
    }
    else 
    {
        printf("%s\n", "false");
        return false;
    }
}

bool Parser::borrando(std::string input)
{
    int rc;
    if(0 == (rc = regcomp(&del, patDelete.c_str(),REG_EXTENDED)))
        return (0 == regexec(&del, input.c_str(), 0, NULL, 0)); 
    else return false;
}

bool Parser::actualizando(std::string input)
{
    int rc; 
    if(0 == (rc = regcomp(&upd, patUpdate.c_str(),REG_EXTENDED)))
        return (0 == regexec(&upd, input.c_str(), 0, NULL, 0));
    else return false; 
}

bool Parser::selecteando(std::string input)
{
    int rc; 
    if(0 == (rc = regcomp(&sel, patSelect.c_str(),REG_EXTENDED)))
        return (0 == regexec(&sel, input.c_str(), 0, NULL, 0));
    else return false;
}

bool Parser::creando(std::string input)
{
    int rc;
    if(0 == (rc = regcomp(&cre, patCreate.c_str(),REG_EXTENDED)))
        return (0 == regexec(&cre, input.c_str(), 0, NULL, 0));
    else return false;
}

Parser::~Parser()
{
    regfree(&ins);
    regfree(&del);
    regfree(&upd);
    regfree(&sel);
    regfree(&cre);
}