//Liam "AFishyFez" Wynn, 5/13/2015, AEOIAF: Factions

/*
Here I implement all functions related to factions (that is,
the Faction class itself, and eventurally the FactionTree).
*/

#include "Faction.h"
#include "../../Utilities/Color_Utilities/AEOIAFColor.h"
#include <iostream>
#include <cstring>

using namespace AEOIAF_AIBehavior;
using namespace AEOIAF_Content;
using namespace std;

/*FACTION IMPLEMENTATIONS*/
Faction::Faction()
{
    id = 0;
}

Faction::Faction(const Faction& toCopy)
{
    Copy(toCopy);
}

Faction::~Faction()
{
}

Faction& Faction::operator = (const Faction& toCopy)
{
    Copy(toCopy);
    return *this;
}

void Faction::Copy(const Faction& toCopy)
{
    id = toCopy.id;
	allies.Copy(toCopy.allies);
	enemies.Copy(toCopy.enemies);
}

void Faction::AddAlly(Faction& toAdd)
{
    allies.Add(toAdd.GetID());
    toAdd.allies.Add(id);
}

void Faction::RemoveAlly(Faction& toRemove)
{
    allies.Remove(toRemove.GetID());
    toRemove.allies.Remove(id);
}

bool Faction::HasAlly(int toFind) const
{
    return allies.Contains(toFind);
}

void Faction::AddEnemy(Faction& toAdd)
{
    enemies.Add(toAdd.GetID());
    toAdd.enemies.Add(id);
}

void Faction::RemoveEnemy(Faction& toRemove)
{
    enemies.Remove(toRemove.GetID());
    toRemove.enemies.Remove(id);
}

bool Faction::HasEnemy(int toFind) const
{
    return enemies.Contains(toFind);
}

/*FACTION TABLE IMPLEMENTATIONS*/
FactionTable::FactionTable()
{
    tableSize = 13;
    table = new FactionNode*[tableSize];

    for(int i = 0; i < tableSize; ++i)
        table[i] = NULL;
}

FactionTable::FactionTable(int newSize)
{
    //Use 13 as a default if the input is bad
    tableSize = newSize < 1 ? 13 : newSize;
    table = new FactionNode*[tableSize];

    for(int i = 0; i < tableSize; ++i)
        table[i] = NULL;
}

FactionTable::FactionTable(const FactionTable& toCopy)
{
    table = NULL; //Set this so we don't try to deallocate garbage in Copy
    Copy(toCopy);
}

FactionTable::~FactionTable()
{
    if(table)
    {
        ClearAll(); //Remove all elements in the table
        delete[] table;
        table = NULL;
    }
}

//First make sure the table is not null and the size
//is valid. Then add the faction to the table by modding
//it's id by the table size then adding a node to the resulting
//LLL
void FactionTable::Add(const Faction& toAdd)
{
    if(!table || tableSize < 1)
        return;

    int data = toAdd.GetID(); //What we store in a faction node
    int tableIndex = data % tableSize; //"Hashing" to find the right index

    //Add by appending a new node to the list in the table at tableIndex
    FactionNode* temp = new FactionNode;
    temp->data = data;
    temp->next = table[tableIndex];
    table[tableIndex] = temp;
}

//Make sure that table and tableSize are valid
//Then hash toRemove to get the right table index,
//and use that to remove toRemove
int FactionTable::Remove(int toRemove)
{
    if(!table || tableSize < 1)
        return 0;

    int tableIndex = toRemove % tableSize; //"Hashing"

    return Remove(table[tableIndex], toRemove);
}

//If head is NULL return 0. If head's data equals toRemove,
//then remove that node and return 1. Otherwise recursively call
//Remove
int FactionTable::Remove(FactionNode*& head, int toRemove)
{
    if(!head)
        return 0;

    int result; //What we will return

    if(head->data == toRemove)
    {
        FactionNode* temp = head->next;
        delete head;
        head = temp;

        result = 1;
    }

    else
        result = Remove(head->next, toRemove);

    return result;
}

//Make sure table/tableSize are good, mod
//lookFor, and then return the result of the
//recursive function
bool FactionTable::Contains(int lookFor) const
{
    if(!table || tableSize < 1)
        return 0;

    int tableIndex = lookFor % tableSize; //"Hashing"

    return Contains(table[tableIndex], lookFor);
}

//Check head, then see if head's data is the same
//as remove, otherwise call the function again
bool FactionTable::Contains(FactionNode*& head, int lookFor) const
{
    if(!head)
        return 0;

    if(head->data == lookFor)
        return true;
    else
        return Contains(head->next, lookFor);
}

//First make sure toCopy and this table are not the same.
//Then deallocate this table/clear it. Finally copy all
//properties
void FactionTable::Copy(const FactionTable& toCopy)
{
    if(this == &toCopy)
        return;

    if(table)
    {
        ClearAll(); //Remove all elements in the table
        delete[] table;
        table = NULL;
    }

    tableSize = toCopy.tableSize;
    table = new FactionNode*[tableSize];

    for(int i = 0; i < tableSize; ++i)
        Copy(table[i], toCopy.table[i]);
}

//If source is NULL, we've reached the end of the list and thus
//set dest to NULL and return. Otherwise we copy the data from source
//into a a newly allocated dest and call the function again
void FactionTable::Copy(FactionNode*& dest, FactionNode* source)
{
    if(!source)
        dest = NULL; //We've reached the end of the list and it is now time to return
    else
    {
        dest = new FactionNode;
        dest->data = source->data;

        Copy(dest->next, source->next);
    }
}

//First make sure the table/table size is valid
//Then traverse each index of the table and remove
//the list
void FactionTable::ClearAll()
{
    if(!table)
        return;

    for(int i = 0; i < tableSize; ++i)
        Clear(table[i]);
}

//If head is NULL, we are done, otherwise save
//head's next in a temp, delete head, and call
//the function again but use temp
void FactionTable::Clear(FactionNode*& head)
{
    if(!head)
        return;

    FactionNode* temp = head->next;
    delete head;
    head = temp;

    Clear(head);
}

//First make sure table and tableSize are
//valid. Then loop through each LLL and display
//their contents
void FactionTable::Display() const
{
    if(!table || tableSize < 1)
        return;

    FactionNode* current; //Use this for traversal

    for(int i = 0; i < tableSize; ++i)
    {
        cout << "Chain: " << i << endl;

        current = table[i];
        while(current)
        {
            cout << current->data << endl;
            current = current->next;
        }
    }
}

/*FACTION NODE IMPLEMENTATIONS*/
FactionNode::FactionNode()
{
    data = 0;
    next = NULL;
}

//Factions are meant to be handled elsewhere
//by deleting the data. It implies either death
//or a bunch of unneccessary copies
FactionNode::~FactionNode()
{
    data = 0;
    next = NULL;
}
