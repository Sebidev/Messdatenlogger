/*
[Datenlogger v1.1.0]

Copyright (C) [2017]  [Sebastian Bürger & Tom Hoffmeister]

Dieses Programm ist freie Software. Sie können es unter den Bedingungen der GNU General Public License, wie von der Free Software Foundation veröffentlicht, weitergeben und/oder modifizieren, entweder gemäß Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren Version.
Die Veröffentlichung dieses Programms erfolgt in der Hoffnung, daß es Ihnen von Nutzen sein wird, aber OHNE IRGENDEINE GARANTIE, sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT FÜR EINEN BESTIMMTEN ZWECK. Details finden Sie in der GNU General Public License.
Sie sollten ein Exemplar der GNU General Public License zusammen mit diesem Programm erhalten haben. Falls nicht, siehe <http://www.gnu.org/licenses/>. 
*/
// ======================================
// Autor von LCDMenuLib: 
// Nils Feldkämper
// License: MIT                                       

  #include <LiquidCrystal_I2C.h>
  #include <LCDMenuLib.h>
  
  // lib config
  #define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms
  #define _LCDML_DISP_cfg_initscreen_time            10000  // enable initscreen time
  #define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar
  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol 

// ********************************************************************* 
// LCDML TYPE SELECT
// *********************************************************************
  // settings for lcd 
  #define _LCDML_DISP_cols             20
  #define _LCDML_DISP_rows             4  

  // lcd object
  // liquid crystal needs (rs, e, dat4, dat5, dat6, dat7)
  LiquidCrystal_I2C lcd(0x27,20,4);
  
  const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1 
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
  }; 

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // create menu
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    16
  
  // LCDML_root        => layer 0 
  // LCDML_root_X      => layer 1 
  // LCDML_root_X_X    => layer 2 
  // LCDML_root_X_X_X  => layer 3 
  // LCDML_root_... 	 => layer ... 
  
  // LCDMenuLib_add(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
  LCDML_DISP_init(_LCDML_DISP_cnt);
  LCDML_DISP_addMenu  (0  , _LCDML_G1  , LCDML_root        , 1  , "Messadapter");
  LCDML_DISP_addMenu  (1  , _LCDML_G1  , LCDML_root        , 2  , "Messzeitintervall");
  LCDML_DISP_add      (2  , _LCDML_G1  , LCDML_root        , 3  , "Messung starten"    , messung);
  LCDML_DISP_add      (3  , _LCDML_G1  , LCDML_root_1      , 5  , "Strommessung"       , strommessungtyp);
  LCDML_DISP_add      (4  , _LCDML_G1  , LCDML_root_1      , 2  , "Spannungsmessung"   , spannungsmessungtyp)
  LCDML_DISP_add      (5  , _LCDML_G1  , LCDML_root        , 5  , "Uhrzeit/Datum"      , show_uhr_date);;
  LCDML_DISP_add      (6  , _LCDML_G1  , LCDML_root        , 6  , "Firmware"           , LCDML_FUNC_information);
  LCDML_DISP_add      (7  , _LCDML_G1  , LCDML_root_1      , 1  , "Leistungsmessung"   , leistungsmessungtyp);
  LCDML_DISP_add      (8  , _LCDML_G1  , LCDML_root_1      , 3  , "Wetterfrosch"       , wetterfroschmessungtyp);
  LCDML_DISP_add      (9  , _LCDML_G1  , LCDML_root_1      , 6  , "Tempaturmessung"    , tempaturmessungtyp);
  LCDML_DISP_add      (10 , _LCDML_G1  , LCDML_root_1      , 7  , "Lichtmodul"         , lichtmodultyp);
  LCDML_DISP_add      (11 , _LCDML_G1  , LCDML_root_1      , 8  , "Regenmodul"         , regenmodul);
  LCDML_DISP_add      (12 , _LCDML_G1  , LCDML_root_2      , 1  , "30 Sekunden"        , x30sek);
  LCDML_DISP_add      (13 , _LCDML_G1  , LCDML_root_2      , 2  , "1 Minuten"          , x1min);
  LCDML_DISP_add      (14 , _LCDML_G1  , LCDML_root_2      , 3  , "5 Minuten"          , x5min);
  LCDML_DISP_add      (15 , _LCDML_G1  , LCDML_root_2      , 4  , "10 Minuten"         , x10min);
  LCDML_DISP_add      (16 , _LCDML_G1  , LCDML_root_2      , 5  , "15 Minuten"         , x15min);  
  LCDML_DISP_createMenu(_LCDML_DISP_cnt);



// ********************************************************************* 
// LCDML BACKEND (core of the menu, do not change here anything yet)
// ********************************************************************* 
  // define backend function  
  #define _LCDML_BACK_cnt    1  // last backend function id
  
  LCDML_BACK_init(_LCDML_BACK_cnt);
  LCDML_BACK_new_timebased_dynamic (0  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
  LCDML_BACK_new_timebased_dynamic (1  , ( 1000UL )       , _LCDML_stop   , LCDML_BACKEND_menu);
  LCDML_BACK_create();


// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {  
    lcd.begin();  
    // set special chars for scrollbar
    lcd.createChar(0, (uint8_t*)scroll_bar[0]);
    lcd.createChar(1, (uint8_t*)scroll_bar[1]);
    lcd.createChar(2, (uint8_t*)scroll_bar[2]);
    lcd.createChar(3, (uint8_t*)scroll_bar[3]);
    lcd.createChar(4, (uint8_t*)scroll_bar[4]);
  
    // Enable all items with _LCDML_G1
    LCDML_DISP_groupEnable(_LCDML_G1); // enable group 1
  
    // LCDMenu Setup
    LCDML_setup(_LCDML_BACK_cnt);  
  }

// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  { 
    // this function must called here, do not delete it
    LCDML_run(_LCDML_priority); 
  }




// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
# if(_LCDML_DISP_rows > _LCDML_DISP_cfg_max_rows)
# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib.h
# endif
# if(_LCDML_DISP_cols > _LCDML_DISP_cfg_max_string_length)
# error change value of _LCDML_DISP_cfg_max_string_length in LCDMenuLib.h
# endif
