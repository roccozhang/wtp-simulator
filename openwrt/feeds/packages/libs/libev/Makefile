#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libev
PKG_VERSION:=4.04
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://dist.schmorp.de/libev/
PKG_MD5SUM:=c1130d0a4782681ba5277df1bc3fb335

PKG_FIXUP:=libtool
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libev
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Another of event notification library
  URL:=http://software.schmorp.de/pkg/libev.html
endef

define Package/libev/description
        A full-featured and high-performance (see benchmark) event loop that is loosely modelled after libevent, but without its limitations and bugs. It is used, among others, in the GNU Virtual Private Ethernet and rxvt-unicode packages, and in the Deliantra MORPG Server and Client.
endef

TARGET_CFLAGS += $(FPIC)

CONFIGURE_ARGS += \
	--enable-shared \
	--enable-static \

MAKE_FLAGS += \
	CFLAGS="$(TARGET_CFLAGS)" \

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libev.{la,a,so} $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libev.so.4* $(1)/usr/lib/
endef

define Package/libev/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libev.so.4* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libev))
