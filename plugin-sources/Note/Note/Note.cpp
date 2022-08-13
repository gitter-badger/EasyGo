// Note.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "Note.h"
#include "HelperFunc.h"


string g_PluginPath;
string g_notePath;
string g_keyword;

// ���ǵ���������һ��ʾ����
bool InitPlugin(char* pPluginPath)
{
	g_PluginPath = pPluginPath;
	g_notePath = g_PluginPath + "\\note";
	if (!PathFileExistsA(g_notePath.c_str()))
		CreateDirectoryA(g_notePath.c_str(),NULL);
	return true;
}

void AddQuery(string& strQuery,vector<Result>& vecResult)
{
	Result result;
	if (strQuery.empty())
	{
		result.title = "��ӱʼ�";
		result.subTitle = "���: ������ʼ���";
	}
	else
	{
		string noteName = strQuery;

		result.title = "��ӱʼ�";

		char fmtBuf[512] = {0};
		sprintf(fmtBuf,"��ӱʼ� [%s] ",noteName.c_str());
		result.subTitle = fmtBuf;
		result.action.funcName = "AddNote";
		result.action.parameter = noteName;
		result.action.hideWindow = false;
	}

	vecResult.push_back(result);
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

	g_keyword = stQuery.keyword;

	vector<Result> vecResult;

	string queryStr = stQuery.parameter;
	if (queryStr.empty())
	{
		string keyword = g_keyword + " add ";

		Result result;
		result.title = "Add a note";
		result.subTitle = "���һ���ʼ�";
		result.action.funcName = "Ra_ChangeQuery";
		result.action.parameter = keyword;
		result.action.hideWindow = false;
		vecResult.push_back(result);

		keyword = g_keyword + " delete ";
		result.title = "Delete a note";
		result.subTitle = "ɾ��һ���ʼ�";
		result.action.funcName = "Ra_ChangeQuery";
		result.action.parameter = keyword;
		result.action.hideWindow = false;
		vecResult.push_back(result);

		keyword = g_keyword + " show ";
		result.title = "Show all notes";
		result.subTitle = "��ʾ���бʼ�";
		result.action.funcName = "Ra_ChangeQuery";
		result.action.parameter = keyword;
		result.action.hideWindow = false;
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

	string subKeyword;
	string parameter;
	int index = queryStr.find(" ");
	if (index != -1)
	{
		subKeyword = queryStr.substr(0,index);
		parameter = queryStr.substr(index+1);
	}
	else
	{
		subKeyword = queryStr;
	}

	if (compareNoCase(subKeyword,"add"))
	{
		AddQuery(parameter,vecResult);
	}
	else if (compareNoCase(subKeyword,"delete"))
	{
		Result result;

		vector<string> fileList;
		GetDirFiles(g_notePath,fileList);

		if (fileList.empty())
		{
			result.title = "û�бʼ�";
			vecResult.push_back(result);
		}
		else
		{
			char fileName[128] = {0};
			for (int i = 0; i < fileList.size(); i++)
			{
				strcpy(fileName, fileList[i].c_str());
				PathRemoveExtensionA(fileName);

				result.title = fileName;
				result.subTitle = g_notePath + "\\" + fileList[i];
				result.action.funcName = "DeleteNote";
				result.action.parameter = g_notePath + "\\" + fileList[i];
				result.action.hideWindow = false;
				vecResult.push_back(result);
			}
		}
	}
	else if (compareNoCase(subKeyword,"show"))
	{
		Result result;

		vector<string> fileList;
		GetDirFiles(g_notePath,fileList);

		if (fileList.empty())
		{
			result.title = "û�бʼ�";
			vecResult.push_back(result);
		}
		else
		{
			char fileName[128] = {0};
			for (int i = 0; i < fileList.size(); i++)
			{
				strcpy(fileName, fileList[i].c_str());
				PathRemoveExtensionA(fileName);

				result.title = fileName;
				result.subTitle = "�����򿪱ʼ�";
				result.action.funcName = "Ra_EditFile";
				result.action.parameter = g_notePath + "\\" + fileList[i];
				result.action.hideWindow = false;
				vecResult.push_back(result);
			}
		}
	}
	else
	{
		Result result;
		result.title = "EasyNote";
		result.subTitle = "һ��򵥵ļ��±�";
		vecResult.push_back(result);
	}

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

void AddNote(char* pParam)
{
	string filePath = g_notePath + "\\" + string(pParam) + ".txt";
	if (!PathFileExistsA(filePath.c_str()))
	{
		FILE* fp = fopen(filePath.c_str(),"w+");
		if (fp == NULL)
		{
			Ra_ShowMsg("����","�޷������ʼ��ļ�");
			return;
		}
		fclose(fp);
	}

	string keyword = g_keyword + " show ";

	Ra_ChangeQuery(keyword.c_str());
}

void DeleteNote(char* pFilePath)
{
	DeleteFileA(pFilePath);

	string keyword = g_keyword + " show ";

	Ra_ChangeQuery(keyword.c_str());
}