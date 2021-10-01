## https://github.com/tzarc/qmk_build/blob/master/Makefile

export ROOTDIR := $(shell pwd)

# Add qmk wrapper to path
#export PATH := $(ROOTDIR)/bin:$(PATH)

BOARD_DEFS := \
	# board_name!board_source!board_target!board_keymap![board_keyboard]
	ferris/0_2!keyboards/ferris!ferris/keymaps/alterecco!alterecco

EXTRA_LINK_DEFS := \
	user!users/alterecco

all: bin

boards: ferris/0_2

remove_artifacts:
	rm "$(ROOTDIR)"/*.bin "$(ROOTDIR)"/*.hex "$(ROOTDIR)"/*.uf2 "$(ROOTDIR)"/*.dump "$(ROOTDIR)"/.clang-format "$(ROOTDIR)"/compile_commands.json "$(ROOTDIR)"/qmk_firmware/compile_commands.json >/dev/null 2>&1 || true

clean: remove_artifacts
	+$(MAKE) -C "$(ROOTDIR)/qmk_firmware" clean || true

distclean: remove_artifacts
	+$(MAKE) $(MAKEFLAGS) -C "$(ROOTDIR)/qmk_firmware" distclean || true

links: extra-links

git-submodule:
	+$(MAKE) -C "$(ROOTDIR)/qmk_firmware" git-submodule

define handle_link_entry
link_source_$1 := $$(word 1,$$(subst !, ,$1))
link_target_$1 := $$(word 2,$$(subst !, ,$1))
link_files_$1 := $$(shell find $$(ROOTDIR)/$$(link_source_$1) -type f \( -name '*.h' -or -name '*.c' \) -and -not -name '*conf.h' -and -not -name 'board.c' -and -not -name 'board.h' | sort)
link_files_all_$1 := $$(shell find $$(ROOTDIR)/$$(link_source_$1) -type f | sort)

extra-links: link_$$(link_source_$1)
link_$$(link_source_$1):
	@if [ ! -L "$(ROOTDIR)/qmk_firmware/$$(link_target_$1)" ] ; then \
		echo "\e[38;5;14mSymlinking: $$(link_source_$1) -> $$(link_target_$1)\e[0m" ; \
		ln -sf $(ROOTDIR)/$$(link_source_$1) $(ROOTDIR)/qmk_firmware/$$(link_target_$1) ; \
	fi

clean: unlink_$$(link_source_$1)
distclean: unlink_$$(link_source_$1)
unlinks: unlink_$$(link_source_$1)
unlink_$$(link_source_$1):
	@if [ -L "$(ROOTDIR)/qmk_firmware/$$(link_target_$1)" ] ; then \
		echo "\e[38;5;14mRemoving symlink: $$(link_source_$1) -> $$(link_target_$1)\e[0m" ; \
		rm $(ROOTDIR)/qmk_firmware/$$(link_target_$1) || true; \
	fi
endef

$(foreach link_entry,$(EXTRA_LINK_DEFS),$(eval $(call handle_link_entry,$(link_entry))))

define handle_board_entry
board_name_$1 := $$(word 1,$$(subst !, ,$1))
board_source_$1 := $$(word 2,$$(subst !, ,$1))
board_target_$1 := $$(word 3,$$(subst !, ,$1))
board_keymap_$1 := $$(word 4,$$(subst !, ,$1))
board_keyboard_$1 := $$(word 5,$$(subst !, ,$1))

ifeq ($$(board_keyboard_$1),)
board_keyboard_$1 := $$(board_target_$1)
endif

board_qmk_$1 := $$(shell echo $$(board_keyboard_$1) | sed -e 's@/keymaps/.*@@g')
board_file_$1 := $$(shell echo $$(board_qmk_$1) | sed -e 's@/@_@g' -e 's@:@_@g')
board_files_$1 := $$(shell find $$(ROOTDIR)/$$(board_source_$1) -type f \( -name '*.h' -or -name '*.c' \) -and -not -name '*conf.h' -and -not -name 'board.c' -and -not -name 'board.h' | sort)
board_files_all_$1 := $$(shell find $$(ROOTDIR)/$$(board_source_$1) -type f | sort)

bin_$$(board_name_$1): board_link_$$(board_name_$1)
	@echo "\e[38;5;14mBuilding: $$(board_qmk_$1):$$(board_keymap_$1)\e[0m"
	+cd "$(ROOTDIR)/qmk_firmware" \
		&& $$(MAKE) distclean \
		&& $$(MAKE) --no-print-directory -r -R -C "$(ROOTDIR)/qmk_firmware" -f "$(ROOTDIR)/qmk_firmware/build_keyboard.mk" $$(MAKEFLAGS) KEYBOARD="$$(board_qmk_$1)" KEYMAP="$$(board_keymap_$1)" REQUIRE_PLATFORM_KEY= COLOR=true SILENT=false CREATE_MAP=yes EXTRAFLAGS=-fstack-usage EXTRALDFLAGS=-Wl,--print-memory-usage
	@cp $$(ROOTDIR)/qmk_firmware/$$(board_file_$1)* $$(ROOTDIR)/qmk_firmware/compile_commands.json $$(ROOTDIR) \
		&& sed -i 's@/home/nickb/qmk_build/qmk_firmware@W:\\\\qmk_build\\\\qmk_firmware@g' $$(ROOTDIR)/compile_commands.json \
		|| true

flash_$$(board_name_$1): bin_$$(board_name_$1)
	@echo "\e[38;5;14mFlashing: $$(board_qmk_$1):$$(board_keymap_$1)\e[0m"
	cd "$(ROOTDIR)/qmk_firmware" \
		&& qmk flash -kb $$(board_qmk_$1) -km $$(board_keymap_$1)

$$(board_name_$1): bin_$$(board_name_$1)
bin: bin_$$(board_name_$1)

board_link_$$(board_name_$1): extra-links
	@if [ ! -L "$$(ROOTDIR)/qmk_firmware/keyboards/$$(board_target_$1)" ] ; then \
		echo "\e[38;5;14mSymlinking: $$(board_source_$1) -> $$(board_target_$1)\e[0m" ; \
		if [ ! -d "$$(shell dirname "$$(ROOTDIR)/qmk_firmware/keyboards/$$(board_target_$1)")" ] ; then \
			mkdir -p "$$(shell dirname "$$(ROOTDIR)/qmk_firmware/keyboards/$$(board_target_$1)")" ; \
		fi ; \
		ln -sf "$$(ROOTDIR)/$$(board_source_$1)" "$$(ROOTDIR)/qmk_firmware/keyboards/$$(board_target_$1)" ; \
	fi
	@touch $$(ROOTDIR)/qmk_firmware/keyboards/$$(board_target_$1)

board_unlink_$$(board_name_$1):
	@if [ -L "$$(ROOTDIR)/qmk_firmware/keyboards/$$(board_target_$1)" ] ; then \
		echo "\e[38;5;14mRemoving symlink: $$(board_target_$1)\e[0m" ; \
		rm "$$(ROOTDIR)/qmk_firmware/keyboards/$$(board_target_$1)" || true; \
	fi

links: board_link_$$(board_name_$1)
unlinks: board_unlink_$$(board_name_$1)
clean: board_unlink_$$(board_name_$1)
distclean: board_unlink_$$(board_name_$1)
endef

$(foreach board_entry,$(BOARD_DEFS),$(eval $(call handle_board_entry,$(board_entry))))
