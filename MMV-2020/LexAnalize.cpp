#include "LexAnalize.h"
#include "stdafx.h"
#define WORD_MAXSIZE 255
#define MAX_INTEGER 255
#define MIN_INTEGER 0
#define MAX_PARAM_NUMBER 2
namespace LexAnalysis
{
	Table lex;
	LT::LexTable lextable = LT::Create(LT_MAXSIZE);
	IT::IdTable idtable = IT::Create(TI_MAXSIZE);
	IT::Entry entryIT;

	const char SpecialSymbols[] = { " .&()[]{}=+-*%/|<>`~^?#" };

	Table LexAnalysis(In::IN in, Log::LOG log)
	{
		int posInLexTable = 0, posInIdTable = 0, countLit = 1, position = 0, line = 0;

		unsigned char emptystr[] = ""; 
		unsigned char* prefix = new unsigned char[ID_MAXSIZE] { "" };
		unsigned char* minus = new unsigned char[2] { "M" };
		unsigned char* bufprefix = new unsigned char[ID_MAXSIZE] { "" };
		unsigned char* oldprefix = new unsigned char[ID_MAXSIZE] { "" };
		unsigned char* buf = new unsigned char[ID_MAXSIZE] { "_" };
		unsigned char* L = new unsigned char[3]{ "L" };
		unsigned char* LexIdintificator = new unsigned char[TI_STR_MAXSIZE];
		char* charclit = new char[10]{ "" }; // строковая запись счетчика
		bool isFunc = false, param = false;
		int HasHead = 0;
		int numberOfLeftbrace = 0, numberOfRightbrace = 0;
		int posOfFunc = 0, numberOfPar = 0;
		ClearSpaces(in.text, in.size, log);
		unsigned char** word = new unsigned char*[LT_MAXSIZE];
		for (int i = 0; i < LT_MAXSIZE; i++) {
			word[i] = new unsigned char[WORD_MAXSIZE] {NULL};
		}	
		do {
			word = GetWord(in.text, in.size);
		} while (word == NULL);

		for (int i = 0; word[i] != NULL; i++, posInLexTable++)
		{
			FST::FST fstSeparator(word[i], EXPRESSION_SEPARATOR);
			if (FST::execute(fstSeparator))
			{
				line++;
				position = 0;
				posInLexTable--;
				continue;
			}

			FST::FST fstVar(word[i], EXPRESSION_VAR);
			if (FST::execute(fstVar))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_VAR;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstTypeInteger(word[i], EXPRESSION_INT);
			if (FST::execute(fstTypeInteger))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_TYPE;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				entryIT.iddatatype = IT::INT;
				continue;
			}

			FST::FST fstTypeBool(word[i], EXPRESSION_BOOL);
			if (FST::execute(fstTypeBool))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_TYPE;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				entryIT.iddatatype = IT::BOOL;
				continue;
			}

			FST::FST fstTypeStr(word[i], EXPRESSION_STR);
			if (FST::execute(fstTypeStr))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_TYPE;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				entryIT.iddatatype = IT::STR;
				_mbscpy(entryIT.value.vstr.str, emptystr);
				continue;
			}

			FST::FST fstFunction(word[i], EXPRESSION_FUNCTION);
			if (FST::execute(fstFunction))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_FUNCTION;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);

				entryIT.idtype = IT::F;
				entryIT.value.params.count = 0;
				entryIT.value.params.types = new IT::IDDATATYPE[MAX_PARAMS_COUNT];
				posOfFunc = posInIdTable;
				isFunc = true;
				continue;
			}
			
			FST::FST fstStrlen(word[i], EXPRESSION_POW);
			if (FST::execute(fstStrlen))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_POW;
				entryLT.idxTI = posInIdTable;
				posInIdTable++;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);

				IT::Entry entryIT;
				_mbscpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = posInLexTable;
				entryIT.idtype = IT::S;
				_mbscpy(entryIT.visibility, emptystr);
				entryIT.iddatatype = STR_POW;
				entryIT.value.params.count = POW_PARAMS_COUNT;
				entryIT.value.params.types = new IT::IDDATATYPE[POW_PARAMS_COUNT];
				for (int k = 0; k < POW_PARAMS_COUNT; k++) {
					entryIT.value.params.types[k] = IT::POW_PARAMS[k];
				}
				IT::Add(idtable, entryIT);
				continue;
			}

			FST::FST fstStrCmp(word[i], EXPRESSION_MAXNUM);
			if (FST::execute(fstStrCmp))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_MAXNUM;
				entryLT.idxTI = posInIdTable;
				posInIdTable++;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);

				entryIT = {};
				_mbscpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = posInLexTable;
				entryIT.idtype = IT::S;
				_mbscpy(entryIT.visibility, emptystr);
				entryIT.iddatatype = MAXNUM_TYPE;
				entryIT.value.params.count = MAXNUM_PARAMS_COUNT;
				entryIT.value.params.types = new IT::IDDATATYPE[MAXNUM_PARAMS_COUNT];
				for (int k = 0; k < MAXNUM_PARAMS_COUNT; k++)
					entryIT.value.params.types[k] = IT::MAXNUM_PARAMS[k];
				IT::Add(idtable, entryIT);
				entryIT = {};
				continue;
			}

			FST::FST fstGoNewStr(word[i], EXPRESSION_NEWSTR);
			if (FST::execute(fstGoNewStr))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_NEWLINE;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				continue;
			}
			 
			FST::FST fstReturn(word[i], EXPRESSION_RETURN);
			if (FST::execute(fstReturn))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_RETURN;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstOut(word[i], EXPRESSION_OUT);
			if (FST::execute(fstOut))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_OUT;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstCheck(word[i], EXPRESSION_CHECK);
			if (FST::execute(fstCheck))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_CHECK;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstOtherwise(word[i], EXPRESSION_OTHERWISE);
			if (FST::execute(fstOtherwise))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_OTHERWISE;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstHead(word[i], EXPRESSION_HEAD);
			if (FST::execute(fstHead))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_HEAD;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);

				_mbscpy(oldprefix, prefix);
				_mbscpy(prefix, word[i]);
				_mbscpy(entryIT.visibility, emptystr);
				HasHead++;
				continue;
			}

			FST::FST fstTrue(word[i], EXPRESSION_TRUE);
			FST::FST fstFalse(word[i], EXPRESSION_FALSE);
			if (FST::execute(fstTrue) || FST::execute(fstFalse))
			{
				int value;
				bool isDefined = false;
				if (!strcmp((char*)word[i], "true")) {
					value = 1;
				}
				else {
					value = 0;
				}
				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::BOOL)
					{
						LT::Entry entryLT;
						entryLT.lexema = LEX_LITERAL;
						entryLT.idxTI = k;
						entryLT.line = line;
						entryLT.sType = LEX_STYPE_NULL;
						LT::Add(lextable, entryLT);
						isDefined = true;
						break;
					}
				}

				if (isDefined)
				{
					continue;
				}

				LT::Entry entryLT;
				entryLT.lexema = LEX_LITERAL;
				entryLT.idxTI = posInIdTable;
				posInIdTable++;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);

				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::BOOL;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = posInLexTable;
				_itoa_s(countLit++, charclit, sizeof(char) * 10, 10);
				_mbscpy(LexIdintificator, L);//
				word[i] = _mbscat(LexIdintificator, (unsigned char*)charclit);
				_mbscpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};
				continue;
			}
			FST::FST fstIdentif(word[i], EXPRESSION_ID);
			if (FST::execute(fstIdentif))
			{
				if (strlen((const char*)word[i]) > 8) {
					word[i][8] = '\0';
				}
				
				if (isFunc)
				{
					int idx = IT::IsId(idtable, word[i]);//is function defined
					if (idx != TI_NULLIDX)
					{
						Log::WriteError(log, Error::geterrorin(308, line, -1));
					}
				}
				else
				{
					int idx = IT::IsId(idtable, word[i]);
					if (idx != TI_NULLIDX)
					{
						LT::Entry entryLT;
						entryLT.lexema = LEX_ID;
						entryLT.idxTI = idx;
						entryLT.line = line;
						entryLT.sType = LEX_STYPE_NULL;
						LT::Add(lextable, entryLT);
						isFunc = false;
						continue;
					}
					_mbscpy(bufprefix, prefix);
					_mbscat(bufprefix, buf);
					word[i] = _mbscat(bufprefix, word[i]);
					idx = IT::IsId(idtable, word[i]);
					if (idx != TI_NULLIDX)
					{
						LT::Entry entryLT;
						entryLT.lexema = LEX_ID;
						entryLT.idxTI = idx;
						entryLT.line = line;
						entryLT.sType = LEX_STYPE_NULL;
						LT::Add(lextable, entryLT);
						if (lextable.table[lextable.size - 3].lexema == LEX_VAR)
						{
							if (idtable.table[idx].idtype == IT::P) {
								Log::WriteError(log, Error::geterrorin(309, line, -1));
							}
							else {
								Log::WriteError(log, Error::geterrorin(310, line, -1));
							}
						}
						continue;
					}
				}

				LT::Entry entryLT;
				entryLT.lexema = LEX_ID;
				entryLT.idxTI = posInIdTable;
				posInIdTable++;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);

				if (param)
				{
					entryIT.idtype = IT::P;//param
					_mbscpy(entryIT.visibility, prefix);
					idtable.table[posOfFunc].value.params.count++;//количество параметров функции
					if (idtable.table[posOfFunc].value.params.count > MAX_PARAM_NUMBER)
						Log::WriteError(log, Error::geterrorin(314, line, -1));//макс кол параметров 2
					idtable.table[posOfFunc].value.params.types[numberOfPar] = entryIT.iddatatype;
					numberOfPar++;
				}

				else if (!isFunc)
				{
					entryIT.idtype = IT::V;//var
					_mbscpy(entryIT.visibility, prefix);
					if (entryIT.iddatatype == IT::INT || entryIT.iddatatype == IT::BOOL)
						entryIT.value.vint = INT_DEFAULT;
					if (entryIT.iddatatype == IT::STR)
					{
						entryIT.value.vstr.len = 0;
						memset(entryIT.value.vstr.str, STR_DEFAULT, sizeof(char));
					}

					if (lextable.table[lextable.size - 3].lexema != LEX_VAR)
						Log::WriteError(log, Error::geterrorin(305, line, position));
					if (lextable.table[lextable.size - 2].lexema != LEX_TYPE)
						Log::WriteError(log, Error::geterrorin(307, line, position));
				}
				else
				{
					_mbscpy(oldprefix, prefix);
					_mbscpy(prefix, word[i]);
					_mbscpy(entryIT.visibility, emptystr);
				}

				entryIT.idxfirstLE = posInLexTable;
				_mbscpy(entryIT.id, word[i]);

				if (entryIT.idtype == IT::F && entryIT.iddatatype == IT::UNKNOWN)
					Log::WriteError(log, Error::geterrorin(311, line, -1));//тип функции
				//if (entryIT.idtype == IT::V && entryIT.iddatatype == IT::UNKNOWN)
				//	Log::WriteError(log, Error::geterrorin(306, line, -1));//идентификатор

				IT::Add(idtable, entryIT);
				entryIT = {};
				isFunc = false;
				continue;
			}
			
			FST::FST fstLiteralInt(word[i], EXPRESSION_INT_LITERAL);
			if (FST::execute(fstLiteralInt))
			{
				bool isDefined = false;
				int value = atoi((char*)word[i]);
				if (value > MAX_INTEGER || value < MIN_INTEGER)
				{
					Log::WriteError(log, Error::geterrorin(319, line, position));
				}
				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::INT)
					{
						LT::Entry entryLT;
						entryLT.lexema = LEX_LITERAL;
						entryLT.idxTI = k;
						entryLT.line = line;
						entryLT.sType = LEX_STYPE_NULL;
						LT::Add(lextable, entryLT);
						isDefined = true;
						break;
					}
				}
				if (isDefined)
				{
					continue;
				}

				LT::Entry entryLT;
				entryLT.lexema = LEX_LITERAL;
				entryLT.idxTI = posInIdTable;
				posInIdTable++;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::INT;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = posInLexTable;
				_itoa_s(countLit++, charclit, sizeof(char) * 10, 10);
				_mbscpy(LexIdintificator, L);
				word[i] = _mbscat(LexIdintificator, (unsigned char*)charclit);
				_mbscpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};
				continue;
			}

			FST::FST fstLiteralInt16(word[i], EXPRESSION_INT16);
			if (FST::execute(fstLiteralInt16))
			{
				bool isDefined = false;
				int numberLength = strlen((char*)word[i]);
				char* number = new char[numberLength - 2];
				for (int j = 0; j < numberLength - 3; j++) {
					number[j] = word[i][j + 3];
				}
				number[numberLength - 3] = '\0';
				int value = strtol(number, NULL, 16);
				if (value > MAX_INTEGER || value < MIN_INTEGER)
				{
					Log::WriteError(log, Error::geterrorin(319, line, position));
				}
				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::INT)
					{
						LT::Entry entryLT;
						entryLT.lexema = LEX_LITERAL;
						entryLT.idxTI = k;
						entryLT.line = line;
						entryLT.sType = LEX_STYPE_NULL;
						LT::Add(lextable, entryLT);
						isDefined = true;
						break;
					}
				}

				if (isDefined)
				{
					continue;
				}

				LT::Entry entryLT;
				entryLT.lexema = LEX_LITERAL;
				entryLT.idxTI = posInIdTable;
				posInIdTable++;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::INT;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = posInLexTable;
				_itoa_s(countLit++, charclit, sizeof(char) * 10, 10);
				_mbscpy(LexIdintificator, L);
				word[i] = _mbscat(LexIdintificator, (unsigned char*)charclit);
				_mbscpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};
				continue;
			}
			FST::FST fstLiteralInt2(word[i], EXPRESSION_INT2);
			if (FST::execute(fstLiteralInt2))
			{
				bool isDefined = false;
				int numberLength = strlen((char*)word[i]);
				char* number = new char[numberLength - 3];
				for (int j = 0; j < numberLength - 4; j++) {
					number[j] = word[i][j + 4];
				}
				number[numberLength - 4] = '\0';
				int value = strtol(number, NULL, 2);
				if (value > MAX_INTEGER || value < MIN_INTEGER)
				{
					Log::WriteError(log, Error::geterrorin(319, line, position));
				}

				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::INT)
					{
						LT::Entry entryLT;
						entryLT.lexema = LEX_LITERAL;
						entryLT.idxTI = k;
						entryLT.line = line;
						entryLT.sType = LEX_STYPE_NULL;
						LT::Add(lextable, entryLT);
						isDefined = true;
						break;
					}
				}

				if (isDefined)
				{
					continue;
				}

				LT::Entry entryLT;
				entryLT.lexema = LEX_LITERAL;
				entryLT.idxTI = posInIdTable;
				posInIdTable++;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::INT;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = posInLexTable;
				_itoa_s(countLit++, charclit, sizeof(char) * 10, 10);
				_mbscpy(LexIdintificator, L);
				word[i] = _mbscat(LexIdintificator, (unsigned char*)charclit);
				_mbscpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};
				continue;
			}
			FST::FST fstLiteralInt8(word[i], EXPRESSION_INT8);
			if (FST::execute(fstLiteralInt8))
			{
				bool isDefined = false;
				int numberLength = strlen((char*)word[i]);
				char* number = new char[numberLength - 4];
				for (int j = 0; j < numberLength - 5; j++) {
					number[j] = word[i][j + 5];
				}
				number[numberLength - 5] = '\0';
				int value = strtol(number, NULL, 8);
				if (value > MAX_INTEGER || value < MIN_INTEGER)
				{
					Log::WriteError(log, Error::geterrorin(319, line, position));
				}
				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::INT)
					{
						LT::Entry entryLT;
						entryLT.lexema = LEX_LITERAL;
						entryLT.idxTI = k;
						entryLT.line = line;
						entryLT.sType = LEX_STYPE_NULL;
						LT::Add(lextable, entryLT);
						isDefined = true;
						break;
					}
				}

				if (isDefined)
				{
					continue;
				}
				LT::Entry entryLT;
				entryLT.lexema = LEX_LITERAL;
				entryLT.idxTI = posInIdTable;
				posInIdTable++;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::INT;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = posInLexTable;
				_itoa_s(countLit++, charclit, sizeof(char) * 10, 10);
				_mbscpy(LexIdintificator, L);
				word[i] = _mbscat(LexIdintificator, (unsigned char*)charclit);
				_mbscpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};
				continue;
			}

			FST::FST fstLiteralString(word[i], EXPRESSION_STRING_LITERAL);
			if (FST::execute(fstLiteralString))
			{
				bool isDefined = false;
				int length = _mbslen(word[i]);
				for (int k = 0; k < length; k++)
					word[i][k] = word[i][k + 1];
				word[i][length - 2] = 0;
				if (_mbslen(word[i]) == 0) {
					Log::WriteError(log, Error::geterrorin(312, line, position));
				}
				for (int k = 0; k < idtable.size; k++)
				{
					if (!(_mbscmp(idtable.table[k].value.vstr.str, word[i])))
					{
						isDefined = true;
						LT::Entry entryLT;
						entryLT.lexema = LEX_LITERAL;
						entryLT.idxTI = k;
						entryLT.line = line;
						entryLT.sType = LEX_STYPE_NULL;
						LT::Add(lextable, entryLT);
						break;
					}
				}

				if (isDefined)
				{
					continue;
				}
				LT::Entry entryLT;
				entryLT.lexema = LEX_LITERAL;
				entryLT.idxTI = posInIdTable;
				posInIdTable++;
				entryLT.line = line;
				entryLT.sType = LEX_STYPE_NULL;
				LT::Add(lextable, entryLT);

				_mbscpy(entryIT.value.vstr.str, word[i]);
				entryIT.value.vstr.len = length - 2;
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::STR;
				entryIT.idxfirstLE = posInLexTable;
				_itoa_s(countLit++, charclit, sizeof(char) * 10, 10);
				_mbscpy(LexIdintificator, L);
				unsigned char* nameLiteral = new unsigned char[10]{ "" };
				nameLiteral = _mbscat(LexIdintificator, (unsigned char*)charclit);
				_mbscpy(entryIT.id, nameLiteral);
				IT::Add(idtable, entryIT);
				entryIT = {};
				continue;
			}

			FST::FST fstOperator(word[i], EXPRESSION_ARITHMETIC);
			if (FST::execute(fstOperator))
			{
				LT::Entry entryLT;
				switch (word[i][0])
				{
				case '+':
					entryLT.lexema = LEX_OPERATOR;
					entryLT.idxTI = LT_TI_NULLIDX;
					entryLT.line = line;
					entryLT.sType = '+';
					entryLT.priority = 1;
					entryLT.operation = LT::PLUS;
					break;
				case '-':
					entryLT.lexema = LEX_OPERATOR;
					entryLT.idxTI = LT_TI_NULLIDX;
					entryLT.line = line;
					entryLT.sType = '-';
					entryLT.priority = 1;
					entryLT.operation = LT::MINUS;
					break;
				case '/':
					entryLT.lexema = LEX_OPERATOR;
					entryLT.idxTI = LT_TI_NULLIDX;
					entryLT.line = line;
					entryLT.sType = '/';
					entryLT.priority = 2;
					entryLT.operation = LT::DIR;
					break;
				case '*':
					entryLT.lexema = LEX_OPERATOR;
					entryLT.idxTI = LT_TI_NULLIDX;
					entryLT.line = line;
					entryLT.sType = '*';
					entryLT.priority = 2;
					entryLT.operation = LT::MUL;
					break;
				case '%':
					entryLT.lexema = LEX_OPERATOR;
					entryLT.idxTI = LT_TI_NULLIDX;
					entryLT.line = line;
					entryLT.sType = '%';
					entryLT.priority = 2;
					entryLT.operation = LT::OST;
					break;
				}
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstLogOperator(word[i], EXPRESSION_LOG_OPERATOR);
			if (FST::execute(fstLogOperator))
			{
				LT::Entry entryLT;
				switch (word[i][0])
				{
				case '>':
					entryLT.lexema = LEX_LOGOPERATOR;
					entryLT.idxTI = LT_TI_NULLIDX;
					entryLT.line = line;
					entryLT.sType = '>';
					entryLT.priority = -1;
					entryLT.operation = LT::MORE;
					break;
				case '<':
					entryLT.lexema = LEX_LOGOPERATOR;
					entryLT.idxTI = LT_TI_NULLIDX;
					entryLT.line = line;
					entryLT.sType = '<';
					entryLT.priority = -1;
					entryLT.operation = LT::LESS;
					break;
				case '`':
					entryLT.lexema = LEX_LOGOPERATOR;
					entryLT.idxTI = LT_TI_NULLIDX;
					entryLT.line = line;
					entryLT.sType = '<=';//<=
					entryLT.priority = -1;
					entryLT.operation = LT::LOREQU;
					break;
				case '~':
					entryLT.lexema = LEX_LOGOPERATOR;
					entryLT.idxTI = LT_TI_NULLIDX;
					entryLT.line = line;
					entryLT.sType = '>=';//>=
					entryLT.priority = -1;
					entryLT.operation = LT::MOREQU;
					break;
				case '?':
					entryLT.lexema = LEX_LOGOPERATOR;
					entryLT.idxTI = LT_TI_NULLIDX;
					entryLT.line = line;
					entryLT.sType = '=';//=
					entryLT.priority = -1;
					entryLT.operation = LT::EQU;
					break;
				case '#':
					entryLT.lexema = LEX_LOGOPERATOR;
					entryLT.idxTI = LT_TI_NULLIDX;
					entryLT.line = line;
					entryLT.sType = '!=';//!=
					entryLT.priority = -1;
					entryLT.operation = LT::NOEQU;
					break;
				}
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstPoint(word[i], EXPRESSION_POINT);
			if (FST::execute(fstPoint))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_POINT;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = '.';
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstAnd(word[i], EXPRESSION_AND);
			if (FST::execute(fstAnd))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_AND;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = '&';
				entryLT.priority = 1;
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstLeftBrace(word[i], EXPRESSION_LEFTBRACE);
			if (FST::execute(fstLeftBrace))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_LEFTBRACE;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = '{';
				LT::Add(lextable, entryLT);
				numberOfLeftbrace++;
				continue;
			}

			FST::FST fstRightBrace(word[i], EXPRESSION_BRACELET);
			if (FST::execute(fstRightBrace))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_BRACELET;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = '}';
				LT::Add(lextable, entryLT);
				numberOfRightbrace++;
				continue;
			}

			FST::FST fstLeftThesis(word[i], EXPRESSION_LEFTTHESIS);
			if (FST::execute(fstLeftThesis))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_LEFTTHESIS;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = '[';
				entryLT.priority = 0;
				LT::Add(lextable, entryLT);
				if (posInIdTable > 0 && idtable.table[posInIdTable - 1].idtype == IT::F) 
				{
					param = true;
				}
					
				continue;
			}

			FST::FST fstRightThesis(word[i], EXPRESSION_RIGHTTHESIS);
			if (FST::execute(fstRightThesis))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_RIGHTTHESIS;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = ']';
				entryLT.priority = 0;
				if (param && word[i + 1][0] != LEX_LEFTBRACE && word[i + 2][0] != LEX_LEFTBRACE) {
					_mbscpy(prefix, oldprefix);
				}
				numberOfPar = 0;
				param = false;
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstLeftBracket(word[i], EXPRESSION_LEFTBRACKET);
			if (FST::execute(fstLeftBracket))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_LEFTBRACKET;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = '(';
				entryLT.priority = 0;
				
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstRightBracket(word[i], EXPRESSION_RIGHTBRACKET);
			if (FST::execute(fstRightBracket))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_RIGHTBRACKET;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = ')';
				entryLT.priority = 0;
				LT::Add(lextable, entryLT);
				continue;
			}

			FST::FST fstEqual(word[i], EXPRESSION_EQUAL);
			if (FST::execute(fstEqual))
			{
				LT::Entry entryLT;
				entryLT.lexema = LEX_EQUAL;
				entryLT.idxTI = LT_TI_NULLIDX;
				entryLT.line = line;
				entryLT.sType = '=';
				LT::Add(lextable, entryLT);
				continue;
			}

			position += _mbslen(word[i]);

			throw ERROR_THROW_IN(205, line, position);
		}

		if (HasHead == 0)
		{
			Log::WriteError(log, Error::geterror(302));
		}
		if (HasHead > 1)
		{
			Log::WriteError(log, Error::geterror(303));
		}
		if (numberOfLeftbrace > numberOfRightbrace) 
		{
			Log::WriteError(log, Error::geterror(612));
		}
		if (numberOfRightbrace > numberOfLeftbrace) 
		{
			Log::WriteError(log, Error::geterror(613));
		}

		lex.idtable = idtable;
		lex.lextable = lextable;
		return lex;
	}

	void ClearSpaces(unsigned char source[], int size, Log::LOG logfile)
	{
		bool IsLiteral = false;
		int count = 0, length = 0;
		for (int i = 0; i < size; i++)
		{
			if (source[i] == '\n')
				source[i] = '|';
		}
		for (int i = 0; i < size; i++)
		{
			if (source[i] == '\"')
			{
				IsLiteral = !IsLiteral;
				if (length + 1 > 255)
				{
					Log::WriteError(logfile, Error::geterror(304));
				}
				length = NULL;
				count++;
			}
			if (IsLiteral)	length++;
			if ((source[i] == ' ' || source[i] == '\t') && !IsLiteral)
			{
				for (int j = 0; j < sizeof(SpecialSymbols) - 1; j++)
				{
					if (source[i + 1] == SpecialSymbols[j] || source[i - 1] == SpecialSymbols[j] || i == 0)
					{
						for (int k = i; k < size; k++)
							source[k] = source[k + 1];
						i--;
						break;
					}
				}
			}
		}
		if (count % 2 != 0)	Log::WriteError(logfile, Error::geterror(300));
	}

	unsigned char** GetWord(unsigned char source[], int size)
	{
		unsigned char** word = new unsigned char* [LT_MAXSIZE];
		for (int i = 0; i < LT_MAXSIZE; i++) {
			word[i] = new unsigned char[256]{ NULL };
		}

		bool IsSpecial, IsLiteral = false;
		int j = 0;

		for (int i = 0, k = 0; i < size - 1; i++, k++)
		{
			IsSpecial = false;
			if (source[i] == '\"') {
				IsLiteral = !IsLiteral;
			}
			for (int t = 0; t < sizeof(SpecialSymbols) - 1; t++)
			{
				if (source[i] == SpecialSymbols[t] && !IsLiteral)
				{
					IsSpecial = true;
					if (word[j][0] != NULL)
					{
						word[j++][k] = '\0';
						k = 0;
					}
					if (SpecialSymbols[t] == ' ')
					{
						k = -1;
						break;
					}
					word[j][k++] = SpecialSymbols[t];
					word[j++][k] = '\0';
					k = -1;
					break;
				}
			}
			if (!IsSpecial) {
				word[j][k] = source[i];
			}
		}
		word[j] = NULL;
		for (int i = 0; i < j; i++)
			if (!strcmp((char*)word[i], ""))
				return NULL;
		return word;
	}
}
