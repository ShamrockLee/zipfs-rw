#define FUSE_USE_VERSION 31

#include <errno.h>
#include <fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <zip.h>

zip_t *archive = NULL;
char *archive_name = NULL;
struct stat archive_stat;

static char *add_slash(const char *path)
{
	long int lenth = strlen(path);
	char *path_add_slash = malloc(sizeof(char) * (lenth + 2));
	strncpy(path_add_slash, path, lenth);
	path_add_slash[lenth] = '/';
	path_add_slash[lenth + 1] = '\0';
	return path_add_slash;
}

static int zipfs_getattr(const char *path, struct stat *stbuf)
{
	printf("path : %s\n", path);
	zip_stat_t file_stat;
	zip_stat_init(&file_stat);
	const char *path_slash = add_slash(path + 1);

	if (strcmp(path, "/") == 0) {
		// root
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_size = archive_stat.st_size;
		stbuf->st_atime = archive_stat.st_atime;
		stbuf->st_ctime = archive_stat.st_ctime;

	} else if (zip_name_locate(archive, path_slash, 0) != -1) {
		// dir
		zip_stat(archive, path_slash, 0, &file_stat);
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_size = 0;
		stbuf->st_mtime = file_stat.mtime;
	} else if (zip_name_locate(archive, path + 1, 0) != -1) {
		// file
		zip_stat(archive, path_slash, 0, &file_stat);
		stbuf->st_mode = S_IFREG | 0777;
		stbuf->st_size = file_stat.size;
		stbuf->st_mtime = file_stat.mtime;
	} else {
		return -ENOENT;
	}
	return 0;
}

static struct fuse_operations zipfs_oper = { .getattr = zipfs_getattr

};

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("./zipfs <file.zip> <mount_point>\n");
		exit(1);
	}

	archive_name = argv[1];
	archive = zip_open(archive_name, ZIP_CREATE, NULL);
	if (archive == NULL) {
		printf("fail to open the archive\n");
		exit(1);
	}

	stat(archive_name, &archive_stat);

	char *args[2];
	args[0] = argv[0];
	args[1] = argv[2];
	return fuse_main(argc - 1, args, &zipfs_oper, NULL);
}
