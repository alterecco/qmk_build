SRC += alterecco.c

ifeq ($(strip $(CUSTOM_ONESHOT_ENABLE)), yes)
	SRC += ./features/oneshot.c
	OPT_DEFS += -DCUSTOM_ONESHOT_ENABLE
endif

ifeq ($(strip $(CUSTOM_MODTAP_ENABLE)), yes)
	SRC += ./features/mod_hold_n_tap.c
	OPT_DEFS += -DCUSTOM_MODTAP_ENABLE
endif

ifeq ($(strip $(CUSTOM_REPEAT_KEY_ENABLE)), yes)
	SRC += ./features/repeat_last_key.c
	OPT_DEFS += -DCUSTOM_REPEAT_KEY_ENABLE
endif

ifeq ($(strip $(CUSTOM_NUM_WORD_ENABLE)), yes)
	SRC += ./features/num_word.c
	OPT_DEFS += -DCUSTOM_NUM_WORD_ENABLE
endif

ifeq ($(strip $(CUSTOM_NAV_WORD_ENABLE)), yes)
	SRC += ./features/nav_word.c
	OPT_DEFS += -DCUSTOM_NAV_WORD_ENABLE
endif

ifeq ($(strip $(CUSTOM_SYS_WORD_ENABLE)), yes)
	SRC += ./features/sys_word.c
	OPT_DEFS += -DCUSTOM_SYS_WORD_ENABLE
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += combos.c
endif

ifeq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
	SRC += overrides.c
endif
