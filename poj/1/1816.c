#include <stdio.h>

int match(const char *text, const char *pat)
{
  if (*text == '\0' && *pat == '\0') {
    return 1;
  } else if (*pat == '*') {
    return match(text, pat+1) || (*text != '\0' && match(text+1, pat));
  } else if (*pat == '?') {
    return *text != '\0' && match(text+1, pat+1);
  } else {
    return *text != '\0' && *pat != '\0' && *text == *pat && match(text+1, pat+1);
  }
}

int main(void)
{
  int N, M;
  scanf("%d %d", &N, &M);
  static char pats[100000][7];
  int i;
  for (i = 0; i < N; i++) {
    scanf("%s", pats[i]);
  }
  for (i = 0; i < M; i++) {
    char text[21];
    scanf("%s", text);

    int j;
    int any = 0;
    for (j = 0; j < N; j++) {
      if (match(text, pats[j])) {
        printf("%d ", j);
        any = 1;
      }
    }
    if (any) {
      puts("");
    } else {
      puts("Not match");
    }
  }
  return 0;
}