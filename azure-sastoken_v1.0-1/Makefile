# by Qige <qigezhao@gmail.com>
# 2017.07.25

include $(TOPDIR)/rules.mk

APP_NAME:=azure-sastoken
PKG_NAME:=azure-sastoken
PKG_VERSION:=1.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=SASToken generator for Microsoft Azure IoTHub
  MAINTAINER:=Qige Zhao <qigezhao@gmail.com>
  DEPENDS:=+libopenssl
endef

define Package/$(PKG_NAME)/description
  SASToken generator for Microsoft Azure IoTHub
endef


define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Build/Configure
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/sbin

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(APP_NAME) $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))


