#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <forward_list>

using namespace std;

class City
// takes a row, divides it to three cells which form one object
{
public:
    string city;
    string country;
    int population;

    City(string row)
    {

        string cell;
        stringstream ss(row);
        vector<string> cityData;

        while (getline(ss, cell, ','))
        {
            cityData.push_back(cell);
        }
        city = cityData[0];
        country = cityData[1];
        population = atoi(cityData[2].c_str());
    }
};

class CountryStats
{
public:
    string name_;
    int numcitiesinlist_;
    int totalpopulationinlist_;
    // Output the data in this CountryStats object by overloading the << operator
    // The format of the output should be e.g., as follows:
    //  Country: Canada, Number of Cities in List: 628, Total Population In List: 37807501
    friend ostream &operator<<(ostream &os, const CountryStats &cs)
    {
        os << "Country: " << cs.name_
           << ", Number of Cities in List: " << cs.numcitiesinlist_
           << ", Total Population In List: " << cs.totalpopulationinlist_;
        return os;
    }
};

class WorldCities
{
    forward_list<City> dataList;

public:
    vector<CountryStats> PrintAllInSameCountry(string city, bool allcountries, bool alphabetical)
    {
        vector<CountryStats> statsVec;
        vector<string> countryNames{};
        // fetches the name of the countries where the given city is
        for (auto it = dataList.begin(); it != dataList.end(); ++it)
        {
            if (city == it->city)
            { //vector of country names
                countryNames.push_back(it->country);
            }
        }

        unique(countryNames.begin(), countryNames.end());
        sort(countryNames.begin(), countryNames.end());

        //for loop to iterate over countryNames
        for (int i = 0; i < countryNames.size(); i++)
        {
            vector<string> allCities;
            int totalPopulation = 0;

            for (auto it = dataList.begin(); it != dataList.end(); ++it)
            {
                if (countryNames[i] == it->country)
                {
                    allCities.push_back(it->city);
                    totalPopulation = totalPopulation + it->population;
                }
            }

            CountryStats statsA;
            statsA.name_ = countryNames[i];
            statsA.numcitiesinlist_ = allCities.size();
            statsA.totalpopulationinlist_ = totalPopulation;

            statsVec.push_back(statsA);

            if (allcountries == false && alphabetical == false)
            {
                if (i > 0)
                {
                    break;
                }
                cout << (countryNames[i]) << endl; //<< allCities << endl;
                //for loop print each city + , + " "
                for (int i = 0; i < (allCities.size() - 1); i++)
                {
                    cout << allCities[i] << ", ";
                }

                cout << allCities[allCities.size() - 1] << endl;
            }
            if (allcountries == true && alphabetical == false)
            {

                cout << (countryNames[i]) << endl;
                for (int i = 0; i < (allCities.size() - 1); i++)
                {
                    cout << allCities[i] << ", ";
                }

                cout << allCities[allCities.size() - 1] << endl;
            }
            if (allcountries == false && alphabetical == true)
            {
                if (i > 0)
                {
                    break;
                }
                sort(allCities.begin(), allCities.end());
                cout << (countryNames[i]) << endl;
                for (int i = 0; i < (allCities.size() - 1); i++)
                {
                    cout << allCities[i] << ", ";
                }

                cout << allCities[allCities.size() - 1] << endl;
            }
            if (allcountries == true && alphabetical == true)
            {

                cout << (countryNames[i]) << endl;
                sort(allCities.begin(), allCities.end());
                for (int i = 0; i < (allCities.size() - 1); i++)
                {
                    cout << allCities[i] << ", ";
                }

                cout << allCities[allCities.size() - 1] << endl;
            }
        }

        return statsVec;
    }
    // Returns true if filename was a valid CSV file and was read in correctly
    // Returns false otherwise
    bool ReadCSVFile(string filename = "./WorldCities.csv")
    {
        ifstream csvFile(filename);
        string line;

        if (csvFile.is_open())
        {
            while (getline(csvFile, line))
            {
                City c(line);
                dataList.push_front(c);
            }
        }
        return true;
    }
};

int main()
{
    WorldCities wc;

    if (wc.ReadCSVFile("WorldCities.csv"))
    {
        // wc.PrintAllInSameCountry("Paris", true, true);

        ifstream testfile("WorldCitiesTests.txt");
        string testline;
        string cityname;
        string allcountries_str;
        string alphabetical_str;
        int allcountries;
        int alphabetical;
        while (getline(testfile, testline))
        {
            stringstream ss(testline);
            getline(ss, cityname, ",");
            getline(ss, allcountries_str, ",");
            getline(ss, alphabetical_str, ",");
            allcountries = atoi(allcountries_str.c_str());
            alphabetical = atoi(alphabetical_str.c_str());
            wc.PrintAllInSameCountry(cityname, (allcountries != 0), (alphabetical != 0));
        }
    }
    return 0;
}
