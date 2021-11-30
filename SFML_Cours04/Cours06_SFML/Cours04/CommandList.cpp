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

const char* CommandList::ConvertListToStr()
{
	std::string str = "";
	if (head == nullptr)
	{
		printf("List was empty");
		const char* chr = "";
		return chr;
	}
	CommandList* newNode = head;

	const char* cmdType = "";
	int tIndex = -1;
	while (newNode != nullptr)
	{
		cmdType = "Undefined type ";
		tIndex = static_cast<CommandType>(newNode->cmd->type);
		if (tIndex == 0)
			cmdType = "Advance";
		else if (tIndex == 1)
			cmdType = "Turn";
		else if (tIndex == 2)
			cmdType = "PenUp";
		else if (tIndex == 3)
			cmdType = "PenDown";

		str += cmdType;
		str += newNode->cmd->currentValue;
		str += newNode->cmd->originalValue;
		if (newNode->next != nullptr)
			str += '\n';

		newNode = newNode->next;
	}
	delete(newNode);
	return str.c_str();
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

void CommandList::saveCommandsInFile(const char* filePath)
{
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, filePath, "w");
	if (err != 0)
		printf("The file was not opened\n");
	else
	{
		while (this->head != nullptr && this != nullptr)
		{
			char curr[256];
			CommandList::Command* tmpCmd = this->head->cmd;
			sprintf_s(curr, "%s %d %d \n", this->ConvertEnumToStr(tmpCmd->type), (int)tmpCmd->originalValue, (int)tmpCmd->speed);
			this->head = this->RemoveFirst();
		}

		fclose(fp);
	}
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
