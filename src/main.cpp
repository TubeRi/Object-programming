#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include <stdexcept>
#include <limits>

#include "student.h"
#include "utils.h"
#include "io.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    try
    {
        Student A;
        vector<Student> grupe;

        char rezimas = SkaitytiChar("Ivedimas ranka, atsitiktinis ar is failo? (r/a/f): ", "rRaAfF");

        if (rezimas == 'f' || rezimas == 'F')
        {
            FailoSkaitymas("data/studentai10000.txt", grupe);
        }
        else
        {
            std::random_device rd;
            std::mt19937 gen(rd());

            vector<string> vardai = {
                "Jonas", "Petras", "Mantas", "Lukas", "Tomas",
                "Ieva", "Austeja", "Greta", "Egle", "Monika"
            };

            vector<string> pavardes = {
                "Kazlauskas", "Jankauskas", "Petrauskas", "Stankevicius", "Vaitkus",
                "Kazlauskaite", "Jankauskaite", "Petrauskaite", "Stankeviciute", "Vaitkute"
            };

            int kiek_studentu = 0;
            int sugeneruota = 0;
            int nd_kiek = 0;

            if (rezimas == 'a' || rezimas == 'A')
            {
                kiek_studentu = SkaitytiInt("Kiek studentu generuoti? ");
                nd_kiek = SkaitytiInt("Kiek ND pazymiu generuoti kiekvienam studentui? ");
            }

            while (true)
            {
                A.paz.clear();

                if (rezimas == 'a' || rezimas == 'A')
                {
                    if (sugeneruota >= kiek_studentu) break;

                    A.vardas = RandomIsSaraso(vardai, gen);
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

                    if (A.pavarde == "0") break;

                    A.vardas = SkaitytiZodi("Iveskite varda: ");
                }

                if (rezimas == 'a' || rezimas == 'A')
                {
                    for (int i = 0; i < nd_kiek; i++)
                    {
                        A.paz.push_back(RandomPazymys(gen));
                    }

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
            "1234"
        );

        char kur = SkaitytiChar("Isvedimas i ekrana ar i faila? (e/f): ", "eEfF");

        if (kur == 'f' || kur == 'F')
        {
            std::ofstream fout("rezultatai.txt");
            if (!fout.is_open())
            {
                throw std::runtime_error("Klaida: nepavyko sukurti failo rezultatai.txt");
            }

            double t = Laikas([&]() {
                Spausdinimas(grupe, rikiavimas, fout);
            });

            cout << "Rezultatai issaugoti faile: rezultatai.txt\n";
            cout << "Spausdinimas (i faila) uztruko: "
                 << std::fixed << std::setprecision(6) << t << " s\n";
        }
        else
        {
            double t = Laikas([&]() {
                Spausdinimas(grupe, rikiavimas, std::cout);
            });

            cout << "Spausdinimas (i ekrana) uztruko: "
                 << std::fixed << std::setprecision(6) << t << " s\n";
        }
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}