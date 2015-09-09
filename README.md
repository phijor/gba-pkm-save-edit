gba-pkm-save-edit
=================

*A commandline application to edit save files of Pokémon-games for the GBA.*

BUILDING
--------

    $ git clone https://github.com/phijor/gba-pkm-save-edit
    $ cd gba-pkm-save-edit
    $ make

If you wish to run a debug-build:

    $ make debug

INSTALLING
----------

    $ make install

If you wish to install to a different location (e.g. `foo/bar/`):

    $ make DESTDIR="foo/bar/" install

###using a package-manager

If you are using Arch, you can install from the [AUR](https://aur.archlinux.org/packages/gba-pkm-save-edit-git/):

    pacaur -S gba-pkm-save-edit-git

RUNNING
-------

    gba-pkm-save-edit [flags] <savefile> commands...

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

Typing `show pokemon party ...` | ...prints out Pokémon...
--------------------------------|-------------------------
`1`                             | 1
`1-3`                           | 1, 2 & 3
`1-`                            | 1 plus however many are in the party
`-3`                            | all up to (and including) 3
`-`                             | all off them

TODO
----

###long-term
- [ ] full savefile description
- [ ] full savefile editability

###short-term
- [x] move `enum`s related to Pokémon data to their own files
- [x] add a convenience-functions to de-/encrypt a Pokémon
- [x] determine whether a Pokémon is an egg or not from occupancy-byte in
    Pokémon-struct
- [ ] add some necessary flags
- [ ] add setter-functions for each value in the savefile that has a getter
- [ ] add format options to `message(...)` which indent instantly
- [ ] remove I/O from `save_` functions as much as possible and handle errors
    via return-values etc.
