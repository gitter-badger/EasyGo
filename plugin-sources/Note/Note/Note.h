// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CLOCK_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CLOCK_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef CLOCK_EXPORTS
#define CLOCK_API extern "C" __declspec(dllexport)
#else
#define CLOCK_API extern "C" __declspec(dllimport)
#endif

CLOCK_API bool InitPlugin(char* pPluginPath);
CLOCK_API bool Query(char* pQuery, char* pResult, int* length);
CLOCK_API bool GetContextMenu(char* result, char* pMenu, int* length);
CLOCK_API void AddNote(char* pParam);
CLOCK_API void DeleteNote(char* pFilePath);