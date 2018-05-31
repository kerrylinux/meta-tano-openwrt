# Copyright (C) 2015 Khem Raj <raj.khem@gmail.com>
# Copyright (C) 2018 Daniel Dickinson <cshored@thecshore.com>
# Copyright (C) 2018 Anton Kikin <a.kikin@tano-systems.com>

# Released under the MIT license (see COPYING.MIT for the terms)

SUMMARY = "Extras Openwrt system requirements"
LICENSE = "MIT"

inherit packagegroup openwrt

PACKAGES = "\
           packagegroup-openwrt-full \
           packagegroup-openwrt-full-base \
           packagegroup-openwrt-full-network \
           "

RDEPENDS_${PN} = "\
                 packagegroup-openwrt-base \
                 packagegroup-openwrt-full-network \
                 "

RDEPENDS_${PN}-network = "\
                         relayd \
                         tcpdump \
                         umbim \
                         umdnsd \
                         uqmi \
                         "
