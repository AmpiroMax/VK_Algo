#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAX_WORD_LENGTH = 30;
const int ALPHABET_SIZE = 26;

class Trie
{
public:
    int size;
    vector<vector<int>> next;
    vector<pair<int, int>> is_terminal;

    Trie()
    {
        size = 1;
        next = vector<vector<int>>(1, vector<int>(ALPHABET_SIZE, -1));
        // Каждый элемент массива хранит в себе два значения
        // - состояние вершины: конечная для какого-то слова или нет
        // - в случае конечности второй элемент будет равен номеру слова
        //   из входных данных, которое завершается в данной вершине
        is_terminal.push_back({0, -1});
    }

    void insert(string str, int index)
    {
        int V = 0;
        for (int i = 0; i < str.size(); ++i)
        {
            if (next[V][str[i] - 'a'] == -1)
            {
                next[V][str[i] - 'a'] = size;

                next.push_back(vector<int>(ALPHABET_SIZE, -1));
                is_terminal.push_back({0, -1});

                size += 1;
            }
            V = next[V][str[i] - 'a'];
        }
        is_terminal[V] = {1, index};
    }

    void print_next()
    {
        cout << "   ";
        for (int i = 'a'; i < 'z' + 1; ++i)
            cout << char(i) << " ";
        cout << endl;

        for (int i = 0; i < next.size(); ++i)
        {
            auto V = next[i];
            cout << i << ": ";
            for (auto s_i : V)
                if (s_i == -1)
                    cout << "# ";
                else
                    cout << s_i << " ";
            // cout << is_terminal[s_i].second << " ";
            cout << endl;
        }
        // for (auto V : next)
        // {
        //     for (auto s_i : V)
        //         if (s_i == -1)
        //             cout << "# ";
        //         else
        //             cout << s_i << " ";
        //     // cout << is_terminal[s_i].second << " ";
        //     cout << endl;
        // }
    }
    void print_terminal()
    {
        for (auto el : is_terminal)
            cout << el.first << " " << el.second << endl;
    }
};

/*
shipmyhesheepspe
5
he
she
heap
sheep
ship

qeqwe 
2
he
heap

qeqwe
4
live
life
lively
lovely


fdsfs
2
heap
he

abababa
4
a
b
aba
bab

*/
int main()
{
    string text;
    int M;
    cin >> text;
    cin >> M;

    vector<int> contains(M, 0);
    Trie trie;

    for (int i = 0; i < M; ++i)
    {
        string str;
        cin >> str;
        trie.insert(str, i);
    }

    // trie.print_next();

    for (int i = 0; i < text.size(); ++i)
    {
        int V = 0;
        for (int j = i; j < text.size(); ++j)
        {
            // cout << V << " " << text[j] << endl;
            if (trie.next[V][text[j] - 'a'] == -1)
                break;

            V = trie.next[V][text[j] - 'a'];
            // cout << V << " " << text[j] << endl;
            if (trie.is_terminal[V].first)
                contains[trie.is_terminal[V].second] = 1;
        }
        // int V = 0;
        // cout << "-----------------------" << endl;
        // for (int j = i; j < text.size(); ++j)
        // {
        //     cout << "V, s[j] " << V << " " << text[j] << endl;
        //     cout << "next    " << trie.next[V][text[j] - 'a'] << endl;
        //     if (trie.next[V][text[j] - 'a'] == -1)
        //         break;

        //     // Напоминаю, что первый элемент массива is_terminal
        //     // это состояние вершины, в второй элемент в случае
        //     // терминальности равен номеру слова, из ввода
        //     cout << trie.is_terminal[V].first << " " << trie.is_terminal[V].second << endl;
        //     if (trie.is_terminal[V].first)
        //         contains[trie.is_terminal[V].second] = 1;

        //     V = trie.next[V][text[j] - 'a'];
        // }
        // cout << "-----------------------" << endl;
    }

    for (auto el : contains)
        cout << (el ? "Yes" : "No") << endl;

    // trie.print_next();
    // trie.print_terminal();

    return 0;
}