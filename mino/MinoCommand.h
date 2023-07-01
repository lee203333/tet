#pragma once

#include"SingleMino.h"
#include"StackMino.h"

enum Action 
{rotate, move_x, move_y};

class Command
{
public:
	Command() {}
	virtual ~Command() {}
	virtual bool call(Action act, int amount) {		return true;	}
};

class SingleMinoCommand :public Command
{
	StackMino& stack;
	StackModifier& stackM;
	SingleMino *singleMino;
public:
	SingleMinoCommand(SingleMino *single_mino, StackMino& stackMino, StackModifier& stackModifier)
		: singleMino(single_mino), stack(stackMino), stackM(stackModifier) {} 
	void SetSingleMino(SingleMino *single_mino);

	bool call(Action act, int amount) const;
};