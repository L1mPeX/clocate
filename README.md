# Clocate

A simple C program to search for files or directories by name within a specified directory. It supports recursive and non-recursive searches and provides several functional flags for enhanced usability.

## Features

- Search for a file or directory by name within a specified directory.
- Recursive search (default behavior) with an option to disable it.
- Display the total count of matches or detailed paths.
- Help menu to understand usage and options.

---

## Usage

```bash
clocate [OPTIONS] <directory> <filename>
```

### Options

- `-h, --help`: Show the help message and exit.
- `-c, --count`: Display only the total count of matches.
- `-r, --recursive`: Search directories recursively (default behavior).
- `-n, --no-recursive`: Do not search directories recursively.

### Examples

1. **Recursive search for a file:**
   ```bash
   ./clocate -r /home/user documents
   ```
   Search recursively in `/home/user` for files or directories named `documents`.

2. **Non-recursive search:**
   ```bash
   ./clocate -n /home/user documents
   ```
   Search only in `/home/user` without descending into subdirectories.

3. **Count matches:**
   ```bash
   ./clocate -c /home/user documents
   ```
   Display the total number of matches found.

4. **Help menu:**
   ```bash
   ./clocate -h
   ```
   Display help information.

---

## Compilation

To compile the program, use the `gcc` compiler:

```bash
gcc clocate.c -o clocate
```

This command generates an executable named `clocate` in the current directory.

---

## Error Handling

1. **Directory not found:**
   If the specified directory does not exist or cannot be opened, the program will display an error message:
   ```bash
   opendir: No such file or directory
   ```

2. **Invalid arguments:**
   If insufficient or incorrect arguments are provided, the program will display an error and the help menu:
   ```bash
   Error: Missing required arguments.
   Usage: clocate [OPTIONS] <directory> <filename>
   ```

3. **Unknown flags:**
   If an unsupported flag is used, the program will display an error message and exit:
   ```bash
   Unknown option: -x
   Usage: clocate [OPTIONS] <directory> <filename>
   ```

---

## Notes

- The program can handle paths up to 4096 characters.
- Recursive search may take longer depending on the depth and size of the directory structure.
- The program only matches files or directories by their exact name.
