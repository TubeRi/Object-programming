#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::vector;
using std::left;
using std::right;
using std::cin;


struct Student
{
    std::string vardas = "A";
    std::string pavarde = "BB";
    //int paz, egz;  
    std::vector<int> paz; 
    int egz=0;
    double rez=0.0;
};
double Mediana(vector<int> paz)
{
    if (paz.empty()) return 0.0;

    std::sort(paz.begin(), paz.end());
    int n = (int)paz.size();

    if (n % 2 == 0)
        return (paz[n/2 - 1] + paz[n/2]) / 2.0;
    else
        return paz[n/2];
}

void Spausdinimas(const vector<Student> &grupe, char pasirinkimas);

int main()
{
    Student A;
    vector<Student> grupe;

    char pasirinkimas;
    cout << "Skaiciuoti galutini pagal vidurki ar mediana? (v/m): ";
    cin >> pasirinkimas;

    for(int ii=0; ii<2; ii++)
    { 
    
    cout<<"Iveskite varda ir pavarde: ";
    cin>>A.vardas>>A.pavarde;
    //std::cout << A.vardas << " " << A.pavarde << std::endl;
    cout<<"Iveskite semestro pazymius:\nKiek pazymiu bus?";
   int n, temp, sum = 0;
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cout << "Iveskite " << i + 1 << " pazymi: ";
            cin >> temp;
            A.paz.push_back(temp);
            sum += temp;
        }

        cout << "Iveskite egzamino pazymi: ";
        cin >> A.egz;
        double vid = (n > 0) ? (static_cast<double>(sum) / n) : 0.0;
        double med = Mediana(A.paz);
        if (pasirinkimas == 'v' || pasirinkimas == 'V')
            A.rez = 0.4 * vid + 0.6 * A.egz;
        else
            A.rez = 0.4 * med + 0.6 * A.egz;
        grupe.push_back(A);

        A.paz.clear(); 
    }
    Spausdinimas(grupe, pasirinkimas);
}
void Spausdinimas(const vector<Student> &grupe, char pasirinkimas)
{
    cout << left << setw(15) << "Pavarde"
         << left << setw(15) << "Vardas";

    if (pasirinkimas == 'v' || pasirinkimas == 'V')
        cout << right << setw(20) << "Galutinis (Vid.)" << endl;
    else
        cout << right << setw(20) << "Galutinis (Med.)" << endl;

    cout <<string(50, '-') << endl;
    for(auto A:grupe)
    {
        std::cout<<left<<setw(10)<<A.vardas<<right<<setw(10)<<A.pavarde<<right<<setw(20)<<A.rez<<endl;


        //for(auto a:A.paz) cout<<setw(3)<<a;
        //cout<<setw(10)<<A.egz<<endl;
    }
}