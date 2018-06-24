#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <uci.h>

// Simple define a related package
#define UCI_CFG_PKG "network"
#define UCI_PACKAGE "network"
#define UCI_SECTION "lan"
#define UCI_OPTION "ipaddr"
#define UCI_VALUE "192.168.2.12"

static int uci_set_option_string(const char *section, const char *option, const char *value)
{
	int ret;
	struct uci_context *ctx = NULL;
	struct uci_package* pkg;
	struct uci_section* sec;
	struct uci_ptr ptr;
	char* err_str = NULL;

	ctx = uci_alloc_context();              // apply a context
	if (ctx == NULL)
	{
		printf("Failed to alloc uci context\n");
		return -1;
	}

	ret = uci_load(ctx, UCI_CFG_PKG, &pkg);         // Load required uci file
	if (ret != 0 || pkg == NULL)
	{
		printf("Failed to load package: '%s' with error\n", UCI_CFG_PKG);
		goto error_pkg;
	}

	sec = uci_lookup_section(ctx, pkg, section);
	if (sec == NULL)
	{
		printf("Failed to find section: '%s'\n", section);
		goto error_msg;
	}

	memset(&ptr, 0, sizeof(struct uci_ptr));
	ptr.package = UCI_PACKAGE;
	ptr.section = section;
	ptr.option = option;
	ptr.value = value;
	ptr.p = pkg;
	ptr.s = sec;

	ret = uci_set(ctx, &ptr);
	if (ret != 0)
	{
		printf("Failed to set option: '%s' with error\n", option);
		goto error_uci;
	}

	uci_save(ctx, pkg);
	uci_commit(ctx, &pkg, true);           // Commit the changes or it will not effect the local file.
	uci_unload(ctx, pkg);
	uci_free_context(ctx);

	return 0;

error_uci:
	uci_unload(ctx, pkg);
error_pkg:
	free(err_str);
	return -1;
error_msg:
	uci_unload(ctx, pkg);
	return -1;
}

int main(void)
{
	uci_set_option_string(UCI_SECTION, UCI_OPTION, UCI_VALUE);

	return 0;
}

