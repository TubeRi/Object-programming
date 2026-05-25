#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include <stdexcept>
#include <limits>
#include <filesystem>

#include "student.h"
#include "utils.h"
#include "io.h"
#include "gen.h"
#include "split.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    try
    {
        std::filesystem::create_directories("data");

        char pasirinkimas = SkaitytiChar(
            "Paleisti tyrimus (t) ar dirbti su studentais (r/a/f)? (t/r/a/f): ",
            "tTrRaAfF");

        if (pasirinkimas == 't' || pasirinkimas == 'T')
        {
            vector<std::pair<string, int>> failai = {
                {"data/sugeneruotas1000.txt",     1000},
                {"data/sugeneruotas10000.txt",    10000},
                {"data/sugeneruotas100000.txt",   100000},
                {"data/sugeneruotas1000000.txt",  1000000},
                {"data/sugeneruotas10000000.txt", 10000000}
            };

            // ===== TEST 1: File generation =====
            cout << "\n===== 1 TYRIMAS: Failu kurimas =====\n";
            cout << std::left  << std::setw(40) << "Failas"
                 << std::right << std::setw(15) << "Laikas (s)\n";
            cout << string(55, '-') << "\n";

            for (auto& [pav, kiek] : failai)
            {
                double t = Laikas([&]() { GeneruotiFaila(pav, kiek); });
                cout << std::left  << std::setw(40) << pav
                     << std::right << std::setw(15)
                     << std::fixed << std::setprecision(6) << t << " s\n";
            }

            // ===== TEST 2: Data processing =====
            cout << "\n===== 2 TYRIMAS: Duomenu apdorojimas =====\n";

            for (auto& [pav, kiek] : failai)
            {
                cout << "\n[ " << pav << " | " << kiek << " studentu ]\n";
                cout << string(55, '-') << "\n";

                vector<Student> grupe, vargsiukai, kietiakai;

                double t_skaitymas = Laikas([&]() {
                    FailoSkaitymas(pav, grupe);
                });
                cout << std::left  << std::setw(20) << "  Skaitymas:"
                     << std::right << std::setw(15)
                     << std::fixed << std::setprecision(6) << t_skaitymas << " s\n";

                double t_skirstymas = Laikas([&]() {
                    SkirstytiStudentus(grupe, vargsiukai, kietiakai);
                });
                cout << std::left  << std::setw(20) << "  Skirstymas:"
                     << std::right << std::setw(15) << t_skirstymas << " s\n";
                cout << "  Vargsiukai: " << vargsiukai.size() << "\n";
                cout << "  Kietiakai:  " << kietiakai.size() << "\n";

                string vPav = "data/vargsiukai_" + std::to_string(kiek) + ".txt";
                string kPav = "data/kietiakai_"  + std::to_string(kiek) + ".txt";

                double t_isvedimas = Laikas([&]() {
                    IsvestiIFaila(vPav, vargsiukai);
                    IsvestiIFaila(kPav, kietiakai);
                });
                cout << std::left  << std::setw(20) << "  Isvedimas:"
                     << std::right << std::setw(15) << t_isvedimas << " s\n";

                double t_total = t_skaitymas + t_skirstymas + t_isvedimas;
                cout << string(55, '-') << "\n";
                cout << std::left  << std::setw(20) << "  VISO:"
                     << std::right << std::setw(15) << t_total << " s\n";
            }
        }
        else
        {
            // ===== ORIGINAL INTERACTIVE CODE =====
            Student A;
            vector<Student> grupe;

            char rezimas = pasirinkimas; // reuse the char already read

            if (rezimas == 'f' || rezimas == 'F')
            {
                FailoSkaitymas("data/sugeneruotas1000.txt", grupe);
                vector<Student> vargsiukai;
                vector<Student> kietiakai;

                SkirstytiStudentus(grupe, vargsiukai, kietiakai);

                IsvestiIFaila("vargsiukai.txt", vargsiukai);
                IsvestiIFaila("kietiakai.txt", kietiakai);

                cout << "Studentai suskirstyti ir issaugoti.\n";
                cout << "Vargsiuku: " << vargsiukai.size() << '\n';
                cout << "Kietiaku: "  << kietiakai.size()  << '\n';
            }
            else
            {
                std::random_device rd;
                std::mt19937 gen(rd());

                vector<string> vardai = {
                    "Jonas", "Petras", "Mantas", "Lukas", "Tomas",
                    "Ieva", "Austeja", "Greta", "Egle", "Monika"};

                vector<string> pavardes = {
                    "Kazlauskas", "Jankauskas", "Petrauskas", "Stankevicius", "Vaitkus",
                    "Kazlauskaite", "Jankauskaite", "Petrauskaite", "Stankeviciute", "Vaitkute"};

                int kiek_studentu = 0;
                int sugeneruota   = 0;
                int nd_kiek       = 0;

                if (rezimas == 'a' || rezimas == 'A')
                {
                    kiek_studentu = SkaitytiInt("Kiek studentu generuoti? ");
                    nd_kiek       = SkaitytiInt("Kiek ND pazymiu generuoti kiekvienam studentui? ");
                }

                while (true)
                {
                    A.paz.clear();

                    if (rezimas == 'a' || rezimas == 'A')
                    {
                        if (sugeneruota >= kiek_studentu)
                            break;

                        A.vardas  = RandomIsSaraso(vardai,   gen);
                        A.pavarde = RandomIsSaraso(pavardes, gen);

                        cout << "\nGeneruojamas studentas: " << A.vardas << " " << A.pavarde << endl;
                    }
                    else
                    {
                        cout << "\nIveskite pavarde (0 - baigti studentu ivedima): ";
                        std::cin >> A.pavarde;

                        if (std::cin.fail())
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cout << "Klaida: neteisinga ivestis.\n";
                            continue;
                        }

                        if (A.pavarde == "0")
                            break;

                        A.vardas = SkaitytiZodi("Iveskite varda: ");
                    }

                    if (rezimas == 'a' || rezimas == 'A')
                    {
                        for (int i = 0; i < nd_kiek; i++)
                            A.paz.push_back(RandomPazymys(gen));

                        A.egz = RandomPazymys(gen);

                        cout << "Sugeneruoti ND: ";
                        for (int x : A.paz) cout << x << " ";
                        cout << "\nSugeneruotas egz: " << A.egz << endl;

                        sugeneruota++;
                    }
                    else
                    {
                        cout << "Iveskite ND pazymius (1 iki 10, 0 - baigti ND ivedima):\n";
                        while (true)
                        {
                            int temp = SkaitytiPazymi("ND: ", true);
                            if (temp == 0) break;
                            A.paz.push_back(temp);
                        }

                        A.egz = SkaitytiPazymi("Iveskite egzamino pazymi nuo 1 iki 10: ");
                    }

                    SkaiciuotiGalutinius(A);
                    grupe.push_back(A);
                }
            }

            char rikiavimas = SkaitytiChar(
                "\nRikiuoti pagal: vardas(1), pavarde(2), galutinis vidurkis(3), galutinis mediana(4): ",
                "1234");

            char kur = SkaitytiChar("Isvedimas i ekrana ar i faila? (e/f): ", "eEfF");

            if (kur == 'f' || kur == 'F')
            {
                std::ofstream fout("rezultatai.txt");
                if (!fout.is_open())
                    throw std::runtime_error("Klaida: nepavyko sukurti failo rezultatai.txt");

                double t = Laikas([&]() { Spausdinimas(grupe, rikiavimas, fout); });
                cout << "Rezultatai issaugoti faile: rezultatai.txt\n";
                cout << "Spausdinimas (i faila) uztruko: "
                     << std::fixed << std::setprecision(6) << t << " s\n";
            }
            else
            {
                double t = Laikas([&]() { Spausdinimas(grupe, rikiavimas, std::cout); });
                cout << "Spausdinimas (i ekrana) uztruko: "
                     << std::fixed << std::setprecision(6) << t << " s\n";
            }
        }
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}