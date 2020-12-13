#include "Generation.h"
#include "stdafx.h"
#include "LT.h"
using namespace std;

namespace CodeGeneration
{
	void Generation(LexAnalysis::Table table, Log::LOG log)
	{
		HEAD
			AddCodeSegm(table, log);
		FOOTER
	}

	void AddCodeSegm(LexAnalysis::Table table, Log::LOG log)
	{
		bool return_flag = false;
		bool convert_flag = false;
		for (int i = 0; i < table.lextable.size; i++)
		{
			switch (table.lextable.table[i].lexema)
			{
			case LEX_TYPE: 
			{
				if (table.lextable.table[i - 1].lexema == LEX_FUNCTION)
				{
					*(log.stream) << "static ";
				}
				if (table.idtable.table[table.lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::INT)
				{
					*(log.stream) << "byte ";
				}
				if (table.idtable.table[table.lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR)
				{
					*(log.stream) << "string ";
				}
				if (table.idtable.table[table.lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::BOOL)
				{
					*(log.stream) << "bool ";
				}
				break;
			}
			case LEX_LITERAL:
			{
				if (table.idtable.table[table.lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
				{
					*(log.stream) << table.idtable.table[table.lextable.table[i].idxTI].value.vint;
				}
				if (table.idtable.table[table.lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::BOOL)
				{
					if (table.idtable.table[table.lextable.table[i].idxTI].value.vint == 1)
					{
						*(log.stream) << "true";
						break;
					}
					*(log.stream) << "false";
				}
				if (table.idtable.table[table.lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				{
					*(log.stream) << "\"" << table.idtable.table[table.lextable.table[i].idxTI].value.vstr.str << "\"";
				}
				break;
			}
			case LEX_POW:
			{
				*(log.stream) << "standlib.Standlib.Pow";
				break;
			}
			case LEX_MAXNUM:
			{
				*(log.stream) << "standlib.Standlib.MaxNum";
				break;
			}
			case LEX_ID:
			{
				*(log.stream)  << table.idtable.table[table.lextable.table[i].idxTI].id;
			    break;
			}
			case LEX_LEFTTHESIS:
			{
				if (return_flag) {
					*(log.stream) << " ";
					break;
				}
				*(log.stream) << "(";
				break;
			}
			case LEX_RIGHTTHESIS:
			{
				if (return_flag) {
					*(log.stream) << " ";
					return_flag = false;
					break;
				}
				*(log.stream) << ")";
				break;
			}
			case LEX_LEFTBRACKET:
			{
				*(log.stream) << "(";
				break;
			}
			case LEX_RIGHTBRACKET:
			{
				*(log.stream) << ")";
				break;
			}
			case LEX_AND:
			{
				*(log.stream) << ", ";
				break;
			}
			case LEX_POINT:
			{
				if (convert_flag) {
					*(log.stream) << ")";
					convert_flag = false;
				}
				*(log.stream) << ";";
				
				break;
			}
			case LEX_LEFTBRACE:
			case LEX_BRACELET:
			{
				*(log.stream) << table.lextable.table[i].lexema;
				break;
			}
			case LEX_RETURN:
			{
				return_flag = true;
				*(log.stream) << "return";
				break;
			}
			case LEX_OUT:
			{
				*(log.stream) << "Console.WriteLine";
				break;
			}
			case LEX_HEAD:
			{
				*(log.stream) << "static void Main(string[] args)";
				break;
			}
			case LEX_CHECK:
			{
				*(log.stream) << "if ";
				break;
			}
			case LEX_OTHERWISE:
			{
				*(log.stream) << "else";
				break;
			}
			case LEX_EQUAL:
			{
				*(log.stream) << " = ";
				if (table.idtable.table[table.lextable.table[i - 1].idxTI].iddatatype == IT::IDDATATYPE::INT)
				{
					convert_flag = true;
					*(log.stream) << "(byte)(";
				}
				break;
			}
			case LEX_OPERATOR:
			{
				*(log.stream) << table.lextable.table[i].sType;
				break;
			}
			case LEX_LOGOPERATOR:
			{
				switch (table.lextable.table[i].operation)
				{
				case LT::MORE:
				{
					*(log.stream) << ">";
					break;
				}
				case LT::LESS:
				{
					*(log.stream) << "<";
					break;
				}
				case LT::LOREQU:
				{
					*(log.stream) << "<=";
					break;
				}
				case LT::MOREQU:
				{
					*(log.stream) << ">=";
					break;
				}
				case LT::EQU:
				{
					*(log.stream) << "==";
					break;
				}
				case LT::NOEQU:
				{
					*(log.stream) << "!=";
					break;
				}
				}
				break;
			}
			case LEX_NEWLINE:
			{
				*(log.stream) << "Console.WriteLine()";
				break;
			}
			}
			if (table.lextable.table[i].line != table.lextable.table[i + 1].line)
			{
				*(log.stream) << endl << "\t" << "\t";
			}
		}
	}
};
