#include <Windows.h>
#include "options.h"
#include "regedit.h"
#include "errors.h"
#include "macros.h"

void set_log_path(char *options, char (*params)[100], char (*messages)[100])
{
	INT val_ret;

	if (has_option('L', options) && messages[1][0] != '\0')	{
		val_ret = store_var("log", messages[1]);
		if (val_ret == EXIT_SUCCESS)
			MessageBox(NULL, "diskcleaner log path changed successfully !", "diskcleaner", MB_ICONINFORMATION);
		else
			display_error_msg("diskcleaner log path change failed : ", val_ret);
	}
	if (has_option('L', options) && messages[1][0] == '\0')
		display_usage_error();
}

void set_path(char *options, char (*params)[100], char (*messages)[100])
{
	INT val_ret;

	if (has_option('p', options) && messages[0][0] != '\0')	{
		val_ret = store_var("path", messages[0]);
		if(val_ret == EXIT_SUCCESS)
			MessageBox(NULL, "diskcleaner path changed successfully !", "diskcleaner", MB_ICONINFORMATION);
		else
			display_error_msg("diskcleaner path change failed : ", val_ret);
	}
	if (has_option('p', options) && messages[0][0] == '\0')
		display_usage_error();
}

BOOL InstallMyService()
{
	char strDir[1024 + 1];
	SC_HANDLE schSCManager, schService;

	GetCurrentDirectory(1024, strDir);
	strcat(strDir, "\\"MY_SERVICE_BIN_NAME);
	if ((schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) {
		display_error_msg("InstallMyService", GetLastError());
		return (TRUE);
	}
	schService = CreateService(schSCManager, MY_SERVICE_NAME, MY_SERVICE_DESCRIPTOR,
								SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
								(LPCTSTR)strDir, NULL, NULL, NULL, NULL, NULL);
	if (schService == NULL)	{
		display_error_msg("InstallMyService", GetLastError());
		return (FALSE);
	}
	CloseServiceHandle(schService);
	MessageBox(NULL, "diskcleaner installed in services !", "diskcleaner", MB_ICONINFORMATION);
	return (TRUE);
}

BOOL DeleteMyService()
{
	SC_HANDLE schSCManager, hService;

	if ((schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) {
		display_error_msg("DeleteMyService", GetLastError());
		return (FALSE);
	}
	if ((hService = OpenService(schSCManager, MY_SERVICE_NAME, SERVICE_ALL_ACCESS)) == NULL) {
		display_error_msg("DeleteMyService", GetLastError());
		return (FALSE);
	}
	if (!DeleteService(hService)) {
		display_error_msg("DeleteMyService", GetLastError());
		return (FALSE);
	}
	if (!CloseServiceHandle(hService)) {
		display_error_msg("DeleteMyService", GetLastError());
		return (FALSE);
	}
	MessageBox(NULL, "diskcleaner deleted from services !", "diskcleaner", MB_ICONINFORMATION);
}