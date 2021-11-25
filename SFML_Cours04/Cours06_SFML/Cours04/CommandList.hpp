#pragma once
#include <iostream>

class CommandList
{
public:

	enum CommandType
	{
		Advance,
		Turn,
		PenUp,
		PenDown,
	};
	const char* StrCommandType[4] =
	{
		"Advance",
		"Turn",
		"PenUp",
		"PenDown",
	};

	struct Command
	{
		CommandType type = Advance;
		float originalValue = 0;
		float currentValue = 0;
		float speed = 0;
	};

	Command* cmd = {};
	CommandList* next = nullptr;
	CommandList* head = nullptr;

	CommandList(Command* _cmd);
	CommandList(CommandType _type, float _val, float _speed);
	CommandList(CommandType _type, float _val, float _speed, CommandList* _next);

	const char* ConvertEnumToStr(int idx);

	CommandList* PushFirst(Command* _cmd);
	CommandList* PushBack(Command* _cmd);

	CommandList* RemoveFirst();
	void CleanList();

	Command* CreateCommand(CommandType _type, float value);

	void PrintList();

};


