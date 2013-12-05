#include <Windows.h>
#include <stdio.h>
#include "errors.h"
#include "params.h"
#include "options.h"
#include "service.h"
#include "actions.h"
#include "macros.h"
#include "process.h"

int main(int argc, char* argv[])
{
	char lastBad;
	char options[10], params[100][100], message[100][100];
	
	lastBad = '\0';
	message[0][0] = '\0';
	message[1][0] = '\0';
	lastBad = getOpts(argc, argv, options, message);
	getParams(argc, argv, params);
	if (lastBad != '\0')
		return display_usage_error();

	set_path(options, params, message);
	set_log_path(options, params, message);

	if (argc > 1) {
		if (isActiveOpt('i', options) && isActiveOpt('d', options))
			return display_usage_error();
		if (isActiveOpt('i', options))
			InstallMyService();
		else if (isActiveOpt('d', options))
			DeleteMyService();
	}
	else {
		SERVICE_TABLE_ENTRY DispatchTable[]={{MY_SERVICE_NAME, ServiceMain}, {NULL, NULL}};
		StartServiceCtrlDispatcher(DispatchTable);
	}
	return (EXIT_SUCCESS);
}
