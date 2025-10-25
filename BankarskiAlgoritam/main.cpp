#include "BankarskiAlgoritam.cpp"

int main()
{
    BankarskiAlgoritam bankarskiAlgoritam;

    std::string ulazniFajl="podaci.txt";
    bankarskiAlgoritam.simulacija(ulazniFajl);

    return 0;
}