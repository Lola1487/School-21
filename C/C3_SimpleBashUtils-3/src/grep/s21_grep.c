#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} grepOptions;

typedef struct {
  int matchedLines;
  int totalMatches;
  char *patterns[128];
  int patternCount;
} grepCounter;

int ReadOptions(int argc, char **argv, grepOptions *options,
                grepCounter *counter);
void AddPatern(grepCounter *counter, char *pattern);
void ReadPatternsFromFile(const char *filename, char *line);
void FreePatterns(grepCounter *counter);
void PrintFile(FILE *file, grepOptions *options, grepCounter *counter,
               const char *filename, int fileCount);

int main(int argc, char **argv) {
  grepOptions options = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  grepCounter counter = {0};

  if (!ReadOptions(argc, argv, &options, &counter)) {
    fprintf(stderr, "Usage: %s [OPTIONS] PATTERN [FILES...]\n", argv[0]);
    FreePatterns(&counter);
    return 1;
  }

  if (counter.patternCount == 0) {
    fprintf(stderr, "No patterns provided.\n");
    FreePatterns(&counter);
    return 1;
  }

  int fileCount = argc - optind;

  for (int i = optind; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (!file) {
      if (!options.s) {
        perror(argv[i]);
      }
      continue;
    }
    PrintFile(file, &options, &counter, argv[i], fileCount);
    fclose(file);
  }

  FreePatterns(&counter);

  return 0;
}

int ReadOptions(int argc, char **argv, grepOptions *options,
                grepCounter *counter) {
  int simbol;

  while ((simbol = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (simbol) {
      case 'e':
        options->e = 1;
        AddPatern(counter, optarg);
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f': {
        char *line = (char *)malloc(sizeof(char) * 128);
        ReadPatternsFromFile(optarg, line);
        AddPatern(counter, line);
        free(line);
        break;
      }

      case 'o':
        options->o = 1;
        break;
      default:
        return 0;
    }
  }

  if (counter->patternCount == 0 && optind < argc) {
    AddPatern(counter, argv[optind++]);
  }

  return 1;
}

void AddPatern(grepCounter *counter, char *pattern) {
  const char *specials = "\\.^$|()[]**?{}";
  size_t length = 0;

  for (const char *p = pattern; *p; p++) {
    if (strchr(specials, *p)) {
      length++;
    }
    length++;
  }

  char *escaped = malloc(length + 1);
  if (!escaped) {
    perror("malloc");
    exit(1);
  }

  char *out = escaped;
  for (const char *p = pattern; *p; p++) {
    if (strchr(specials, *p)) {
      *out++ = '\\';
    }
    *out++ = *p;
  }
  *out = '\0';

  if (counter->patternCount < 128) {
    counter->patterns[counter->patternCount++] = escaped;
  } else {
    fprintf(stderr, "Too many patterns\n");
    free(escaped);
    exit(1);
  }
}

void ReadPatternsFromFile(const char *filename, char *line) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening pattern file");
    exit(1);
  }
  fgets(line, sizeof(line), file);
  fclose(file);
}

void FreePatterns(grepCounter *counter) {
  for (int i = 0; i < counter->patternCount; i++) {
    free((void *)counter->patterns[i]);
  }
}

void PrintFile(FILE *file, grepOptions *options, grepCounter *counter,
               const char *filename, int fileCount) {
  if (counter->patternCount == 0) {
    fprintf(stderr, "No patterns provided for matching.\n");
    return;
  }

  char line[4096];
  int lineNumber = 0;
  int matchedInFile = 0;
  regex_t compiledPatterns[128];
  int compileFlags = REG_EXTENDED | REG_NEWLINE;

  if (options->i) {
    compileFlags |= REG_ICASE;
  }

  for (int i = 0; i < counter->patternCount; i++) {
    if (regcomp(&compiledPatterns[i], counter->patterns[i], compileFlags) !=
        0) {
      fprintf(stderr, "Error compiling pattern '%s'\n", counter->patterns[i]);
      return;
    }
  }

  while (fgets(line, sizeof(line), file)) {
    lineNumber++;
    line[strcspn(line, "\n")] = '\0';
    int matched = 0;

    for (int i = 0; i < counter->patternCount; i++) {
      regmatch_t match;
      if (regexec(&compiledPatterns[i], line, 1, &match, 0) == 0) {
        matched = 1;

        if (options->v) {
          continue;
        } else if (options->o) {
          const char *ptr = line;
          while (regexec(&compiledPatterns[i], ptr, 1, &match, 0) == 0) {
            if (fileCount > 1 && !options->h) {
              printf("%s:", filename);
            }
            printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
                   ptr + match.rm_so);
            ptr += match.rm_eo;
          }
        }
        break;
      }
    }

    if (options->v) {
      matched = !matched;
    }

    if (matched) {
      matchedInFile++;
      counter->matchedLines++;

      if (options->l) {
        printf("%s\n", filename);
        break;
      }

      if (options->c && !options->l) {
        continue;
      }

      if (!options->o) {
        if (options->n) {
          printf("%d:", lineNumber);
        }
        if (fileCount > 1 && !options->h) {
          printf("%s:", filename);
        }
        printf("%s\n", line);
      }
    }
  }

  if (options->c && !options->l) {
    printf("%d\n", matchedInFile);
  }

  for (int i = 0; i < counter->patternCount; i++) {
    regfree(&compiledPatterns[i]);
  }
}
