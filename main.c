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
  char const * multiplicand,
  char const * multiplier);

char * multiply_impl(
  size_t product_sz,
  char * product,
  char const * multiplicand,
  char const * multiplier);

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
 *  MARK:  count_zeros()
 */
static
inline
__attribute__((always_inline))
size_t count_zeros(size_t sz, char str[]) {
  size_t zeros = 0ul;
  for (size_t z_ = 0ul; z_ < sz; ++z_) {
    if (str[z_] != '0') {
      break;
    }
    zeros++;
  }
  return zeros;
}

/*
 *  MARK:  get_sign()
 */
static
inline
__attribute__((always_inline))
int_fast8_t get_sign(char * numstr) {
  int_fast8_t sign = 1;
  if (*numstr == '-') {
    sign = -1;
    *numstr = '0';
  }
  return sign;
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
    { "", "" },  //  space for ULLONG_MAX
    { "", "" },  //  space for LLONG_MIN, LLONG_MAX
    { "150353265326", "22055653351" },
    {   "100",   "100" },
    {   "100",  "-100" },
    {  "-100",   "100" },
    {  "-100",  "-100" },
    {  "0100",  "0100" },
    { "-0100",  "0100" },
    {  "0100", "-0100" },
    { "-0100", "-0100" },
    {     "0",     "0" },
    {     "1",     "1" },
    {    "-1",    "-1" },
    {   "00",     "00" },
    {  "-00",    "-00" },
    {   "01",     "00" },
    {  "-01",    "-01" },
    {  "-00",    "-01" },
    {  "-01",    "-00" },
  };
  size_t samples_sz = sizeof samples / sizeof *samples;

  //  add some big numbers
  sprintf(samples[0].first, "%llu", ULLONG_MAX);
  sprintf(samples[0].second, "%llu", ULLONG_MAX);
  sprintf(samples[1].first, "%lld", LLONG_MIN);
  sprintf(samples[1].second, "%lld", LLONG_MAX);

  for (size_t s_ = 0ul; s_ < samples_sz; ++s_) {
    putchar('\n');
    char product[LEN_O + 1] = { '\0', };
    char * product_p = product;
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
 *  MARK:  multiplier()
 */
char * multiply(
  size_t product_sz,
  char * product,
  char const * multiplicand,
  char const * multiplier) {

  char * product_ptr = product;

#ifndef NDEBUG
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
   printf("} md: %zu %s\n", strlen(multiplicand), multiplicand);
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("} mr: %zu %s\n", strlen(multiplier), multiplier);
#endif

  //  some shortcuts
  if ((strcmp(multiplicand, "0") == 0)
    || (strcmp(multiplicand, "-0") == 0)) {
    //  x * 0 = 9
    product_ptr = strcpy(product, "0");
  }
  else if ((strcmp(multiplier, "0") == 0)
    || (strcmp(multiplier, "-0") == 0)) {
    //  x * 0 = 0
    product_ptr = strcpy(product, "0");
  }
  else if (strcmp(multiplicand, "1") == 0) {
    //  x * 1 = x
    product_ptr = strcpy(product, multiplier);
  }
  else if (strcmp(multiplier, "1") == 0) {
    //  x * 1 = x
    product_ptr = strcpy(product, multiplicand);
  }
  else if ((strcmp(multiplicand, "-1") == 0)
    && (strcmp(multiplier, "-1") == 0)) {
    //  -1 * -1 = 1;
    product_ptr = strcpy(product, "1");
  }
  else if ((strcmp(multiplicand, "-1") == 0)
    && multiplier[0] != '-') {
    //  x * -1 = -x;
    product[0] = '-';
    strcpy(product + 1, multiplier);
  }
  else if ((strcmp(multiplier, "-1") == 0)
    && multiplicand[0] != '-') {
    //  x * -1 = -x
    product[0] = '-';
    strcpy(product + 1, multiplicand);
  }
  else if ((strcmp(multiplicand, "-1") == 0)
    && multiplier[0] != '-') {
    //  -x * -1 = x
    strcpy(product, multiplier + 1);
  }
  else if ((strcmp(multiplier, "-1") == 0)
    && multiplicand[0] != '-') {
      //  -x * -1 = x
    strcpy(product, multiplicand + 1);
  }
  else {
    product_ptr = multiply_impl(product_sz, product, multiplicand, multiplier);
  }

  return product_ptr;
}

/*
 *  MARK: multiply_impl()
 */
char * multiply_impl(
  size_t product_sz,
  char * product,
  char const * multiplicand_p,
  char const * multiplier_p) {

#ifndef NDEBUG
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("} md: %zu %s\n", strlen(multiplicand_p), multiplicand_p);
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("} mr: %zu %s\n", strlen(multiplier_p), multiplier_p);
#endif

  char * multiplicand = calloc((LEN_I + 1), sizeof(char));
  if (multiplicand == NULL) {
    printf("malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  char * multiplier = calloc((LEN_I + 1), sizeof(char));
  if (multiplier == NULL) {
    printf("malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  strcpy(multiplicand, multiplicand_p);
  strcpy(multiplier, multiplier_p);

  size_t multiplicand_sz = strlen(multiplicand);
  size_t multiplier_sz   = strlen(multiplier);

#ifndef NDEBUG
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("} md: %zu %s\n", multiplicand_sz, multiplicand);
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("} mr: %zu %s\n", multiplier_sz, multiplier);
#endif

  int_fast8_t mdsign = get_sign(multiplicand);
  int_fast8_t mrsign = get_sign(multiplier);
  int_fast8_t sign = mdsign * mrsign;

#ifndef NDEBUG
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("mdsign: %2hhd\n", mdsign);
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("mrsign: %2hhd\n", mrsign);
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("  sign: %2hhd\n", sign);
#endif

  if (mdsign == -1) {
    multiplicand[0] = '0';
  }
  if (mrsign == -1) {
    multiplier[0] = '0';
  }
  size_t mdzeros = count_zeros(LEN_I + 1, multiplicand);
  size_t mrzeros = count_zeros(LEN_I + 1, multiplier);
  if (mdzeros > 0) {
    memmove(multiplicand, multiplicand + mdzeros, multiplicand_sz);
    multiplicand_sz = strlen(multiplicand);
  }
  if (mrzeros > 0) {
    memmove(multiplier, multiplier + mrzeros, multiplier_sz);
    multiplier_sz = strlen(multiplier);
  }

  if (multiplicand_sz == 0) {
    multiplicand[0] = '0';
    multiplicand_sz = 1;
  }
  if (multiplier_sz == 0) {
    multiplier[0] = '0';
    multiplier_sz = 1;
  }
#ifndef NDEBUG
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("} md: %zu %s\n", multiplicand_sz, multiplicand);
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("} mr: %zu %s\n", multiplier_sz, multiplier);
#endif

  uint8_t multiplicand_digit[LEN_I] = { 0, };
  uint8_t multiplier_digit[LEN_I] = { 0, };
  uint16_t product_digit[LEN_O] = { 0, };

  //  extract individual digits from multiplicand
  for (ssize_t i = multiplicand_sz - 1, j = 0; i >= 0; i--, j++) {
    multiplicand_digit[j] = multiplicand[i] - '0';
#ifndef NDEBUG
    printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
    printf("[%2zu][%2zu]: %3hhu %04hhx %04hhx\n",
      i, j, multiplicand_digit[j], multiplicand_digit[j], multiplicand_digit[j] + '0');
#endif
  }
#ifndef NDEBUG
  for (size_t p = 1, cc = 1, cl = 10; p < multiplicand_sz; ++p) {
    printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
    printf("%3hhu%s", multiplicand_digit[p], (cc++ % cl == 0 ? "\n" : ""));
  }
  putchar('\n');
#endif

  //  extract individual digits from multiplier
  for (ssize_t i = multiplier_sz - 1, j = 0; i >= 0; i--, j++) {
    multiplier_digit[j] = multiplier[i] - '0';
#ifndef NDEBUG
    printf("[%2zu][%2zu]: %3hhu %04hhx %04hhx\n",
      i, j, multiplier_digit[j], multiplier_digit[j], multiplier_digit[j] + '0');
#endif
  }

#ifndef NDEBUG
  for (size_t p = 0, cc = 1, cl = 10; p < multiplier_sz; ++p) {
    printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
    printf("%3hhu%s", multiplier_digit[p], (cc++ % cl == 0 ? "\n" : ""));
  }
  putchar('\n');
#endif

  //  multiply digits from multiplicand and multiplier
  for (size_t i = 0; i < multiplier_sz; i++) {
    for (size_t j = 0; j < multiplicand_sz; j++) {
      product_digit[i + j] += multiplier_digit[i] * multiplicand_digit[j];
#ifndef NDEBUG
      printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
      printf("[%2zu][%2zu][%2zu]: %4hu %3hhu %3hhu\n",
        i, j, i + j,
      product_digit[i + j], multiplier_digit[i], multiplicand_digit[j]);
#endif
    }
  }

  //  carry
  for (size_t i = 0; i < multiplicand_sz + multiplier_sz; i++) {
    uint8_t carry_digit = product_digit[i] / 10;
    product_digit[i] = product_digit[i] % 10;
    product_digit[i + 1] = product_digit[i + 1] + carry_digit;
#ifndef NDEBUG
    printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
    printf("[%2zu]: %4hu\n", i, product_digit[i]);
#endif
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
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("last: %zu\n", last);

  for (size_t p = 0, ct = 1, lc = 10; p <= last; ++p) {
    printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
    printf("%3hhu%s", product_digit[p], (ct++ % lc == 0 ? "\n" : ""));
  }
  putchar('\n');
#endif

  for (ssize_t i = multiplicand_sz -1 + multiplier_sz - 1, p = 0; i >= 0; i--, p++) {
    product[p] = product_digit[i] + '0';
#ifndef NDEBUG
    printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
    printf("[%2zu][%2zu]: %c\n", i, p, product_digit[i] + '0');
#endif
  }

  //  reset sign in multiplicand & multiplier
  // if (mdsign == -1) { multiplicand[0] = '-'; }
  // if (mrsign == -1) { multiplier[0] = '-'; }

  size_t product_len = strlen(product);

  //  count leading zeros in product
//   size_t zeros = count_zeros(product_len, product);

  #ifndef NDEBUG
    // printf("} zeros, sp: %zu %zu\n", zeros, sp);
    printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
    printf("} product: %zu %s\n", product_len, product);
  #endif

  //  set sign in product
  size_t sp = 0ul;
  if (sign == -1) {
    // if (zeros == 0) {
      //  add space for -ve sign
      memmove(product + 1ul, product, product_len);
      product_len++;
    // }
    product[0] = '-';
    sp++;
    // zeros = zeros > 0 ? zeros - 1ul : 0ul;
  }

#ifndef NDEBUG
  // printf("} zeros, sp: %zu %zu\n", zeros, sp);
  printf("%s %s %d :", __FILE__, __func__, __LINE__ + 1);
  printf("} product: %zu %s\n", product_len, product);
#endif

  //  remove leading zeros
  // memmove(product + sp, product + zeros + sp, product_len - zeros - sp);

  free(multiplicand);
  free(multiplier);

  return product;
}
