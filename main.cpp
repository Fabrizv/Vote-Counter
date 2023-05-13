// Name: Fabrizio Valdivia
// Description: This program takes in a text file with canndidates and parties along with votes, and 
//      finds out what was the party of the winnning canidate.#include <string>
#include <fstream>
#include <iostream>
#include <vector>

// template Class
template <typename t1, typename t2>
class hashMap
{
public:
    struct hashPair
    {
        t1 key;
        t2 value;
        hashPair * link;
    };

    struct iteratorPair
    {
        t1 * key;
        t2 * value;
        iteratorPair * link;
    };

    class iterator
    {
    public:
        friend class hashMap;
        iterator ();
        const iterator& operator ++(int);
        bool operator ==( const iterator &) const;
        bool operator !=( const iterator &) const;
        t1 first ();
        t2 second ();
    private:
        iterator(iteratorPair *);
        iteratorPair * element;
    };

    hashMap ();
    ~hashMap ();
    t2& operator [](t1);
    iterator begin () const;
    iterator end() const;
private:
    void resize ();
    int h(std:: string) const;
    int items;
    int size;
    hashPair ** table;
    iteratorPair * head;
};

// Function: Default constructor
template <typename t1, typename t2>
hashMap<t1, t2>::hashMap()
{
    // initialize variables
    size = 5;
    items = 0;
    head = NULL;
    table = new hashPair*[size];

    // Set the table to NULL
    for (int i = 0; i < size; i++)
        table[i]= NULL;
}

//Fucntion: Destructor
template <typename t1, typename t2>
hashMap<t1, t2>::~hashMap()
{
    // Deallocates each note and node link
    for (int i = 0; i < size; i++)
    {
        if (table[i] != NULL)
        {
            if (table[i]->link != NULL)
            {
                delete table[i]->link;
                table[i]->link = NULL;
            }
            delete table[i];
            table[i] = NULL;
        }
        else if(table[i] == NULL)
        {
            delete table[i];
            table[i] = NULL;
        }
    }
    delete[] table;
    table = NULL;

    // Deallocates the head
    while (head != NULL)
    {
        iteratorPair * del;
        del = head;
        head = head->link;
        delete del;
        del = NULL;
    }
}

// Function: [] OPERATOR
template <typename t1, typename t2>
t2& hashMap<t1, t2>::operator[](t1 key)
{
    // Calculcates the load Size, its its over 0.5 call resize
    double loadSize = static_cast<double>(items)/static_cast<double>(size);
    if (loadSize >= 0.5 )
        resize();

    // Save the ascii value of the key into x
    int x = h(key);

    // Create hashPair and iteratorPair pointer
    hashPair * i;
    iteratorPair * j;

    // Sets j to head and does to the end of head
    if (head != NULL)
    {
        j = head;
        for (head; head != NULL; head= head->link )
            j = j->link;
    }
    else
        j = head;
    
    // Sets i to table
    i = table[x];

    // bool is set to false
    bool a = false;

    // Loop to insert/ search
    while (true)
    {
        // If i is NULL add a node
        if (i == NULL)
        {
            // Creates a new hashPair object and has the key and value set
            i = new hashPair;
            i->key = key;
            i->value = t2();
            
            // Set the next node to null 
            if (a == true)
            {
                table[x]->link = i;
                table[x]->link->link = NULL;
            }
            else 
            {
                table[x] = i;
                table[x]->link = NULL;
            }
            
            // Creates a new iteratorPair object and has the key and value set
            // Set the next node to null 
            j = new iteratorPair;
            j->key = &(i->key);
            j->value = &(i->value);
            j->link = NULL;
            // If it reached the second node, increment items
            if (a==true)
                items++;

            // Set a back to false
            a = false;

            delete j;
            // Return the valu eof the current node
            return i->value;
        }
        // If the key was found return the value of the current node
        if (i->key == key)
            return i->value;

        // If its at the second node then resize x, set i to new table[x], and set the bool to false
        //      else go to the next node and set the bool to true
        if (a==true)
        {
            x = (x + 1) % size;
            i = table[x];
            a = false;
        }
        else
        {
            i = table[x]->link;
            a = true;
        }
    }
}

// Function: begin()
template <typename t1, typename t2>
typename hashMap<t1, t2>::iterator hashMap<t1, t2>::begin() const
{
    // Creates an iteratorPair object, sets it to head, and returns it
    iteratorPair * begining;
    begining = head;
    return begining;
}

// Function end()
template <typename t1, typename t2>
typename hashMap<t1, t2>::iterator hashMap<t1, t2>::end() const
{
    // Creates an iteratorPair object, sets it to null, and returns it
    iteratorPair * aNull;
    aNull = NULL;
    return aNull;
}

// Function: resize()
template <typename t1, typename t2>
void hashMap<t1, t2>::resize()
{
    // Creates a new hashPair object for the new table
    hashPair ** oldTable = table;
    
    // Saves the old size into oldSize and new size into newSize
    int oldSize = size;
    int newSize = size * 2;

    // Creates a new table with the new size
    table = new hashPair*[newSize];

    // Deallocates the head
    iteratorPair * del;
    while (head != NULL)
    {
        del = head;
        head = head->link;
        delete del;
        del = NULL;
    }

    // Creates a new hashPair object and sets the size to newSize
    hashPair * i;
    size = newSize;

    // Loop though oldTable and add all nodes to the new table id they're not NULL
    for (int j = 0; j < oldSize; j++)
    {
        
        if (oldTable[j] != NULL)
        {
            if (oldTable[j]->link != NULL)
            {
                i = oldTable[j]->link;
                (*this)[i->key] = i->value;
            }
            i = oldTable[j];
            (*this)[i->key] = i->value;
        }
        else if (oldTable[j] == NULL)
        {
            continue;
        }
    }

    // Deallocate oldTable
    for (int i = 0; i < oldSize; i++)
    {
        if (oldTable[i] != NULL)
        {
            if (oldTable[i]->link != NULL)
            {
                delete oldTable[i]->link;
                oldTable[i]->link = NULL;
            }
            delete oldTable[i];
            oldTable[i] = NULL;
        }
        else if(oldTable[i] == NULL)
        {
            delete oldTable[i];
            oldTable[i] = NULL;
        }
    }
    delete[] oldTable;
    oldTable = NULL;
}

// Function: h()
template <typename t1, typename t2>
int hashMap<t1, t2>::h(std::string key) const
{
    // Initialize variables
    int a = 0;
    int b = 0;

    // Loop though key and add the ascii of all the chars
    for (int i = 0; i <= key.length(); i++)
    {
        a = int(key[i]);
        b += a;
    }
    // Get the remainder and return it
    b = b % size;
    return b;
}

// Function: Default contructor iterator()
template <typename t1, typename t2>
hashMap<t1, t2>::iterator::iterator()
{
    // Sets element to NULL;
    element = NULL;
}

// Function: Contructor iterator()
template <typename t1, typename t2>
hashMap<t1, t2>::iterator::iterator(iteratorPair * p)
{
    // Sets element with the address in p
    element = p;
}

// Function: ++ Operator
template <typename t1, typename t2>
const typename hashMap<t1, t2>::iterator& hashMap<t1, t2>::iterator::operator++(int)
{
    // Goes to the next element and returns it
    element = element->link;
    return * this;
}

// Function: == Operator
template <typename t1, typename t2>
bool hashMap<t1, t2>::iterator::operator==(const hashMap<t1, t2>::iterator& rhs) const
{
    // Returns true if equal, and false if not equal
    if (this->element == rhs.element)
        return true;
    else
        return false;
}

// Function: != Operator
template <typename t1, typename t2>
bool hashMap<t1, t2>::iterator::operator!=(const hashMap<t1, t2>::iterator& rhs) const
{
    // Returns true if not equal, and false if equal
    if (this->element != rhs.element)
        return true;
    else
        return false;
}

// Function: first()
template <typename t1, typename t2>
t1 hashMap<t1, t2>::iterator::first()
{
    // Returns the address to the element's key
    return *(element->key);
}

// Function: second()
template <typename t1, typename t2>
t2 hashMap<t1, t2>::iterator::second()
{
    // Returns the address to the element's value
    return *(element->value);

}

// struct for name and party
struct something
{
    std::string name;
    std::string party;
};

int main ()
{
    // File stuff
    std::string filename;
    std::ifstream infile;

    // Number of rounds and candidates
    std::string roundString;
    std::string canString;
    int roundNum = 0;
    int canNum = 0;

    // Candidate Names and parties
    //std::string canName;
    std::string canParty;


    // Prompts the user to enter a file
    std::cout << "Enter filename: ";
    std::cin >> filename;
    infile.open(filename);

    // retrives the number of rounds and converts it to an int
    getline(infile, roundString);
    roundNum = std::stoi(roundString);

    // Loops for the number of rounds of voting
    for(int i = 0; i < roundNum; i++)
    {
        // other variables
        std::string votesString;
        int votesNum = 0;
        std::string validVote;
        int largestVote = 0;
        int tieVote = 0;
        std::string winnerName;
        std::string winningParty;
        bool tie = false;
        std::vector<something> myVector;

        // retrives the number of candidates and converts it to an int
        getline(infile, canString);
        canNum = std::stoi(canString);
        std::string canName[canNum];

        // Creates  hashmap ;
        hashMap<std::string, int> nameAndVotes;
        
        // Loops to get the Candidate Name and their affiliated Party
        //     Sets the hashmap and vextor
        for (int j = 0; j < canNum; j++)
        {
            getline(infile, canName[j]);
            getline(infile, canParty);
            
            // Puts the name and party into a vector
            myVector.push_back(something());
            myVector[j].name = canName[j];
            myVector[j].party = canParty;
        }

        // Gets the number of votes
        getline(infile, votesString);
        votesNum = std::stoi(votesString);

        // Gets the vote and adds one to the candidate
        for (int j = 0; j < votesNum; j++)
        {
            getline(infile, validVote);
            nameAndVotes[validVote]++;
        }

        // Loops through the votes for every candidate to find the winner, or if there is a tie
        for (int j = 0; j< canNum; j++)
        {
            if (nameAndVotes[canName[j]] > largestVote)
            {
                largestVote = nameAndVotes[canName[j]];
                winnerName = canName[j];
            }
            else if (nameAndVotes[canName[j]] == largestVote)
            {
                tie = true;
                tieVote = largestVote;
            }
        }

        // Uses vector to look for the party of the winning candidate
        for (int j = 0; j< canNum; j++)
        {
            if ( myVector[j].name == winnerName)
                winningParty = myVector[j].party;
        }
        
        // If there is a tie and its bigger than or equal to the largestVote then say tie
        //      else say who won
        if ((tie == true) && (tieVote >= largestVote))
            std::cout << "Case " << i+1 << " Results: Tie " << std::endl;
        else
            std::cout << "Case " << i+1 << " Results: " << winningParty <<std::endl;

        tie = false;
    }
    // Closes the file and returns 0
    infile.close();
    return 0;
}