#pragma once
#include <iostream>

class CommandList
{
public:

	enum CommandType
	{
		Advance,
		Turn,
	};
	struct Command
	{
		CommandType type = Advance;
		float originalValue = 0;
		float currentValue = 0;
	};

	Command* cmd = {};
	CommandList* next = nullptr;
	CommandList* head = nullptr;

	CommandList(Command* _cmd);
	CommandList(CommandType _type, float _val);
	CommandList(CommandType _type, float _val, CommandList* _next);

	CommandList* PushFirst(Command* _cmd);
	CommandList* PushBack(Command* _cmd);

	CommandList* RemoveFirst();

	Command* CreateCommand(CommandType _type, float value);

	void PrintList();

};


