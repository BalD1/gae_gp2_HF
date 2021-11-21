#include "CommandList.hpp"

CommandList::CommandList(CommandType _type, float _val)
{
	cmd = new Command();
	cmd->type = _type;
	cmd->currentValue = cmd->originalValue = _val;

	head = this;
}

CommandList::CommandList(CommandType _type, float _val, CommandList* _next)
{
	cmd = new Command();
	cmd->type = _type;
	cmd->currentValue = cmd->originalValue = _val;

	next = _next;
	head = this;
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
	if (this == nullptr)
		return;
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

		printf(" { %s : %0.2f / %0.2f } ", cmdType, newNode->cmd->currentValue, newNode->cmd->originalValue);
		if (newNode->next != nullptr)
			printf(" --->");

		newNode = newNode->next;
	}
	printf("\n");
	delete(newNode);
}
