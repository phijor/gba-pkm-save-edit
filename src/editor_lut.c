#include "editor_lut.h"

char* editor_move_names[] = {
    "--",
    "Pound",
    "Karate Chop",
    "Double Slap",
    "Comet Punch",
    "Mega Punch",
    "Pay Day",
    "Fire Punch",
    "Ice Punch",
    "Thunder Punch",
    "Scratch",
    "Vice Grip",
    "Guillotine",
    "Razor Wind",
    "Swords Dance",
    "Cut",
    "Gust",
    "Wing Attack",
    "Whirlwind",
    "Fly",
    "Bind",
    "Slam",
    "Vine Whip",
    "Stomp",
    "Double Kick",
    "Mega Kick",
    "Jump Kick",
    "Rolling Kick",
    "Sand Attack",
    "Headbutt",
    "Horn Attack",
    "Fury Attack",
    "Horn Drill",
    "Tackle",
    "Body Slam",
    "Wrap",
    "Take Down",
    "Thrash",
    "Double-Edge",
    "Tail Whip",
    "Poison Sting",
    "Twineedle",
    "Pin Missile",
    "Leer",
    "Bite",
    "Growl",
    "Roar",
    "Sing",
    "Supersonic",
    "Sonic Boom",
    "Disable",
    "Acid",
    "Ember",
    "Flamethrower",
    "Mist",
    "Water Gun",
    "Hydro Pump",
    "Surf",
    "Ice Beam",
    "Blizzard",
    "Psybeam",
    "Bubble Beam",
    "Aurora Beam",
    "Hyper Beam",
    "Peck",
    "Drill Peck",
    "Submission",
    "Low Kick",
    "Counter",
    "Seismic Toss",
    "Strength",
    "Absorb",
    "Mega Drain",
    "Leech Seed",
    "Growth",
    "Razor Leaf",
    "Solar Beam",
    "Poison Powder",
    "Stun Spore",
    "Sleep Powder",
    "Petal Dance",
    "String Shot",
    "Dragon Rage",
    "Fire Spin",
    "Thunder Shock",
    "Thunderbolt",
    "Thunder Wave",
    "Thunder",
    "Rock Throw",
    "Earthquake",
    "Fissure",
    "Dig",
    "Toxic",
    "Confusion",
    "Psychic",
    "Hypnosis",
    "Meditate",
    "Agility",
    "Quick Attack",
    "Rage",
    "Teleport",
    "Night Shade",
    "Mimic",
    "Screech",
    "Double Team",
    "Recover",
    "Harden",
    "Minimize",
    "Smokescreen",
    "Confuse Ray",
    "Withdraw",
    "Defense Curl",
    "Barrier",
    "Light Screen",
    "Haze",
    "Reflect",
    "Focus Energy",
    "Bide",
    "Metronome",
    "Mirror Move",
    "Self-Destruct",
    "Egg Bomb",
    "Lick",
    "Smog",
    "Sludge",
    "Bone Club",
    "Fire Blast",
    "Waterfall",
    "Clamp",
    "Swift",
    "Skull Bash",
    "Spike Cannon",
    "Constrict",
    "Amnesia",
    "Kinesis",
    "Soft-Boiled",
    "High Jump Kick",
    "Glare",
    "Dream Eater",
    "Poison Gas",
    "Barrage",
    "Leech Life",
    "Lovely Kiss",
    "Sky Attack",
    "Transform",
    "Bubble",
    "Dizzy Punch",
    "Spore",
    "Flash",
    "Psywave",
    "Splash",
    "Acid Armor",
    "Crabhammer",
    "Explosion",
    "Fury Swipes",
    "Bonemerang",
    "Rest",
    "Rock Slide",
    "Hyper Fang",
    "Sharpen",
    "Conversion",
    "Tri Attack",
    "Super Fang",
    "Slash",
    "Substitute",
    "Struggle",
    "Sketch",
    "Triple Kick",
    "Thief",
    "Spider Web",
    "Mind Reader",
    "Nightmare",
    "Flame Wheel",
    "Snore",
    "Curse",
    "Flail",
    "Conversion 2",
    "Aeroblast",
    "Cotton Spore",
    "Reversal",
    "Spite",
    "Powder Snow",
    "Protect",
    "Mach Punch",
    "Scary Face",
    "Feint Attack",
    "Sweet Kiss",
    "Belly Drum",
    "Sludge Bomb",
    "Mud-Slap",
    "Octazooka",
    "Spikes",
    "Zap Cannon",
    "Foresight",
    "Destiny Bond",
    "Perish Song",
    "Icy Wind",
    "Detect",
    "Bone Rush",
    "Lock-On",
    "Outrage",
    "Sandstorm",
    "Giga Drain",
    "Endure",
    "Charm",
    "Rollout",
    "False Swipe",
    "Swagger",
    "Milk Drink",
    "Spark",
    "Fury Cutter",
    "Steel Wing",
    "Mean Look",
    "Attract",
    "Sleep Talk",
    "Heal Bell",
    "Return",
    "Present",
    "Frustration",
    "Safeguard",
    "Pain Split",
    "Sacred Fire",
    "Magnitude",
    "Dynamic Punch",
    "Megahorn",
    "Dragon Breath",
    "Baton Pass",
    "Encore",
    "Pursuit",
    "Rapid Spin",
    "Sweet Scent",
    "Iron Tail",
    "Metal Claw",
    "Vital Throw",
    "Morning Sun",
    "Synthesis",
    "Moonlight",
    "Hidden Power",
    "Cross Chop",
    "Twister",
    "Rain Dance",
    "Sunny Day",
    "Crunch",
    "Mirror Coat",
    "Psych Up",
    "Extreme Speed",
    "Ancient Power",
    "Shadow Ball",
    "Future Sight",
    "Rock Smash",
    "Whirlpool",
    "Beat Up",
    "Fake Out",
    "Uproar",
    "Stockpile",
    "Spit Up",
    "Swallow",
    "Heat Wave",
    "Hail",
    "Torment",
    "Flatter",
    "Will-O-Wisp",
    "Memento",
    "Facade",
    "Focus Punch",
    "Smelling Salts",
    "Follow Me",
    "Nature Power",
    "Charge",
    "Taunt",
    "Helping Hand",
    "Trick",
    "Role Play",
    "Wish",
    "Assist",
    "Ingrain",
    "Superpower",
    "Magic Coat",
    "Recycle",
    "Revenge",
    "Brick Break",
    "Yawn",
    "Knock Off",
    "Endeavor",
    "Eruption",
    "Skill Swap",
    "Imprison",
    "Refresh",
    "Grudge",
    "Snatch",
    "Secret Power",
    "Dive",
    "Arm Thrust",
    "Camouflage",
    "Tail Glow",
    "Luster Purge",
    "Mist Ball",
    "Feather Dance",
    "Teeter Dance",
    "Blaze Kick",
    "Mud Sport",
    "Ice Ball",
    "Needle Arm",
    "Slack Off",
    "Hyper Voice",
    "Poison Fang",
    "Crush Claw",
    "Blast Burn",
    "Hydro Cannon",
    "Meteor Mash",
    "Astonish",
    "Weather Ball",
    "Aromatherapy",
    "Fake Tears",
    "Air Cutter",
    "Overheat",
    "Odor Sleuth",
    "Rock Tomb",
    "Silver Wind",
    "Metal Sound",
    "Grass Whistle",
    "Tickle",
    "Cosmic Power",
    "Water Spout",
    "Signal Beam",
    "Shadow Punch",
    "Extrasensory",
    "Sky Uppercut",
    "Sand Tomb",
    "Sheer Cold",
    "Muddy Water",
    "Bullet Seed",
    "Aerial Ace",
    "Icicle Spear",
    "Iron Defense",
    "Block",
    "Howl",
    "Dragon Claw",
    "Frenzy Plant",
    "Bulk Up",
    "Bounce",
    "Mud Shot",
    "Poison Tail",
    "Covet",
    "Volt Tackle",
    "Magical Leaf",
    "Water Sport",
    "Calm Mind",
    "Leaf Blade",
    "Dragon Dance",
    "Rock Blast",
    "Shock Wave",
    "Water Pulse",
    "Doom Desire",
    "Psycho Boost",
};

char* editor_species_names[] = {
    "??????????",
    "Bulbasaur",
    "Ivysaur",
    "Venusaur",
    "Charmander",
    "Charmeleon",
    "Charizard",
    "Squirtle",
    "Wartortle",
    "Blastoise",
    "Caterpie",
    "Metapod",
    "Butterfree",
    "Weedle",
    "Kakuna",
    "Beedrill",
    "Pidgey",
    "Pidgeotto",
    "Pidgeot",
    "Rattata",
    "Raticate",
    "Spearow",
    "Fearow",
    "Ekans",
    "Arbok",
    "Pikachu",
    "Raichu",
    "Sandshrew",
    "Sandslash",
    "Nidoran♀",
    "Nidorina",
    "Nidoqueen",
    "Nidoran♂",
    "Nidorino",
    "Nidoking",
    "Clefairy",
    "Clefable",
    "Vulpix",
    "Ninetales",
    "Jigglypuff",
    "Wigglytuff",
    "Zubat",
    "Golbat",
    "Oddish",
    "Gloom",
    "Vileplume",
    "Paras",
    "Parasect",
    "Venonat",
    "Venomoth",
    "Diglett",
    "Dugtrio",
    "Meowth",
    "Persian",
    "Psyduck",
    "Golduck",
    "Mankey",
    "Primeape",
    "Growlithe",
    "Arcanine",
    "Poliwag",
    "Poliwhirl",
    "Poliwrath",
    "Abra",
    "Kadabra",
    "Alakazam",
    "Machop",
    "Machoke",
    "Machamp",
    "Bellsprout",
    "Weepinbell",
    "Victreebel",
    "Tentacool",
    "Tentacruel",
    "Geodude",
    "Graveler",
    "Golem",
    "Ponyta",
    "Rapidash",
    "Slowpoke",
    "Slowbro",
    "Magnemite",
    "Magneton",
    "Farfetch'd",
    "Doduo",
    "Dodrio",
    "Seel",
    "Dewgong",
    "Grimer",
    "Muk",
    "Shellder",
    "Cloyster",
    "Gastly",
    "Haunter",
    "Gengar",
    "Onix",
    "Drowzee",
    "Hypno",
    "Krabby",
    "Kingler",
    "Voltorb",
    "Electrode",
    "Exeggcute",
    "Exeggutor",
    "Cubone",
    "Marowak",
    "Hitmonlee",
    "Hitmonchan",
    "Lickitung",
    "Koffing",
    "Weezing",
    "Rhyhorn",
    "Rhydon",
    "Chansey",
    "Tangela",
    "Kangaskhan",
    "Horsea",
    "Seadra",
    "Goldeen",
    "Seaking",
    "Staryu",
    "Starmie",
    "Mr. Mime",
    "Scyther",
    "Jynx",
    "Electabuzz",
    "Magmar",
    "Pinsir",
    "Tauros",
    "Magikarp",
    "Gyarados",
    "Lapras",
    "Ditto",
    "Eevee",
    "Vaporeon",
    "Jolteon",
    "Flareon",
    "Porygon",
    "Omanyte",
    "Omastar",
    "Kabuto",
    "Kabutops",
    "Aerodactyl",
    "Snorlax",
    "Articuno",
    "Zapdos",
    "Moltres",
    "Dratini",
    "Dragonair",
    "Dragonite",
    "Mewtwo",
    "Mew",
    "Chikorita",
    "Bayleef",
    "Meganium",
    "Cyndaquil",
    "Quilava",
    "Typhlosion",
    "Totodile",
    "Croconaw",
    "Feraligatr",
    "Sentret",
    "Furret",
    "Hoothoot",
    "Noctowl",
    "Ledyba",
    "Ledian",
    "Spinarak",
    "Ariados",
    "Crobat",
    "Chinchou",
    "Lanturn",
    "Pichu",
    "Cleffa",
    "Igglybuff",
    "Togepi",
    "Togetic",
    "Natu",
    "Xatu",
    "Mareep",
    "Flaaffy",
    "Ampharos",
    "Bellossom",
    "Marill",
    "Azumarill",
    "Sudowoodo",
    "Politoed",
    "Hoppip",
    "Skiploom",
    "Jumpluff",
    "Aipom",
    "Sunkern",
    "Sunflora",
    "Yanma",
    "Wooper",
    "Quagsire",
    "Espeon",
    "Umbreon",
    "Murkrow",
    "Slowking",
    "Misdreavus",
    "Unown",
    "Wobbuffet",
    "Girafarig",
    "Pineco",
    "Forretress",
    "Dunsparce",
    "Gligar",
    "Steelix",
    "Snubbull",
    "Granbull",
    "Qwilfish",
    "Scizor",
    "Shuckle",
    "Heracross",
    "Sneasel",
    "Teddiursa",
    "Ursaring",
    "Slugma",
    "Magcargo",
    "Swinub",
    "Piloswine",
    "Corsola",
    "Remoraid",
    "Octillery",
    "Delibird",
    "Mantine",
    "Skarmory",
    "Houndour",
    "Houndoom",
    "Kingdra",
    "Phanpy",
    "Donphan",
    "Porygon2",
    "Stantler",
    "Smeargle",
    "Tyrogue",
    "Hitmontop",
    "Smoochum",
    "Elekid",
    "Magby",
    "Miltank",
    "Blissey",
    "Raikou",
    "Entei",
    "Suicune",
    "Larvitar",
    "Pupitar",
    "Tyranitar",
    "Lugia",
    "Ho-Oh",
    "Celebi",
    "? (252)",
    "? (253)",
    "? (254)",
    "? (255)",
    "? (256)",
    "? (257)",
    "? (258)",
    "? (259)",
    "? (260)",
    "? (261)",
    "? (262)",
    "? (263)",
    "? (264)",
    "? (265)",
    "? (266)",
    "? (267)",
    "? (268)",
    "? (269)",
    "? (270)",
    "? (271)",
    "? (272)",
    "? (273)",
    "? (274)",
    "? (275)",
    "? (276)",
    "Treecko",
    "Grovyle",
    "Sceptile",
    "Torchic",
    "Combusken",
    "Blaziken",
    "Mudkip",
    "Marshtomp",
    "Swampert",
    "Poochyena",
    "Mightyena",
    "Zigzagoon",
    "Linoone",
    "Wurmple",
    "Silcoon",
    "Beautifly",
    "Cascoon",
    "Dustox",
    "Lotad",
    "Lombre",
    "Ludicolo",
    "Seedot",
    "Nuzleaf",
    "Shiftry",
    "Nincada",
    "Ninjask",
    "Shedinja",
    "Taillow",
    "Swellow",
    "Shroomish",
    "Breloom",
    "Spinda",
    "Wingull",
    "Pelipper",
    "Surskit",
    "Masquerain",
    "Wailmer",
    "Wailord",
    "Skitty",
    "Delcatty",
    "Kecleon",
    "Baltoy",
    "Claydol",
    "Nosepass",
    "Torkoal",
    "Sableye",
    "Barboach",
    "Whiscash",
    "Luvdisc",
    "Corphish",
    "Crawdaunt",
    "Feebas",
    "Milotic",
    "Carvanha",
    "Sharpedo",
    "Trapinch",
    "Vibrava",
    "Flygon",
    "Makuhita",
    "Hariyama",
    "Electrike",
    "Manectric",
    "Numel",
    "Camerupt",
    "Spheal",
    "Sealeo",
    "Walrein",
    "Cacnea",
    "Cacturne",
    "Snorunt",
    "Glalie",
    "Lunatone",
    "Solrock",
    "Azurill",
    "Spoink",
    "Grumpig",
    "Plusle",
    "Minun",
    "Mawile",
    "Meditite",
    "Medicham",
    "Swablu",
    "Altaria",
    "Wynaut",
    "Duskull",
    "Dusclops",
    "Roselia",
    "Slakoth",
    "Vigoroth",
    "Slaking",
    "Gulpin",
    "Swalot",
    "Tropius",
    "Whismur",
    "Loudred",
    "Exploud",
    "Clamperl",
    "Huntail",
    "Gorebyss",
    "Absol",
    "Shuppet",
    "Banette",
    "Seviper",
    "Zangoose",
    "Relicanth",
    "Aron",
    "Lairon",
    "Aggron",
    "Castform",
    "Volbeat",
    "Illumise",
    "Lileep",
    "Cradily",
    "Anorith",
    "Armaldo",
    "Ralts",
    "Kirlia",
    "Gardevoir",
    "Bagon",
    "Shelgon",
    "Salamence",
    "Beldum",
    "Metang",
    "Metagross",
    "Regirock",
    "Regice",
    "Registeel",
    "Kyogre",
    "Groudon",
    "Rayquaza",
    "Latias",
    "Latios",
    "Jirachi",
    "Deoxys",
    "Chimecho",
    "Pokémon Egg",
    "Unown B",
    "Unown C",
    "Unown D",
    "Unown E",
    "Unown F",
    "Unown G",
    "Unown H",
    "Unown I",
    "Unown J",
    "Unown K",
    "Unown L",
    "Unown M",
    "Unown N",
    "Unown O",
    "Unown P",
    "Unown Q",
    "Unown R",
    "Unown S",
    "Unown T",
    "Unown U",
    "Unown V",
    "Unown W",
    "Unown X",
    "Unown Y",
    "Unown Z",
    "Unown !",
    "Unown ?",
};

char* editor_item_names[] = {
    "????????",
    "Master Ball",
    "Ultra Ball",
    "Great Ball",
    "Poké Ball",
    "Safari Ball",
    "Net Ball",
    "Dive Ball",
    "Nest Ball",
    "Repeat Ball",
    "Timer Ball",
    "Luxury Ball",
    "Premier Ball",
    "Potion",
    "Antidote",
    "Burn Heal",
    "Ice Heal",
    "Awakening",
    "Parlyz Heal",
    "Full Restore",
    "Max Potion",
    "Hyper Potion",
    "Super Potion",
    "Full Heal",
    "Revive",
    "Max Revive",
    "Fresh Water",
    "Soda Pop",
    "Lemonade",
    "Moomoo Milk",
    "EnergyPowder",
    "Energy Root",
    "Heal Powder",
    "Revival Herb",
    "Ether",
    "Max Ether",
    "Elixir",
    "Max Elixir",
    "Lava Cookie",
    "Blue Flute",
    "Yellow Flute",
    "Red Flute",
    "Black Flute",
    "White Flute",
    "Berry Juice",
    "Sacred Ash",
    "Shoal Salt",
    "Shoal Shell",
    "Red Shard",
    "Blue Shard",
    "Yellow Shard",
    "Green Shard",
    "Unknown 0034",
    "Unknown 0035",
    "Unknown 0036",
    "Unknown 0037",
    "Unknown 0038",
    "Unknown 0039",
    "Unknown 003A",
    "Unknown 003B",
    "Unknown 003C",
    "Unknown 003D",
    "Unknown 003E",
    "HP Up",
    "Protein",
    "Iron",
    "Carbos",
    "Calcium",
    "Rare Candy",
    "PP Up",
    "Zinc",
    "PP Max",
    "Unknown 0048",
    "Guard Spec.",
    "Dire Hit",
    "X Attack",
    "X Defend",
    "X Speed",
    "X Accuracy",
    "X Special",
    "Poké Doll",
    "Fluffy Tail",
    "Unknown 0052",
    "Super Repel",
    "Max Repel",
    "Escape Rope",
    "Repel",
    "Unknown 0057",
    "Unknown 0058",
    "Unknown 0059",
    "Unknown 005A",
    "Unknown 005B",
    "Unknown 005C",
    "Sun Stone",
    "Moon Stone",
    "Fire Stone",
    "Thunder Stone",
    "Water Stone",
    "Leaf Stone",
    "Unknown 0063",
    "Unknown 0064",
    "Unknown 0065",
    "Unknown 0066",
    "TinyMushroom",
    "Big Mushroom",
    "Unknown 0069",
    "Pearl",
    "Big Pearl",
    "Stardust",
    "Star Piece",
    "Nugget",
    "Heart Scale",
    "Unknown 0070",
    "Unknown 0071",
    "Unknown 0072",
    "Unknown 0073",
    "Unknown 0074",
    "Unknown 0075",
    "Unknown 0076",
    "Unknown 0077",
    "Unknown 0078",
    "Orange Mail",
    "Harbor Mail",
    "Glitter Mail",
    "Mech Mail",
    "Wood Mail",
    "Wave Mail",
    "Bead Mail",
    "Shadow Mail",
    "Tropic Mail",
    "Dream Mail",
    "Fab Mail",
    "Retro Mail",
    "Cheri Berry",
    "Chesto Berry",
    "Pecha Berry",
    "Rawst Berry",
    "Aspear Berry",
    "Leppa Berry",
    "Oran Berry",
    "Persim Berry",
    "Lum Berry",
    "Sitrus Berry",
    "Figy Berry",
    "Wiki Berry",
    "Mago Berry",
    "Aguav Berry",
    "Iapapa Berry",
    "Razz Berry",
    "Bluk Berry",
    "Nanab Berry",
    "Wepear Berry",
    "Pinap Berry",
    "Pomeg Berry",
    "Kelpsy Berry",
    "Qualot Berry",
    "Hondew Berry",
    "Grepa Berry",
    "Tamato Berry",
    "Cornn Berry",
    "Magost Berry",
    "Rabuta Berry",
    "Nomel Berry",
    "Spelon Berry",
    "Pamtre Berry",
    "Watmel Berry",
    "Durin Berry",
    "Belue Berry",
    "Liechi Berry",
    "Ganlon Berry",
    "Salac Berry",
    "Petaya Berry",
    "Apicot Berry",
    "Lansat Berry",
    "Starf Berry",
    "Enigma Berry",
    "Unknown 00B0",
    "Unknown 00B1",
    "Unknown 00B2",
    "BrightPowder",
    "White Herb",
    "Macho Brace",
    "Exp. Share",
    "Quick Claw",
    "Soothe Bell",
    "Mental Herb",
    "Choice Band",
    "King's Rock",
    "SilverPowder",
    "Amulet Coin",
    "Cleanse Tag",
    "Soul Dew",
    "DeepSeaTooth",
    "DeepSeaScale",
    "Smoke Ball",
    "Everstone",
    "Focus Band",
    "Lucky Egg",
    "Scope Lens",
    "Metal Coat",
    "Leftovers",
    "Dragon Scale",
    "Light Ball",
    "Soft Sand",
    "Hard Stone",
    "Miracle Seed",
    "BlackGlasses",
    "Black Belt",
    "Magnet",
    "Mystic Water",
    "Sharp Beak",
    "Poison Barb",
    "NeverMeltIce",
    "Spell Tag",
    "TwistedSpoon",
    "Charcoal",
    "Dragon Fang",
    "Silk Scarf",
    "Up-Grade",
    "Shell Bell",
    "Sea Incense",
    "Lax Incense",
    "Lucky Punch",
    "Metal Powder",
    "Thick Club",
    "Stick",
    "Unknown 00E2",
    "Unknown 00E3",
    "Unknown 00E4",
    "Unknown 00E5",
    "Unknown 00E6",
    "Unknown 00E7",
    "Unknown 00E8",
    "Unknown 00E9",
    "Unknown 00EA",
    "Unknown 00EB",
    "Unknown 00EC",
    "Unknown 00ED",
    "Unknown 00EE",
    "Unknown 00EF",
    "Unknown 00F0",
    "Unknown 00F1",
    "Unknown 00F2",
    "Unknown 00F3",
    "Unknown 00F4",
    "Unknown 00F5",
    "Unknown 00F6",
    "Unknown 00F7",
    "Unknown 00F8",
    "Unknown 00F9",
    "Unknown 00FA",
    "Unknown 00FB",
    "Unknown 00FC",
    "Unknown 00FD",
    "Red Scarf",
    "Blue Scarf",
    "Pink Scarf",
    "Green Scarf",
    "Yellow Scarf",
    "Mach Bike",
    "Coin Case",
    "Itemfinder",
    "Old Rod",
    "Good Rod",
    "Super Rod",
    "S.S. Ticket",
    "Contest Pass",
    "Unknown 010B",
    "Wailmer Pail",
    "Devon Goods",
    "Soot Sack",
    "Basement Key",
    "Acro Bike",
    "Pokéblock Case",
    "Letter",
    "Eon Ticket",
    "Red Orb",
    "Blue Orb",
    "Scanner",
    "Go-Goggles",
    "Meteorite",
    "Rm. 1 Key",
    "Rm. 2 Key",
    "Rm. 4 Key",
    "Rm. 6 Key",
    "Storage Key",
    "Root Fossil",
    "Claw Fossil",
    "Devon Scope",
    "TM01",
    "TM02",
    "TM03",
    "TM04",
    "TM05",
    "TM06",
    "TM07",
    "TM08",
    "TM09",
    "TM10",
    "TM11",
    "TM12",
    "TM13",
    "TM14",
    "TM15",
    "TM16",
    "TM17",
    "TM18",
    "TM19",
    "TM20",
    "TM21",
    "TM22",
    "TM23",
    "TM24",
    "TM25",
    "TM26",
    "TM27",
    "TM28",
    "TM29",
    "TM30",
    "TM31",
    "TM32",
    "TM33",
    "TM34",
    "TM35",
    "TM36",
    "TM37",
    "TM38",
    "TM39",
    "TM40",
    "TM41",
    "TM42",
    "TM43",
    "TM44",
    "TM45",
    "TM46",
    "TM47",
    "TM48",
    "TM49",
    "TM50",
    "HM01",
    "HM02",
    "HM03",
    "HM04",
    "HM05",
    "HM06",
    "HM07",
    "HM08",
    "Unknown 15B",
    "Unknown 15C",
    "Oak's Parcel",
    "Poké Flute",
    "Secret Key",
    "Bike Voucher",
    "Gold Teeth",
    "Old Amber",
    "Card Key",
    "Lift Key",
    "Helix Fossil",
    "Dome Fossil",
    "Silph Scope",
    "Bicycle",
    "Town Map",
    "Vs. Seeker",
    "Fame Checker",
    "TM Case",
    "Berry Pouch",
    "Teachy TV",
    "Tri-Pass",
    "Rainbow Pass",
    "Tea",
    "MysticTicket",
    "AuroraTicket",
    "Powder Jar",
    "Ruby",
    "Sapphire",
    "Magma Emblem",
    "Old Sea Map",
};

char* editor_nature_names[] = {
    "Hardy",
    "Lonely",
    "Brave",
    "Adamant",
    "Naughty",
    "Bold",
    "Docile",
    "Relaxed",
    "Impish",
    "Lax",
    "Timid",
    "Hasty",
    "Serious",
    "Jolly",
    "Naive",
    "Modest",
    "Mild",
    "Quiet",
    "Bashful",
    "Rash",
    "Calm",
    "Gentle",
    "Sassy",
    "Careful",
    "Quirky",
};
