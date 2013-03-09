/* --------------------------------------------------------------------------
    Copyright 2012 by Richard Albrecht
    richard.albrecht@rleofield.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ------------------------------------------------------------------------------
*/



#include "stringhelper.h"

#include <iomanip>

using namespace std;


namespace ral {
   namespace strings {

      bool string2bool( std::string const& s )  {
         if( s == s_true ) {
            return true;
         }

         if( s == s_false ) {
            return false;
         }

         std::string temp = to_upper( s );

         // was ist hier?
         // nicht true, also false?, ist das gewollt?
         return false;
      }

      string to_hex_0x( size_t val, size_t w ) {
         string lower = to_hex( val, w );
         to_upper_in_place( lower );
         return "0x" + lower;
      }

      string to_hex( size_t val, size_t w ) {
         std::ostringstream o;
         o <<  std::setfill( '0' ) << std::setw( w ) << hex << val;
         return o.str();
      }

      string to_bin( size_t val, size_t l ) {
         size_t i;
         char str[65];

         for( i = l; i > 0; i-- ) {
            str[l - i] = '0' + ( ( val >> ( i - 1 ) ) & 0x1 );
         }

         str[l] = 0;
         return string( str );
      }


      void to_lower_in_place( string& s ) {
         std::string::iterator start = s.begin();

         while( start != s.end() ) {
            *start = ( char )::tolower( *start );
            ++start;
         }
      }
      string to_lower( string const& s ) {
         string temp = s;
         to_lower_in_place( temp );
         return temp;
      }
      void to_upper_in_place( string& s ) {
         std::string::iterator start = s.begin();

         while( start != s.end() ) {
            *start = ( char )::toupper( *start );
            ++start;
         }
      }

      string to_upper( string const& s ) {
         string temp = s;
         to_upper_in_place( temp );
         return temp;
      }

      string clip( string const& in, string const& pattern ) {
         if( in.size() > 0 ) {
            size_t i = index( in, pattern );

            if( i != std::string::npos ) {
               return in.substr( 0, i ) ;
            }
         }

         return in;
      }

      string clip_after( string const& in , string const& pattern ) {
         size_t i = index( in, pattern );

         if( i != std::string::npos ) {
            return in.substr( 0, i + pattern.size() );
         }

         return in;
      }

      string clip_at_char( string const& s, char ch ) {
         if( s.size() > 0 ) {
            size_t i = index( s, ch );

            if( i != string::npos ) {
               return s.substr( 0, i ) ;
            }
         }

         return s;
      }
      string clip_at_pos( string const& s, size_t pos ) {
         if( s.size() > 0 ) {
            size_t i = pos;

            if( i != string::npos ) {
               return s.substr( 0, i ) ;
            }
         }

         return s;
      }
      string truncate( string const& s, size_t pos ) {
         return clip_at_pos( s, pos );
      }


      string trim( string const& str, char ch ) {
         if( str.size() == 0 ) {
            return "";
         }

         string::const_iterator begin = str.begin();

         while( begin < str.end() && *begin == ch ) {
            ++begin;
         }

         if( begin == str.end() ) {
            return "";
         }

         string::const_reverse_iterator last = str.rbegin();

         while( *last == ch ) {
            ++last;
         }

         size_t start = begin - str.begin();
         size_t n = last.base() - begin;
         return str.substr( start, n );
      }

      string trim_right( string const& str, char ch ) {
         if( str.size() == 0 ) {
            return str;
         }

         string::const_reverse_iterator last = str.rbegin();

         while( last < str.rend() && *last == ch ) {
            ++last;
         }

         if( last == str.rend() ) {
            return "";
         }

         size_t n = str.rend() - last;
         return str.substr( 0, n );
      }

      string trim_left( string const& str, char ch ) {
         if( str.size() == 0 ) {
            return str;
         }

         string::const_iterator begin = str.begin();

         while( begin < str.end() && *begin == ch ) {
            ++begin;
         }

         if( begin == str.end() ) {
            return "";
         }

         if( begin == str.begin() ) {
            return str;
         }

         size_t start = begin - str.begin();
         return str.substr( start );
      }


      size_t index( string const& s, char ch, size_t pos ) {
         return s.find( ch, pos );
      }

      size_t index_right( string const& s, char ch ) {
         return s.rfind( ch );
      }

      size_t index( string const& s, string const& pattern, size_t pos ) {
         return s.find( pattern, pos );
      }

      size_t index_right( string const& s, const string& pattern ) {
         return s.rfind( pattern );
      }


      string replace_first( string const& in, string const& pattern, string const& replace ) {
         string s = in;
         size_t pos = index( s, pattern );

         if( pos != std::string::npos ) {
            s.erase( pos, pattern.size() );
            s.insert( pos, replace );
         }

         return s;
      }

      string replace( string const& ins, const string& pattern, const string& replace ) {
         return replace_first( ins, pattern, replace );
      }

      string replace_all( string const& ins, const string& pattern, const string& replace ) {
         string s = ins;
         size_t pos = index( s, pattern );
         size_t oldpos;

         while( pos != std::string::npos ) {
            s.erase( pos, pattern.size() );
            s.insert( pos, replace );
            oldpos = pos;
            pos = index( s, pattern, oldpos + replace.size() );
         }

         return s;
      }


      string fillup( string const& in, char ch, size_t n ) {
         string s = in;

         if( s.size() < n ) {
            s += string( n - s.size(), ch ) ;
         }

         return s;
      }
      string erase( string const& in, size_t pos, size_t len ) {
         string s = in;
         erase_in_place( s, pos, len );
         return s;
      }
      void erase_in_place( string& s, size_t pos, size_t len ) {
         s.erase( pos, len );
      }

      char last_char( string const& s ) {
         if( s.length() == 0 ) {
            return 0;
         }

         return *( s.end() - 1 );
      }
      char first_char( string const& s ) {
         if( s.length() == 0 ) {
            return 0;
         }

         return s[0];
      }



      string remove_first( string const& in ) {
         return erase( in, 0, 1 );
      }
      string remove_first( string const& in, char ch ) {
         size_t i = index( in, ch );

         if( i != std::string::npos ) {
            return erase( in, i, 1 );
         }

         return in;
      }

      string remove_first( string const& in, string const& pattern ) {
         size_t i = index( in, pattern );

         if( i != std::string::npos ) {
            return erase( in, i, pattern.length() );
         }

         return in;
      }


      string remove_last( string const& in ) {
         string s = in;
         remove_last_in_place( s );
         return s;
      }

      void remove_last_in_place( string& s, char ch ) {
         if( s.size() > 0 ) {
            size_t i = s.size() - 1;

            if( s[i] == ch ) {
               s.erase( i, 1 );
            }
         }
      }
      void remove_last_in_place( string& s ) {
         if( s.size() > 0 ) {
            size_t i = s.size() - 1;
            s.erase( i, 1 );
         }
      }



      string insert_at( string const& in, char ch, size_t pos ) {
         string s = in;

         if( pos <= s.size() ) {
            s.insert( pos, 1, ch );
         }

         return s;
      }
      string insert_at( string const& str, const string& insert, size_t pos ) {
         string s = str;

         if( pos <= s.length() && insert.length() > 0 ) {
            s.insert( pos, insert );
         }

         return s;
      }


      vector<string> tokenize( string const& str, const string& delimiters ) {
         string::size_type pos_not_delimiter = str.find_first_not_of( delimiters, 0 );
         string::size_type pos_delimiter     = str.find_first_of( delimiters, pos_not_delimiter );
         vector<string> tokens;

         while( string::npos != pos_delimiter || string::npos != pos_not_delimiter ) {
            string::size_type length = pos_delimiter - pos_not_delimiter;
            tokens.push_back( str.substr( pos_not_delimiter, length ) );
            pos_not_delimiter = str.find_first_not_of( delimiters, pos_delimiter );
            pos_delimiter = str.find_first_of( delimiters, pos_not_delimiter );
         }

         return tokens;
      }

      vector<string> split( string const& l, string const& delimiters ) {
         vector<string> v = tokenize( l, delimiters );
         return v;
      }


   }


} // end ns ral

//EOFheise