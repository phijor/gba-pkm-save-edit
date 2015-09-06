gba-pkm-save-edit
=================

*A commandline application to edit save files of Pokémon-games for the GBA.*

BUILDING
--------

Run `make`. For a debug-version run `make debug`.

RUNNING
-------

`gba-pkm-save-edit [flags] <savefile> commands...`

###flags (optional)

*none*

(at least for now)

###savefile

The savefile to read from.

###commands

* `show`:
    * `show pokedex [range: entries]`:
        * show which Pokémon are caught, seen or unseen
        * the optional [`range`](#ranges) limits output to only a subset of all entries
    * `show pokemon <party|box>`:
        * show information about Pokémon
        * `party [range: slots]` shows Pokémon from the players party
        * `box [range: boxes] [range: slots]` shows Pokémon from the PC storage
    * `show trainer`:
        * show information about the trainer (the player) of the current
            savefile
* `dump [filename]`:
    * export the most recent gamestate in an unpacked format to `filename`
        * if `filename` is missing, it defaults to `dump.sav.unpacked`
* `export`:
    * `export pokemon <party|box>`:
        * export a Pokémon to a file
        * `party [range: slots] [directory]`:
            * export each Pokémon of the players party in `slots` to a file in
                `directory`
        * `box [range: boxes] [range: slots] [directory]`:
            * export all Pokémon occupying `slots` in `boxes` to a file each in
                `directory`

###<a name="ranges">ranges</a>
A `range` has the form of `/[0-9]*-[0-9]*/` and describes on which indices
a command should operate.

Example: showing information about different Pokémon in the party.

Typing `show pokemon party ...` | ...prints out...
--------------------------------|-----------------
`1`                             | 1
`1-3`                           | 1, 2 & 3
`1-`                            | 1 plus however many are in the party
`-3`                            | all up to (and including) 3
`-`                             | all off them

TODO
----

- [ ] move `enum`s related to Pokémon data to their own files
