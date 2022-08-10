// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CMDPLUGIN_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CMDPLUGIN_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef CMDPLUGIN_EXPORTS
#define CMDPLUGIN_API extern "C" __declspec(dllexport)
#else
#define CMDPLUGIN_API extern "C" __declspec(dllimport)
#endif

CMDPLUGIN_API bool InitPlugin(char* pPluginPath);
CMDPLUGIN_API bool Query(char* pQuery, char* pResult, int* length);
CMDPLUGIN_API bool GetContextMenu(char* result, char* pMenu, int* length);
CMDPLUGIN_API void ExecuteCommand(char* cmd);