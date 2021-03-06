# Copyright (C) 2015 Khem Raj <raj.khem@gmail.com>
# Copyright (C) 2018 Anton Kikin <a.kikin@tano-systems.com>
# Released under the MIT license (see COPYING.MIT for the terms)

PR = "tano0"
DESCRIPTION = "OpenWrt UBUS RPC server"
HOMEPAGE = "http://git.openwrt.org/?p=project/rpcd.git;a=summary"
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://main.c;beginline=1;endline=18;md5=da5faf55ed0618f0dde1c88e76a0fc74"
SECTION = "base"
DEPENDS = "json-c libubox ubus uci iwinfo"

SRC_URI = "\
	git://git.openwrt.org/project/rpcd.git;name=rpcd; \
	"

# 13.05.2018 22:13:05
SRCREV_rpcd = "820621952d537c49deba470c6f61c40df93f4ba8"

S = "${WORKDIR}/git"
OR = "${S}/openwrt/package/system/rpcd/files"

inherit cmake pkgconfig openwrt-services openwrt openwrt-base-files

OPENWRT_SERVICE_PACKAGES = "${PN}"
OPENWRT_SERVICE_SCRIPTS_${PN} = "${PN}"
OPENWRT_SERVICE_STATE_${PN}-${PN} = "enabled"

SRCREV_openwrt = "${OPENWRT_SRCREV}"

do_install_append() {
    install -d ${D}${includedir}/rpcd
    install -m 0644 ${S}/include/rpcd/* ${D}${includedir}/rpcd/
    install -Dm 0644 ${OR}/rpcd.config ${D}${sysconfdir}/config/rpcd
    install -Dm 0755 ${OR}/rpcd.init ${D}${sysconfdir}/init.d/rpcd

    mkdir -p ${D}/sbin
    ln -s /usr/sbin/rpcd ${D}/sbin/rpcd
}

FILES_${PN}  += "${libdir}/*"

RDEPENDS_${PN} += "iwinfo"
