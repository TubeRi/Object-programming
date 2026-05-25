#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

struct Student
{
    std::string vardas = "A";
    std::string pavarde = "BB";
    std::vector<int> paz;
    int egz = 0;
    double rez_vid = 0.0;
    double rez_med = 0.0;
};

double Mediana( std::vector<int> paz);
double Vidurkis(const std::vector<int>& paz);
void SkaiciuotiGalutinius(Student& A);

#endif