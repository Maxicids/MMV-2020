#pragma once
#include "LT.h"
#include "IT.h"
#include "PolishNotation.h"
#include <stack>
#include <queue>
#include <string>
#include <iostream>
#include "LexAnalize.h"
namespace Converter {
	void ToPolish(LexAnalysis::Table table)
	{
		for (int i = 0; i < table.lextable.size; i++) {
			if (table.lextable.table[i].lexema == LEX_EQUAL && table.lextable.table[i].polish == true)
			{
				PolishNotation(i + 1, table.lextable, table.idtable);
			}
		}
	}

	void Show(LexAnalysis::Table table)
	{
		for (int i = 0; i < table.lextable.size; i++) 
		{
			cout << table.lextable.table[i].lexema << " " << table.lextable.table[i].idxTI << endl;
		}
	}


	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable) {
		std::stack<LT::Entry> stack;
		std::vector<LT::Entry>ResultingString;
		LT::Entry temp;
		bool isCompleted = false;
		bool functionflag = false;
		int paramcounter = 0;
		int currentLexTableLine;
		int functionIndexTI;
		for (int i = lextable_pos; ; i++)
		{
			temp = LT::GetEntry(lextable, i);
			currentLexTableLine = temp.line;

			if (temp.lexema == LEX_ID || temp.lexema == LEX_LITERAL || temp.lexema == LEX_OUT || temp.lexema == LEX_POW || temp.lexema == LEX_MAXNUM)
			{
				if (lextable.table[i].idxTI != -1 && (idtable.table[lextable.table[i].idxTI].idtype == IT::F
					|| idtable.table[lextable.table[i].idxTI].idtype == IT::S)) {
					functionflag = true;
					functionIndexTI = lextable.table[i].idxTI;
				}
				else 
				ResultingString.push_back(temp);
				continue;
			}
			if (temp.lexema == LEX_OPERATOR) {
				if (stack.empty()) {
					stack.push(temp);
				}
				else { 
					while (!stack.empty() && temp.priority <= stack.top().priority) {
						ResultingString.push_back(stack.top());
						stack.pop();
					}
					stack.push(temp);
					if (temp.priority > stack.top().priority) {
						stack.push(temp);
					}
				}
				continue;
			}
			if (temp.lexema == LEX_AND) {
				paramcounter++;
				while (stack.top().lexema == LEX_OPERATOR) {
					ResultingString.push_back(stack.top());
					stack.pop();
				}
				continue;
			}

			if (temp.lexema == LEX_LEFTBRACKET || temp.lexema == LEX_LEFTTHESIS) {
				stack.push(temp);
				continue;
			}

			if (temp.lexema == LEX_RIGHTTHESIS) {
				while (stack.top().lexema != LEX_LEFTTHESIS) {
						ResultingString.push_back(stack.top());
						stack.pop();
					}
					stack.pop();
				if (functionflag) {
					ResultingString.push_back({ LEX_DOG, currentLexTableLine, functionIndexTI });
					ResultingString.push_back(LT::Entry{ (unsigned char)(paramcounter + 1 + '0'), currentLexTableLine, -1 });
					functionflag = false;
				}
				continue;
			}


			if (temp.lexema == LEX_RIGHTBRACKET) {
				while (stack.top().lexema != LEX_LEFTBRACKET) {
					ResultingString.push_back(stack.top());
					stack.pop();
				}
				stack.pop();
				continue;
			}

			if (temp.lexema == LEX_POINT) {
				isCompleted = true;
			}

			if (isCompleted) {
				while (!stack.empty()) {
					ResultingString.push_back(stack.top());
					stack.pop();
				}
				int i = lextable_pos;
				int j = 0;
				for (; lextable.table[i].lexema != LEX_POINT; i++, j++) {
					if (j < ResultingString.size())
						lextable.table[i] = ResultingString[j];
					else if (j == ResultingString.size()) {
						lextable.table[i] = { LEX_POINT, lextable.table[i].line, -1 };

					}
					else {
						for (int k = i; k > lextable_pos + ResultingString.size(); k--)
							lextable.table[k] = { '\0', lextable.table[k].line , -1 };
					}
				}
				if (j != ResultingString.size()) 
					lextable.table[i] = { '\0', lextable.table[i].line , -1 };
				return true;
			}
		}
		return false;
	}
}