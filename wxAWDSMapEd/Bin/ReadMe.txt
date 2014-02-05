 ========================================
||  ADVANCE  WARS  SERIES  MAP  EDITOR  ||
||                                      ||
|| By Joao Pedro S. Francese (Roma_emu) ||
||      Version 1.0 (16/August/2007)    ||
 ========================================

          
  ***********
  * HISTORY *
  ***********

  For a long time, fans of the Nintendo Advance Wars portable series have
asked Intelligent Systems for a way of sharing maps and playing online
battles against other human players. While this program will not help with
the online gaming part, it is the most mapmaker-friendly editor to be
released this far.

  Long-time fans may also have come into contact with the Advance Wars (1)
editor developed by Kamek. It was the de facto standard editor used in PCs
running Windows. His editor was very practical, and aimed to be as easy
as the one built-in in the GBA game. All editors released after his tried
to look like his in some way.

  Later, with the release of Advance Wars 2, I updated his editor, adding
the Neotank, Black Hole buildings and units, and the new building graphics.
When Advance Wars Dual Strike was released, the editor was once again
updated, now with not only with AWDS units and buildings, but also with an
Extras tab, containing the BH-only buildings used in Campaign, such as
Minicannons, Deathrays and Volcanoes.

  Those were only updates though, and possible expansion was limited because
I was not familiar with the base code it used. So I started developing a new
editor from scratch. This editor is the result, with new features including
variable map size, permanent preferences, drawing modes and undo/redo buttons.
It still aims to look like Kamek's editor, so those who have used his editor
in the past will feel at home. This editor was also designed to be
multi-platform; to date, Windows and Linux versions are available, and a
Mac version is planned.

  Support for Custom Wars <www.customwars.com> units, buildings and
tilesets were planned for this release, but due to my lack of free time
(and, unfortunately, plain interest) I opted to not include it for now
so I could release the editor sooner. I have considered making the editor
open-source (GPL), but I haven't reached a decision yet and it will stay
closed-source freeware for now.


  **************
  * HOW TO USE *
  **************

  This editor works like the Advance Wars DS in-game editor. In the right
panel, you can switch between Terrain, Unit and Extra modes. (Extra contains
terrain types not available in the in-game editor.) Then, click a terrain or
unit in the list, and left-click a tile in the map area to the left to place
the selected terrain or unit in it. Some terrains or units have placement
restrictions, and some terrains in the Extra tab are larger than one tile.

  You can change the active Unit army by clicking the correspondently-colored
city, and you can delete units by choosing the Delete (hammer) icon.
Mouse shortcuts include the middle-button (click to switch tabs quickly)
and the scroll wheel (switch armies when a building or unit is selected).
Right-clicking the map area will select the terrain or unit (depending on
the active tab) from the clicked tile. You can undo a previous action by
pressing the Undo button in the toolbar (or with the Ctrl+Z shortcut), or
redo an undone action the same way.

  The default drawing mode is the Pencil, which places one terrain or unit
at a time, and the mouse button can be held down so terrains and units
continue to be placed while the cursor is dragged around. Line mode allows
you to place a straight line of the selected terrain or unit; position the
cursor over the start point, then hold the left mouse button, move to the
desired end point and release the button. Square and Filled Square work the
same way, but instead making a rectangle. Fill Bucket will fill an area of
tiles equal to the clicked tile with the active unit or terrain.

  Selection will let you select a map area in the same fashion of Square;
you can then move the selected area around (both terrains and units are
moved), copy or cut it with the Edit menu options, clear the selected area
with delete (press Esc to only cancel the selection) or make a quick copy
by holding the Control keyboard button while moving the selected area.
More options regarding selected areas can be found in the Edit menu.
Note that when you cut or copy an area, you can paste it in other instances
(windows) of the editor.

  The map status (information about placed armies) can be seen in the
Status screen, which can be accessed from the Map -> Status menu
(or the F8 shortcut). In this screen you can view how many buildings of
each kind and units are owned by each army, as well as the total number
of buildings (the in-game real limit is 60) and if the map contains data
that is unavailable in one of the real games.

  Map information can be saved in the Information screen (Map -> Information
or Ctrl+I shortcut). The map author can set his or her name, as well as the
map name and a short description of the map. It is strongly recommended
to always fill the two first fields before sharing maps with friends.
Map settings, including height, width and tileset (map graphics), can be set
in the Settings (Map -> Settings or F10) screen. Note that so far the in-game
editor only accepts 30x20 maps.

  This editor stores some preferences in a .ini file, which must be kept in
the same folder of the main program (.exe) file. The preferences that can
be saved are as follows:
  - Background music can be disabled, or enabled with adjustable volume.
       To change the background music, put any MP3 music file in the
       editor folder and rename it to bgm.mp3.
  - Default width, height, tileset and terrain can be set.
  - Default author name can be set.
  - Undo/redo limit can be changed; keep it low if your computer has
       limited available (RAM) memory.
  - AW-style cursors can be disabled; drawing these cursors is
       CPU-intensive, so this is recommended for older computers.

  This editor's default save type is the .aws map format. It can open files
from old editors (with extensions .awm, .aw2 and .awd). It can also save in
these formats, but incompatible units and terrains may not be saved. You
will be warned if this happens.

  You can save screenshots (pictures of the entire map) to your computer with
the File -> Screenshot menu entry. You can pick one of the various file types:
  - PNG produces the best results (no quality loss), with reasonable
       file sizes. You can also make miniatures (half-sized pictures).
  - BMP is a format used by Windows that produces large files.
  - JPG pictures can also be saved. They have small sizes as well, but
       some quality may be lost. Useful if the website or program does
       not support PNG files.
  - XPM files are used mainly by some Linux programs.
  - ICO files can be saved to be used as Windows file shortcuts' icons.
       The picture is resized when needed to fit the maximum size of
       255x197 pixels (the map's proportion is kept).

  Some terrain tiles are special and worth mentioning or explaining:
  - Labs are HQ-equivalents: only one of them (either a Lab or a HQ) of each
       army may be placed at a time.
  - The terrain tile to the right of the bridge is the "destroyed minicannon"
       sprite. It will become a "destroyed pipeline seam" sprite if placed in
       the middle of a pipe line. When porting a map to the GBA/DS, simply
       change it to a normal plain tile.
  - The Sea kind of Black Arc can only be placed in sea areas; you will not be
       allowed to place it if there is any ground tile under the cursor or its
       adjacent tiles.


  This package also includes some sample maps:
  - AWS maps: Abcdefg, Abcdefgh and Absdfsdfsd.
  - AWDS maps: Red Sand Desert, Devil Lake and Devil Lake DS.
  - AW1 maps: Butterfly Island, Road-Block, Spann Island and Wrench Island.
  - AW2 maps: Black Hole, The Circle and Triple Front.

  More maps can be found at the Design Maps section of Advance Wars Net:
     http://www.advancewarsnet.com/designamps



  ****************************
  * CREDITS AND CONTACT INFO *
  ****************************

This map editor was designed and programmed solely and completely by
the Brazilian programmer João Pedro Schara Francese. (For the technically
curious, I've used C++ and the GUI toolkit wxWidgets.) I, however, owe
much of my inspiration to Kamek, who designed the original editor.

If you have a suggestion, complaint or comment, send it to my e-mail:
<roma.emu@gmail.com> or <joaofrancese@gmail.com>. You can also contact
me via MSN <joaofrancese@gmail.com> or via AIM <Roma emu>.

Check for editor updates and new versions at its website:
http://mapeditor.hopto.org

Special thanks to:
 - Kamek, for creating the original map editor and giving me its
      source code so I could update it.
 - CO Sonic, Alex05 and ChessRules, for the AWDS Normal tileset, AWDS-style
      buildings and AWDS unit sprites.
 - Rimdev, omnitarian, Oracle of Wuffing, Kosheh and Zen, for the
      AWDS snow/desert/wasteland tilesets and Black Hole campaign
      weapons + volcano sprites.
 - Madcow, for creating Advance Wars Net and hosting the map editor
      for so much time.
 - DeathBerzerker, jb55, UrzaMTG, Veggiehunter and MoogleGunner,
      for helping me various times or just listening to my ratings...


  *******************
  * VERSION HISTORY *
  *******************

  v1.0 (16/August/2007)
    - Windows and Linux versions.
    - First public release. (Previous alphas/betas were time-locked.)


  *********************
  * WEBMASTERS NOTICE *
  *********************

Note to webmasters: feel free to upload this editor to your server.
However, if you do, you will be responsible for checking the editor site
<http://mapeditor.hopto.org> every once in a while for new versions.
You must also credit me (Roma_emu or Joao Pedro S. Francese) properly,
and all files found in this zip file (the editor, the background MP3,
the readme file and the map samples) must be kept.
please don't point directly to the file on AWN's server or host it in your
server/domain. Please link to the editor's home page instead.
<http://www.advancewarsnet.com/mapeditors.shtml>