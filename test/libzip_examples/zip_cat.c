#include <zip.h>

#include <stdio.h>
#include <stdlib.h>

// Size of buffer_cat
#ifndef BUFFER_SIZE_CAT
#define BUFFER_SIZE_CAT 4096
#endif /* BUFFER_SIZE_CAT */

int main(int argc, char *argv[])
{
	// Integer to store exit status
	int ret_full = EXIT_SUCCESS;
	// Check the number of input arguments
	if (argc <= 2) {
		fprintf(stderr, "zip-cat: Expect arguments ZIPFILE SUBPATH\n");
		return EXIT_FAILURE;
	}
	// Path to the ZIP archive
	const char *path_zipfile = argv[1];
	// Sub-path of the file inside the archive
	const char *subpath = argv[2];
	// Integer to store the error code from libzip functions
	int errno_zip = 0;
	// Pointer to the structure representing the ZIP archive being opened
	// Open the ZIP archive
	struct zip *p_zip_in = zip_open(path_zipfile, ZIP_RDONLY, &errno_zip);
	if (!p_zip_in) {
		fprintf(stderr, "zip-cat: zip_open: Failed with exit code %d\n",
			errno_zip);
		return errno_zip;
	}
	// Pointer to the structure representing the file inside the ZIP archive
	// Open the file inzide the ZIP archive by specifying the subdir
	struct zip_file *p_file_target = zip_fopen(p_zip_in, subpath, 0);
	if (!p_file_target) {
		fprintf(stderr,
			"zip-cat: zip_fopen: Failed to open subpath %s in ZIP file %s",
			subpath, path_zipfile);
		ret_full = EXIT_FAILURE;
		goto finalize_zip_in;
	}
	// Content buffer to cat
	char *buffer_cat[BUFFER_SIZE_CAT];
	// Number of bytes actually read
	zip_int64_t nbytes_read;
	// Read from the file inside the ZIP archive
	// Loop until EOL has already reached during the previous iteration
	while ((nbytes_read = zip_fread(p_file_target, buffer_cat,
					BUFFER_SIZE_CAT)) > 0) {
		// Write what is read out to stdin
		fwrite(buffer_cat, nbytes_read, 1, stdout);
	}
	// Negative read-byte means error during zip_fread().
	if (nbytes_read < 0) {
		fprintf(stderr, "zip-cat: zip_fead: Failed");
		ret_full = EXIT_FAILURE;
		goto finalize_file_target;
	}
finalize_file_target:
	// Close the file inside the ZIP archive
	// if the pointer is not NULL
	if (p_file_target) {
		zip_fclose(p_file_target);
	}
finalize_zip_in:
	// Close the ZIP archive
	// if the pointer is not NULL
	if (p_zip_in) {
		zip_close(p_zip_in);
	}
	return ret_full;
}
