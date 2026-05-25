#include "utils.h"

#include <iostream>
#include <limits>
#include <cctype>
#include <stdexcept>

int RandomPazymys(std::mt19937& gen)
{
    try
    {
        static std::uniform_int_distribution<int> dist(1, 10);
        return dist(gen);
    }
    catch (...)
    {
        throw std::runtime_error("Klaida generuojant atsitiktini pazymi.");
    }
}

std::string RandomIsSaraso(const std::vector<std::string>& sar, std::mt19937& gen)
{
    if (sar.empty())
    {
        throw std::runtime_error("Klaida: tuscias sarasas atsitiktiniam parinkimui.");
    }

    try
    {
        std::uniform_int_distribution<int> dist(0, static_cast<int>(sar.size()) - 1);
        return sar[dist(gen)];
    }
    catch (...)
    {
        throw std::runtime_error("Klaida parenkant elementa is saraso.");
    }
}

std::string SkaitytiZodi(const std::string& zinute)
{
    std::string s;

    while (true)
    {
        try
        {
            std::cout << zinute;
            std::cin >> s;

            if (std::cin.fail())
            {
                throw std::runtime_error("Nepavyko nuskaityti zodzio.");
            }

            if (s.empty())
            {
                throw std::invalid_argument("Zodis negali buti tuscias.");
            }

            for (char c : s)
            {
                unsigned char uc = static_cast<unsigned char>(c);
                if (!std::isalpha(uc))
                {
                    throw std::invalid_argument("Galima ivesti tik raides.");
                }
            }

            return s;
        }
        catch (const std::exception& e)
        {
            std::cout << "Klaida: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

char SkaitytiChar(const std::string& zinute, const std::string& galimi)
{
    char c;

    while (true)
    {
        try
        {
            std::cout << zinute;
            std::cin >> c;

            if (std::cin.fail())
            {
                throw std::runtime_error("Nepavyko nuskaityti simbolio.");
            }

            if (galimi.find(c) == std::string::npos)
            {
                throw std::invalid_argument("Netinkamas pasirinkimas.");
            }

            return c;
        }
        catch (const std::exception& e)
        {
            std::cout << "Klaida: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int SkaitytiInt(const std::string& zinute)
{
    int x;

    while (true)
    {
        try
        {
            std::cout << zinute;
            std::cin >> x;

            if (std::cin.fail())
            {
                throw std::runtime_error("Reikia ivesti sveika skaiciu.");
            }

            return x;
        }
        catch (const std::exception& e)
        {
            std::cout << "Klaida: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

double SkaitytiDouble(const std::string& zinute)
{
    double x;

    while (true)
    {
        try
        {
            std::cout << zinute;
            std::cin >> x;

            if (std::cin.fail())
            {
                throw std::runtime_error("Reikia ivesti realuji skaiciu.");
            }

            return x;
        }
        catch (const std::exception& e)
        {
            std::cout << "Klaida: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int SkaitytiPazymi(const std::string& zinute, bool leistiNuli)
{
    while (true)
    {
        try
        {
            int x = SkaitytiInt(zinute);

            if (leistiNuli && x == 0)
            {
                return 0;
            }

            if (x < 1 || x > 10)
            {
                if (leistiNuli)
                {
                    throw std::invalid_argument("Galima ivesti 1-10 arba 0 baigimui.");
                }
                else
                {
                    throw std::invalid_argument("Galima ivesti tik skaiciu nuo 1 iki 10.");
                }
            }

            return x;
        }
        catch (const std::exception& e)
        {
            std::cout << "Klaida: " << e.what() << "\n";
        }
    }
}