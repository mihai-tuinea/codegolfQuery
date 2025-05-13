// I/O
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
// Containers
#include <list>
#include <array>
#include <queue>
#include <deque>
#include <set>
#include <stack>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>
// Other
#include <algorithm>
#include <bitset>
#include <functional>
#include <iterator>
#include <tuple>
#include <cstring>
#include <limits>
#include <ostream>
#include <string>
#include <utility>
#include <regex>

using namespace std;

struct Pr
{
    string n;
    unsigned int p{};
    string c;
    unsigned int s{};
    string b;
    float r{};
    unsigned int d{};

    friend std::istream& operator>>(std::istream& is, Pr& pr)
    {
        string line;
        getline(is, line);

        stringstream ss(line);
        string tmp;
        getline(ss, pr.n, '|');
        getline(ss, tmp, '|');
        pr.p = stoul(tmp);
        getline(ss, pr.c, '|');
        getline(ss, tmp, '|');
        pr.s = stoul(tmp);
        getline(ss, pr.b, '|');
        getline(ss, tmp, '|');
        pr.r = stof(tmp);
        getline(ss, tmp, '|');
        pr.d = stoul(tmp);

        return is;
    }
};

// INCEPUT cod de trimis pe platforma
void f(const vector<Pr>& prs, const string& q)
{
    // Parse queries by type
    unordered_map<char, vector<pair<char, string>>> typeToFilters;
    stringstream ss(q);
    string query;
    while (getline(ss, query, ';'))
    {
        if (query.size() < 2) continue;

        char type = query[0];
        char mode = query[1];
        string val = (query.size() > 2) ? query.substr(2) : "";

        for (char& ch : val) ch = tolower(ch);
        typeToFilters[type].emplace_back(mode, val);
    }

    vector<string> orderedUniques;
    unordered_set<string> seen;

    for (const auto& pr : prs)
    {
        bool allTypesMatch = true;

        for (const auto& [type, filters] : typeToFilters)
        {
            bool anyMatchThisType = false;

            for (const auto& [mode, val] : filters)
            {
                string prn = pr.n;
                switch (type)
                {
                case 'n':
                    {
                        string prnLower = pr.n;
                        for (char& ch : prnLower) ch = tolower(ch);

                        if (mode == '=' && prnLower == val) anyMatchThisType = true;
                        else if (mode == '@' && prnLower.find(val) != string::npos) anyMatchThisType = true;
                        else if (mode == '!' && prnLower.find(val) == string::npos) anyMatchThisType = true;

                        break;
                    }


                case 'p':
                    {
                        unsigned int prp = pr.p;

                        if (mode == '=' && prp == stoi(val)) anyMatchThisType = true;
                        else if (mode == '>')
                        {
                            auto it = val.find('<');
                            if (it != string::npos)
                            {
                                unsigned int low = stoi(val.substr(0, it));
                                unsigned int up = stoi(val.substr(it + 1));
                                if (prp > low && prp < up) anyMatchThisType = true;
                            }
                            else if (prp > stoi(val)) anyMatchThisType = true;
                        }
                        else if (mode == '<')
                        {
                            auto it = val.find('>');
                            if (it != string::npos)
                            {
                                unsigned int up = stoi(val.substr(0, it));
                                unsigned int low = stoi(val.substr(it + 1));
                                if (prp > low && prp < up) anyMatchThisType = true;
                            }
                            else if (prp < stoi(val)) anyMatchThisType = true;
                        }
                        break;
                    }


                case 'c':
                    {
                        string prc = pr.c;
                        for (char& ch : prc) ch = tolower(ch);

                        if (mode == '=' && prc == val) anyMatchThisType = true;
                        else if (mode == '@' && prc.find(val) != string::npos) anyMatchThisType = true;
                        else if (mode == '!' && prc.find(val) == string::npos) anyMatchThisType = true;

                        break;
                    }


                case 's':
                    {
                        if (mode == '!' && pr.s != 0)
                            anyMatchThisType = true;
                        break;
                    }


                case 'b':
                    {
                        string prb = pr.b;
                        for (char& ch : prb) ch = tolower(ch);

                        if (mode == '=' && prb == val) anyMatchThisType = true;
                        else if (mode == '@' && prb.find(val) != string::npos) anyMatchThisType = true;
                        else if (mode == '!' && prb.find(val) == string::npos) anyMatchThisType = true;

                        break;
                    }


                case 'r':
                    {
                        float prr = pr.r;
                        if (mode == '=' && prr == stof(val)) anyMatchThisType = true;
                        else if (mode == '>')
                        {
                            auto it = val.find('<');
                            if (it != string::npos)
                            {
                                float low = stof(val.substr(0, it));
                                float up = stof(val.substr(it + 1));
                                if (prr > low && prr < up) anyMatchThisType = true;
                            }
                            else if (prr > stof(val)) anyMatchThisType = true;
                        }
                        else if (mode == '<')
                        {
                            auto it = val.find('>');
                            if (it != string::npos)
                            {
                                float up = stof(val.substr(0, it));
                                float low = stof(val.substr(it + 1));
                                if (prr > low && prr < up) anyMatchThisType = true;
                            }
                            else if (prr < stof(val)) anyMatchThisType = true;
                        }
                        break;
                    }


                case 'd':
                    {
                        if (mode == '!' && pr.d != 0)
                            anyMatchThisType = true;
                        break;
                    }


                default: break;
                }


                if (anyMatchThisType)
                    break; // no need to test more filters of same type
            }

            if (!anyMatchThisType)
            {
                allTypesMatch = false;
                break;
            }
        }

        if (allTypesMatch && !seen.count(pr.n))
        {
            seen.insert(pr.n);
            orderedUniques.push_back(pr.n);
        }
    }

    for (const auto& name : orderedUniques)
        cout << name << ";";
    cout << endl;
}


// FINAL cod de trimis pe platforma

int main(int argc, char** argv)
{
    const ifstream in(argv[1]);
    cin.rdbuf(in.rdbuf());

    int pc;
    string text;
    getline(cin, text);
    pc = atoi(text.c_str());

    vector<Pr> prs(pc);

    for (int i = 0; i < pc; i++)
    {
        cin >> prs[i];
    }

    int qc; // queryCount
    string text2;
    getline(cin, text2);
    qc = atoi(text2.c_str());

    for (int i = 0; i < qc; i++)
    {
        string q; // query
        getline(cin, q);
        f(prs, q);
    }

    return 0;
}
