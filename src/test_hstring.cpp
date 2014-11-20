/* --------------------------------------------------------------------------
    Copyright 2012 by Richard Albrecht
    richard.albrecht@rleofield.de
    www.rleofield.de

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



#include <iostream>
#include "stringhelper.h"
#include "test_hstring.h"



using namespace std;
using rlf_hstring::string2type;
using rlf_hstring::toString;
using rlf_hstring::to_hex_0x;
using rlf_hstring::to_bin;
using rlf_hstring::to_hex;
using rlf_hstring::to_lower_in_place;
using rlf_hstring::to_lower;
using rlf_hstring::to_upper_in_place;
using rlf_hstring::to_upper;
using rlf_hstring::clip;
using rlf_hstring::clip_after;
using rlf_hstring::clip_at_pos;
using rlf_hstring::clip_at_char;
using rlf_hstring::truncate;
using rlf_hstring::trim;
using rlf_hstring::trim_left;
using rlf_hstring::trim_right;
using rlf_hstring::index;
using rlf_hstring::index_right;
using rlf_hstring::insert_at;
using rlf_hstring::truncate;
using rlf_hstring::replace_first;
using rlf_hstring::replace_all;
using rlf_hstring::fillup;
using rlf_hstring::last_char;
using rlf_hstring::first_char;
using rlf_hstring::remove_last_in_place;
using rlf_hstring::erase;
using rlf_hstring::erase_in_place;
using rlf_hstring::remove_last;
using rlf_hstring::remove_last_in_place;
using rlf_hstring::remove_first;
using rlf_hstring::split;


namespace test_hstring{

namespace {

   std::string  msgFail( string const& m, string const& testvalue, string const& correctvalue ) {
      return ( m + " ist: '" + testvalue + "'   soll: '" + correctvalue + "'" );
   }
   std::string  msgFail( string const& m, double testvalue, double correctvalue ) {
      return msgFail( m, toString( testvalue ), toString( correctvalue ) );
   }
   std::string  msgFail( string const& m, int testvalue, int correctvalue ) {
      return msgFail( m, toString( testvalue ), toString( correctvalue ) );
   }
   std::string  msgFail( string const& m, size_t testvalue, size_t correctvalue ) {
      return msgFail( m, toString( testvalue ), toString( correctvalue ) );
   }
   std::string  msgFail( string const& m, char testvalue, char correctvalue ) {
      return msgFail( m, toString( testvalue ), toString( correctvalue ) );
   }
   // hlp
}

class TestStrings {


public:

   void test_string_to_type_double();
   void test_string_to_type_int();
   void test_string_to_type_size_t();

   void test_double_to_string_default_format();
   void test_double_to_string_format_supplied();

   void test_negative_int_to_string();

   void test_int_to_hex_0x();
   void test_int_to_hex_0x_32bit();
   void test_int_to_hex_0x_example2();
   void test_int_to_hex_0x_width16();
   void test_int_to_hex();

   void test_int_to_binaer_string();
   void test_int_to_binaer_string_width16();

   void test_to_lower_in_place();
   void test_to_lower_copy_string();

   void test_to_upper_in_place();
   void test_to_upper_copy_string();

   void test_clip_before_pattern();
   void test_clip_after_pattern();
   void test_clip_at_pos();
   void test_clip_at_char();
   void test_truncate_at_pos();

   void test_trim();
   void test_trim_right();
   void test_trim_left();
   void test_trim_with_empty_string();

   void test_index_at_char();
   void test_index_at_pattern();

   void test_index_right_at_char();

   void test_index_at_pattern_from_pos();
   void test_index_right_at_pattern();

   void test_index_not_found();

   void test_replace_first();
   void test_replace_all();

   void test_fillup();

   void test_last_char();
   void test_first_char();

   void test_erase();
   void test_erase_in_place();

   void test_remove_last();
   void test_remove_last_in_place();

   void test_remove_first();
   void test_remove_first_pattern();

   void test_insert_at_char();
   void test_insert_at_pattern();

   void test_split_to_6_tokens();
   void test_split_to_3_tokens();
   void test_split_with_multiple_delimiters();

};

void testPass( std::string f,  bool b, std::string const& msg ) {
   //f = replace_first(f,"TestStrings::","");
   if( f.size() > 30 ) {
      f = f.substr( 0, 30 );
   }

   if( b  == true ) {
      std::cout << setw( 40 ) << left << f << "  PASS  >>>> " << msg << endl;
      return;
   }

   std::cout << setw( 40 ) << left << f << "  WRONG >>>> " << msg << endl;

}

#define VERIFY(bool1,msg) testPass(__FUNCTION__,bool1,msg)




void TestStrings::test_string_to_type_double() {
   // Umwandlung eines Strings in einen Wert, Beispiel nach 'double'

   double ist = string2type<double>( "1234.7" );
   double soll  = 1234.7;
   VERIFY( ( ( ist - soll ) < 0.0000001 ), msgFail( "string2type<double>(\"1234.7\")", ist, soll ) );

}


void TestStrings::test_string_to_type_int() {
   // Umwandlung eines Strings in einen Wert, Beispiel nach 'int'

   int ist  = string2type<int>( "4711" );
   int soll = 4711;
   VERIFY( ist == soll, msgFail( "string2type<int>(\"4711\")", ist, soll ) );
}

void TestStrings::test_string_to_type_size_t() {
   // Umwandlung eines Strings in einen Wert, Beispiel nach 'size_t'

   string temp;
   size_t a = 0;

   if( sizeof( a ) == 8 ) {
      // 64bit
      temp = "18446744073709551615";
   } else {
      // 32bit
      temp = "4294967295";
   }

   size_t ist = string2type<size_t>( temp );
   size_t soll = -1;
   VERIFY( ist ==  soll, msgFail( "string2type<size_t>(\"18446744073709551615\")", ist, soll ) );

}
// --------------------------------
// --
// Wert nach String, war frueher: 'itoa', 'ftoa' usw.
// --

void TestStrings::test_double_to_string_default_format() {
   // Umwandlung eines double-Wertes in einen String, default Format '%6.3lf'

   string ist = toString( 1234.7 ); // 1234.700, 3 dezimalstellen, default
   string soll = "1234.700";
   VERIFY( ist == soll, msgFail( "toString(1234.7)",  ist, soll ) );

}


void TestStrings::test_double_to_string_format_supplied() {

   // Umwandlung eines double-Wertes in einen String mit Format, '%10.7lf'
   string ist = toString( 1234.7,  10, 7 ); // 1234.7000000, 7 nachkommastellen, user defined
   string soll = "1234.7000000";
   VERIFY( ist == soll, msgFail( "toString", ist, soll ) );

}

void TestStrings::test_negative_int_to_string() {

   // Umwandlung eines negativen Int-Wertes in einen String'

   string ist = toString( -1 );
   string soll = "-1";
   VERIFY( ist == soll, msgFail( "toString(-1)", ist, soll ) );
}

// --------------------------------
// --
// Sonderfaelle, Int-Wert nach Hexadezimal und Binaer
//--

void TestStrings::test_int_to_hex_0x() {

   // Int-Wert in einen hexadezimalen String, mit '0x' Prefix, nur mit 64 bit
   size_t a = 0;
   string temp;

   if( sizeof( a ) == 8 ) {
      // 64bit
      a = 18446744073709551615ul;
      temp = "18446744073709551615";
   } else {
      // 32bit
      a = 4294967295ul;
      temp = "4294967295";
   }

   // 32 bit
   string ist = to_hex_0x( a );
   // 64 bit
   //string ist = to_hex_0x( 18446744073709551615ul ) ; // mit 0x "0xFFFFFFFFFFFFFFFF
   string soll = "0xFFFFFFFFFFFFFFFF";

   if( sizeof( a ) == 4 ) {
      soll = "0xFFFFFFFF";
   }

   VERIFY( ist == soll, msgFail( "to_hex_0x( " + temp + " )", ist, soll ) );
}

void TestStrings::test_int_to_hex_0x_32bit() {

   // Int-Wert in einen hexadezimalen String, mit '0x' Prefix

   string ist = to_hex_0x( 4294967295 ) ; // mit 0x "0xFFFFFFFF
   string soll = "0xFFFFFFFF";
   VERIFY( ist == soll, msgFail( "to_hex_0x( 4294967295 )", ist, soll ) );
}

void TestStrings::test_int_to_hex_0x_example2() {

   // Int-Wert in einen hexadezimalen String, mit '0x' Prefix, anderes Beispiel

   string ist = to_hex_0x( 1234567 ); // 0x0012D687
   string soll =  "0x0012D687";
   VERIFY( ist == soll, msgFail( "to_hex_0x( 1234567 )", ist, soll ) );
}

void TestStrings::test_int_to_hex_0x_width16() {

   // Int-Wert in einen hexadezimalen String, mit '0x' Prefix, Feldbreite 16

   string ist = to_hex_0x( 1234567, 16 );
   string soll =  "0x000000000012D687";
   VERIFY( ist == soll, msgFail( "to_hex_0x( 1234567, 16 )", ist, soll ) );
}

void TestStrings::test_int_to_hex() {
   // Int-Wert in einen hexadezimalen String, ohne '0x' Prefix

   string ist = to_hex( 256 * 256 + 1 ); // ohne 0x "00010001"
   string soll = "00010001" ;
   VERIFY( ist == soll, msgFail( "to_hex(  256*256 + 1 )", ist, soll ) );

}

void TestStrings::test_int_to_binaer_string() {

   // Int-Wert in einen binaeren String, Feldbreite 32

   string ist = to_bin( 256 * 256 - 1 );
   string soll = "00000000000000001111111111111111";
   VERIFY( ist == soll, msgFail( "to_bin(  256*256-1 )", ist, soll ) );
}

void TestStrings::test_int_to_binaer_string_width16() {

   // Int-Wert in einen binaeren String, Feldbreite 16

   string ist = to_bin( 256 * 256 - 1, 16 );
   string soll = "1111111111111111";
   VERIFY( ist == soll, msgFail( "to_bin(  256*256-1, 16 )", ist, soll ) );
}






// --------------------------------
// --
// -- String, Umwandlung Gross-/Kleinschreibung, in Place und/oder als Kopie
// --

// 'in Place' Funktionen funktionieren nicht mit einem
//  statischen String, z.B. "abc"
void TestStrings::test_to_lower_in_place() {

   // to lower, 'in Place'

   string upper = "KAPITAELCHEN";
   to_lower_in_place( upper ); // "kapitaelchen"
   string ist = upper;
   string soll = "kapitaelchen";
   VERIFY( ist == soll, msgFail( "to_lower_in_place( upper )", ist, soll ) );
}

void TestStrings::test_to_lower_copy_string() {

   // to lower, als Kopie

   string ist = to_lower( "TEST mit KOPIE DES STRINGS" );
   string soll = "test mit kopie des strings" ;
   VERIFY( ist == soll, msgFail( "to_lower( upper2 )", ist, soll ) );
}

void TestStrings::test_to_upper_in_place() {

   // to upper, 'in Place'

   string lower = "test in Place";
   to_upper_in_place( lower );
   string ist = lower;
   string soll = "TEST IN PLACE";
   VERIFY( ist == soll, msgFail( "to_upper_in_place( lower2 )", ist, soll ) )  ;
}

void TestStrings::test_to_upper_copy_string() {

   // to upper, als Kopie, mit Sonderzeichen

   string ist = to_upper( "abcdfghi++??u" );
   string soll =  "ABCDFGHI++??U" ;
   VERIFY( ist == soll, msgFail( "to_upper( \"abcdfghi++??u\" );", ist, soll ) );
}

// --------------------------------
// --
//  -- clip a String
// --

void TestStrings::test_clip_before_pattern() {
   // clip vor Pattern

   string ist = clip( " 1234pattern1234, ", "pattern" );
   string soll = " 1234" ;
   VERIFY( ist == soll, msgFail( "clip()", ist, soll ) );
}

void TestStrings::test_clip_after_pattern() {

   // clip nach einem Pattern

   string ist = clip_after( "hgxxxxxypattxy xy " , "patt" ) ;
   string soll = "hgxxxxxypatt"  ;
   VERIFY( ist == soll, msgFail( "clip_after( )", ist, soll ) );
}

void TestStrings::test_clip_at_pos() {

   // clip an einer Position

   string ist = clip_at_pos( "12 34pattern1234", 6 );
   string soll =  "12 34p" ;
   VERIFY( ist == soll, msgFail( "clip_at_pos()", ist, soll ) );
}

void TestStrings::test_clip_at_char() {

   // clip an einem Char

   string ist = clip_at_char( "123 4pattern12W34, ", 'W' ) ;
   string soll = "123 4pattern12" ;
   VERIFY( ist == soll, msgFail( "clip_at_char()", ist, soll ) );
}

void TestStrings::test_truncate_at_pos() {

   // truncate an einer Position, entspricht clip_at_pos()

   string ist = rlf_hstring::truncate( "hier ist das 1234 ", 7 );
   string soll = "hier is" ;
   VERIFY( ist == soll, msgFail( "truncate()", ist, soll ) );
}

// --------------------------------
// --
// -- trim a String, default ist ' ', andere Zeichen als 2. Parameter möglich
// --

void TestStrings::test_trim() {

   string trimtest = "    spaces before    and     spaces after    ";

   // trim, beide Seiten

   string ist = trim( trimtest ) ;
   string soll = "spaces before    and     spaces after" ;
   VERIFY( ist == soll, msgFail( "trim()", ist, soll ) );
}

void TestStrings::test_trim_right() {

   // trim, nur rechte Seite
   string trimtest = "    spaces before    and     spaces after    ";
   //trimtest = "s    ";

   string ist = trim_right( trimtest );
   string soll = "    spaces before    and     spaces after" ;
   VERIFY( ist == soll, msgFail( "trim_right()", ist, soll ) );
}

void TestStrings::test_trim_left() {

   // trim, nur linke Seite
   string trimtest = "    spaces before    and     spaces after    ";
   // trimtest = "    s";

   string ist = trim_left( trimtest );
   string soll = "spaces before    and     spaces after    " ;
   VERIFY( ist == soll, msgFail( "trim_left()", ist, soll ) );
}

void TestStrings::test_trim_with_empty_string() {

   string trimtest = "        "; // Test mit Leerstring

   string ist = trim( trimtest ) ;
   string soll = "" ;
   VERIFY( ist == soll, msgFail( "trim(), mit Leerstring", ist, soll ) );


   ist = trim_right( trimtest ) ;
   soll = "" ;
   VERIFY( ist == soll, msgFail( "trim_right(), mit Leerstring", ist, soll ) );

   ist = trim_left( trimtest ) ;
   soll = "" ;
   VERIFY( ist == soll, msgFail( "trim_left(), mit Leerstring", ist, soll ) );
}

// --------------------------------
// --
// -- Index in einem String
// -- nicht gefunden = string::npos
// --

void TestStrings::test_index_at_char() {

   // char index von links

   size_t ist = rlf_hstring::index( "einW an Position 3", 'W' ) ;
   size_t soll = 3 ;
   VERIFY( ist == soll, msgFail( "index()", ist, soll ) );
}

void TestStrings::test_index_at_pattern() {

   // patten index von links

   size_t ist = index( "ein W an Position 4", "W an " ) ;
   size_t soll = 4 ;
   VERIFY( ist == soll, msgFail( "index(pattern)", ist, soll ) );
}

void TestStrings::test_index_right_at_char() {

   // char index von rechts

   size_t ist = index_right( "einW an Position 20 W ", 'W' ) ;
   size_t soll = 20;
   VERIFY( ist == soll, msgFail( "index_right()", ist, soll ) );
}

void TestStrings::test_index_at_pattern_from_pos() {

   // pattern index von links, mit start Position

   size_t ist = index( "hgxx123456hg12hgEE fy", "hg", 3 ) ;
   size_t soll = 10; // = 10, weil start bei 3
   VERIFY( ist == soll, msgFail( "index(), pattern", ist, soll ) );
}

void TestStrings::test_index_right_at_pattern() {
   // pattern index von rechts

   size_t ist = index_right( "hgxxxyzWpatternWfxyzgfyeg fy", "xyz" ) ;
   size_t soll = 17;
   VERIFY( ist == soll, msgFail( "index_right(), pattern", ist, soll ) );
}

void TestStrings::test_index_not_found() {

   // index nicht gefunden, return ist immer 'string::npos' (nicht -1 verwenden)

   size_t ist = rlf_hstring::index( "einW an Position 3", 'w' ) ;
   size_t soll = string::npos ; // 'w' war eine kleines 'w'
   VERIFY( ist == soll, msgFail( "index(), nicht gefunden", ist, soll ) );


   ist = index_right( "einW an Position W ", 'w' ) ;
   soll = string::npos ;
   VERIFY( ist == soll, msgFail( "index_right(), nicht gefunden", ist, soll ) );
}

// --------------------------------
// --
// -- ersetze Pattern im String durch ein anderes Pattern
// --

void TestStrings::test_replace_first() {

   // Ersatz nur an erster Stelle, an der das Pattern vorkommt

   string ist = replace_first( "hgxxxxhghfhxxeg fy", "xx", "1234567890" ) ;
   string soll = "hg1234567890xxhghfhxxeg fy"  ;
   VERIFY( ist == soll, msgFail( "replace_first()", ist, soll ) );
}

void TestStrings::test_replace_all() {

   // Ersatz an allen Stellen

   // Pattern ist nicht im Ergebnis
   string ist = replace_all( "hgxxxxhgxxxhfgxydxxxxxxxxxhWxypattxy xy ", "xx", "yy1234" ) ;
   string soll = "hgyy1234yy1234hgyy1234xhfgxydyy1234yy1234yy1234yy1234xhWxypattxy xy "  ;
   // Pattern ist im Ergebnis
   string ist1 = replace_all( "hgxxxxhgxxxhfgxydxxxxxxxxxhWxypattxy xy ", "xx", "xxyy1234" ) ;
   string soll1 = "hgxxyy1234xxyy1234hgxxyy1234xhfgxydxxyy1234xxyy1234xxyy1234xxyy1234xhWxypattxy xy "  ;
   VERIFY( ist1 == soll1, msgFail( "replace_all()", ist1, soll1 ) );
}

// --------------------------------
// --
// -- String nach rechts bis angegebener Breite mit Zeichen fuellen, nur rechts
// --

void TestStrings::test_fillup() {

   string ist = fillup( "abc", 'k', 6 ) ;
   string soll = "abckkk";
   VERIFY( ist == soll, msgFail( "fillup()", ist, soll ) );
}


// --------------------------------
// --
// -- Finde erstes und letztes Zeichen im String
// --
void TestStrings::test_last_char() {

   char ist = last_char( "hgxxxx fy" ) ;
   char soll = 'y';
   VERIFY( ist == soll, msgFail( "last_char()", ist, soll ) );
}
void TestStrings::test_first_char() {

   char ist = first_char( "hgxxx fy" ) ;
   char soll = 'h'  ;
   VERIFY( ist == soll, msgFail( "first_char()", ist, soll ) );
}
// --------------------------------
// --
// -- Loeschen von Teilstrings, an Position, mit Anzahl der Zeichen
// --

void TestStrings::test_erase() {

   string ist = erase( "hgxxxxFFhgh fy", 6, 2 ); // FF wird entfernt
   string soll = "hgxxxxhgh fy";
   VERIFY( ist == soll, msgFail( "erase()", ist, soll ) );
}

void TestStrings::test_erase_in_place() {

   // dto., 'in Place'
   string testErase = "12345";
   erase_in_place( testErase, 2, 1 ); // 3 wird entfernt, returns void
   string ist = testErase;
   string soll = "1245"  ;
   VERIFY( ist == soll, msgFail( "erase_in_place()", ist, soll ) );
}

void TestStrings::test_remove_last() {

   // remove last

   string ist = remove_last( "hgxxxxhghfgx fy" ) ;
   string soll = "hgxxxxhghfgx f";
   VERIFY( ist == soll, msgFail( "remove_last()", ist, soll ) );
}

void TestStrings::test_remove_last_in_place() {

   string testForRemove = "hgxxxxhghfgxy fy";

   remove_last_in_place( testForRemove ) ;   // returns void
   string ist = testForRemove;
   string soll = "hgxxxxhghfgxy f"  ;
   VERIFY( ist == soll, msgFail( "remove_last_in_place()", ist, soll ) );
}

void TestStrings::test_remove_first() {

   // remove first

   string ist = remove_first( "hgxxxxh fy" ) ;
   string soll = "gxxxxh fy"  ;
   VERIFY( ist == soll, msgFail( "remove_first", ist, soll ) );
}

void TestStrings::test_remove_first_pattern() {

   // remove first, with pattern

   string ist = remove_first( "hgxxhfgx-ydhWxypxy x-y  fy", "x-y" ) ;
   string soll = "hgxxhfgdhWxypxy x-y  fy"  ;
   VERIFY( ist == soll, msgFail( "remove_first(), pattern", ist, soll ) );
}

// --------------------------------
// --
// -- Einfuegen von Teilstrings, an Position, mit Anzahl der Zeichen
// --

void TestStrings::test_insert_at_char() {

   string ist = insert_at( "hgxxxxheg fy", 'A', 3 ) ;
   string soll = "hgxAxxxheg fy"  ;
   VERIFY( ist == soll, msgFail( "insert_at(), char", ist, soll ) );
}

void TestStrings::test_insert_at_pattern() {

   string ist = insert_at( "hgxxxxhgxxxh fy", "ABC", 3 ) ;
   string soll = "hgxABCxxxhgxxxh fy"  ;
   VERIFY( ist == soll, msgFail( "insert_at(), pattern", ist, soll ) );
}

// --------------------------------
// --
// -- Zerlegen in Tokens
// --


void TestStrings::test_split_to_6_tokens() {

   // 6 tokens
   std::vector<std::string> v = split( "Fuchs, du ha,st die Gans gestohlen.", " " );

   VERIFY( v.size() == 6, "split to vector, 6 tokens" );

}

void TestStrings::test_split_to_3_tokens() {

   // 3 tokens

   std::vector<std::string> v = split( "Fuchs,f| du ha,st| die Gans gestohlen ", '|' );
   VERIFY( v.size() == 3, "split to vector with 3 tokens" );

}


void TestStrings::test_split_with_multiple_delimiters() {

   // 3 tokens
   std::vector<std::string> v = split( "Fuchs, du ha,st die Gans gestohlen.", ", " );
   VERIFY( v.size() == 7, "split to vector with 7 tokens" );

}

// Test mit dem Macro VERIFY aus dem Qt Framework
void test2() {
   TestStrings testStrings;

   testStrings.test_string_to_type_double();
   testStrings.test_string_to_type_int();
   testStrings.test_string_to_type_size_t();

   testStrings.test_double_to_string_default_format();
   testStrings.test_double_to_string_format_supplied();

   testStrings.test_negative_int_to_string();

   testStrings.test_int_to_hex_0x();
   testStrings.test_int_to_hex_0x_32bit();
   testStrings.test_int_to_hex_0x_example2();
   testStrings.test_int_to_hex_0x_width16();
   testStrings.test_int_to_hex();

   testStrings.test_int_to_binaer_string();
   testStrings.test_int_to_binaer_string_width16();

   testStrings.test_to_lower_in_place();
   testStrings.test_to_lower_copy_string();

   testStrings.test_to_upper_in_place();
   testStrings.test_to_upper_copy_string();

   testStrings.test_clip_before_pattern();
   testStrings.test_clip_after_pattern();
   testStrings.test_clip_at_pos();
   testStrings.test_clip_at_char();
   testStrings.test_truncate_at_pos();

   testStrings.test_trim();
   testStrings.test_trim_right();
   testStrings.test_trim_left();
   testStrings.test_trim_with_empty_string();

   testStrings.test_index_at_char();
   testStrings.test_index_at_pattern();

   testStrings.test_index_right_at_char();

   testStrings.test_index_at_pattern_from_pos();
   testStrings.test_index_right_at_pattern();

   testStrings.test_index_not_found();

   testStrings.test_replace_first();
   testStrings.test_replace_all();

   testStrings.test_fillup();

   testStrings.test_last_char();
   testStrings.test_first_char();

   testStrings.test_erase();
   testStrings.test_erase_in_place();

   testStrings.test_remove_last();
   testStrings.test_remove_last_in_place();

   testStrings.test_remove_first();
   testStrings.test_remove_first_pattern();

   testStrings.test_insert_at_char();
   testStrings.test_insert_at_pattern();

   testStrings.test_split_to_6_tokens();
   testStrings.test_split_to_3_tokens();
   testStrings.test_split_with_multiple_delimiters();


}

} // end of namespace test_hstring

//EOF
