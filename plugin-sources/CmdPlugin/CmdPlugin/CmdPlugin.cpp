// CmdPlugin.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "CmdPlugin.h"
#include "HelperFunc.h"

char g_PluginPath[MAX_PATH] = {0};

// ���ǵ���������һ��ʾ����
bool InitPlugin(char* pPluginPath)
{
	strcpy(g_PluginPath,pPluginPath);
	return true;
}

bool Query(char* pQuery,char* pResult,int* length)
{
	static string strJson;

	if (pResult == NULL)
	{
		strJson.clear();
	}
	else
	{
		if (!strJson.empty())
		{
			strcpy(pResult,strJson.c_str());
			return true;
		}
	}

	QueryText stQuery;
	if (!ParseQuery(pQuery,stQuery))
	{
		return false;
	}

	vector<Result> vecResult;

	string queryStr = stQuery.parameter;
	if (queryStr.empty())
	{
		Result result;
		result.title = "CMD";
		result.subTitle = "����cmd��ִ������";

		vecResult.push_back(result);

		strJson = CreateResultJson(vecResult);
		if (NULL == pResult)
		{
			*length = strJson.size();
		}
		else
		{
			strcpy(pResult,strJson.c_str());
		}

		return true;
	}

	Result result;
	result.title = "CMD";
	result.subTitle = string("Command : ") + queryStr;
	result.action.funcName = "ExecuteCommand";

	char cmd[MAX_PATH] = {0};
	sprintf(cmd,"cmd /c \"%s\" & pause",queryStr.c_str());

	result.action.parameter = cmd;
	vecResult.push_back(result);

	strJson = CreateResultJson(vecResult);
	if (NULL == pResult)
	{
		*length = strJson.size();
	}
	else
	{
		strcpy(pResult,strJson.c_str());
	}

	return true;
}

bool GetContextMenu(char* result, char* pMenu,int* length)
{
	return false;
}

void ExecuteCommand(char* cmd)
{
	WinExec(cmd,SW_SHOW);
}