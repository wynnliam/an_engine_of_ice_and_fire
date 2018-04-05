#ifndef FACTION_H
#define FACTION_H

namespace AEOIAF_AIBehavior
{
    //Use this to store/find allies and enemies
    class FactionTable
    {
        public:
            FactionTable(); //Sets table size to a default of 13
            FactionTable(int newSize);
            FactionTable(const FactionTable& toCopy);
            ~FactionTable();

            int GetTableSize() const { return tableSize; }

            //Adds a faction to the table
            void Add(const class Faction& toAdd);
            //Tries to remove a faction from the list, returns 0 if fail
            int Remove(int toRemove);
            //Returns true if lookFor is found, otherwise returns false
            bool Contains(int lookFor) const;
            //Copies the properties in toCopy into this faction table
            void Copy(const FactionTable& toCopy);
            //Clears the entire table
            void ClearAll();
            //Displays the data in the table
            void Display() const;

        private:
            /*RECURSIVE FUNCTIONS*/
            int Remove(struct FactionNode*& head, int toRemove);
            bool Contains(struct FactionNode*& head, int loofFor) const;
            //Recursively copies a single LLL in the table
            void Copy(struct FactionNode*& dest, struct FactionNode* source);
            //Recursively clears a single chain in the table
            void Clear(struct FactionNode*& head);

            struct FactionNode** table;
            int tableSize; //The number of chains we will store
    };

    struct FactionNode
    {
        FactionNode();
        ~FactionNode();

        int data; //Don't delete! It won't allocate anything!
        FactionNode* next;
    };

    class Faction
    {
        public:
            Faction();
            Faction(int newID) : id(newID) { }
            Faction(const Faction& toCopy);
            virtual ~Faction();

            virtual Faction& operator = (const Faction& toCopy);

            int GetID() const { return id; }
            void SetID(int val) { id = val; }

            virtual void Copy(const Faction& toCopy);

            void AddAlly(Faction& toAdd);
            void RemoveAlly(Faction& toRemove);
            bool HasAlly(int toFind) const;

            void AddEnemy(Faction& toAdd);
            void RemoveEnemy(Faction& toRemove);
            bool HasEnemy(int toFind) const;

        private:
            int id; //A simple int is all that is needed to represent a faction

            FactionTable allies, enemies;
    };
}

#endif // FACTION_H
