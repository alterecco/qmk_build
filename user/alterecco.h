#include "./keycodes.h"

#ifdef CUSTOM_MODTAP_ENABLE
# include "features/mod_hold_n_tap.h"
#endif

#ifdef CUSTOM_REPEAT_KEY_ENABLE
# include "features/repeat_last_key.h"
#endif

#ifdef CUSTOM_ONESHOT_ENABLE
# include "features/oneshot.h"
#endif

#ifdef CUSTOM_NUM_WORD_ENABLE
#include "features/num_word.h"
#endif

#ifdef CUSTOM_NAV_WORD_ENABLE
#include "features/nav_word.h"
#endif

#ifdef CUSTOM_SYS_WORD_ENABLE
#include "features/sys_word.h"
#endif
