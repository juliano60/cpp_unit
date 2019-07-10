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
    ASSERT_THAT( soundex_.encode( "Ax" ), Eq( "A200" ) );
}

TEST_F( SoundexEncoding, IgnoresNonAlphabetics )
{
    ASSERT_THAT( soundex_.encode( "A#" ), Eq( "A000" ) );
}

TEST_F( SoundexEncoding, ReplacesMultipleConsonantsWithDigits )
{
    ASSERT_THAT( soundex_.encode( "Acdl" ), Eq( "A234" ) );
}

TEST_F( SoundexEncoding, LimitsLengthToFourCharacters )
{
    ASSERT_THAT( soundex_.encode( "Dcdlb" ).size(), Eq( 4u ) );
}
