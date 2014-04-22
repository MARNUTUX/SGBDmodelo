#include"Parser.h"       

Parser::Parser()
{  
    this->tipoDato = "(int|varchar\\([[:digit:]]+\\)|float|double|text|date)";   
    this->name = "[[:alpha:]][[:alnum:]]*"; 
    this->declaracion = name+" "+tipoDato;   
    this->patInsert = "insert into "+name+" values\\([[:alnum:]]+( , [[:alnum:]]+)*\\);"; 
    this->patDelete = "delete from "+name+"( where "+name+" = [[:alnum:]]+( and "+name+" = [[:alnum:]]+)*)*;";
    this->patCreate = "create table "+name+"\\("+declaracion+"( , "+declaracion+")*\\);";
    this->patSelect = "select (\\*|"+name+"(, "+name+")*) from "+name+";"; 
    this->patUpdate = "update "+name+" set "+name+" = [[:alnum:]]+(, "+name+" = [[:alnum:]]+)*( where "+name+" = [[:alnum:]]+( and "+name+" = [[:alnum:]]+)*)*;";
    regcomp(&ins, patInsert.c_str(),REG_EXTENDED);
    regcomp(&del, patDelete.c_str(),REG_EXTENDED);
    regcomp(&upd, patUpdate.c_str(),REG_EXTENDED);
    regcomp(&sel, patSelect.c_str(),REG_EXTENDED);
    regcomp(&cre, patCreate.c_str(),REG_EXTENDED);
}

bool Parser::insertando(std::string input)
{
    return (0 == regexec(&ins, input.c_str(), 0, NULL, 0));
}

bool Parser::borrando(std::string input)
{
    return (0 == regexec(&del, input.c_str(), 0, NULL, 0));
}

bool Parser::actualizando(std::string input)
{
    return (0 == regexec(&upd, input.c_str(), 0, NULL, 0));
}

bool Parser::selecteando(std::string input)
{
    return (0 == regexec(&sel, input.c_str(), 0, NULL, 0));
}

bool Parser::creando(std::string input)
{
    return (0 == regexec(&cre, input.c_str(), 0, NULL, 0));
}

Parser::~Parser()
{
    regfree(&ins);
    regfree(&del);
    regfree(&upd);
    regfree(&sel);
    regfree(&cre);
}