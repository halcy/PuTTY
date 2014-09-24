/*
 * This header file provides the various versioning-related #defines
 * for a particular PuTTY build.
 *
 * When my automated build system does a full build, Buildscr
 * completely overwrites this file with information derived from the
 * circumstances and type of that build. The information _here_ is
 * default stuff used for local development runs of 'make'.
 */

#ifndef VERNAME
#define TEXTVER "Unidentified build"
#define SSHVER "PuTTY-Unidentified-Local-Build"
#define BINARY_VERSION 0,0,0,0
#else

#define _Q2_(xx) #xx
#define _QQ_(xx) _Q2_(xx)
#define TEXTVER _QQ_(VERNAME)
#ifdef SHORTVERNAME
#define SSHVER "PuTTY-" _QQ_(SHORTVERNAME)
#else
#define SSHVER "PuTTY-" _QQ_(VERNAME)
#endif
#ifndef BINARY_VERSION
#define BINARY_VERSION 0,0,0,0
#endif

#endif
