#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// Function to display help message
void display_help() {
    printf("Usage: locate [OPTIONS] <directory> <filename>\n");
    printf("Options:\n");
    printf("  -h, --help          Show this help message and exit.\n");
    printf("  -c, --count         Only display the total count of matches.\n");
    printf("  -r, --recursive     Search directories recursively (default behavior).\n");
    printf("  -n, --no-recursive  Do not search directories recursively.\n");
    printf("\n");
}

// Function to search for a file or directory by name in a given path.
void search_in_directory(const char *directory, const char *filename, int *found_count, int recursive) {
    struct dirent *entry;
    DIR *dp = opendir(directory);

    // Check if directory can be opened
    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        // Skip current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Build the full path of the current entry
        char path[4096];
        snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);

        // Check if the current entry matches the target filename
        if (strcmp(entry->d_name, filename) == 0) {
            printf("Found: %s\n", path);
            (*found_count)++;
        }

        // If the current entry is a directory, search recursively if enabled
        if (recursive) {
            struct stat entry_stat;
            if (stat(path, &entry_stat) == 0 && S_ISDIR(entry_stat.st_mode)) {
                search_in_directory(path, filename, found_count, recursive);
            }
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    // Default options
    int recursive = 1;
    int count_only = 0;

    // Parse command-line arguments
    int arg_index = 1;
    while (arg_index < argc && argv[arg_index][0] == '-') {
        if (strcmp(argv[arg_index], "-h") == 0 || strcmp(argv[arg_index], "--help") == 0) {
            display_help();
            return EXIT_SUCCESS;
        } else if (strcmp(argv[arg_index], "-c") == 0 || strcmp(argv[arg_index], "--count") == 0) {
            count_only = 1;
        } else if (strcmp(argv[arg_index], "-r") == 0 || strcmp(argv[arg_index], "--recursive") == 0) {
            recursive = 1;
        } else if (strcmp(argv[arg_index], "-n") == 0 || strcmp(argv[arg_index], "--no-recursive") == 0) {
            recursive = 0;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[arg_index]);
            display_help();
            return EXIT_FAILURE;
        }
        arg_index++;
    }

    // Check for remaining arguments
    if (argc - arg_index != 2) {
        fprintf(stderr, "Error: Missing required arguments.\n");
        display_help();
        return EXIT_FAILURE;
    }

    const char *directory = argv[arg_index];
    const char *filename = argv[arg_index + 1];
    int found_count = 0;

    // Start searching for the file or directory
    search_in_directory(directory, filename, &found_count, recursive);

    // Print results
    if (count_only) {
        printf("Total matches found: %d\n", found_count);
    } else {
        if (found_count == 0) {
            printf("No matches found for '%s' in '%s'.\n", filename, directory);
        } else {
            printf("Total matches found: %d\n", found_count);
        }
    }

    return EXIT_SUCCESS;
}
