/*
 * Copyright (C) 2026, Samuel Zormeister.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef __CRASHREPORTERCLIENT__
#define __CRASHREPORTERCLIENT__

#include <sys/cdefs.h>
#include <stdint.h>

__BEGIN_DECLS

#define CRASH_REPORTER_CLIENT_HIDDEN        __attribute__((visibility("hidden")))

// gCRAnnotations should always be in __DATA,__crash_info
#define CRASHREPORTER_ANNOTATIONS_SEGMENT   "__DATA"
#define CRASHREPORTER_ANNOTATIONS_SECTION   "__crash_info"
#define CRASHREPORTER_ANNOTATIONS_VERSION   5

// if these are all const char pointers then perhaps the fields should be uintptr_t for 32-bit platforms.
typedef struct crashreporter_annotations_t {
    uint64_t version;
    uint64_t message;
    uint64_t signature_string;
    uint64_t backtrace;
    uint64_t message2;
    uint64_t thread;            // 'Crashed Thread' ?
    uint64_t dialog_mode;
    uint64_t abort_cause;       // this is used by libplatform
} crashreporter_annotations_t;

// image-local crash reporter annotations.
CRASH_REPORTER_CLIENT_HIDDEN
extern crashreporter_annotations_t gCRAnnotations;

// field accessors
#define _crc_make_getter(attr)  ((const char *)gCRAnnotations.attr)
#define _crc_make_setter(attr, v)  (gCRAnnotations.attr = (uint64_t)(v))

// this is typically where messages are stored.
#define CRGetCrashLogMessage() _crc_make_getter(message)
#define CRSetCrashLogMessage(msg) _crc_make_setter(message, msg)

// some clients make use of this, see dyld
#define CRGetCrashLogMessage2() _crc_make_getter(message2)
#define CRSetCrashLogMessage2(msg) _crc_make_setter(message2, msg)

__END_DECLS

#endif /* __CRASHREPORTERCLIENT__ */
