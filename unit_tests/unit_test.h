#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdio.h>
#include <stdlib.h>

extern int totalTested;
extern int totalPassed;
extern int totalFailed;

#define SUCCESS(desc, result) do {                                             \
    totalPassed++;                                                             \
    printf("\nSUCCESS - %s line %d succeed", __FILE__, __LINE__);              \
    fputs("\n    Description: ", stdout); printf desc;                         \
    fputs("\n    result:   ", stdout); printf result; fputs("\n\n", stdout);   \
    fflush(stdout);                                                            \
} while (0)

#define FAIL(desc, result) do {                                                 \
    totalFailed++;                                                             \
    printf("\nERROR - %s line %d failed with:", __FILE__, __LINE__);           \
    fputs("\n    expected: ", stdout); printf desc;                            \
    fputs("\n    result:   ", stdout); printf result; fputs("\n\n", stdout);   \
    fflush(stdout);                                                            \
} while (0)

#define SKIP_TEST(reason) do {                             \
    totalTested++;                                         \
    totalSkipped++;                                        \
    printf("[SKIPPED] %s\n", reason);                      \
} while(0)

#define Assert(test, description, result) if (!(test)) FAIL(description, result)

#define AssertTrue(x)    Assert( (x), ("%s is true",     #x), (#x " => FALSE"))
#define AssertFalse(x)   Assert(!(x), ("%s is false",    #x), (#x " => TRUE"))
#define AssertNotNull(x) Assert( (x), ("%s is not null", #x), (#x " => NULL"))

#define AssertNull(x) do {                                                     \
    PEDANTIC_EXTENSION void* _x = (void*)(x);                                  \
    Assert(!_x, ("%s is null", #x), (#x " => %p", _x));                        \
} while(0)

#define AssertInt(x, y, op, er)                                                     \
    do                                                                              \
    {                                                                               \
        totalTested++;                                                              \
        int _x = (int)(x);                                                          \
        int _y = (int)(y);                                                          \
        if (!(_x op _y))                                                           \
        {                                                                           \
            Assert(_x op _y, ("%s " #op " %s", #x, #y), ("%d " #er " %d", _x, _y)); \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            SUCCESS(("%s " #op " %s", #x, #y), ("%d " #er " %d", _x, _y));          \
        }                                                                           \
} while(0)

#define AssertIntInRange(x, low, high) do {                                         \
    totalTested++;                                                                  \
    int _x = (int)(x);                                                              \
    int _lo = (int)(low);                                                           \
    int _hi = (int)(high);                                                          \
    if (!(_x >= _lo && _x <= _hi))                                                  \
    {                                                                               \
        Assert((_x >= _lo && _x <= _hi),                                            \
               ("%s in range [%s, %s]", #x, #low, #high),                           \
               ("%d not in [%d, %d]", _x, _lo, _hi));                               \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        SUCCESS(("%s in range [%s, %s]", #x, #low, #high),                          \
                ("%d in [%d, %d]", _x, _lo, _hi));                                  \
    }                                                                               \
} while(0)

#define AssertUIntInRange(x, low, high) do {                                        \
    totalTested++;                                                                  \
    unsigned int _x = (unsigned int)(x);                                            \
    unsigned int _lo = (unsigned int)(low);                                         \
    unsigned int _hi = (unsigned int)(high);                                        \
    if (!(_x >= _lo && _x <= _hi))                                                  \
    {                                                                               \
        Assert((_x >= _lo && _x <= _hi),                                            \
               ("%s in range [%s, %s]", #x, #low, #high),                           \
               ("%u not in [%u, %u]", _x, _lo, _hi));                               \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        SUCCESS(("%s in range [%s, %s]", #x, #low, #high),                          \
                ("%u in [%u, %u]", _x, _lo, _hi));                                  \
    }                                                                               \
} while(0)

#define AssertIsBinary(x) do {                                                          \
    totalTested++;                                                                       \
    int _x = (int)(x);                                                                   \
    if (!(_x == 0 || _x == 1))                                                           \
    {                                                                                    \
        Assert((_x == 0 || _x == 1),                                                     \
              ("%s is 0 or 1", #x),                                                      \
              ("%d is not binary (expected 0 or 1)", _x));                               \
    }                                                                                    \
    else                                                                                 \
    {                                                                                    \
        SUCCESS(("%s is 0 or 1", #x), ("%d is valid binary", _x));                       \
    }                                                                                    \
} while (0)

#define AssertIntEQ(x, y) AssertInt(x, y, ==, !=)
#define AssertIntNE(x, y) AssertInt(x, y, !=, ==)
#define AssertIntGT(x, y) AssertInt(x, y,  >, <=)
#define AssertIntLT(x, y) AssertInt(x, y,  <, >=)
#define AssertIntGE(x, y) AssertInt(x, y, >=,  <)
#define AssertIntLE(x, y) AssertInt(x, y, <=,  >)


#define FLOAT_TOLERANCE 0.0001f
#define DOUBLE_TOLERANCE 0.0000001

#define AssertFloat(x, y, op, er)                                                  \
    do                                                                             \
    {                                                                              \
        totalTested++;                                                             \
        float _x = (float)(x);                                                     \
        float _y = (float)(y);                                                    \
        if (!(_x op _y))                                                             \
        {                                                                          \
            Assert(_x op _y, ("%s " #op " %s", #x, #y),                             \
                   ("%f " #er " %f", _x, _y));                                     \
        }                                                                          \
        else                                                                       \
        {                                                                          \
            SUCCESS(("%s " #op " %s", #x, #y), ("%f " #op " %f", _x, _y));         \
        }                                                                          \
    } while(0)

#define AssertFloatInRange(x, min, max)                                            \
    do                                                                             \
    {                                                                              \
        totalTested++;                                                             \
        float _x = (float)(x);                                                     \
        float _min = (float)(min);                                                 \
        float _max = (float)(max);                                                 \
        if (!(_x >= _min && _x <= _max))                                           \
        {                                                                          \
            Assert((_x >= _min && _x <= _max),                                     \
                   ("%s in range [%s, %s]", #x, #min, #max),                       \
                   ("%f not in [%f, %f]", _x, _min, _max));                        \
        }                                                                          \
        else                                                                       \
        {                                                                          \
            SUCCESS(("%s in range [%s, %s]", #x, #min, #max),                      \
                    ("%f in [%f, %f]", _x, _min, _max));                           \
        }                                                                          \
    } while (0)


#define AssertFloatEQ(x, y) AssertFloat(x, y, ==, !=)
#define AssertFloatNE(x, y) AssertFloat(x, y, !=, ==)
#define AssertFloatGT(x, y) AssertFloat(x, y,  >, <=)
#define AssertFloatLT(x, y) AssertFloat(x, y,  <, >=)
#define AssertFloatGE(x, y) AssertFloat(x, y, >=,  <)
#define AssertFloatLE(x, y) AssertFloat(x, y, <=,  >)

#define AssertDouble(x, y, op, er)                                                 \
    do                                                                             \
    {                                                                              \
        totalTested++;                                                             \
        double _x = (double)(x);                                                   \
        double _y = (double)(y);                                                   \
        double _diff = (_x > _y) ? (_x - _y) : (_y - _x);                          \
        if (!(op == == && _diff <= DOUBLE_TOLERANCE) && !(_x op _y))              \
        {                                                                          \
            Assert(_x op _y, ("%s " #op " %s", #x, #y),                             \
                   ("%lf " #er " %lf", _x, _y));                                   \
        }                                                                          \
        else                                                                       \
        {                                                                          \
            SUCCESS(("%s " #op " %s", #x, #y), ("%lf " #op " %lf", _x, _y));       \
        }                                                                          \
    } while(0)

#define AssertDoubleInRange(x, min, max)                                           \
    do                                                                             \
    {                                                                              \
        totalTested++;                                                             \
        double _x = (double)(x);                                                   \
        double _min = (double)(min);                                               \
        double _max = (double)(max);                                               \
        if (!(_x >= _min && _x <= _max))                                           \
        {                                                                          \
            Assert((_x >= _min && _x <= _max),                                     \
                   ("%s in range [%s, %s]", #x, #min, #max),                       \
                   ("%lf not in [%lf, %lf]", _x, _min, _max));                     \
        }                                                                          \
        else                                                                       \
        {                                                                          \
            SUCCESS(("%s in range [%s, %s]", #x, #min, #max),                      \
                    ("%lf in [%lf, %lf]", _x, _min, _max));                        \
        }                                                                          \
    } while (0)


#define AssertDoubleEQ(x, y) AssertDouble(x, y, ==, !=)
#define AssertDoubleNE(x, y) AssertDouble(x, y, !=, ==)
#define AssertDoubleGT(x, y) AssertDouble(x, y,  >, <=)
#define AssertDoubleLT(x, y) AssertDouble(x, y,  <, >=)
#define AssertDoubleGE(x, y) AssertDouble(x, y, >=,  <)
#define AssertDoubleLE(x, y) AssertDouble(x, y, <=,  >)


#define AssertStr(x, y, op, er) do {                                           \
    const char* _x = (const char*)(x);                                         \
    const char* _y = (const char*)(y);                                         \
    int         _z = (_x && _y) ? strcmp(_x, _y) : -1;                         \
    Assert(_z op 0, ("%s " #op " %s", #x, #y),                                 \
                                            ("\"%s\" " #er " \"%s\"", _x, _y));\
} while(0)

#define AssertStrEQ(x, y) AssertStr(x, y, ==, !=)
#define AssertStrNE(x, y) AssertStr(x, y, !=, ==)
#define AssertStrGT(x, y) AssertStr(x, y,  >, <=)
#define AssertStrLT(x, y) AssertStr(x, y,  <, >=)
#define AssertStrGE(x, y) AssertStr(x, y, >=,  <)
#define AssertStrLE(x, y) AssertStr(x, y, <=,  >)

void run_tests(void);
void print_test_results(void);

#endif // End UNIT_TEST_H