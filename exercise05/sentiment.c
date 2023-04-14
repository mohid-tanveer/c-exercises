#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

#define MAP_SIZE (1 << 14)
#define BUFFER_SIZE 2048

// Represents the sentiment value for a single word/term.
typedef struct sentiment_t {
  double pos; // mean positive sentiment for the term
  double neg; // mean negative sentiment for the term
  int count;  // number of times the term appears
} sentiment_t;

// Map from string words/terms to sentiment_t values.
map_t *sentiments = NULL;

// Convert a string to lower case and strip whitespace and punctuation.
//
// Resizes string by nulling the unused suffix.
void lower_and_strip(char *str) {
  char *t = str; // insert point
  char *c = str; // current char
  for (; *c; c++) {
    if (isalnum(*c)) {
      // convert to lowercase; append at insert point.
      *t = tolower(*c); // t <= c
      t++;
    }
  }
  // c is null terminator; cut end of string after alnum chars.
  while (t < c) {
    *(t++) = '\0';
  }
}

// Print a single entry in a map string -> sentiment_t.
void *print_map_entry(const char *key, void *value) {
  sentiment_t *v = value;
  printf("%s : +%f -%f (%d)\n", key, v->pos, v->neg, v->count);
  return value;
}

// Free a single value from a map.
void *free_map_value(const char *key, void *value) {
  free(value);
  return NULL;
}

// Free all values in a map.
void free_map_values() { map_apply(sentiments, free_map_value); }

// Print all sentiments in a map string -> sentiment_t.
void dump_sentiments() { map_apply(sentiments, print_map_entry); }

// Build a map string -> sentiment_t by parsing input file.
//
// Modifies sentiments map.
void build_sentiment_map(FILE *f) {
  if (sentiments) {
    free_map_values();
    map_free(&sentiments);
  }
  sentiments = map_create(MAP_SIZE);
  char buff[BUFFER_SIZE];
  int line_no = -1;
  while (fgets(buff, BUFFER_SIZE, f) != NULL) {
    line_no++;
    // clang-format off
    //
    // Line is ether:
    // POS<TAB>ID<TAB>PosScore<TAB>NegScore<TAB>Word#n Word#n Word#n ...<TAB>Definition
    // OR
    // # this line is a comment since it starts with #
    //
    // clang-format on

    // end of the file
    if (feof(f)) {
      printf("end of file. at line #%d", line_no);
      break;
    }
    // comment line
    if (buff[0] == '#') {
      continue;
    }
    // isolate starter stuff
    char *pos = strtok(buff, "\t");
    char *id = strtok(NULL, "\t");
    char *posScoreTok = strtok(NULL, "\t");
    char *negScoreTok = strtok(NULL, "\t");
    char *words = strtok(NULL, "\t");
    if (!pos || !id || !posScoreTok || !negScoreTok || !words) {
      continue;
    }
    double posScore = atof(posScoreTok);
    double negScore = atof(negScoreTok);

    char *word = words;
    // iterate through words stripping them and added to map if not already in
    while (word != NULL && *word != '\0') {
      char curWord[BUFFER_SIZE];
      char *wheresHash = strchr(word, '#');
      if (wheresHash != NULL) {
        snprintf(curWord, wheresHash - word + 1, "%s", word);
      } else {
        break;
      }
      lower_and_strip(curWord);
      sentiment_t *sentiment;
      int inMap = map_get(sentiments, curWord, (void **)&sentiment);
      if (!inMap) {
        sentiment = (sentiment_t *)malloc(sizeof(sentiment_t));
        sentiment->pos = posScore;
        sentiment->neg = negScore;
        sentiment->count = 1;
        map_put(sentiments, curWord, sentiment);
      } else {
        sentiment->count++;
        sentiment->pos += (posScore - sentiment->pos) / sentiment->count;
        sentiment->neg += (negScore - sentiment->neg) / sentiment->count;
      }
      words = NULL;
      word += strcspn(word, " \t");
      word += strspn(word, " \t");
    }
  }
}

void sentiment_stdin() {
  char buffer[BUFFER_SIZE];
  char input[BUFFER_SIZE];
  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
    size_t buff_len = strlen(buffer);
    if (buffer[buff_len - 1] == '\n') {
      buffer[buff_len - 1] = '\0';
    }
    strncpy(input, buffer, BUFFER_SIZE);
    double sentiment = 0.0;
    char *word = strtok(input, " ");
    // go through words in input getting the sentiment values and added them to
    // the overall sentiment
    while (word != NULL) {
      lower_and_strip(word);
      sentiment_t *sentimentT;

      if (map_get(sentiments, word, (void **)&sentimentT)) {
        sentiment += sentimentT->pos - sentimentT->neg;
      }
      word = strtok(NULL, " ");
    }
    printf("%s : %f\n", buffer, sentiment);
  }
}

void usage(char *name) {
  printf("Usage: %s <sentiment_file.txt>\n", name);
  exit(1);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Must supply filename.\n");
    usage(argv[0]);
  }

  FILE *f = fopen(argv[1], "r");
  if (!f) {
    perror("fopen");
    exit(1);
  }
  fprintf(stderr, "loading sentiment map...");
  // Build the map of sentiments...
  build_sentiment_map(f);
  fprintf(stderr, "loaded.\n");
  // if you want to get sentiments out of your map in order to debug:
  // dump_sentiments();
  // Read sentiments from standard in...
  sentiment_stdin();

  free_map_values();
  map_free(&sentiments);
}
