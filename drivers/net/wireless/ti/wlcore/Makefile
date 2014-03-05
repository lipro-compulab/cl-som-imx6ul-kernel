wlcore-objs		= main.o cmd.o io.o event.o tx.o rx.o ps.o acx.o \
			  boot.o init.o debugfs.o scan.o sysfs.o

# use special params for the compat case
ifneq ($(KLIB_BUILD),)
ifneq ($(GIT_TREE),)
GIT_PATH := $(GIT_TREE)/
GIT_CHDIR_CMD := cd $(GIT_TREE) &&
endif
endif

ifeq ($(wildcard $(GIT_PATH).git/HEAD),)
# use release_version.h if .git not exists
WLCORE_VERSION_DEPS := $(obj)/release_version.h

define filechk_version.h
	(cat $(obj)/release_version.h)
endef

else
# use git describe to determine version
WLCORE_VERSION_DEPS := $(GIT_PATH).git/HEAD $(GIT_PATH).git/index $(GIT_PATH).git/refs/tags

define filechk_version.h
	(echo 'static const char *wlcore_timestamp = __TIMESTAMP__;'; \
	echo 'static const char *wlcore_git_head = \
			"$(shell $(GIT_CHDIR_CMD) git describe --dirty)";')
endef

endif

$(obj)/version.h: $(WLCORE_VERSION_DEPS)
	@$(call filechk,version.h)

# seems like in some cases, for unknown reason,
# this dependency is not enforced implictly,
# so add it explicitly
$(obj)/main.c: $(src)/version.h

wlcore_spi-objs 	= spi.o
wlcore_sdio-objs	= sdio.o

wlcore-$(CONFIG_NL80211_TESTMODE)	+= testmode.o
obj-$(CONFIG_WLCORE)			+= wlcore.o
obj-$(CONFIG_WLCORE_SPI)		+= wlcore_spi.o
obj-$(CONFIG_WLCORE_SDIO)		+= wlcore_sdio.o

ccflags-y += -D__CHECK_ENDIAN__
