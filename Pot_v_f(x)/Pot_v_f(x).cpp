#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

void PrintVector(vector<double>& vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        cout << vector[i] << endl;
    }
}

void PrintPairVector(vector<pair<double, double>>& vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        cout << vector[i].first << " -> " << vector[i].second << endl;
    }
}

double ProcessDecimal(double y)
{
    stringstream yS; string wholePart; string decimalPart;
    yS << y;
    string s = yS.str();
    
    if (s.find('.') != string::npos)
    {
        int pos = s.find(".");
        wholePart = s.substr(0, pos);
        decimalPart = s.substr(s.find(".") + 1);

        for (int i = 0; i < decimalPart.length(); i++)
        {
            if (i > 0)
                decimalPart[i] = '0';
        }
        string rounded = wholePart + '.' + decimalPart;
        return stod(rounded);
    }
    return y;
}

void DrawGraph(vector<pair<double, double>>results, int intervalLength)
{
    for (int i = 0; i < results.size() - 1; i++)
    {
        results[i].second = ProcessDecimal(results[i].second);
        float a = floor(results[i].second * 100.0) / 100.0;
        float b = floor(results[i+1].second * 100.0) / 100.0;

        double cellsY = results[i].second - results[i + 1].second;
        cellsY *= 10;
        int cellsX = abs((results[0].first - results[i+1].first)*10);
        
        for (int i = 0; i < cellsY; i++)
        {
            bool hastagWritten = false;
            for (int i = 0; i < intervalLength + 1; i++)
            {
                //int dots = (intervalLength + 1) - cellsX;
                if (!hastagWritten)
                {
                    for (int i = 0; i < cellsX; i++)
                    {
                        cout << "#";
                        hastagWritten = true;
                    }
                }
                cout << ".";
            }
            cout << endl;
        }
    }
}

void CalculatePolynom(double l, double r, int n, vector<double>& coeffiecients)
{
    int intervalLenght = (r - l) * 10;
    double equationResult;
    double x = l;
    vector<pair<double, double>>results;
    for (int i = 0; i < intervalLenght; i++)
    {
        if (n == 3)
        {
            equationResult = coeffiecients[0] * pow(x, 3) + coeffiecients[1] * pow(x, 2) + coeffiecients[2] * x + coeffiecients[3];
        }
        if (n == 2)
        {
            equationResult = coeffiecients[0] * pow(x, 2) + coeffiecients[1] * x + coeffiecients[2];
        }
        if (n == 1)
        {
            equationResult = coeffiecients[0] * x + coeffiecients[1];
        }
        if (n == 0)
        {
            equationResult = coeffiecients[0];
        }
        results.push_back(make_pair(x, equationResult));
        x += 0.1;
    }
    PrintPairVector(results);

    DrawGraph(results, intervalLenght);
    //return results;
}


//int main(int argc, char* argv[])
int main()
{
    //preberi vhodne podatke
    ifstream infile("C:\\Users\\icovi\\OneDrive\\Desktop\\College\\2022-2023\\ATURP\\Seminarska_naloga\\Pot_v_f(x)\\Debug\\testne_primere\\test.txt");
  
    string l, r, n, polynomDegree;
    vector<double>coefficients;
    infile >> l >> r >> n;
    while (infile >> polynomDegree)
        coefficients.push_back(stod(polynomDegree));

    PrintVector(coefficients);

    CalculatePolynom(stod(l), stod(r), stoi(n), coefficients);
    //PrintPairVector(results);

    //PrintVector(results);
}

