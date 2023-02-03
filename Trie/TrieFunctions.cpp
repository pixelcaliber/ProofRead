#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
// #include <dictionary.h>

unsigned int size_of_dict = 0;

#define maxsize 27

class Trie
{
    Trie *array[300];
    bool end;

public:

    Trie(){
        end=false;
        for (int i = 0; i < 300; i++) {
            array[i] = NULL;
        }
    }


    bool load();
    bool unload();
    bool check(string);
    void dell(Trie* t);
};

Trie *root = new Trie();
//To load the dictionary into memory
bool Trie ::load()
{
    char c;
    //initialize file pointer
    ifstream fin("dictionary.txt");
    try
    {
        if (!fin){
            cout<<"error"<<endl;
            throw "ERROR in loading file";            
            return false;
        }
    }
    catch (char *err)
    {

        cout << err;
        fin.close();
        return false;
    }
    Trie *temp = root;
    fin >> noskipws; //to prevent skipping spaces and newline chars in text file
    while (fin >> c)
    {
        //If root points to a null node
        if(temp == nullptr)
        // if (temp->array[c - 'a'] == NULL)
        {
            // temp->array[c - 'a'] = new Trie();
            Trie *node = new Trie;
            root = node;
            temp = root;
        }
        //if c ranges from a to z, have its pointer index be 0 to 25 respectively
        if (isalpha(c))
        {
            if (temp->array[c] == NULL)
            {
                // Trie *node = new Trie;       //Allocate space for new node
                temp->array[c] = new Trie; //Have the pointer corresponding to c-th index point to node
                // temp = node;                 // now put temp = newnode
            }
            // else
                temp = temp->array[c];
        }
        //if c is ' then have its pointer index be 26
        // else if (c == '\'')
        // {
        //     if (temp->array[maxsize - 1] == NULL)
        //     {
        //         Trie *node = new Trie;           //Allocate space for new node
        //         temp->array[maxsize - 1] = node; //Have the pointer corresponding to 26th index point to node
        //         // temp = node;                     // now put temp = newnode
        //     }
        //     // else
        //         temp = temp->array[maxsize - 1];
        // }

        //If a word has been fully loaded
        if (c == '\n')
        {
            temp->end = true; //If a word has been loaded then put boolean true
            temp = root;      //Then start again from root
            size_of_dict++;
            continue;
        }
    }

    //close the file after loading it into the Trie
    fin.close();

    return true;
}

//To check if a word is correct or not
bool Trie ::check(string w)
{
    char c;
    Trie *temp = root;

    for (int i = 0; i < w.length(); i++)
    {
        c = w[i];
        //traverse the trie until the node corresponding to the last character
        //If trie ends while finding word return false
        if (temp->array[c] == NULL)
            return false;
        if (isalpha(c))
        {
            temp = temp->array[c];
        }
        // else if (c == '\'')
        // {
        //     temp = temp->array[maxsize - 1];
        // }
    }

    // for (int i = 0; i < l; i++)
    // {
    //     c = word[i];

    //     //traverse the trie until the node corresponding to the last character

    //     //If trie ends while finding word return false
    //     if (temp->array[c - 'a'] == NULL)
    //         return false;
    //     if (isalpha(c))
    //     {
    //         temp = temp->array[c - 'a'];
    //     }
    //     else if (c == '\'')
    //     {
    //         temp = temp->array[maxsize - 1];
    //     }
    // }

    //If boolean corresponding to last character is false then return false
    if (temp->end == true)
        return true;

    return false;
}

bool Trie::unload(void)
{
    if (root != NULL)
    {
        dell(root);
        return true;
    }
    return false;
}

void Trie ::dell(Trie *t) //for freeing the trie using recursion
{
    // recursive case (go to end of trie)
    for (int i = 0; i < 300; i++)
    {
        if (t->array[i] != NULL)
        {
            dell(t->array[i]);
        }
    }

    // base case
    delete (t);
}
