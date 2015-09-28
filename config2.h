/* TODO: access correct bindings according to mode (with macro?)  */

#define ONLY(ch) { ch }

static const Key command_keys[] = {
/*  key        function    argument */
  { ONLY('h'), k_move,  { .pos = m_left_one  }},
  { ONLY('l'), k_move,  { .pos = m_right_one }},
  { ONLY('j'), k_move,  { .pos = m_down_one  }},
  { ONLY('k'), k_move,  { .pos = m_up_one    }}
};

Keyset bindings[] = {
  { "command", command_keys }
};