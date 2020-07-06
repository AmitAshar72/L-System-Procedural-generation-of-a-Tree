#pragma once
#include <string>
using namespace std;
class lsystem
{
public:
	lsystem();
	~lsystem();

public:
	string axiom, axiom2, rule, next;
	string lsys(), lsys2();
	int i, j;
	string ruleSet[4];
};