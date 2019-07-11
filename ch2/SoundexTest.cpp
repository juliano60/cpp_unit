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

TEST_F( SoundexEncoding, DropsVowelLikeLetters )
{
    ASSERT_THAT( soundex_.encode( "BAeIoUyHwcdl"), Eq( "B234" ) );
}

TEST_F( SoundexEncoding, CombinesDuplicateLetters )
{
    ASSERT_THAT( soundex_.encoded_digit( 'b' ), Eq( soundex_.encoded_digit( 'f' ) ) );
    ASSERT_THAT( soundex_.encoded_digit( 'c' ), Eq( soundex_.encoded_digit( 'g' ) ) );
    ASSERT_THAT( soundex_.encoded_digit( 'd' ), Eq( soundex_.encoded_digit( 't' ) ) );

    ASSERT_THAT( soundex_.encode( "Abfcgdt" ), Eq( "A123" ) );
}

TEST_F( SoundexEncoding, UppercasesFirstLetter )
{
    ASSERT_THAT( soundex_.encode( "abcd" ), StartsWith( "A" ) );
}

TEST_F( SoundexEncoding, IgnoresCasingWhenEncodingConsonants )
{
    ASSERT_THAT( soundex_.encode( "BCDL" ), Eq( soundex_.encode( "Bcdl" ) ) );
}

TEST_F( SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st )
{
    ASSERT_THAT( soundex_.encode( "Bbcd" ), Eq( "B230" ) );
}

TEST_F( SoundexEncoding, DoesNotCombineDuplicateCodesSeparatedByVowels )
{
    ASSERT_THAT( soundex_.encode( "Jbob" ), Eq( "J110" ) );
}
