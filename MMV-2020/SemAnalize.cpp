#include "SemAnalize.h"
#include "LT.h"

namespace Semantics
{
	void Analize(LexAnalysis::Table lex, Log::LOG log)
	{
		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexema)
			{

			case LEX_EQUAL:
			{
				IT::IDDATATYPE lefttype = lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype;
				IT::IDDATATYPE righttype = lefttype;
				int y = i + 1;
				for (; lex.lextable.table[y].lexema != LEX_POINT;)
				{
					if (lex.lextable.table[y].lexema == LEX_LEFTTHESIS)
					{
						while (lex.lextable.table[y].lexema != LEX_RIGHTTHESIS)
						{
							y++;
						}
						y++;
						continue;
					}
					if (lex.lextable.table[y].lexema != LEX_OPERATOR && lex.lextable.table[y].lexema != LEX_LEFTBRACKET && lex.lextable.table[y].lexema != LEX_RIGHTBRACKET)
					{
						if (righttype != lex.idtable.table[lex.lextable.table[y].idxTI].iddatatype)
						{
							Log::WriteError(log, Error::geterrorin(320, lex.lextable.table[i].line, -1));
						}
						else if (lex.lextable.table[y].lexema == LEX_MAXNUM || lex.lextable.table[y].lexema == LEX_POW)
						{
							if (lex.lextable.table[i].polish != true) {
								lex.lextable.table[i].polish = true;
							}
							righttype = lex.idtable.table[lex.lextable.table[y].idxTI].iddatatype;
							y = y + 6;
						}
						else
						{
							righttype = lex.idtable.table[lex.lextable.table[y].idxTI].iddatatype;
							y++;
						}
					}
					else
					{
						if (lex.lextable.table[i].polish != true) {
							lex.lextable.table[i].polish = true;
						}
						y++;
					}
				}
				if (lefttype != righttype)
				{
					Log::WriteError(log, Error::geterrorin(318, lex.lextable.table[i].line, -1));
				}
				
				if (lex.lextable.table[i - 3].lexema == LEX_VAR)// var int r = func[r]
				{
					y = i + 1;
					for (; lex.lextable.table[y].lexema != LEX_POINT; y++)
					{
						if (lex.lextable.table[y].lexema == LEX_ID)
						{
							if (lex.idtable.table[lex.lextable.table[y].idxTI].id == lex.idtable.table[lex.lextable.table[i - 1].idxTI].id)
							{
								Log::WriteError(log, Error::geterrorin(301, lex.lextable.table[i].line, -1));
							}
						}
					}
				}

				break;
			}

			case LEX_POW:
			case LEX_MAXNUM:
			case LEX_ID://параметры функции
			{
				if ((lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::F || lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::S)//функция или библиотечная
					&& lex.lextable.table[i - 2].lexema != LEX_FUNCTION)
				{
					IT::Entry entry = lex.idtable.table[lex.lextable.table[i].idxTI];
					int numberOfPar = 0;
					for (int j = i + 2; lex.lextable.table[j].lexema != LEX_RIGHTTHESIS; j++)
					{
						if (lex.lextable.table[j].lexema == LEX_ID || lex.lextable.table[j].lexema == LEX_LITERAL)
						{
							
							if (numberOfPar > entry.value.params.count)
							{
								Log::WriteError(log, Error::geterrorin(316, lex.lextable.table[j].line, -1));
							}
							if (lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype != entry.value.params.types[numberOfPar])
							{
								Log::WriteError(log, Error::geterrorin(315, lex.lextable.table[j].line, -1));
							}
							numberOfPar++;
						}

					}
					if (numberOfPar < entry.value.params.count) {
						Log::WriteError(log, Error::geterrorin(317, lex.lextable.table[i].line, -1));
					}
				}
				if (lex.idtable.table[lex.lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				{
					int y = i + 1;
					for (; lex.lextable.table[y].lexema != LEX_POINT; y++)
					{
						if (lex.lextable.table[y].lexema == LEX_OPERATOR)
						{
							if (lex.lextable.table[y].operation != LT::OPER::PLUS)
							{
								Log::WriteError(log, Error::geterrorin(323, lex.lextable.table[i].line, -1));
							}
						}
					}
				}
				if (lex.idtable.table[lex.lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::BOOL)
				{
					int y = i + 1;
					for (; lex.lextable.table[y].lexema != LEX_POINT; y++)
					{
						if (lex.lextable.table[y].lexema == LEX_RIGHTTHESIS)
						{
							break;
						}
						if (lex.lextable.table[y].lexema == LEX_LOGOPERATOR)
						{
							if (lex.lextable.table[y].operation != LT::OPER::EQU || lex.lextable.table[y].operation != LT::OPER::NOEQU)
							{
								Log::WriteError(log, Error::geterrorin(323, lex.lextable.table[i].line, -1));
							}
						}
					}
				}
				break;
			}



			case LEX_FUNCTION:
			{
				IT::IDDATATYPE typeOfFunction = lex.idtable.table[lex.lextable.table[i + 2].idxTI].iddatatype;
				for (int y = i; y < lex.lextable.size; y++)
				{
					if (lex.lextable.table[y].lexema == LEX_RETURN)
					{
						IT::IDDATATYPE typeOfRetern = lex.idtable.table[lex.lextable.table[y + 2].idxTI].iddatatype;
						if (typeOfFunction != typeOfRetern)
						{
							Log::WriteError(log, Error::geterrorin(313, lex.lextable.table[i].line, -1));
						}
						break;
					}
				}
				break;
			}

			case LEX_LOGOPERATOR:
			{
				IT::IDDATATYPE lefttype = lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype;
				IT::IDDATATYPE righttype = lex.idtable.table[lex.lextable.table[i + 1].idxTI].iddatatype;
				if ((lefttype == IT::IDDATATYPE::STR || righttype == IT::IDDATATYPE::STR) || lefttype != righttype)
				{
					Log::WriteError(log, Error::geterrorin(322, lex.lextable.table[i].line, -1));
				}

				break;
			}
			}
		}
	}
	//void ToPolish(LexAnalysis::Table lex, Log::LOG log)
	//{
	//	for (int i = 0; i < lex.lextable.size; i++)
	//	{
	//		if (lex.lextable.table[i].lexema == LEX_EQUAL && lex.lextable.table[i].polish == true)
	//		{
	//			std::string result;
	//			LT::Entry* resultArr = new LT::Entry[MAX_PARAM_POLISH];
	//			std::vector<LT::Entry> stack;

	//			for (int y = i + 1, num = 0; lex.lextable.table[y].lexema != LEX_POINT; y++)
	//			{
	//				std::string stackString;

	//				if (isalpha(lex.lextable.table[y].lexema) || lex.lextable.table[y].lexema == '_' 
	//					|| lex.lextable.table[y].lexema == '[' || lex.lextable.table[y].lexema == ']')
	//				{
	//					resultArr[num] = lex.lextable.table[y];
	//					num++;
	//				}
	//				else if (Converter::isOperations(lex.lextable.table[y].lexema))
	//				{
	//					if (stack.empty() || stack.back().lexema == '(')
	//					{
	//						stack.push_back(lex.lextable.table[y]); // добавление в конец
	//					}
	//					else if (!stack.empty() && Converter::isOperations(stack.back().lexema))
	//					{
	//						for (std::vector<LT::Entry>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
	//						{
	//							if (Converter::Polish::priority(lex.lextable.table[y].lexema) <= Converter::Polish::priority(*i))
	//							{
	//								resultArr[num] = lex.lextable.table[y];
	//								num++;
	//								i = std::vector<LT::Entry>::reverse_iterator(stack.erase(i.base() - 1));
	//							}
	//							else
	//							{
	//								break;
	//							}
	//						}
	//						stack.push_back(lex.lextable.table[y]);
	//					}
	//				}
	//				else if (lex.lextable.table[y].lexema == '(')
	//				{
	//					stack.push_back(lex.lextable.table[y]);
	//				}
	//				else if (lex.lextable.table[y].lexema == ')')
	//				{
	//					for (std::vector<LT::Entry>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
	//					{
	//						if (*i != '(')
	//						{
	//							//result += *i;
	//							resultArr[num] = i;
	//							num++;
	//							i = std::vector<LT::Entry>::reverse_iterator(stack.erase(i.base() - 1));//i.base() - 1 прямой итератор
	//						}
	//						else
	//						{
	//							stack.erase(i.base() - 1);
	//							break;
	//						}
	//					}
	//				}
	//			}
	//			for (std::vector<char>::const_reverse_iterator i = stack.crbegin(); i != stack.crend(); ++i)
	//			{
	//				result += *i;
	//			}
	//		}
	//	}
	//}
	//void ToPolish(LexAnalysis::Table lex, Log::LOG log)
	//{
	//	for (int i = 0; i < lex.lextable.size; i++)
	//	{
	//		if (lex.lextable.table[i].lexema == LEX_EQUAL && lex.lextable.table[i].polish == true)
	//		{
	//			//lex.lextable.table[i]
	//			std::string result;
	//			std::vector<LT::Entry> stack;
	//			for (int y = i + 1, num = 0; lex.lextable.table[y].lexema != LEX_POINT; y++)
	//			{
	//				std::string stackString;

	//				if (lex.idtable.table[lex.lextable.table[y].idxTI].idtype == IT::V)
	//				{
	//					lex.lextable.table[i + 1] = lex.lextable.table[y];
	//					i++;
	//					//result += ch;
	//				}
	//				else if (Converter::isOperations(lex.lextable.table[y].lexema))
	//				{
	//					if (stack.empty() || stack.back() == '(')
	//					{
	//						stack.push_back(ch); // добавление в конец
	//					}
	//					else if (!stack.empty() && isOperations(stack.back()))
	//					{
	//						for (std::vector<char>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
	//						{
	//							if (priority(ch) <= priority(*i))
	//							{
	//								result += *i;
	//								i = std::vector<char>::reverse_iterator(stack.erase(i.base() - 1));
	//							}
	//							else
	//							{
	//								break;
	//							}
	//						}
	//						stack.push_back(ch);
	//					}
	//				}
	//				else if (ch == '(')
	//				{
	//					stack.push_back(ch);
	//				}
	//				else if (ch == ')')
	//				{
	//					for (std::vector<char>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
	//					{
	//						if (*i != '(')
	//						{
	//							result += *i;
	//							i = std::vector<char>::reverse_iterator(stack.erase(i.base() - 1));//i.base() - 1 прямой итератор
	//						}
	//						else
	//						{
	//							stack.erase(i.base() - 1);
	//							break;
	//						}
	//					}
	//				}
	//			}
	//			for (std::vector<char>::const_reverse_iterator i = stack.crbegin(); i != stack.crend(); ++i)
	//			{
	//				result += *i;
	//			}

	//				
	//		}
	//			/*std::string str;
	//			std::string par[MAX_PARAM_POLISH];
	//			for (int y = i + 1, num = 0; lex.lextable.table[y].lexema != LEX_POINT; y++, num++)
	//			{
	//				if (lex.lextable.table[y].operation == LT::PLUS) {
	//					str += '+';
	//					par[num] = '+';
	//				}
	//				else if (lex.lextable.table[y].operation == LT::MINUS) {
	//					str += '-';
	//					par[num] = '-';
	//				}
	//				else if (lex.lextable.table[y].operation == LT::MUL) {
	//					str += '*';
	//					par[num] = '*';
	//				}
	//				else if (lex.lextable.table[y].operation == LT::DIR) {
	//					str += '/';
	//					par[num] = '/';
	//				}
	//				else if (lex.lextable.table[y].idxTI != LT_TI_NULLIDX) {
	//					str += (char *)lex.idtable.table[lex.lextable.table[y].idxTI].id;
	//					par[num] = (char*)lex.idtable.table[lex.lextable.table[y].idxTI].id;
	//				}
	//				else {
	//					str += lex.lextable.table[y].lexema;
	//				}
	//			}
	//			std::string newStr = Converter::Polish::convert(str);
	//			std::cout << "\tSource:\t" << str << std::endl;
	//			for (int j = 0; par[j] ; j++) {

	//			}
	//			std::cout << "\tResult:\t" << newStr << std::endl << std::endl;
	//			for (int y = i + 1; lex.lextable.table[y].lexema != LEX_POINT; y++)
	//			{

	//			}*/
	//			/*bool bl = true;
	//			for (int j = i; strcmp(totalLexTable.table[j].lexema, ";") != 0; ++j) {
	//				if (bl) {
	//					for (int m = 0; m < newStr.length(); j++, m++) {
	//						*totalLexTable.table[j].lexema = newStr[m];
	//					}
	//					bl = false;
	//				}
	//				*totalLexTable.table[j].lexema = '\0';
	//			}
	//			for (int y = i + 1; lex.lextable.table[y].lexema != LEX_POINT; y++)
	//			{
	//				cout << lex.lextable.table[y].lexema << " ";
	//			}
	//			cout << endl;*/
	//		}
	//	}
	
}
