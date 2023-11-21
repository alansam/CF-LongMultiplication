//  example data:
//  150353265326
//  22055653351

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define NDEBUG 1

#define LEN_I 100
#define LEN_O (LEN_I + LEN_I)

char * multiply(
  size_t product_sz,
  char * product,
  char * multiplicand,
  char * multiplier);

typedef struct aupair aupair;
struct aupair {
  char first[LEN_I + 1];
  char second[LEN_I + 1];
};

/*
 *  MARK:  show_n_tell()
 */
static
inline
__attribute__((always_inline))
void show_n_tell(char const product[], char const multiplicand[], char const multiplier[]) {
  printf("Product      : %3zu : %s\n", strlen(product), product);
  printf("multiplicand : %3zu : %s\n", strlen(multiplicand), multiplicand);
  printf("multiplier   : %3zu : %s\n", strlen(multiplier), multiplier);
  return;
}

/*
 *  MARK: main()
 */
int main(int argc, char const * argv[]) {
#ifdef RUN_MAIN
  uint8_t a[LEN_I] = { 0, }, b[LEN_I] = { 0, };
  uint8_t ans[LEN_O] = { 0, };
  // int i, j, tmp;
  char s1[LEN_I + 1] = { '\0', }, s2[LEN_I + 1] = { '\0', };
  char p1[LEN_O + 1] = { '\0', };
  char * p1p = NULL;

  int scrc = 0;
  scrc = scanf(" %s", s1);
  if (scrc <= 0) {
    printf("GRONK! scanf() failed.");
    exit(EXIT_FAILURE);
  }
  scrc = scanf(" %s", s2);
  if (scrc <= 0) {
    printf("GRONK! scanf() failed.");
    exit(EXIT_FAILURE);
  }

  printf("%d\n", 10 * 5);
  printf("%d\n", 10 * -5);
  printf("%d\n", -10 * 5);
  printf("%d\n", -10 * -5);

  size_t l1 = strlen(s1);
  size_t l2 = strlen(s2);

  for (ssize_t i = l1 - 1, j = 0; i >= 0; i--, j++) {
    a[j] = s1[i] - '0';
#ifndef NDEBUG
    printf("%2zu %3hhu %04hhx %04hhx\n", j, a[j], (uint8_t) a[j], a[j] + '0');
#endif
  }
  putchar('\n');

  for (ssize_t i = l2 - 1, j = 0; i >= 0; i--, j++) {
    b[j] = s2[i] - '0';
#ifndef NDEBUG
    printf("%2zu %3hhu %04hhx %04hhx\n", j, b[j], (uint8_t) b[j], b[j] + '0');
#endif
  }
  putchar('\n');

  for (size_t i = 0; i < l2; i++) {
    for (size_t j = 0; j < l1; j++) {
      ans[i + j] += b[i] * a[j];
    }
  }

  for (size_t i = 0; i < l1 + l2; i++) {
    uint8_t tmp = ans[i] / 10;
    ans[i] = ans[i] % 10;
    ans[i + 1] = ans[i + 1] + tmp;
  }

  size_t last = l1 + l2;
  for (ssize_t i = l1 + l2; i >= 0; i--) {
    if (ans[i] > 0) {
      break;
    }
    last--;
  }

  printf("Product      : %3zu : ", last + 1ul);
  for (ssize_t i = last; i >= 0; i--) {
    printf("%hhu", ans[i]);
  }
  putchar('\n');
#ifndef NDEBUG
  for (size_t p = 0, ct = 1, lc = 10; p <= last; ++p) {
    printf("%3hhu%s", ans[p], (ct++ % lc == 0 ? "\n" : ""));
  }
  putchar('\n');
#endif

  p1p = multiply(LEN_O + 1, p1, s1, s2);
  show_n_tell(p1, s1, s2);

  char mult[LEN_I + 1] = { '\0', };
  sprintf(mult, "%llu", ULLONG_MAX);
  p1p = multiply(LEN_I + 1, p1, mult, mult);
  show_n_tell(p1p, mult, mult);
#endif /* RUN_MAIN */

  aupair samples[] = {
    { "", "" },
    { "150353265326", "22055653351" },
    {   "100",   "100" },
    {   "100",  "-100" },
    {  "-100",   "100" },
    {  "-100",  "-100" },
    {  "0100",  "0100" },
    { "-0100",  "0100" },
    {  "0100", "-0100" },
    { "-0100", "-0100" },
};
  size_t samples_sz = sizeof samples / sizeof *samples;

  sprintf(samples[0].first, "%llu", ULLONG_MAX);
  sprintf(samples[0].second, "%llu", ULLONG_MAX);

  for (size_t s_ = 0ul; s_ < samples_sz; ++s_) {
    putchar('\n');
    char product[LEN_O + 1] = { '\0', };
    char * product_p = NULL;
    product_p = multiply(LEN_O + 1, product,
                         samples[s_].first,
                         samples[s_].second);
    show_n_tell(product_p,
                samples[s_].first,
                samples[s_].second);
  }
  putchar('\n');

  return EXIT_SUCCESS;
}

/*
 *  MARK: multiply()
 */
char * multiply(
  size_t product_sz,
  char * product,
  char * multiplicand,
  char * multiplier) {

  size_t multiplicand_sz = strlen(multiplicand);
  size_t multiplier_sz   = strlen(multiplier);

  int_fast8_t mdsign = 1;
  int_fast8_t mrsign = 1;
  int_fast8_t sign = 1; 
  if (multiplicand[0] == '-') {
    mdsign = -1;
    multiplicand[0] = '0';
  }
  if (multiplier[0] == '-') {
    mrsign = -1;
    multiplier[0] = '0';
  }
  sign = mdsign * mrsign;

  uint8_t multiplicand_digit[LEN_I] = { 0, };
  uint8_t multiplier_digit[LEN_I] = { 0, };
  uint8_t product_digit[LEN_O] = { 0, };

  //  extract individual from multiplicand
  for (ssize_t i = multiplicand_sz - 1, j = 0; i >= 0; i--, j++) {
    multiplicand_digit[j] = multiplicand[i] - '0';
#ifndef NDEBUG
    printf("%2zu %3hhu %04hhx %04hhx\n",
      j, multiplicand_digit[j], multiplicand_digit[j], multiplicand_digit[j] + '0');
#endif
  }
#ifndef NDEBUG
  for (size_t p = 1, cc = 1, cl = 10; p < multiplicand_sz; ++p) {
    printf("%3hhu%s", multiplicand_digit[p], (cc++ % cl == 0 ? "\n" : ""));
  }
  putchar('\n');
#endif

  //  extract individual from multiplier
  for (ssize_t i = multiplier_sz - 1, j = 0; i >= 0; i--, j++) {
    multiplier_digit[j] = multiplier[i] - '0';
#ifndef NDEBUG
    printf("%2zu %3hhu %04hhx %04hhx\n",
      j, multiplier_digit[j], multiplier_digit[j], multiplier_digit[j] + '0');
#endif
  }
#ifndef NDEBUG
  for (size_t p = 1, cc = 1, cl = 10; p < multiplier_sz; ++p) {
    printf("%3hhu%s", multiplier_digit[p], (cc++ % cl == 0 ? "\n" : ""));
  }
  putchar('\n');
#endif

  //  multiply digits from multiplicand and multiplier
  for (size_t i = 0; i < multiplier_sz; i++) {
    for (size_t j = 0; j < multiplicand_sz; j++) {
      product_digit[i + j] += multiplier_digit[i] * multiplicand_digit[j];
    }
  }

  //  carry
  for (size_t i = 0; i < multiplicand_sz + multiplier_sz; i++) {
    uint8_t carry_digit = product_digit[i] / 10;
    product_digit[i] = product_digit[i] % 10;
    product_digit[i + 1] = product_digit[i + 1] + carry_digit;
  }

  //  find last digit in product
  size_t last = multiplicand_sz + multiplier_sz;
  for (ssize_t i = multiplicand_sz + multiplier_sz; i >= 0; i--) {
    if (product_digit[i] > 0) {
      break;
    }
    last--;
  }
#ifndef NDEBUG
  for (size_t p = 0, ct = 1, lc = 10; p <= last; ++p) {
    printf("%3hhu%s", product_digit[p], (ct++ % lc == 0 ? "\n" : ""));
  }
  putchar('\n');
#endif

  for (ssize_t i = multiplicand_sz -1 + multiplier_sz - 1, p = 0; i >= 0; i--, p++) {
    product[p] = product_digit[i] + '0';
#ifndef NDEBUG
    printf("%2zu %2zu %c\n", i, p, product_digit[i] + '0');
#endif
  }

  if (mdsign == -1) {
    multiplicand[0] = '-';
  }
  if (mrsign == -1) {
    multiplier[0] = '-';
  }
  if (sign == -1) {
    product[0] = '-';
  }

  size_t zeros = 0ul;
  for (size_t z_ = 0ul; z_ < product_sz; ++z_) {
    if (product[z_] != '0') {
      break;
    }
    zeros++;
  }
  memmove(product, product + zeros, product_sz - zeros);

  return product;
}
