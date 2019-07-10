#pragma once
#include <string>
#include <cassert>
#include <cstddef>
#include <unordered_map>

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
            return encoded_digit( input[1] );
        }
        else
        {
            return "";
        }
    }

    std::string encoded_digit( char c ) const
    {
        static const std::unordered_map< char, std::string > encoding_tbl = {
                std::make_pair( 'b', "1" ),
                std::make_pair( 'f', "1" ),
                std::make_pair( 'p', "1" ),
                std::make_pair( 'v', "1" ),
                std::make_pair( 'c', "2" ),
                std::make_pair( 'g', "2" ),
                std::make_pair( 'k', "2" ),
                std::make_pair( 'q', "2" ),
                std::make_pair( 's', "2" ),
                std::make_pair( 'x', "2" ),
                std::make_pair( 'z', "2" ),
                std::make_pair( 'd', "3" ),
                std::make_pair( 't', "3" ),
                std::make_pair( 'l', "4" ),
                std::make_pair( 'm', "5" ),
                std::make_pair( 'n', "5" ),
                std::make_pair( 'b', "6" ),
        };

        auto it = encoding_tbl.find( c );

        if( it != encoding_tbl.end() )
        {
            return it->second;
        }
        else
        {
            return "";
        } 
    }
};
