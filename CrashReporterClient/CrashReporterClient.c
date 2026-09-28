/*
 * Copyright (C) 2026, Samuel Zormeister.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CrashReporterClient.h"

//
// This library is used by many Darwin projects.
//
// Also LLVM, for some reason.
//
// Namely:
//  dyld
//  Libc
//  Libsystem
//

crashreporter_annotations_t gCRAnnotations __attribute__((section(CRASHREPORTER_ANNOTATIONS_SEGMENT "," CRASHREPORTER_ANNOTATIONS_SECTION))) = {
    CRASHREPORTER_ANNOTATIONS_VERSION,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
