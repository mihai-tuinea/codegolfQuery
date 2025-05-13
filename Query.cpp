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
    char type = q[0]; // n p c s b r d
    char mode = q[1]; // = @ > ... not discovered yet

    string val = q.substr(2);
    for (char& ch : val) ch = tolower(ch);

    switch (type)
    {
    case 'n':
        {
            switch (mode)
            {
            case '=':
                {
                    for (const auto& pr : prs)
                    {
                        string prn = pr.n;
                        for (char& ch : prn) ch = tolower(ch);

                        if (prn == val)
                        {
                            cout << pr.n << ";";
                        }
                    }
                    break;
                }
            case '@':
                {
                    for (const auto& pr : prs)
                    {
                        string prn = pr.n;
                        for (char& ch : prn) ch = tolower(ch);

                        if (prn.find(val) != string::npos)
                        {
                            cout << pr.n << ";";
                        }
                    }
                    break;
                }
            case '>':
                {
                    break;
                }
            default:
                break;
            }
            break;
        }
    case 'p':
        {
            switch (mode)
            {
            case '=':
                {
                    for (const auto& pr : prs)
                    {
                        unsigned int prp = pr.p;

                        if (prp == stoi(val))
                        {
                            cout << pr.n << ";";
                        }
                    }
                    break;
                }
            case '@':
                {
                    break;
                }
            case '>':
                {
                    auto it = val.find('<'); // check if it's an interval
                    if (it != string::npos)
                    {
                        unsigned int lower = stoi(val.substr(0, it));
                        unsigned int upper = stoi(val.substr(it + 1));
                        for (const auto& pr : prs)
                        {
                            if (pr.p > lower && pr.p < upper)
                            {
                                cout << pr.n << ";";
                            }
                        }
                    }
                    else // just p > something
                    {
                        unsigned int threshold = stoi(val);
                        for (const auto& pr : prs)
                        {
                            if (pr.p > threshold)
                            {
                                cout << pr.n << ";";
                            }
                        }
                    }
                    break;
                }

            default:
                break;
            }
            break;
        }
    case 'c':
        {
            switch (mode)
            {
            case '=':
                {
                    for (const auto& pr : prs)
                    {
                        string prc = pr.c;
                        for (char& ch : prc) ch = tolower(ch);

                        if (prc == val)
                        {
                            cout << pr.n << ";";
                        }
                    }
                    break;
                }
            case '@':
                {
                    for (const auto& pr : prs)
                    {
                        string prc = pr.c;
                        for (char& ch : prc) ch = tolower(ch);

                        if (prc.find(val) != string::npos)
                        {
                            cout << pr.n << ";";
                        }
                    }
                    break;
                }
            case '>':
                {
                    break;
                }
            default:
                break;
            }
            break;
        }
    case 's':
        {
            switch (mode)
            {
            case '!':
                {
                    for (const auto& pr : prs)
                    {
                        unsigned int prss = pr.s;

                        if (prss != 0)
                        {
                            cout << pr.n << ";";
                        }
                    }
                    break;
                }
            default:
                break;
            }
        }
    case 'b':
        {
            switch (mode)
            {
            case '=':
                {
                    for (const auto& pr : prs)
                    {
                        string prb = pr.b;
                        for (char& ch : prb) ch = tolower(ch);

                        if (prb == val)
                        {
                            cout << pr.n << ";";
                        }
                    }
                    break;
                }
            case '@':
                {
                    for (const auto& pr : prs)
                    {
                        string prb = pr.b;
                        for (char& ch : prb) ch = tolower(ch);

                        if (prb.find(val) != string::npos)
                        {
                            cout << pr.n << ";";
                        }
                    }
                    break;
                }
            case '>':
                {
                    break;
                }
            default:
                break;
            }
            break;
        }
    case 'r':
        {
            switch (mode)
            {
            case '>':
                {
                    auto it = val.find('<'); // check if it's an interval
                    if (it != string::npos)
                    {
                        float lower = stof(val.substr(0, it));
                        float upper = stof(val.substr(it + 1));
                        for (const auto& pr : prs)
                        {
                            if (pr.r > lower && pr.r < upper)
                            {
                                cout << pr.n << ";";
                            }
                        }
                    }
                    else // just p > something
                    {
                        float threshold = stof(val);
                        for (const auto& pr : prs)
                        {
                            if (pr.r > threshold)
                            {
                                cout << pr.n << ";";
                            }
                        }
                    }
                    break;
                }
            case '<':
                {
                    auto it = val.find('>'); // check if it's an interval
                    if (it != string::npos)
                    {
                        float upper = stof(val.substr(0, it));
                        float lower = stof(val.substr(it + 1));
                        for (const auto& pr : prs)
                        {
                            if (pr.r > lower && pr.r < upper)
                            {
                                cout << pr.n << ";";
                            }
                        }
                    }
                    else // just p > something
                    {
                        float threshold = stof(val);
                        for (const auto& pr : prs)
                        {
                            if (pr.r < threshold)
                            {
                                cout << pr.n << ";";
                            }
                        }
                    }
                    break;
                }
            default:
                break;
            }
            break;
        }
    case 'd':
        {
            switch (mode)
            {
            case '!':
                {
                    for (const auto& pr : prs)
                    {
                        unsigned int prd = pr.d;

                        if (prd != 0)
                        {
                            cout << pr.n << ";";
                        }
                    }
                    break;
                }
            default:
                break;
            }
            break;
        }
    default:
        break;
    }
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
