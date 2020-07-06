#include "lsystem.h"
//RULESET
//  ω: A	
//	p1 : A →[&FL!A]/////’[&FL!A]///////’[&FL!A]
//	p2 : F → S ///// F
//	p3 : S → F L
//	p4 : L →[’’’∧∧{ -f + f + f - | -f + f + f }]
//

lsystem::lsystem()
{
	axiom = "A";
	axiom2 = "F";
	ruleSet[0] = "[&FL!A]/////’[&FL!A]///////’[&FL!A]";
	ruleSet[1] = "S ///// F";

	ruleSet[2] = "F L";
	ruleSet[3] = "[’’’∧∧{ -f + f + f - | -f + f + f }]";
	rule = "FF+[+F-F-F]-[-F+F+F]";
	//rule = "F[+F]F[-F][F]";

	next = "";
}


lsystem::~lsystem()
{
}

string lsystem::lsys()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0;j < axiom.length();j++)
		{
			if (axiom.at(j) == 'A')
			{
				next += ruleSet[0];
			}
			else if (axiom.at(j) == 'F')
			{
				next += ruleSet[1];
			}
			else if (axiom.at(j) == 'S')
			{
				next += ruleSet[2];
			}
			else if (axiom.at(j) == 'L')
			{
				next += ruleSet[3];
			}
			else
			{
				next += axiom.at(j);
			}
		}
		axiom = next;
		next.clear();
	}
	return axiom;
}

string lsystem::lsys2()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < axiom2.length(); j++)
		{
			 if (axiom2.at(j) == 'F')
			{
				 next += rule;
			}
			 else
			{
				next += axiom2.at(j);
			}
		}
		axiom2 = next;
		next.clear();
	}
	return axiom2;
}
