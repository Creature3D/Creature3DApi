#include "stdafx.h"
#include "SystemInfo.h"
#include "float.h"
#include "winperf.h"


CSystemInfo::CSystemInfo(void)
{
}

CSystemInfo::~CSystemInfo(void)
{
}

BOOL CSystemInfo::IsWow64() 
{ 
	typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL); 
	LPFN_ISWOW64PROCESS fnIsWow64Process; 
	BOOL bIsWow64 = FALSE; 
	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress( GetModuleHandle(_T("kernel32")),"IsWow64Process"); 
	if (NULL != fnIsWow64Process) 
	{ 
		fnIsWow64Process(GetCurrentProcess(), &bIsWow64);
	} 
	return bIsWow64; 
} 

void CSystemInfo::GetCpuInfo(CString &chProcessorName,CString &chProcessorType,DWORD &dwNum,DWORD &dwMaxClockSpeed)
{
	HKEY hKey;
	CString strPath=_T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");//ע����Ӽ�·��
	LONG lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, LPCTSTR(strPath), 0, KEY_QUERY_VALUE, &hKey );
	if (lResult != ERROR_SUCCESS)
	{
		return;
	}

	//��ȡProcessorNameString�ֶ�ֵ
	WCHAR chCPUName[50] = {0};
	DWORD dwSize=50, type = 0;
	if (ERROR_SUCCESS == RegQueryValueEx(hKey, _T("ProcessorNameString"), 0, &type, LPBYTE(chCPUName), &dwSize))
	{
		chProcessorName = chCPUName;
	}

	//��ѯCPU��Ƶ
	DWORD dwValue = 0;
	DWORD size = sizeof(DWORD);
	if (ERROR_SUCCESS == RegQueryValueEx(hKey, TEXT("~MHz"), 0, &type, (LPBYTE)&dwValue, &size))
	{
		dwMaxClockSpeed = dwValue;
	}
	RegCloseKey(hKey);

	//��ȡCPU������Ŀ
	SYSTEM_INFO si;
	memset(&si,0,sizeof(SYSTEM_INFO));
	GetSystemInfo(&si);
	dwNum = si.dwNumberOfProcessors;
	switch (si.dwProcessorType)
	{
	case PROCESSOR_INTEL_386:
		{
			chProcessorType.Format(_T("Intel 386 processor"));
		}
		break;
	case PROCESSOR_INTEL_486:
		{
			chProcessorType.Format(_T("Intel 486 Processor"));
		}
		break;
	case PROCESSOR_INTEL_PENTIUM:
		{
			chProcessorType.Format(_T("Intel Pentium Processor"));
		}
		break;
	case PROCESSOR_INTEL_IA64:
		{
			chProcessorType.Format(_T("Intel IA64 Processor"));
		}
		break;
	case PROCESSOR_AMD_X8664:
		{
			chProcessorType.Format(_T("AMD X8664 Processor"));
		}
		break;
	default:
		chProcessorType.Format(_T("δ֪"));
		break;
	}
}

void CSystemInfo::GetMemoryInfo(CString &dwTotalPhys, CString &dwTotalVirtual) 
{
	// TODO: Add extra initialization here 
	MEMORYSTATUS Mem; 
	// get the memory status 
	GlobalMemoryStatus(&Mem); 

	DWORD dwSize = (DWORD)Mem.dwTotalPhys/(1024*1024); 
	DWORD dwVirtSize = (DWORD)Mem.dwTotalVirtual/(1024*1024);

	dwTotalPhys.Format(_T("�����ڴ�:%ld MB"),dwSize); 
	dwTotalVirtual.Format(_T("�����ڴ�:%ld MB"),dwVirtSize);
}

int CSystemInfo::GetInterFaceCount()
{
	try
	{
#define DEFAULT_BUFFER_SIZE 40960L

		unsigned char *data = (unsigned char*)malloc(DEFAULT_BUFFER_SIZE);
		DWORD type;
		DWORD size = DEFAULT_BUFFER_SIZE;
		DWORD ret;

		char s_key[4096];
		sprintf_s(s_key , 4096 , "510");
		//RegQueryValueEx�Ĺ̶����ø�ʽ
		CString str(s_key);

		//���RegQueryValueEx����ִ��ʧ�������ѭ��
		while((ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA, str, 0, &type, data, &size)) != ERROR_SUCCESS)
		{
			Sleep(10);
			//���RegQueryValueEx�ķ���ֵΪERROR_MORE_DATA(������ڴ���data̫С����������RegQueryValueEx���ص�����)
			if(ret == ERROR_MORE_DATA) 
			{
				Sleep(10);
				size += DEFAULT_BUFFER_SIZE;
				data = (unsigned char*) realloc(data, size);//���·����㹻����ڴ�

				ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA, str, 0, &type, data, &size);//����ִ��RegQueryValueEx����
			} 
			//���RegQueryValueEx����ֵ�Ծ�δ�ɹ���������.....(ע���ڴ�й¶��free������~~~)��
			//���if��֤�����whileֻ�ܽ���һ��~~~������ѭ��
			if(ret != ERROR_SUCCESS)
			{
				if (NULL != data)
				{
					free(data);
					data = NULL;
				}
				return 0;//0���ӿ�
			}
		}

		//����ִ�гɹ�֮����ǶԷ��ص�data�ڴ������ݵĽ����ˣ��������ȥ�鿴MSDN�й�RegQueryValueEx�����������ݽṹ��˵���õ����ݿ�
		PERF_DATA_BLOCK*dataBlockPtr = (PERF_DATA_BLOCK *)data;
		//�õ���һ������
		PERF_OBJECT_TYPE *objectPtr = (PERF_OBJECT_TYPE *) ((BYTE *)dataBlockPtr + dataBlockPtr->HeaderLength);
		for(int a=0 ; a<(int)dataBlockPtr->NumObjectTypes ; a++) 
		{
			char nameBuffer[255] = {0};
			if(objectPtr->ObjectNameTitleIndex == 510) 
			{
				DWORD processIdOffset = ULONG_MAX;
				PERF_COUNTER_DEFINITION *counterPtr =(PERF_COUNTER_DEFINITION *) ((BYTE *)objectPtr + objectPtr->HeaderLength);

				for(int b=0 ; b<(int)objectPtr->NumCounters ; b++) 
				{
					if(counterPtr->CounterNameTitleIndex == 520)
						processIdOffset = counterPtr->CounterOffset;

					counterPtr =(PERF_COUNTER_DEFINITION *) ((BYTE *) counterPtr + counterPtr->ByteLength);
				}

				if(processIdOffset == ULONG_MAX) {
					if(data != NULL)
					{
						free(data);
						data = NULL;
					}
					return 0;
				}

				PERF_INSTANCE_DEFINITION *instancePtr =(PERF_INSTANCE_DEFINITION *)((BYTE *) objectPtr + objectPtr->DefinitionLength);
				for(int b=0 ; b<objectPtr->NumInstances ; b++) 
				{
					wchar_t *namePtr = (wchar_t *) ((BYTE *)instancePtr + instancePtr->NameOffset);
					PERF_COUNTER_BLOCK *counterBlockPtr = (PERF_COUNTER_BLOCK *) ((BYTE *)instancePtr + instancePtr->ByteLength);

					char pName[256] = {0};
					WideCharToMultiByte(CP_ACP, 0, namePtr, -1, pName, sizeof(nameBuffer), 0, 0);

					DWORD bandwith = *((DWORD *) ((BYTE *)counterBlockPtr + processIdOffset));
					DWORD tottraff = 0;

					Interfaces.AddTail(CString(pName)); //������������
					Bandwidths.AddTail(bandwith); //����
					TotalTraffics.AddTail(tottraff);// ������ʼ��Ϊ0

					PERF_COUNTER_BLOCK * pCtrBlk = (PERF_COUNTER_BLOCK *) ((BYTE *)instancePtr + instancePtr->ByteLength);

					instancePtr = (PERF_INSTANCE_DEFINITION *) ((BYTE *)instancePtr + instancePtr->ByteLength + pCtrBlk->ByteLength);
				}
			}
			objectPtr = (PERF_OBJECT_TYPE *) ((BYTE *)objectPtr + objectPtr->TotalByteLength);
		}
		if(data != NULL)
		{
			free(data);
			data = NULL;
		}
	}
	catch(...)
	{
		return 0;
	}
	return Interfaces.GetCount();
}

void CSystemInfo::GetInterFaceName(CString &InterfaceName,int pNum)
{
	POSITION pos = Interfaces.FindIndex(pNum);
	if(pos==NULL)
		return ;

	InterfaceName = Interfaces.GetAt(pos);
	pos = Bandwidths.FindIndex(pNum);
	if (pos == NULL)
		return;
	DWORD dwBandwidth = Bandwidths.GetAt(pos);

	CString str;
	str.Format(_T("%d"),dwBandwidth);

	InterfaceName = InterfaceName + str;
}

void CSystemInfo::GetDiskInfo(DWORD &dwNum, CString chDriveInfo[], unsigned __int64 iDiskFreeSize[],wchar_t disk[])
{
	DWORD DiskCount = 0;

	//����GetLogicalDrives()�������Ի�ȡϵͳ���߼����������������������ص���һ��32λ�޷����������ݡ�
	DWORD DiskInfo = GetLogicalDrives();

	//ͨ��ѭ�������鿴ÿһλ�����Ƿ�Ϊ1�����Ϊ1�����Ϊ��,���Ϊ0����̲����ڡ�
	while(DiskInfo)
	{
		//ͨ��λ������߼���������ж��Ƿ�Ϊ1
		Sleep(10);
		if(DiskInfo&1)
		{
			DiskCount++;
		}
		DiskInfo = DiskInfo >> 1;//ͨ��λ��������Ʋ�����֤ÿѭ��һ��������λ�������ƶ�һλ��*/
	}

	if (dwNum < DiskCount)
	{
		return;//ʵ�ʵĴ�����Ŀ����dwNum
	}
	dwNum = DiskCount;//�����̷�����������

	//ͨ��GetLogicalDriveStrings()������ȡ�����������ַ�����Ϣ����
	int DSLength = GetLogicalDriveStrings(0, NULL);

	WCHAR* DStr = new WCHAR[DSLength];
	memset(DStr, 0, DSLength);

	//ͨ��GetLogicalDriveStrings���ַ�����Ϣ���Ƶ�����������,���б�������������������Ϣ��
	GetLogicalDriveStrings(DSLength,DStr);

	int DType;
	int si=0;
	BOOL fResult;
	unsigned __int64 i64FreeBytesToCaller;
	unsigned __int64 i64TotalBytes;
	unsigned __int64 i64FreeBytes;

	//��ȡ����������Ϣ������DStr�ڲ����ݸ�ʽ��A:\NULLB:\NULLC:\NULL������DSLength/4���Ի�þ����ѭ����Χ
	for(int i=0; i<DSLength/4; ++i)
	{
		Sleep(10);
		CString strdriver = DStr + i*4;
		CString strTmp,strTotalBytes, strFreeBytes;
		DType = GetDriveType(strdriver);//GetDriveType���������Ի�ȡ���������ͣ�����Ϊ�������ĸ�Ŀ¼
		disk[i] = strdriver[0];
		switch (DType)
		{
		case DRIVE_FIXED:
			{
				strTmp.Format(_T("���ش���"));
			}
			break;
		case DRIVE_CDROM:
			{
				strTmp.Format(_T("DVD������"));
			}
			break;
		case DRIVE_REMOVABLE:
			{
				strTmp.Format(_T("���ƶ�����"));
			}
			break;
		case DRIVE_REMOTE:
			{
				strTmp.Format(_T("�������"));
			}
			break;
		case DRIVE_RAMDISK:
			{
				strTmp.Format(_T("����RAM����"));
			}
			break;
		case DRIVE_UNKNOWN:
			{
				strTmp.Format(_T("����RAMδ֪�豸"));
			}
			break;
		default:
			strTmp.Format(_T("δ֪�豸"));
			break;
		}

		//GetDiskFreeSpaceEx���������Ի�ȡ���������̵Ŀռ�״̬,�������ص��Ǹ�BOOL��������
		fResult = GetDiskFreeSpaceEx (strdriver, (PULARGE_INTEGER)&i64FreeBytesToCaller, (PULARGE_INTEGER)&i64TotalBytes, (PULARGE_INTEGER)&i64FreeBytes);
		if(fResult)
		{
			iDiskFreeSize[i] = i64FreeBytesToCaller;
			strTotalBytes.Format(_T("����������%fMB"), (float)i64TotalBytes/1024/1024);
			strFreeBytes.Format(_T("����ʣ��ռ�%fMB"), (float)i64FreeBytesToCaller / 1024 / 1024);
		}
		else
		{
			strTotalBytes.Format(_T(""));
			strFreeBytes.Format(_T(""));
		}
		chDriveInfo[i] = strTmp + _T("(") + strdriver + _T("):") + strTotalBytes + strFreeBytes;
		si+=4;
	}
}

void CSystemInfo::GetDisplayCardInfo(DWORD &dwNum, CString chCardName[])
{
	HKEY keyServ;
	HKEY keyEnum;
	HKEY key;
	HKEY key2;
	LONG lResult;//LONG�ͱ��������溯������ֵ

	//��ѯ"SYSTEM\\CurrentControlSet\\Services"�µ������Ӽ����浽keyServ
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("SYSTEM\\CurrentControlSet\\Services"),0,KEY_READ,&keyServ);
	if (ERROR_SUCCESS != lResult)
		return;

	//��ѯ"SYSTEM\\CurrentControlSet\\Enum"�µ������Ӽ����浽keyEnum
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("SYSTEM\\CurrentControlSet\\Enum"),0,KEY_READ,&keyEnum);
	if (ERROR_SUCCESS != lResult)
		return;

	int i = 0,count = 0;
	DWORD size = 0,type = 0;
	for (;;++i)
	{
		Sleep(5);
		size = 512;
		TCHAR name[512] = {0};//����keyServ�¸�������ֶ�����

		//���ö��keyServ�µĸ������ֶα��浽name��
		lResult = RegEnumKeyEx(keyServ,i,name,&size,NULL,NULL,NULL,NULL);

		//Ҫ��ȡ��������ڣ���keyServ������ȫ��������ʱ����ѭ��
		if(lResult == ERROR_NO_MORE_ITEMS)
			break;

		//��keyServ�������ֶ�Ϊname����ʶ���ֶε�ֵ���浽key
		lResult = RegOpenKeyEx(keyServ,name,0,KEY_READ,&key);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(keyServ);
			return;
		}

		size = 512;
		//��ѯkey�µ��ֶ�ΪGroup���Ӽ��ֶ������浽name
		lResult = RegQueryValueEx(key, TEXT("Group"), 0, &type,(LPBYTE)name, &size);
		if(lResult == ERROR_FILE_NOT_FOUND)
		{
			//?��������
			RegCloseKey(key);
			continue;
		};

		//�����ѯ����name����Video��˵���ü������Կ�������
		if(_tcscmp(TEXT("Video"),name)!=0)
		{
			RegCloseKey(key);
			continue; //����forѭ��
		};

		//��������������ִ�еĻ�˵���Ѿ��鵽���й��Կ�����Ϣ������������Ĵ���ִ����֮��Ҫbreak��һ��forѭ������������
		lResult = RegOpenKeyEx(key,TEXT("Enum"),0,KEY_READ,&key2);
		RegCloseKey(key);
		key = key2;
		size = sizeof(count);
		lResult = RegQueryValueEx(key,TEXT("Count"),0,&type,(LPBYTE)&count,&size);//��ѯCount�ֶΣ��Կ���Ŀ��

		dwNum = count;	//�����Կ���Ŀ
		for(int j=0;j <count;++j)
		{
			TCHAR sz[512] = {0};
			TCHAR name[64] = {0};
			wsprintf(name,TEXT("%d"),j);
			size = sizeof(sz);
			lResult= RegQueryValueEx(key,name,0,&type,(LPBYTE)sz,&size);

			lResult = RegOpenKeyEx(keyEnum,sz,0,KEY_READ,&key2);
			if (ERROR_SUCCESS)
			{
				RegCloseKey(keyEnum);
				return;
			}

			size = sizeof(sz);
			lResult = RegQueryValueEx(key2,TEXT("FriendlyName"),0,&type,(LPBYTE)sz,&size);
			if(lResult == ERROR_FILE_NOT_FOUND)
			{
				size = sizeof(sz);
				lResult = RegQueryValueEx(key2,TEXT("DeviceDesc"),0,&type,(LPBYTE)sz,&size);
				chCardName[j] = sz;//�����Կ�����
			};
			RegCloseKey(key2);
			key2 = NULL;
		};
		RegCloseKey(key);
		key = NULL;
		break;
	}
}

