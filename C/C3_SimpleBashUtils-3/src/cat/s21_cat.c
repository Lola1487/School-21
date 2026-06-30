#include <getopt.h>
#include <stdio.h>

typedef struct {
  int v;
  int b;
  int e;
  int n;
  int s;
  int t;
} catOptions;

typedef struct {
  int stringCount;
  int emptyStringCount;
  int lastSimb;
} catCounters;

int readOptions(int argc, char *argv[], catOptions *catOpts);

void printFile(FILE *file, catOptions *catOpts, catCounters *catCount);

int main(int argc, char *argv[]) {
  catOptions catOpts = {0, 0, 0, 0, 0, 0};
  catCounters catCount = {1, 0, '\n'};

  if (argc > 1 && readOptions(argc, argv, &catOpts)) {
    if (optind < argc) {
      while (optind < argc) {
        FILE *file = fopen(argv[optind++], "r");
        if (file != NULL) {
          printFile(file, &catOpts, &catCount);
          fclose(file);
        } else {
          printf("cat: %s: No such file or directory\n", argv[optind - 1]);
        }
      }
    } else {
      printf("no files\n");
    }
  } else {
    printf("Invalid options\n");
  }
  return 0;
}

int readOptions(int argc, char *argv[], catOptions *catOpts) {
  int flag = 0;
  int correctOpts = 1;

  struct option catLongOptions[] = {{"number-nonblank", 0, 0, 'b'},
                                    {"number", 0, 0, 'n'},
                                    {"squeeze-blank", 0, 0, 's'},
                                    {0, 0, 0, 0}};

  while ((flag = getopt_long(argc, argv, "vbeEnstT", catLongOptions, NULL)) !=
         -1) {
    switch (flag) {
      case 'v':
        catOpts->v = 1;
        break;
      case 'b':
        catOpts->b = 1;
        break;
      case 'e':
        catOpts->e = 1;
        catOpts->v = 1;
        break;
      case 'E':
        catOpts->e = 1;
        break;
      case 'n':
        catOpts->n = 1;
        break;
      case 's':
        catOpts->s = 1;
        break;
      case 't':
        catOpts->t = 1;
        catOpts->v = 1;
        break;
      case 'T':
        catOpts->t = 1;
        break;
      default:
        correctOpts = 0;
    }
  }
  if (catOpts->n && catOpts->b) {
    catOpts->n = 0;
  }
  return correctOpts;
}

void printFile(FILE *file, catOptions *catOpts, catCounters *catCount) {
  int simb;

  while ((simb = getc(file)) != EOF) {
    int canBePrinted = 1;

    if (catOpts->s && catCount->lastSimb == '\n' && simb == '\n') {
      catCount->emptyStringCount++;
      if (catCount->emptyStringCount > 1) {
        canBePrinted = 0;
      }
    } else {
      catCount->emptyStringCount = 0;
    }

    if (canBePrinted) {
      if (catOpts->n && catCount->lastSimb == '\n') {
        printf("%6d\t", catCount->stringCount++);
      }

      if (catOpts->b && catCount->lastSimb == '\n' && simb != '\n') {
        printf("%6d\t", catCount->stringCount++);
      }

      if (catOpts->t && simb == '\t') {
        printf("^");
        simb = 'I';
      }

      if (catOpts->v && simb != '\n' && simb != '\t') {
        if (simb >= 128) {
          simb -= 128;
          printf("M-");
        }

        if (simb < 32 || simb == 127) {
          simb ^= 0x40;
          printf("^");
        }
      }

      if (catOpts->e && simb == '\n') {
        printf("$");
      }
      catCount->lastSimb = simb;
      printf("%c", simb);
    }
  }
}
