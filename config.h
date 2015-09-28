#define ONLY(ch) { ch }

static Key command_keys[] = {
/*  key         function    argument */
  { ONLY('h'),  k_move,         { .pos = m_left_one     }},
  { ONLY('l'),  k_move,         { .pos = m_right_one    }},
  { ONLY('j'),  k_move,         { .pos = m_down_one     }},
  { ONLY('k'),  k_move,         { .pos = m_up_one       }},
  { ONLY('2'),  k_change_mode,  { .val = COMMAND_MODE   }},
  { ONLY('3'),  k_change_mode,  { .val = EDIT_MODE      }},
  { ONLY('\0'), k_move,         { .pos = m_noop         }}
};

static Key edit_keys[] = {
/*  key         function           argument */
  { ONLY('2'),  k_change_mode,  { .val = COMMAND_MODE   }},
  { ONLY('3'),  k_change_mode,  { .val = EDIT_MODE      }},
  { ONLY('\0'), k_move,         { .pos = m_noop         }}
};

Keyset bindings[] = {
  { COMMAND_MODE, command_keys },
  { EDIT_MODE,    edit_keys }
};
