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
    vector<pair<char, pair<char, string>>> queries;
    stringstream ss(q);
    string query;
    while (getline(ss, query, ';'))
    {
        char type = query[0];
        char mode = query[1];
        string val = query.substr(2);
        for (char& ch : val) ch = tolower(ch);
        queries.push_back({type, {mode, val}});
    }

    // have to use both a vector and a set because c++ is too primitive
    vector<string> orderedUniques;
    unordered_set<string> seen;

    for (const auto& pr : prs)
    {
        for (const auto& qquery : queries)
        {
            char type = qquery.first;
            char mode = qquery.second.first;
            string val = qquery.second.second;

            string prn = pr.n;

            bool matches = false;

            switch (type)
            {
            case 'n':
                {
                    string prnCopy = pr.n;
                    for (char& ch : prnCopy) ch = tolower(ch);

                    if (mode == '=' && prnCopy == val) matches = true;
                    else if (mode == '@' && prnCopy.find(val) != string::npos) matches = true;

                    break;
                }


            case 'p':
                {
                    unsigned int prp = pr.p;

                    if (mode == '=' && prp == stoi(val)) matches = true;
                    else if (mode == '>')
                    {
                        auto it = val.find('<'); // check if it's an interval
                        if (it != string::npos)
                        {
                            unsigned int lower = stoi(val.substr(0, it));
                            unsigned int upper = stoi(val.substr(it + 1));
                            if (pr.p > lower && pr.p < upper)
                            {
                                matches = true;
                            }
                        }
                        else // just p > something
                        {
                            unsigned int threshold = stoi(val);
                            if (pr.p > threshold)
                            {
                                matches = true;
                            }
                        }
                        break;
                    }
                    else if (mode == '<')
                    {
                        auto it = val.find('>'); // check if it's an interval
                        if (it != string::npos)
                        {
                            unsigned int upper = stoi(val.substr(0, it));
                            unsigned int lower = stoi(val.substr(it + 1));
                            if (pr.p > lower && pr.p < upper)
                            {
                                matches = true;
                            }
                        }
                        else // just p > something
                        {
                            unsigned int threshold = stoi(val);
                            if (pr.p < threshold)
                            {
                                matches = true;
                            }
                        }
                        break;
                    }
                }


            case 'c':
                {
                    string prc = pr.c;
                    for (char& ch : prc) ch = tolower(ch);

                    if (mode == '=' && prc == val) matches = true;
                    else if (mode == '@' && prc.find(val) != string::npos) matches = true;

                    break;
                }


            case 's':
                {
                    unsigned int prss = pr.s;

                    if (mode == '!' && prss != 0) matches = true;

                    break;
                }


            case 'b':
                {
                    string prb = pr.b;
                    for (char& ch : prb) ch = tolower(ch);

                    if (mode == '=' && prb == val) matches = true;
                    else if (mode == '@' && prb.find(val) != string::npos) matches = true;

                    break;
                }


            case 'r':
                {
                    float prr = pr.r;

                    if (mode == '=' && prr == stof(val)) matches = true;
                    else if (mode == '>')
                    {
                        auto it = val.find('<'); // check if it's an interval
                        if (it != string::npos)
                        {
                            float lower = stof(val.substr(0, it));
                            float upper = stof(val.substr(it + 1));
                            if (pr.r > lower && pr.r < upper)
                            {
                                matches = true;
                            }
                        }
                        else // just p > something
                        {
                            float threshold = stof(val);
                            if (pr.r > threshold)
                            {
                                matches = true;
                            }
                        }
                        break;
                    }
                    else if (mode == '<')
                    {
                        auto it = val.find('>'); // check if it's an interval
                        if (it != string::npos)
                        {
                            float upper = stof(val.substr(0, it));
                            float lower = stof(val.substr(it + 1));
                            if (pr.r > lower && pr.r < upper)
                            {
                                matches = true;
                            }
                        }
                        else // just p > something
                        {
                            float threshold = stof(val);
                            if (pr.r < threshold)
                            {
                                matches = true;
                            }
                        }
                        break;
                    }
                }


            case 'd':
                {
                    unsigned int prd = pr.d;

                    if (mode == '!' && prd != 0) matches = true;

                    break;
                }

            default: break;
            }

            if (matches && !seen.count(prn))
            {
                seen.insert(prn);
                orderedUniques.push_back(prn);
            }
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
