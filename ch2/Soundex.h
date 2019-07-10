#pragma once
#include <string>
#include <cassert>
#include <cstddef>

namespace
{
    constexpr size_t max_code_length { 4 };
}

class Soundex
{
public:
    std::string encode( const std::string& input ) const
    {
        if( input.empty() )
        {
            return input;
        }

        return zero_pad( head( input ) + encoded_digits( input ) );
    }

private:
    std::string head( const std::string& input ) const
    {
        assert( !input.empty() );

        return input.substr( 0, 1 );
    }

    std::string zero_pad( const std::string& input ) const
    {
        std::string res = input;

        for( size_t i = input.size(); i < max_code_length; ++i )
        {
            res += '0';
        }
        
        return res;
    } 

    std::string encoded_digits( const std::string& input ) const
    {
        assert( !input.empty() );

        if( input.length() > 1 )
        {
            return encoded_digit();
        }
        else
        {
            return "";
        }
    }

    std::string encoded_digit() const
    {
        return "1";
    }
};
