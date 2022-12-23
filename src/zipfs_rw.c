#include <config.h>

#include <stringify.h>

#include <fuse.h>
#include <zip.h>

#define OPTPARSE_IMPLEMENTATION
#include <optparse.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	(void)argc;
	struct optparse_long longopts[] = {
		{ "help", 'h', OPTPARSE_NONE },
		{ "version", 'V', OPTPARSE_NONE },
		{ NULL },
	};

	static const char *str_help =
		"Usage:\n"
		" zipfs-rw -h\n"
		"\n"
		"Mount a ZIP file read-only or read-write.\n"
		"\n"
		"Options:\n"
		" -h, --help              Display this help message and exit.\n"
		" -V, --version           Display the version and exit.\n"
		"\n"
		"For more details, see zipfs-rw(8)\n";

	int option;
	struct optparse options;

	optparse_init(&options, argv);
	while ((option = optparse_long(&options, longopts, NULL)) != -1) {
		switch (option) {
		case 'h':
			fputs(str_help, stderr);
			break;
		case 'V':
			fputs(stringify_expanded(VERSION) "\n", stderr);
			break;
		case '?':
			fprintf(stderr, "%s: %s\n", argv[0], options.errmsg);
			exit(EXIT_FAILURE);
			break;
		}
	}

	if (options.optind < 2) {
		fprintf(stderr, "Expects <source> and <mountpoint>\n");
		exit(EXIT_FAILURE);
	}
	const char *source = optparse_arg(&options);
	const char *mountpoint = optparse_arg(&options);

	// Awaiting implementation
	(void)mountpoint;
	(void)source;

	return EXIT_SUCCESS;
}
