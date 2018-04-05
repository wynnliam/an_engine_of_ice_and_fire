//Liam "AFishyFez" Wynn, 11/30/2015, An Engine of Ice and Fire

/*
 An important aspect of many games is the use of
 scripted events. These are normally related to
 the story, wherein two NPC's for example are
 interacting in a way most NPC's would not.

 However, scripted events could really be anything,
 as long as you have the creativity for it.

 Here, we simply create an interface between actors
 and scripted sequences. The idea is that Script Actions
 will override the stored actor's normal behavior until
 that action is complete.

 Script Sequences are simply a queue represented as
 as circular linked list.

 The job of scripted sequences is simply to manage
 a sequence of Script Actions. The job of actually
 playing the script is handled in the level. 
*/

#ifndef AEOIAF_SCRIPT_SEQUENCE
#define AEOIAF_SCRIPT_SEQUENCE

namespace AEOIAF_Actor
{
	class Actor; //Avoid cyclic dependency
}

namespace AEOIAF_Level
{
	class Level;
}

namespace AEOIAF_ScriptedEvents
{
	//Until it is complete, the ScriptAction will override
	//the behavior of an actor
	class ScriptAction
	{
		public:
			ScriptAction();
			ScriptAction(AEOIAF_Actor::Actor* toOverride);
			ScriptAction(const ScriptAction& toCopy);
			virtual ~ScriptAction();

			AEOIAF_Actor::Actor* GetToOverride() { return toOverride; }
			void SetToOverride(AEOIAF_Actor::Actor* val) { toOverride = val; }

			bool IsComplete() { return bComplete; }

			//Copy the data in toCopy into this
			virtual void Copy(const ScriptAction& toCopy);
			//Return a copy of this
			virtual ScriptAction* GetCopy();

			//The update function that overrides the behavior of
			//toOverride
            virtual void Update(AEOIAF_Level::Level* level, float deltaTime) = 0;

		protected:
			AEOIAF_Actor::Actor* toOverride; //Who we will override
			bool bComplete; //A flag to denote if this action is finished
	};

	//Manages a single ScriptAction in the ScriptSequence queue
	struct ScriptActionNode
	{
		ScriptActionNode();
		ScriptActionNode(const ScriptActionNode& toCopy);
		~ScriptActionNode();

		//Handles setting the action safely
		void SetScriptAction(ScriptAction* val);
		//Handles copying the node safely
		void Copy(const ScriptActionNode& toCopy);

		ScriptAction* action; //The action we hold
		ScriptActionNode* next; //Pointer to the next item in the queue
	};

	//Manages a queue of ScriptActions that form the event
	class ScriptSequence
	{
		public:
			ScriptSequence();
			ScriptSequence(const ScriptSequence& toCopy);
			virtual ~ScriptSequence();

			int GetID(char*& result) const;
			int SetID(const char* val);

			bool CanRun() const { return bCanRun; }

			virtual ScriptSequence& operator= (const ScriptSequence& toCopy);
			virtual bool operator== (const ScriptSequence& compareTo) const;
			virtual bool operator== (const char* compareTo) const; 
			
			bool Equals(const ScriptSequence* compareTo) const;
			bool Equals(const char* compareTo) const;

			//Copies toCopy into this
			void Copy(const ScriptSequence& toCopy);
			//Adds a ScriptAction to the list
			void Enqueue(ScriptAction* toAdd);
			//Removes the top item from the queue
			void Dequeue();
			//Clears the entire queue
			void Clear();
			//Returns if the sequence is empty
			bool IsEmpty() const;

			//Updates the queue, assuming bCanRun is true
			virtual void Update(AEOIAF_Level::Level* level, float deltaTime);

		protected:
			//Determines if the queue should be updated (IE, updates bCanRun)
			virtual void UpdateCanRun();
			//Where we update the queue itself
			virtual void UpdateQueue(AEOIAF_Level::Level* level, float deltaTime);

			//Recursively copy toCopy into this
			void Copy(ScriptActionNode* source);

			char* id; //A unique identifier for this script (mainly used in ScriptSequenceList for levels)

			ScriptActionNode* rear; //Represent the queue as a CLL
			bool bCanRun; //A flag that denotes the conditions to run the event are met
	};
}

#endif
