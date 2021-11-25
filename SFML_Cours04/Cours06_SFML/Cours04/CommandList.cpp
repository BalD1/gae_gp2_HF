#include "CommandList.hpp"

CommandList::CommandList(CommandType _type, float _val, float _speed)
{
	cmd = new Command();
	cmd->type = _type;
	cmd->currentValue = cmd->originalValue = _val;
	cmd->speed = _speed;

	head = this;
}

CommandList::CommandList(CommandType _type, float _val, float _speed, CommandList* _next)
{
	cmd = new Command();
	cmd->type = _type;
	cmd->currentValue = cmd->originalValue = _val;
	cmd->speed = _speed;

	next = _next;
	head = this;
}

const char* CommandList::ConvertEnumToStr(int idx)
{
	const char* tmp(StrCommandType[idx]);
	return tmp;
}

CommandList* CommandList::PushFirst(Command* _cmd)
{
	CommandList* newNode = new CommandList(_cmd);
	newNode->next = head;
	head = newNode;

	return head;
}

CommandList* CommandList::PushBack(Command* _cmd)
{
	if (head == nullptr)
	{
		head = new CommandList(_cmd);
		return head;
	}
	CommandList* node = head;
	while (node->next != nullptr)
	{
		node = node->next;
	}
	node->next = new CommandList(_cmd);

	return node;
}

CommandList* CommandList::RemoveFirst()
{
	if (head == nullptr)
		return nullptr;
	if (head->next == nullptr)
		return nullptr;

	CommandList* nextNode = head->next;
	head = nextNode;
	head->next = nextNode->next;
	return head;
}

void CommandList::CleanList()
{
	if (this == nullptr)
		return;
	CommandList* curr = head;
	CommandList* n = nullptr;
	while (curr != nullptr)
	{
		n = curr->next;
		free(curr);
		curr = n;
	}
	head = nullptr;
}


CommandList::CommandList(Command* _cmd)
{
	cmd = _cmd;

	head = this;
}

CommandList::Command* CommandList::CreateCommand(CommandType _type, float value)
{
	Command* newCmd = new Command();
	newCmd->type = _type;
	newCmd->currentValue = newCmd->originalValue = value;

	return newCmd;
}

void CommandList::PrintList()
{
	if (head == nullptr)
	{
		printf("List was empty");
		return;
	}
	CommandList* newNode = head;

	const char* cmdType = "";
	int tIndex = -1;
	while (newNode != nullptr)
	{
		cmdType = "Undefinied in print";
		tIndex = static_cast<CommandType>(newNode->cmd->type);
		if (tIndex == 0)
			cmdType = "Advance";
		else if (tIndex == 1)
			cmdType = "Turn";
		else if (tIndex == 2)
			cmdType = "PenUp";
		else if (tIndex == 3)
			cmdType = "PenDown";

		printf(" { %s : %0.2f / %0.2f } ", cmdType, newNode->cmd->currentValue, newNode->cmd->originalValue);
		if (newNode->next != nullptr)
			printf(" --->");

		newNode = newNode->next;
	}
	printf("\n");
	delete(newNode);
}
