#include "gmock/gmock.h"
#include "Soundex.h"

using namespace testing;

class SoundexEncoding: public Test
{
protected:
    Soundex soundex_;
};

TEST_F( SoundexEncoding, RetainsSoleLetterOfOneLetterWord )
{
    auto encoded = soundex_.encode( "A" );
    ASSERT_THAT( encoded, Eq( "A000" ) );
}

TEST_F( SoundexEncoding, PadsWithZeroToEnsureThreeDigits )
{
    auto encoded = soundex_.encode( "I" );
    ASSERT_THAT( encoded, Eq( "I000" ) );
}

TEST_F( SoundexEncoding, ReplacesConsonantsWithAppropriateDigits )
{
    auto encoded = soundex_.encode( "Ab" );
    ASSERT_THAT( encoded, Eq( "A100" ) );
}
