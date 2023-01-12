#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <zip.h>

char *add_slash(char *path)
{
	long int lenth = strlen(path);
	char *path_add_slash = malloc(sizeof(char) * (lenth + 2));
	strncpy(path_add_slash, path, lenth);
	path_add_slash[lenth] = '/';
	path_add_slash[lenth + 1] = '\0';
	return path_add_slash;
}

void show_stat_zip(struct stat *st)
{
	printf("mode : %o\n", st->st_mode);
	printf("size : %ld\n", st->st_size);
}

void show_stat_file(zip_stat_t *st)
{
	printf("size : %ld\n", st->size);
}

int main(int argc, char *argv[])
{
	char *full_path = argv[argc - 1];
	char buf[50] = { 0 };
	char *delim = ":";
	char *fname = NULL;
	char *archive_name = NULL;
	zip_t *archive = NULL;
	zip_stat_t file_stat;
	zip_stat_init(&file_stat);
	struct stat stat_buff;
	int err = 0, count = 0;

	strcpy(buf, full_path);
	archive_name = strtok(buf, delim);
	long lenth = strlen(archive_name);
	fname = full_path + lenth;

	archive = zip_open(archive_name, ZIP_CHECKCONS, &err);
	if (archive == NULL) {
		printf("error: Fail to open archive %s\n", archive_name);
		exit(1);
	}
	char *path_slash = add_slash(fname + 1);
	if (strcmp(fname, "\0") == 0) {
		// root
		printf("root\n");
		stat(archive_name, &stat_buff);
		show_stat_zip(&stat_buff);
	} else if (zip_name_locate(archive, path_slash, 0) != -1) {
		// is dir
		zip_stat(archive, path_slash, 0, &file_stat);
		printf("is dir\n");
		show_stat_file(&file_stat);
	} else if (zip_name_locate(archive, fname + 1, 0) != -1) {
		// is file
		zip_stat(archive, fname + 1, 0, &file_stat);
		printf("is file\n");
		show_stat_file(&file_stat);
	} else {
		printf("no such file\n");
		return 1;
	}

	zip_close(archive);
}
