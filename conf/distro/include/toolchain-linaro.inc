# Original file from meta-arago-distro

# Select external binary prebuilt Linaro toolchain
TCMODE = "external-linaro"
TCLIBC = "external-linaro-toolchain"

ELT_TARGET_SYS = "arm-linux-gnueabihf"
ELT_TARGET_SYS_armv5 = "arm-linux-gnueabi"
ELT_TARGET_SYS_aarch64 = "aarch64-linux-gnu"
TARGET_VENDOR = ""

PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}gcc-intermediate = "external-linaro-toolchain"

# Set some vars to help locate the toolchain automatically from PATH
TOOLCHAIN_SYS := "${ELT_TARGET_SYS}"
TOOLCHAIN_PREFIX := "${TOOLCHAIN_SYS}-"

# Use specific libc headers instead of ones provided by toolchain
PREFERRED_PROVIDER_linux-libc-headers_forcevariable = "linux-libc-headers"
PREFERRED_PROVIDER_linux-libc-headers-dev_forcevariable = "linux-libc-headers"
PREFERRED_PROVIDER_virtual/linux-libc-headers_forcevariable = "linux-libc-headers"

PREFERRED_PROVIDER_gcc-cross-canadian-${TRANSLATED_TARGET_ARCH} ?= "external-linaro-sdk-toolchain"
PREFERRED_PROVIDER_binutils-cross-canadian-${TRANSLATED_TARGET_ARCH} ?= "external-linaro-sdk-toolchain"
#PREFERRED_PROVIDER_gdb-cross-canadian-${TRANSLATED_TARGET_ARCH} = "external-linaro-sdk-toolchain"

# Special case for gdb to be built as part of canadian-cross-sdk, instead of packaged from external toolchain
bindir_pn-gdb-cross-canadian-${TRANSLATED_TARGET_ARCH} = "${exec_prefix}/bin"
PREFERRED_PROVIDER_gdb-cross-canadian-${TRANSLATED_TARGET_ARCH} = "gdb-cross-canadian-${TRANSLATED_TARGET_ARCH}"

# Set up runtime preferences
PREFERRED_PROVIDER_libgcc = "external-linaro-toolchain"
PREFERRED_PROVIDER_gcc-runtime = "external-linaro-toolchain"

# Set Cross and SDK toolchain preferences
SDKGCCVERSION ?= "linaro-6.2%"
SDKBINUVERSION ?= "linaro-2.27%"
SDKGLIBCVERSION ?= "2.24%"
SDKLINUXLIBCVERSION ?= "4.9%"

PREFERRED_VERSION_gcc-crosssdk-${SDK_SYS} ?= "${SDKGCCVERSION}"
PREFERRED_VERSION_gcc-crosssdk-initial-${SDK_SYS} ?= "${SDKGCCVERSION}"
PREFERRED_VERSION_binutils-crosssdk-${SDK_SYS} ?= "${SDKBINUVERSION}"

PREFERRED_VERSION_nativesdk-gcc-runtime ?= "${SDKGCCVERSION}"
PREFERRED_VERSION_nativesdk-libgcc ?= "${SDKGCCVERSION}"
PREFERRED_VERSION_nativesdk-libgcc-initial ?= "${SDKGCCVERSION}"
PREFERRED_VERSION_nativesdk-linux-libc-headers ?= "${SDKLINUXLIBCVERSION}"
PREFERRED_VERSION_nativesdk-glibc ?= "${SDKGLIBCVERSION}"
PREFERRED_VERSION_nativesdk-glibc-initial ?= "${SDKGLIBCVERSION}"

# Set target toolchain preferences to match Cross/SDK by default
# Can be overwritten globally, if needed
GCCVERSION ?= "linaro-6.2%"
BINUVERSION ?= "linaro-2.27%"
GLIBCVERSION ?= "2.24%"
GLIBCINITVERSION ?= "2.24%"
LINUXLIBCVERSION ?= "4.9%"

PREFERRED_VERSION_gcc ?= "${GCCVERSION}"
PREFERRED_VERSION_binutils ?= "${BINUVERSION}"
PREFERRED_VERSION_linux-libc-headers ?= "${LINUXLIBCVERSION}"
PREFERRED_VERSION_glibc ?= "${GLIBCVERSION}"
PREFERRED_VERSION_glibc-locale ?= "${GLIBCVERSION}"
PREFERRED_VERSION_glibc-initial ?= "${GLIBCINITVERSION}"

# Licenses set for main components of the toolchain:
# (g)libc is always LGPL version 2 (or later)
# gcc has switched from GPL version 2 (or later) to version 3 (or later) after 4.2.1,
#    see this announcement - http://gcc.gnu.org/ml/gcc-announce/2007/msg00003.html
# libgcc and libstdc++ always had exceptions to GPL called Runtime Library Exception, but
#    it was based on GPL version 2 (or later), until new GPL version 3 (or later) exception
#    was introduced on 27 Jan 2009 - http://gcc.gnu.org/ml/gcc-announce/2009/msg00000.html
#    and http://www.gnu.org/licenses/gcc-exception.html, which was several days after
#    gcc 4.3.3 was released - http://gcc.gnu.org/releases.html
# gdb/gdbserver version 6.6 was the last one under GPL version 2 (or later), according
#    to the release schedule - http://www.gnu.org/software/gdb/schedule/
# binutils version 2.17 was the last one under GPL version 2 (or later), according
#    to the published releases - http://ftp.gnu.org/gnu/binutils/

python external_linaro_toolchain_license_handler () {
	if not isinstance(e, bb.event.ConfigParsed):
		return
	d = e.data
	ld = d.createCopy()
	ld.finalize()

	lc_libc = "LGPL-2.1"
	lc_gcc = ["GPL-3.0", "GPL-2.0"][elt_get_gcc_version(ld) <= "4.2.1"]
	lc_rle = ["GPL-3.0-with-GCC-exception", "GPL-2.0-with-GCC-exception"][elt_get_gcc_version(ld) <= "4.3.3"]
	lc_gdb = ["GPL-3.0", "GPL-2.0"][elt_get_gdb_version(ld) <= "6.6"]
#	lc_bfd = ["GPL-3.0", "GPL-2.0"][elt_get_bfd_version(ld) <= "2.17"]

	d.setVar('ELT_LIC_LIBC', lc_libc)
	d.setVar('ELT_LIC_GCC', lc_gcc)
	d.setVar('ELT_LIC_RLE', lc_rle)
	d.setVar('ELT_LIC_GDB', lc_gdb)
#	d.setVar('ELT_LIC_BFD', lc_bfd)

	d.setVar('ELT_LICENSE', "%s&%s&%s&%s" % (lc_libc, lc_gcc, lc_rle, lc_gdb))
}
addhandler external_linaro_toolchain_license_handler
