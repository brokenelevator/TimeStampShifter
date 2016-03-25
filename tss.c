#define _UNICODE
#define _WIN32_WINNT 0x0601

#define WEEKinSECONDS 604800LL
#define DAYinSECONDS 86400LL
#define HOURinSECONDS 3600LL
#define MINUTEinSECONDS 60LL

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

HANDLE target;
FILETIME creation_time_stamp;
FILETIME access_time_stamp;
FILETIME edit_time_stamp;
ULARGE_INTEGER time_stamp;
ULARGE_INTEGER offset;

int _tmain(int argc, _TCHAR* argv[])
{
if(argc != 11)
        {
        printf("\nTimeStampShifter\n\nUsage: tss [target] [creation] [access] [write] [direction] [weeks] [days] [hours] [minutes] [seconds]\n\ntarget - file to save timestamp[s] to\ncreation, access, write - timestamp options:\n\tc - replace the timestamp\n\tx - leave unchanged\ndirection:\n\t+(plus) shift forwards(towards the future)\n\t-(minus) shift backwards(towards the past)\nweeks, days, hours, minutes, seconds - amount of time to shift\n");
        return 0;
        }
target = CreateFile(argv[1], GENERIC_READ | FILE_WRITE_ATTRIBUTES, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
if(target == INVALID_HANDLE_VALUE)
        {
        printf("Could not open file.");
        return -1;
        }
int tmp = 0;
tmp = GetFileTime(target, &creation_time_stamp, &access_time_stamp, &edit_time_stamp);
if(tmp == 0)
        {
        printf("Getting timestamps failed");
        CloseHandle(target);
        return -1;
        }
offset.QuadPart = (((_wtoi(argv[6])*WEEKinSECONDS)+(_wtoi(argv[7])*DAYinSECONDS)+(_wtoi(argv[8])*HOURinSECONDS)+(_wtoi(argv[9])*MINUTEinSECONDS))+_wtoi(argv[10])) * 10000000LL; //10000000 is amount of 100 nanosecond intervals in 1 second
if(wcscmp(argv[2], L"c") == 0)
        {
		time_stamp.LowPart=creation_time_stamp.dwLowDateTime;
		time_stamp.HighPart=creation_time_stamp.dwHighDateTime;
		if(wcscmp(argv[5], L"+") == 0) time_stamp.QuadPart += offset.QuadPart;
		else if(wcscmp(argv[5], L"-") == 0) time_stamp.QuadPart -= offset.QuadPart;
		else
			{
			printf("Wrong direction");
			CloseHandle(target);
			return -1;
			};
		creation_time_stamp.dwLowDateTime = time_stamp.LowPart;
		creation_time_stamp.dwHighDateTime = time_stamp.HighPart;
        tmp = SetFileTime(target, &creation_time_stamp, (LPFILETIME) NULL, (LPFILETIME) NULL);
        if(tmp == 0)
                {
                printf("Changing timestamps failed");
                CloseHandle(target);
                return -1;
                }
        }
if(wcscmp(argv[3], L"c") == 0)
        {
		time_stamp.LowPart=access_time_stamp.dwLowDateTime;
		time_stamp.HighPart=access_time_stamp.dwHighDateTime;
		if(wcscmp(argv[5], L"+") == 0) time_stamp.QuadPart +=  offset.QuadPart;
		else if(wcscmp(argv[5], L"-") == 0) time_stamp.QuadPart -= offset.QuadPart;
		else
			{
			printf("Wrong direction");
			CloseHandle(target);
			return -1;
			};
		access_time_stamp.dwLowDateTime = time_stamp.LowPart;
		access_time_stamp.dwHighDateTime = time_stamp.HighPart;
        tmp = SetFileTime(target, (LPFILETIME) NULL, &access_time_stamp, (LPFILETIME) NULL);
        if(tmp == 0)
                {
                printf("Changing timestamps failed");
                CloseHandle(target);
                return -1;
                }
        }
if(wcscmp(argv[4], L"c") == 0)
        {
		time_stamp.LowPart=edit_time_stamp.dwLowDateTime;
		time_stamp.HighPart=edit_time_stamp.dwHighDateTime;
		if(wcscmp(argv[5], L"+") == 0) time_stamp.QuadPart += offset.QuadPart;
		else if(wcscmp(argv[5], L"-") == 0) time_stamp.QuadPart -= offset.QuadPart;
		else
			{
			printf("Wrong direction");
			CloseHandle(target);
			return -1;
			};
		edit_time_stamp.dwLowDateTime = time_stamp.LowPart;
		edit_time_stamp.dwHighDateTime = time_stamp.HighPart;
        tmp = SetFileTime(target, (LPFILETIME) NULL, (LPFILETIME) NULL, &edit_time_stamp);
        if(tmp == 0)
                {
                printf("Changing timestamps failed");
                CloseHandle(target);
                return -1;
                }
        }
CloseHandle(target);
return 0;
}

