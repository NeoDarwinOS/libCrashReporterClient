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

//
// gCRAnnotations facilitates libraries and applications to have self-reporting crash logs.
//
// Research Sources:
//  - https://alastairs-place.net/blog/2013/01/10/interesting-os-x-crash-report-tidbits/
//  - https://developer.apple.com/documentation/xcode/examining-the-fields-in-a-crash-report
//

#define CRASH_REPORTER_CLIENT_HIDDEN        __attribute__((visibility("hidden")))

// gCRAnnotations should always be in __DATA,__crash_info
#define CRASHREPORTER_ANNOTATIONS_SEGMENT   "__DATA"
#define CRASHREPORTER_ANNOTATIONS_SECTION   "__crash_info"
#define CRASHREPORTER_ANNOTATIONS_VERSION   5

typedef struct crashreporter_annotations_t {
    uint64_t version;
    uint64_t message;           // 'Application Specific Information'
    uint64_t signature_string;  // 'Application Specific Signatures'
    uint64_t backtrace;         // 'Application Specific Backtrace'
    uint64_t message2;          // TODO: is included in ASI?
    uint64_t thread;            // unsure
    uint64_t dialog_mode;       // unsure
    uint64_t abort_cause;       // OS_BUG_INTERNAL and OS_BUG_CLIENT use this to include the failed condition.
} crashreporter_annotations_t;

CRASH_REPORTER_CLIENT_HIDDEN
extern crashreporter_annotations_t gCRAnnotations;

// field accessors
#define _crc_make_getter(attr)  ((const char *)gCRAnnotations.attr)
#define _crc_make_setter(attr, v)  (gCRAnnotations.attr = (uint64_t)(v))

#define CRGetCrashLogMessage() _crc_make_getter(message)
#define CRSetCrashLogMessage(msg) _crc_make_setter(message, msg)

#define CRGetCrashLogBacktrace() _crc_make_getter(backtrace)
#define CRSetCrashLogBacktrace(trace) _crc_make_setter(backtrace, trace)

#define CRGetCrashLogSignatureString() _crc_make_getter(signature_string)
#define CRSetCrashLogSignatureString(sig) _crc_make_setter(signature_string, sig)

#define CRGetCrashLogMessage2() _crc_make_getter(message2)
#define CRSetCrashLogMessage2(msg) _crc_make_setter(message2, msg)

__END_DECLS

#endif /* __CRASHREPORTERCLIENT__ */
