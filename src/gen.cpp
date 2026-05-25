#include "gen.h"
#include <fstream>
#include <random>
#include <iomanip>
#include <stdexcept>
#include <filesystem>



void GeneruotiFaila(const std::string& pav, int studentuKiekis)
{
    std::filesystem::path p(pav);
    if (p.has_parent_path())
        std::filesystem::create_directories(p.parent_path());

    std::ofstream out(pav);

    if (!out)
        throw std::runtime_error("Nepavyko sukurti failo");

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 10);

    const int ndKiekis = 15;

    // ---------------- HEADER ----------------
    out << std::left
        << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde";

    for (int i = 1; i <= ndKiekis; i++)
    {
        out << std::right
            << std::setw(6)
            << ("ND" + std::to_string(i));
    }

    out << std::setw(6) << "Egz." << '\n';

    for (int i = 1; i <= studentuKiekis; i++)
    {
        out << std::left
            << std::setw(20)
            << ("Vardas" + std::to_string(i))

            << std::setw(20)
            << ("Pavarde" + std::to_string(i));

        // ND pažymiai
        for (int j = 0; j < ndKiekis; j++)
        {
            out << std::right
                << std::setw(6)
                << dist(gen);
        }

        // Egzaminas
        out << std::right
            << std::setw(6)
            << dist(gen)
            << '\n';
    }

    out.close();
}