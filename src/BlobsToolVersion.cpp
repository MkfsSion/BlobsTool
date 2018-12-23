/* BlobsToolVersion.cpp
 *
 * Copyright (C) 2018 MkfsSion <mkfssion@mkfssion.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <BlobsToolVersion.h>

static const char *blobstool_version_str="0.1";
static const uint8_t blobstool_version_major = 0;
static const uint8_t blobstool_version_minor = 1;
static const uint16_t blobstool_version = ((uint16_t) blobstool_version_major << 8) | (uint16_t) blobstool_version_minor;

const std::string getBlobsToolVersionStr()
{
    return blobstool_version_str;
}

const uint16_t getBlobsToolVersion()
{
    return blobstool_version;
}