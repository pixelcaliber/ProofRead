#include <bits/stdc++.h>
#include "TrieFunctions.cpp"
using namespace std;

unsigned int wrongWords = 0;
Trie *globalObject;


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./checker [filename]\n";
        return 1;
    }
    string filename = argv[1];
    ifstream fin(filename);
    ofstream fout("temp.txt");

    if (!fin)
    {
        cout << "File not found\n";
        return 2;
    }

    char c;
    string w;
    clock_t start = clock();
    if (!globalObject->load())
    {
        cout << "Error while loading trie\n";
        return 3;
    }

    fin >> noskipws;
    vector<string>res;
    int i = 0;
    while (!fin.eof())
    {
        fin >> c;
        if (!isalpha(c))
        {
            // cout << w << endl;
            if (c != ' ' and c != '\n')
            {
                char cnext;
                fin>>cnext;
                if (cnext != ' ' and cnext != '\n')
                {
                    w += c;
                    w += cnext;
                    i+=2;
                }            
            }
            else if (w.length() && !globalObject->check(w))
            {
                fout << "<div>" << w << "</div>"
                     << "\n";
                res.push_back(w);
                // cout << "Wrong word: ";    
                // cout << w << "   ";
                wrongWords++;
                i = 0;
                w.erase();
            }
            else{
                fout << w << " ";
                w.erase();
                i = 0;
            }
        }
        else if (c != ' ' && c != '\n')
        {
            if (isalpha(c) || c == '\'')
                w += c, i++;
        }
        if (i > 45)
        {
            cout << "Wrong word: " << w << endl;
            wrongWords++;
        }
    }
    w.erase();
    fin.close();

    if(res.size() == 0)
    {
        cout<<"No Misspelled Words Found!"<<endl;
    }
    else
    {
        cout<<"Wrong Words: "<<endl;
        for (int i = 0; i < res.size(); i++)
        {
            cout<<res[i];
            if(i%5 == 0 and i > 0)
                cout<<endl;
            else if(i != res.size() - 1)
                cout<<",   ";
        }
        cout<<endl;
    }
    clock_t s = clock();
    if (!globalObject->unload())
    {
        cout << "Error while unloading trie\n";
        return 4;
    }

    cout << "\nWords in the dictionary used: " << size_of_dict << endl;
    cout << "Words misspelled in " << filename << ": " << wrongWords << endl;
    cout << "Loading time of the dictionary in Trie: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << "ms" << endl;
    cout << "Unloading time for Trie: " << (clock() - s) / (double)(CLOCKS_PER_SEC / 1000) << "ms" << endl;
    return 0;
}