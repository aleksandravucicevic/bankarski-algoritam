#include "BankarskiAlgoritam.h"

void BankarskiAlgoritam::dodajProces(int id, const std::string& naziv, const std::vector<int>& maks, const std::vector<int>& alocirano, const std::vector<int>& potrebno)
{
    procesiID.push_back(id);
    naziviProcesa.push_back(naziv);
    maksimalno.push_back(maks);
    this->alocirano.push_back(alocirano);
    this->potrebno.push_back(potrebno);
}

int BankarskiAlgoritam::nadjiProces(int id) const
{
    for(int i=0;i<procesiID.size();i++)
    {
        if(procesiID[i]==id)
        {
            return i;
        }
    }
    return -1;
}

bool BankarskiAlgoritam::sigurnoStanje(std::vector<bool>& zavrseno, std::vector<int>& sekvenca) const
{
    int brojProcesa=maksimalno.size();
    int brojResursa=raspolozivo.size();

    std::vector<int> rad=raspolozivo;
    
    sekvenca.clear();
    zavrseno.assign(brojProcesa, false);

    while(true)
    {
        bool pronadjenProces=false;

        for(int i=0;i<brojProcesa;i++)
        {
            if(!zavrseno[i])
            {
                bool mozeZavrsiti=true;
                
                // provjera da li proces moze da se zavrsi sa trenutnim raspolozivim resursima
                for(int j=0;j<brojResursa;j++)
                {
                    if(potrebno[i][j]>rad[j])
                    {
                        mozeZavrsiti=false;
                        break;
                    }
                }
                
                if(mozeZavrsiti)
                {
                    // oslobadjanje resursa
                    for(int j=0;j<brojResursa;j++)
                    {
                        rad[j]+=alocirano[i][j];
                    }

                    zavrseno[i]=true;
                    sekvenca.push_back(i);
                    pronadjenProces=true;
                }
            }
        }

        // prekidamo petlju ako nema procesa koji mogu da se izvrse
        if (!pronadjenProces)
            break;
    }

    // provjera da li su svi procesi zavrseni
    for(int i=0;i<brojProcesa;i++)
    {
        if(!zavrseno[i])
            return false;
    }

    return true;
}

std::vector<std::pair<std::string,std::vector<int>>> BankarskiAlgoritam::ucitavanjePodatakaIzFajla(const std::string naziv)
{
    std::ifstream fajl(naziv);

    int brProcesa;
    std::string brProcesaStr;
    fajl>>brProcesaStr;
    brProcesa=std::stoi(brProcesaStr);
    this->naziviProcesa.resize(brProcesa);
    for(int i=0;i<brProcesa;i++)
    {
        fajl>>naziviProcesa[i];
    }

    this->procesiID.resize(brProcesa);
    for(int i=0;i<brProcesa;i++)
    {
        procesiID[i]=i;
    }

    int brResursa;
    std::string brResursaStr;
    fajl>>brResursaStr;
    brResursa=std::stoi(brResursaStr);
    this->resursi.resize(brResursa);
    for(int i=0;i<brResursa;i++)
    {
        fajl>>resursi[i];
    }

    std::string pom;
    this->instanceResursa.resize(brResursa);
    for(int i=0;i<brResursa;i++)
    {
        fajl>>pom;
        instanceResursa[i]=std::stoi(pom);
    }

    this->raspolozivo.resize(brResursa);
    for(int i=0;i<brResursa;i++)
    {
        fajl>>pom;
        raspolozivo[i]=std::stoi(pom);
    }
    this->alocirano.resize(brProcesa, std::vector<int>(brResursa));
    for(int i=0;i<brProcesa;i++)
        for(int j=0;j<brResursa;j++)
        {
            fajl>>pom;
            alocirano[i][j]=std::stoi(pom);
        }
    this->maksimalno.resize(brProcesa, std::vector<int>(brResursa));
    for(int i=0;i<brProcesa;i++)
        for(int j=0;j<brResursa;j++)
        {
            fajl>>pom;
            maksimalno[i][j]=std::stoi(pom);
        }
    
    // racunanje potreba procesa za svakim od resursa
    this->potrebno.resize(brProcesa,std::vector<int>(brResursa));
    for(int i=0;i<brProcesa;i++)
        for(int j=0;j<brResursa;j++)
        {
            potrebno[i][j]=maksimalno[i][j]-alocirano[i][j];
        }

    std::vector<std::pair<std::string,std::vector<int>>> zahtjevi;
    std::string zahtjeviStr;
    std::vector<std::string> elementi;
    std::string element;
    while(getline(fajl,zahtjeviStr))
    {
        std::stringstream ss(zahtjeviStr);
        while(ss>>element)
            elementi.push_back(element);

        if(elementi.size()>1)
        {
            std::string nazivProcesa=elementi[0];
            int procesID=std::stoi(nazivProcesa.substr(1));

            std::vector<int> zahtjev;
            for(int i=1;i<elementi.size();i++)
            {
                zahtjev.push_back(std::stoi(elementi[i]));
            }

            if(!nazivProcesa.empty() && !zahtjev.empty())
            {
                zahtjevi.push_back({nazivProcesa,zahtjev});
            }

            elementi.clear();
        }
    }
    fajl.close();
    return zahtjevi;
}

std::vector<std::pair<std::string,std::vector<int>>> BankarskiAlgoritam::ispisUcitanihPodataka(const std::string naziv)
{
    std::vector<std::pair<std::string,std::vector<int>>> zahtjevi=this->ucitavanjePodatakaIzFajla(naziv);
    
    std::cout<<"Broj procesa: "<<procesiID.size()<<std::endl;
    std::cout<<"Nazivi procesa: ";
    for(const auto& proces: naziviProcesa)
    {
        std::cout<<proces<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"Broj resursa: "<<raspolozivo.size()<<std::endl;
    std::cout<<"Nazivi resursa: ";
    for(const auto& naziv: resursi)
    {
        std::cout<<naziv<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"Broj instanci po resursu: ";
    for(const auto& inst: instanceResursa)
    {
        std::cout<<inst<<" ";
    }
    std::cout<<std::endl;
    
    std::cout<<"Vektor raspolozivosti: ";
    for(const auto& pom: raspolozivo)
    {
        std::cout<<pom<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"Matrica alokacija: "<<std::endl;
    for(const auto& red: alocirano)
    {
        for(const auto& elem: red)
            std::cout<<elem<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    std::cout<<"Matrica maksimalnih zahtjeva: "<<std::endl;
    for(const auto& red: maksimalno)
    {
        for(const auto& elem: red)
            std::cout<<elem<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    std::cout<<"Lista zahtjeva: "<<std::endl;
    for(const auto& zahtjev: zahtjevi)
    {
        std::cout<<zahtjev.first<<" ";
        for(const auto& elem: zahtjev.second)
            std::cout<<elem<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    return zahtjevi;
}

bool BankarskiAlgoritam::zatraziResurs(int id, const std::vector<int>& zahtjev)
{
    int index=nadjiProces(id);
    if(index==-1)
    {
        std::cout<<"Proces P"<<id<<" nije pronadjen."<<std::endl;
        return false;
    }

    // kreiranje stringa za ispis zahtjeva
    std::ostringstream zahtjevStr;
    zahtjevStr<<"Zahtjev (P"<<id;
    for(const auto& z: zahtjev)
        zahtjevStr<<", "<<z;
    zahtjevStr<<")";

    // provjera da li zahtjev prelazi maksimalne potrebe procesa
    for(int i=0;i<zahtjev.size();i++)
    {
        if(zahtjev[i]>potrebno[index][i])
        {
            std::cout<<zahtjevStr.str()<<" nece biti odobren." << std::endl;
            return false;
        }
    }

    // provjera da li zahtjev prelazi raspolozive resurse
    for(int i=0;i<zahtjev.size();i++)
    {
        if(zahtjev[i]>raspolozivo[i])
        {
            std::cout<<zahtjevStr.str()<<" nece biti odobren."<<std::endl;
            return false;
        }
    }

    // privremeno dodjeljivanje resursa procesu
    for(int i=0;i<zahtjev.size();i++)
    {
        raspolozivo[i]-=zahtjev[i];
        alocirano[index][i]+=zahtjev[i];
        potrebno[index][i]-=zahtjev[i];
    }

    // provjera da li je sistem u sigurnom stanju nakon privremene dodjele resursa
    std::vector<bool> zavrseno(maksimalno.size(),false);
    std::vector<int> sekvenca;
    if(!sigurnoStanje(zavrseno,sekvenca))
    {
        // vracanje resursa ako sistem nije u sigurnom stanju
        for(int i=0;i<zahtjev.size();i++)
        {
            raspolozivo[i]+=zahtjev[i];
            alocirano[index][i]-=zahtjev[i];
            potrebno[index][i]+=zahtjev[i];
        }
        std::cout<<zahtjevStr.str()<<" nece biti odobren."<<std::endl;
        return false;
    }

    std::cout<<zahtjevStr.str()<<" ce biti odobren."<<std::endl;
    return true;
}

void BankarskiAlgoritam::simulacija(const std::string& naziv)
{
    std::vector<std::pair<std::string, std::vector<int>>> zahtjevi=this->ispisUcitanihPodataka(naziv);
    
    std::cout<<"--- Rezultati simulacije ---\n";
    std::cout<<"Matrica potreba:\n";
    for(const auto& red: potrebno)
    {
        for(const auto& elem: red)
        {
            std::cout<<elem<<" ";
        }
        std::cout<<std::endl;
    }
    
    // provjera da li je sistem u stabilnom stanju
    std::vector<bool> zavrseno(maksimalno.size(), false);
    std::vector<int> sekvenca;
    if(sigurnoStanje(zavrseno, sekvenca))
    {
        std::cout<<"Sistem je u stabilnom stanju (";
        for(size_t i = 0; i < sekvenca.size(); ++i)
        {
            std::cout<<"P"<<sekvenca[i];
            if(i!=sekvenca.size()-1)
            {
                std::cout<<"->";
            }
        }
        std::cout<<").\n";
    }
    else
    {
        std::cout<<"Sistem nije u stabilnom stanju.\n";
    }

    // cuvanje pocetnog stanja sistema
    std::vector<int> pocetnoRaspolozivo=raspolozivo;
    std::vector<std::vector<int>> pocetnoAlocirano=alocirano;
    std::vector<std::vector<int>> pocetnoPotrebno=potrebno;

    for(const auto& zahtjev: zahtjevi)
    {
        // vracanje na pocetno stanje
        raspolozivo=pocetnoRaspolozivo;
        alocirano=pocetnoAlocirano;
        potrebno=pocetnoPotrebno;

        // izdvajanje ID procesa iz naziva procesa
        char IDStr=zahtjev.first[1];
        int id=IDStr-'0';

        // pokusaj obrade zahtjeva
        this->zatraziResurs(id,zahtjev.second);
    }
}