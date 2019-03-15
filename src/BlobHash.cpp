/* BlobHash.cpp
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

#include <cstdio>
#include <cstring>
#include <openssl/sha.h>
#include <BlobHash.h>

std::string getBlobHexSHA1(const std::string &top,const Blob &b, bool source)
{
    if (top.empty()||b.source.empty()||b.destination.empty())
    {
        return {};
    }
    std::string path;
    if (source)
    {
        path = top + (top[top.size() - 1] == '/' ? "" : "/") + b.source;
    }
    else
    {
        path = top + (top[top.size() - 1] == '/' ? "" : "/") + b.destination;
    }
    FILE *fptr = fopen(path.c_str(), "r");
    if (!fptr)
    {
        return {};
    }
    uint8_t buf[512] = {0};
    uint8_t hash[20] = {0};
    char hexhash[41] = {0};
    size_t s = 0;
    SHA_CTX ctx;
    if (!SHA1_Init(&ctx))
    {
        fclose(fptr);
        return {};
    }
    while ((s = fread(buf, 1, 512, fptr)))
    {
        SHA1_Update(&ctx, buf, s);
    }
    SHA1_Final(hash, &ctx);
    fclose(fptr);
    for (int i = 0; i < 20; i++)
    {
        snprintf(&hexhash[2*i], 3, "%02x", hash[i]);
    }
    return hexhash;
}
