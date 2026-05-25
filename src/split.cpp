#include "split.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>

void SkirstytiStudentus(const std::vector<Student>& visi,
                        std::vector<Student>& vargsiukai,
                        std::vector<Student>& kietiakai)
{
    vargsiukai.clear();
    kietiakai.clear();

    for (const auto& s : visi)
    {
        if (s.rez_vid < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakai.push_back(s);
    }
}
