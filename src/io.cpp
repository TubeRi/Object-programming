#include "io.h"
#include "student.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::string;
using std::vector;

void Spausdinimas(vector<Student> grupe, char rikiavimas, std::ostream& out)
{
    auto byPavardeVardas = [](const Student& a, const Student& b) {
        if (a.pavarde != b.pavarde) return a.pavarde < b.pavarde;
        return a.vardas < b.vardas;
    };

    switch (rikiavimas)
    {
        case '1':
            std::sort(grupe.begin(), grupe.end(), [](const Student& a, const Student& b) {
                if (a.vardas != b.vardas) return a.vardas < b.vardas;
                return a.pavarde < b.pavarde;
            });
            break;

        case '2':
            std::sort(grupe.begin(), grupe.end(), byPavardeVardas);
            break;

        case '3':
            std::sort(grupe.begin(), grupe.end(), [&](const Student& a, const Student& b) {
                if (a.rez_vid != b.rez_vid) return a.rez_vid < b.rez_vid;
                return byPavardeVardas(a, b);
            });
            break;

        case '4':
            std::sort(grupe.begin(), grupe.end(), [&](const Student& a, const Student& b) {
                if (a.rez_med != b.rez_med) return a.rez_med < b.rez_med;
                return byPavardeVardas(a, b);
            });
            break;

        default:
            std::sort(grupe.begin(), grupe.end(), byPavardeVardas);
            break;
    }

    out << left  << setw(18) << "Pavarde"
        << left  << setw(18) << "Vardas"
        << right << setw(20) << "Galutinis (Vid.)"
        << right << setw(20) << "Galutinis (Med.)"
        << endl;

    out << string(76, '-') << endl;
    out << std::fixed << std::setprecision(2);

    for (const auto& A : grupe)
    {
        out << left  << setw(18) << A.pavarde
            << left  << setw(18) << A.vardas
            << right << setw(20) << A.rez_vid
            << right << setw(20) << A.rez_med
            << endl;
    }
}

void FailoSkaitymas(const std::string& failoVardas, std::vector<Student>& grupe)
{
    std::ifstream fin(failoVardas);

    if (!fin)
    {
        throw std::runtime_error("Klaida: failas neegzistuoja arba nepavyko jo atidaryti.");
    }

    string headerLine;
    std::getline(fin, headerLine);

    std::istringstream hs(headerLine);
    string tok;
    int nd_kiek = 0;

    while (hs >> tok)
    {
        if (tok.rfind("ND", 0) == 0) nd_kiek++;
    }

    Student A;
    while (fin >> A.vardas >> A.pavarde)
    {
        A.paz.clear();

        for (int i = 0; i < nd_kiek; i++)
        {
            int nd;
            fin >> nd;
            A.paz.push_back(nd);
        }

        fin >> A.egz;

        SkaiciuotiGalutinius(A);
        grupe.push_back(A);
    }
}
void IsvestiIFaila(const std::string& pav, const std::vector<Student>& studentai)
{
    std::ofstream out(pav);

    if (!out.is_open())
    {
        throw std::runtime_error("Nepavyko sukurti failo: " + pav);
    }

    out << std::left
        << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::setw(15) << "Galutinis (Vid.)"
        << "Galutinis (Med.)\n";

    out << std::string(70, '-') << '\n';

    for (const auto& studentas : studentai)
    {
        out << std::left
            << std::setw(20) << studentas.vardas
            << std::setw(20) << studentas.pavarde
            << std::fixed << std::setprecision(2)
            << std::setw(15) << studentas.rez_vid
            << studentas.rez_med << '\n';
    }

    out.close();
}