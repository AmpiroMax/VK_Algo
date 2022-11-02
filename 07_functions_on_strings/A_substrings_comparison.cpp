#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Point
{
    size_t p1;
    size_t p2;
    size_t p3;

    Point operator+(Point rhs)
    {
        Point rez = {
            p1 + rhs.p1,
            p2 + rhs.p2,
            p3 + rhs.p3};
        return rez;
    }

    Point operator+(size_t rhs)
    {
        Point rez = {
            p1 + rhs,
            p2 + rhs,
            p3 + rhs};
        return rez;
    }

    Point operator*(Point rhs)
    {
        Point rez = {
            p1 * rhs.p1,
            p2 * rhs.p2,
            p3 * rhs.p3};
        return rez;
    }

    Point operator%(size_t mod)
    {
        Point rez = {
            p1 % mod,
            p2 % mod,
            p3 % mod};
        return rez;
    }

    Point operator%(Point mod)
    {
        Point rez = {
            p1 % mod.p1,
            p2 % mod.p2,
            p3 % mod.p3};
        return rez;
    }

    Point operator-(Point rhs)
    {
        Point rez = {
            p1 - rhs.p1,
            p2 - rhs.p2,
            p3 - rhs.p3};
        return rez;
    }

    bool operator==(Point rhs)
    {
        return p1 == rhs.p1 && p2 == rhs.p2 && p3 == rhs.p3;
    }
};

std::ostream &operator<<(std::ostream &os, const Point &obj)
{
    os << obj.p1 << " " << obj.p2 << " " << obj.p3 << " " << endl;
    return os;
}

class SubstringHasher
{
private:
    Point M = {1000000123ULL, 1000000321ULL, 1000000007ULL};
    const Point P = {31, 31, 31};

    vector<Point> subhash;
    vector<Point> powp;

    void init_subhash(const string &str)
    {
        subhash.resize(str.size());
        powp.resize(str.size());

        subhash[0] = {size_t(str[0] - 'a' + 1), size_t(str[0] - 'a' + 1), size_t(str[0] - 'a' + 1)};
        powp[0] = {1, 1, 1};

        for (int i = 1; i < str.size(); ++i)
        {
            subhash[i] = (((subhash[i - 1] * P) % M + (str[i] - 'a' + 1)) % M);
            powp[i] = (powp[i - 1] * P) % M;
        }
    }

public:
    SubstringHasher(const string &str)
    {
        init_subhash(str);
    }

    Point get_hash(int l, int r)
    {
        if (l == 0)
            return subhash[r];
        return ((M + subhash[r] - (subhash[l - 1] * powp[r - (l - 1)]) % M)) % M;
    }

    void print()
    {
        for (auto el : subhash)
            cout << el;
        cout << endl;

        for (auto el : powp)
            cout << el;
        cout << endl;
    }
};

int main()
{
    string str;
    cin >> str;
    SubstringHasher hasher(str);

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        int l1;
        int r1;
        int l2;
        int r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if ((r1 - l1) != (r2 - l2))
        {
            cout << "No" << endl;
            continue;
        }
        Point hashs1 = hasher.get_hash(l1 - 1, r1 - 1);
        Point hashs2 = hasher.get_hash(l2 - 1, r2 - 1);

        if (hashs1 == hashs2)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}