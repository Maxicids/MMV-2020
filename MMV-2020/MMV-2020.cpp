#include "Error.h"
#include "stdafx.h"
#include "In.h"
#include "Log.h"
#include "Parm.h"
#include "LexAnalize.h"
#include "IT.h"
#include "LT.h"
#include "MFST.h"
#include "SemAnalize.h"
#include "Generation.h"
#include "PolishNotation.h"

Log::LOG logfile;
Log::LOG outfile;

int _tmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "rus");
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		logfile = Log::getlog(parm.log);
		In::IN in = In::getin(parm.in);
		LexAnalysis::Table table = LexAnalysis::LexAnalysis(in, logfile);
		Log::WriteLog(logfile);
		Log::WriteParm(logfile, parm);
		Log::WriteIn(logfile, in);
		Log::WriteLexTableLog(table.lextable, logfile);
		Log::WriteIDTableLog(table.idtable, logfile);
		MFST_TRACE_START_LOG(logfile);
		MFST::Mfst mfst(table, GRB::getGreibach());
		mfst.start(logfile);
		mfst.savededucation();
		mfst.printrules(logfile);
		Semantics::Analize(table, logfile);

		//Converter::ToPolish(table);
		//Converter::Show(table);
		
		Log::WriteIDTableLog(table.idtable, logfile);
		Log::WriteLexTableLog(table.lextable, logfile);

		LT::WriteLexTable(table.lextable);

		outfile = Log::getlog(parm.out);
		CodeGeneration::Generation(table, outfile);

		IT::Delete(table.idtable);
		LT::Delete(table.lextable);

		Log::Close(outfile);

		system("C:\\Windows\\Microsoft.NET\\Framework\\v4.0.30319\\csc.exe -out:\"D:\\Epam\\Yap\\MMV-2020\\OUT.exe\" \"D:\\Epam\\Yap\\MMV-2020\\standlib\\standlib.cs\" \"D:\\Epam\\Yap\\MMV-2020\\Out.cs\" -warn:0");
		system("cls");
		system("D:\\Epam\\Yap\\MMV-2020\\OUT.exe");
		cout << endl;
		system("pause");
	}

	catch (Error::ERROR e)
	{
		Log::WriteError(logfile, e);
	}
}