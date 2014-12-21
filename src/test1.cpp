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


#include "stringhelper.h"
#include "test_hstring.h"


#ifdef _WIN32
#pragma warning( disable : 4309 ) // Warning  truncation of constant value in line 128
#endif


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


namespace test_hstring {

   // bitte Breakpoints mit dem debugger an 'int debug_i = 0' einfuegen
   // danach kann man die Werte im Debugger vergleichen
   void test1() {

      // Umwandlung eines Strings in einen Wert, Beispiel nach 'double'
      {
         double ist = string2type<double>( "1234.7" );
         double soll  = 1234.7;
         int debug_i = 0;
      }
      // Umwandlung eines Strings in einen Wert, Beispiel nach 'int'
      {
         int ist  = string2type<int>( "4711" );
         int soll = 4711;
         int debug_i = 0;
      }
      // Umwandlung eines Strings in einen Wert, Beispiel nach 'size_t'
      {
         // 32 bit      soll  4294967295  unsigned int
         size_t ist = string2type<size_t>( "4294967295" );
         // 64 bit
         //    size_t ist = strhlp::string2type<size_t>("18446744073709551615");
         size_t soll = -1;
         int debug_i = 0;
      }
      // --------------------------------
      // --
      // Wert nach String, war frueher: 'itoa', 'ftoa' usw.
      // --

      // Umwandlung eines double-Wertes in einen String, default Format '%6.3lf'
      {
         string ist = toString( 1234.7 ); // 1234.700, 3 dezimalstellen, default
         string soll = "1234.700";
         int debug_i = 0;
      }


      // Umwandlung eines double-Wertes in einen String mit Format, '%10.7lf'
      {
         string ist = toString( 1234.7, 10, 7 );  // 1234.7000000, 7 nachkommastellen, user defined
         string soll = "1234.7000000";
         int debug_i = 0;
      }


      // Umwandlung eines negativen Int-Wertes in einen String'
      {
         string ist = toString( -1 );
         string soll = "-1";
         int debug_i = 0;
      }
      // --------------------------------
      // --
      // Sonderfaelle, Int-Wert nach Hexadezimal und Binaer
      //--


      // Int-Wert in einen hexadezimalen String, mit '0x' Prefix, nur mit 64 bit
      {
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

         string ist = to_hex_0x( a ) ; // mit 0x "0xFFFFFFFFFFFFFFFF
         string soll = "0xFFFFFFFFFFFFFFFF";
         int debug_i = 0;
      }

      // Int-Wert in einen hexadezimalen String, mit '0x' Prefix
      {
         string ist = to_hex_0x( 4294967295 ) ; // mit 0x "0xFFFFFFFF
         string soll = "0xFFFFFFFF";
         int debug_i = 0;
      }

      // Int-Wert in einen hexadezimalen String, mit '0x' Prefix, anderes Beispiel
      {
         string ist = to_hex_0x( 1234567 ); // 0x0012D687
         string soll =  "0x0012D687";
         int debug_i = 0;
      }

      // Int-Wert in einen hexadezimalen String, mit '0x' Prefix, Feldbreite 16
      {
         string ist = to_hex_0x( 1234567, 16 );
         string soll =  "0x000000000012D687";
         int debug_i = 0;
      }
      // Int-Wert in einen hexadezimalen String, ohne '0x' Prefix
      {
         string ist = to_hex( 256 * 256 + 1 ); // ohne 0x "00010001"
         string soll = "00010001" ;
         int debug_i = 0;
      }
      // Int-Wert in einen binaeren String, Feldbreite 32
      {
         string ist = to_bin( 256 * 256 - 1 );
         string soll = "00000000000000001111111111111111";
         int debug_i = 0;
      }

      // Int-Wert in einen binaeren String, Feldbreite 16
      {
         string ist = to_bin( 256 * 256 - 1, 16 );
         string soll = "1111111111111111";
         int debug_i = 0;
      }





      // --------------------------------
      // --
      // -- String, Umwandlung Gross-/Kleinschreibung, in Place und/oder als Kopie
      // --

      // 'in Place' Funktionen funktionieren nicht mit einem
      //  statischen String, z.B. "abc"

      // to lower, 'in Place'
      {
         string upper = "KAPITAELCHEN";
         to_lower_in_place( upper ); // "kapitaelchen"
         string ist = upper;
         string soll = "kapitaelchen";

         int debug_i = 0;
      }
      // to lower, als Kopie
      {
         string ist = to_lower( "TEST mit KOPIE DES STRINGS" );
         string soll = "test mit kopie des strings" ;
         int debug_i = 0;
      }


      // to upper, 'in Place'
      {
         string lower = "test in Place";
         to_upper_in_place( lower );
         string ist = lower;
         string soll = "TEST IN PLACE";
         int debug_i = 0;
      }

      {

         // to upper, als Kopie, mit Sonderzeichen

         string ist = to_upper( "abcdfghi++??u" );
         string soll =  "ABCDFGHI++??U" ;
         int debug_i = 0;
      }

      // --------------------------------
      // --
      //  -- clip a String
      // --

      {
         // clip vor Pattern

         string ist = clip( " 1234pattern1234, ", "pattern" );
         string soll = " 1234" ;
         int debug_i = 0;
      }

      {

         // clip nach einem Pattern

         string ist = clip_after( "hgxxxxxypattxy xy " , "patt" ) ;
         string soll = "hgxxxxxypatt"  ;
         int debug_i = 0;
      }

      {

         // clip an einer Position

         string ist = clip_at_pos( "12 34pattern1234", 6 );
         string soll =  "12 34p" ;
         int debug_i = 0;
      }

      {

         // clip an einem Char

         string ist = clip_at_char( "123 4pattern12W34, ", 'W' ) ;
         string soll = "123 4pattern12" ;
         int debug_i = 0;
      }

      {

         // truncate an einer Position, entspricht clip_at_pos()

         string ist = rlf_hstring::truncate( "hier ist das 1234 ", 7 );
         string soll = "hier is" ;
         int debug_i = 0;
      }

      // --------------------------------
      // --
      // -- trim a String, default ist ' ', andere Zeichen als 2. Parameter möglich
      // --

      {

         string trimtest = "    spaces before    and     spaces after    ";

         // trim, beide Seiten

         string ist = trim( trimtest ) ;
         string soll = "spaces before    and     spaces after" ;
         int debug_i = 0;
      }

      {

         // trim, nur rechte Seite
         string trimtest = "    spaces before    and     spaces after    ";

         string ist = trim_right( trimtest );
         string soll = "    spaces before    and     spaces after" ;
         int debug_i = 0;
      }

      {

         // trim, nur linke Seite
         string trimtest = "    spaces before    and     spaces after    ";

         string ist = trim_left( trimtest );
         string soll = "spaces before    and     spaces after    " ;
         int debug_i = 0;
      }

      {

         string trimtest = "        "; // Test mit Leerstring

         string ist = trim( trimtest ) ;
         string soll = "" ;


         ist = trim_right( trimtest ) ;
         soll = "" ;

         ist = trim_left( trimtest ) ;
         soll = "" ;
         int debug_i = 0;
      }

      // --------------------------------
      // --
      // -- Index in einem String
      // -- nicht gefunden = string::npos
      // --

      {

         // char index von links

         size_t ist = rlf_hstring::index( "einW an Position 3", 'W' ) ;
         size_t soll = 3 ;
         int debug_i = 0;
      }

      {

         // patten index von links

         size_t ist = index( "ein W an Position 4", "W an " ) ;
         size_t soll = 4 ;
         int debug_i = 0;
      }

      {

         // char index von rechts

         size_t ist = index_right( "einW an Position 20 W ", 'W' ) ;
         size_t soll = 20;
         int debug_i = 0;
      }

      {

         // pattern index von links, mit start Position

         size_t ist = index( "hgxx123456hg12hgEE fy", "hg", 3 ) ;
         size_t soll = 10; // = 10, weil start bei 3
         int debug_i = 0;
      }

      {
         // pattern index von rechts

         size_t ist = index_right( "hgxxxyzWpatternWfxyzgfyeg fy", "xyz" ) ;
         size_t soll = 17;
         int debug_i = 0;
      }

      {

         // index nicht gefunden, return ist immer 'string::npos' (nicht -1 verwenden)

         size_t ist = rlf_hstring::index( "einW an Position 3", 'w' ) ;
         size_t soll = string::npos ; // 'w' war eine kleines 'w'


         ist = index_right( "einW an Position W ", 'w' ) ;
         soll = string::npos ;
         int debug_i = 0;
      }

      // --------------------------------
      // --
      // -- ersetze Pattern im String durch ein anderes Pattern
      // --

      {

         // Ersatz nur an erster Stelle, an der das Pattern vorkommt

         string ist = replace_first( "hgxxxxhghfhxxeg fy", "xx", "1234567890" ) ;
         string soll = "hg1234567890xxhghfhxxeg fy"  ;
         int debug_i = 0;
      }

      {

         // Ersatz an allen Stellen

         string ist = replace_all( "hgxxxxhgxxxhfgxydxxxxxxxxxhWxypattxy xy ", "xx", "yy1234" ) ;
         string soll = "hgyy1234yy1234hgyy1234xhfgxydyy1234yy1234yy1234yy1234xhWxypattxy xy "  ;

         // pattern ist im Ergebnis und darf ncht zum 2.mal ausgetauscht werden
         // geht mit VS2010 nicht
         //string ist1 = strhlp::replace_all( "hgxxxxhgxxxhfgxydxxxxxxxxxhWxypattxy xy ", "xx", "xxyy1234" ) ;
         //string soll1 = "hgxxyy1234xxyy1234hgxxyy1234xhfgxydxxyy1234xxyy1234xxyy1234xxyy1234xhWxypattxy xy "  ;
         int debug_i = 0;
      }

      // --------------------------------
      // --
      // -- String nach rechts bis angegebener Breite mit Zeichen fuellen, nur rechts
      // --

      {

         string ist = fillup( "abc", 'k', 6 ) ;
         string soll = "abckkk";
         int debug_i = 0;
      }


      // --------------------------------
      // --
      // -- Finde erstes und letztes Zeichen im String
      // --
      {

         char ist = last_char( "hgxxxx fy" ) ;
         char soll = 'y';
         int debug_i = 0;
      }
      {

         char ist = first_char( "hgxxx fy" ) ;
         char soll = 'h'  ;
         int debug_i = 0;
      }
      // --------------------------------
      // --
      // -- Loeschen von Teilstrings, an Position, mit Anzahl der Zeichen
      // --

      {

         string ist = erase( "hgxxxxFFhgh fy", 6, 2 ); // FF wird entfernt
         string soll = "hgxxxxhgh fy";
         int debug_i = 0;
      }

      {

         // dto., 'in Place'
         string testErase = "12345";
         erase_in_place( testErase, 2, 1 ); // 3 wird entfernt, returns void
         string ist = testErase;
         string soll = "1245"  ;
         int debug_i = 0;
      }

      {

         // remove last

         string ist = remove_last( "hgxxxxhghfgx fy" ) ;
         string soll = "hgxxxxhghfgx f";
         int debug_i = 0;
      }

      {

         string testForRemove = "hgxxxxhghfgxy fy";

         remove_last_in_place( testForRemove ) ;   // returns void
         string ist = testForRemove;
         string soll = "hgxxxxhghfgxy f"  ;
         int debug_i = 0;
      }

      {

         // remove first

         string ist = remove_first( "hgxxxxh fy" ) ;
         string soll = "gxxxxh fy"  ;
         int debug_i = 0;
      }

      {

         // remove first, with pattern

         string ist = remove_first( "hgxxhfgx-ydhWxypxy x-y  fy", "x-y" ) ;
         string soll = "hgxxhfgdhWxypxy x-y  fy"  ;
         int debug_i = 0;
      }

      // --------------------------------
      // --
      // -- Einfuegen von Teilstrings, an Position, mit Anzahl der Zeichen
      // --

      {

         string ist = insert_at( "hgxxxxheg fy", 'A', 3 ) ;
         string soll = "hgxAxxxheg fy"  ;
         int debug_i = 0;
      }

      {

         string ist = insert_at( "hgxxxxhgxxxh fy", "ABC", 3 ) ;
         string soll = "hgxABCxxxhgxxxh fy"  ;
         int debug_i = 0;
      }

      // --------------------------------
      // --
      // -- Zerlegen in Tokens
      // --


      {

         // 6 tokens
         std::vector<std::string> v = split( "Fuchs, du ha,st die Gans gestohlen.", " " );


         int debug_i = 0;
      }

      {

         // 3 tokens
         std::vector<std::string> v = split( "Fuchs, du ha,st die Gans gestohlen.", "," );

         int debug_i = 0;
      }


      {

         // 3 tokens
         std::vector<std::string> v = split( "Fuchs, du ha,st die Gans gestohlen.", ", " );

         int debug_i = 0;
      }

   }

}// end of namespace test_hstring

//EOF


