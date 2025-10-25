#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class BankarskiAlgoritam
{
    std::vector<int> procesiID;
    std::vector<std::string> naziviProcesa;
    std::vector<std::string> resursi;
    std::vector<int> instanceResursa;
    std::vector<int> raspolozivo;
    std::vector<std::vector<int>> maksimalno;
    std::vector<std::vector<int>> alocirano;
    std::vector<std::vector<int>> potrebno;

    int nadjiProces(int) const;
    void dodajProces(int,const std::string&,const std::vector<int>&,const std::vector<int>&,const std::vector<int>&);
    bool sigurnoStanje(std::vector<bool>&,std::vector<int>&) const;
    std::vector<std::pair<std::string,std::vector<int>>> ucitavanjePodatakaIzFajla(const std::string);
    std::vector<std::pair<std::string,std::vector<int>>> ispisUcitanihPodataka(const std::string);
    bool zatraziResurs(int,const std::vector<int>&);

    public:
    void simulacija(const std::string&);
};