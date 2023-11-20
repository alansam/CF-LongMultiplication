//  example data:
//  150353265326
//  22055653351

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
  char const * multiplicand,
  char const * multiplier);

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
  uint8_t a[LEN_I] = { 0, }, b[LEN_I] = { 0, };
  uint8_t ans[LEN_O] = { 0, };
  // int i, j, tmp;
  char s1[LEN_I + 1] = { '\0', }, s2[LEN_I + 1] = { '\0', };
  char p1[LEN_O + 1] = { '\0', };
  char * p1p = NULL;

  scanf(" %s", s1);
  scanf(" %s", s2);

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

  char mpnd[LEN_I + 1] = { '\0', };
  char mpyr[LEN_I + 1] = { '\0', };
  memset(p1, '\0', LEN_O + 1);
  sprintf(mpnd, "%d", 10);
  sprintf(mpyr, "%d", -1);
  p1p = multiply(LEN_I + 1, p1, mpnd, mpyr);
  show_n_tell(p1p, mpnd, mpyr);

  return 0;
}

/*
 *  MARK: multiply()
 */
char * multiply(
  size_t product_sz,
  char * product,
  char const * multiplicand,
  char const * multiplier) {

  size_t multiplicand_sz = strlen(multiplicand);
  size_t multiplier_sz   = strlen(multiplier);

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

  return product;
}
