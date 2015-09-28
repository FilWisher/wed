#define ONLY(ch)   { ch }

static Key command_keys[] = {
/*  key         function    argument */
  { ONLY('h'),  k_move,         { .pos = m_left_one     }},
  { ONLY('l'),  k_move,         { .pos = m_right_one    }},
  { ONLY('j'),  k_move,         { .pos = m_down_one     }},
  { ONLY('k'),  k_move,         { .pos = m_up_one       }},
  { ONLY('3'),  k_change_mode,  { .val = EDIT_MODE      }},
  { ONLY('0'),  k_save,         { .val = "save"         }},
  { ONLY('\0'), k_move,         { .pos = m_noop         }}
};

static Key edit_keys[] = {
/*  key         function           argument */
  { ONLY('a'),  k_insert,       { .val = "*ch*"         }},
  { ONLY('b'),  k_insert,       { .val = "b"            }},
  { ONLY('c'),  k_insert,       { .val = "c"            }},
  { ONLY('d'),  k_insert,       { .val = "d"            }},
  { ONLY('e'),  k_insert,       { .val = "e"            }},
  { ONLY('f'),  k_insert,       { .val = "f"            }},
  { ONLY('g'),  k_insert,       { .val = "g"            }},
  { ONLY('h'),  k_insert,       { .val = "h"            }},
  { ONLY('i'),  k_insert,       { .val = "i"            }},
  { ONLY('j'),  k_insert,       { .val = "j"            }},
  { ONLY('k'),  k_insert,       { .val = "k"            }},
  { ONLY('l'),  k_insert,       { .val = "l"            }},
  { ONLY('m'),  k_insert,       { .val = "m"            }},
  { ONLY('n'),  k_insert,       { .val = "n"            }},
  { ONLY('o'),  k_insert,       { .val = "o"            }},
  { ONLY('p'),  k_insert,       { .val = "p"            }},
  { ONLY('q'),  k_insert,       { .val = "q"            }},
  { ONLY('r'),  k_insert,       { .val = "r"            }},
  { ONLY('s'),  k_insert,       { .val = "s"            }},
  { ONLY('t'),  k_insert,       { .val = "t"            }},
  { ONLY('u'),  k_insert,       { .val = "u"            }},
  { ONLY('v'),  k_insert,       { .val = "v"            }},
  { ONLY('w'),  k_insert,       { .val = "w"            }},
  { ONLY('x'),  k_insert,       { .val = "x"            }},
  { ONLY('y'),  k_insert,       { .val = "y"            }},
  { ONLY('z'),  k_insert,       { .val = "z"            }},
  { ONLY('A'),  k_insert,       { .val = "A"            }},
  { ONLY('B'),  k_insert,       { .val = "B"            }},
  { ONLY('C'),  k_insert,       { .val = "C"            }},
  { ONLY('D'),  k_insert,       { .val = "D"            }},
  { ONLY('E'),  k_insert,       { .val = "E"            }},
  { ONLY('F'),  k_insert,       { .val = "F"            }},
  { ONLY('G'),  k_insert,       { .val = "G"            }},
  { ONLY('H'),  k_insert,       { .val = "H"            }},
  { ONLY('I'),  k_insert,       { .val = "I"            }},
  { ONLY('J'),  k_insert,       { .val = "J"            }},
  { ONLY('K'),  k_insert,       { .val = "K"            }},
  { ONLY('L'),  k_insert,       { .val = "L"            }},
  { ONLY('M'),  k_insert,       { .val = "M"            }},
  { ONLY('N'),  k_insert,       { .val = "N"            }},
  { ONLY('O'),  k_insert,       { .val = "O"            }},
  { ONLY('P'),  k_insert,       { .val = "P"            }},
  { ONLY('Q'),  k_insert,       { .val = "Q"            }},
  { ONLY('R'),  k_insert,       { .val = "R"            }},
  { ONLY('S'),  k_insert,       { .val = "S"            }},
  { ONLY('T'),  k_insert,       { .val = "T"            }},
  { ONLY('U'),  k_insert,       { .val = "U"            }},
  { ONLY('V'),  k_insert,       { .val = "V"            }},
  { ONLY('W'),  k_insert,       { .val = "W"            }},
  { ONLY('X'),  k_insert,       { .val = "X"            }},
  { ONLY('Y'),  k_insert,       { .val = "Y"            }},
  { ONLY('Z'),  k_insert,       { .val = "Z"            }},
  { ONLY(' '),  k_insert,       { .val = " "            }},
  { ONLY('2'),  k_change_mode,  { .val = COMMAND_MODE   }},
  { ONLY('\0'), k_move,         { .pos = m_noop         }}
};

Keyset bindings[] = {
  { COMMAND_MODE, command_keys },
  { EDIT_MODE,    edit_keys }
};
