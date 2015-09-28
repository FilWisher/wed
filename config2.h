#define ONLY(ch) { ch }

static Key command_keys[] = {
/*  key         function    argument */
  { ONLY('h'),  k_move,  { .pos = m_left_one  }},
  { ONLY('l'),  k_move,  { .pos = m_right_one }},
  { ONLY('j'),  k_move,  { .pos = m_down_one  }},
  { ONLY('k'),  k_move,  { .pos = m_up_one    }},
  { ONLY('\0'), k_move,  { .pos = m_noop      }}
};

Keyset bindings[] = {
  { "command", command_keys }
};
