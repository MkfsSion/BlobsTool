/* BlobsListParser.h
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
#ifndef BLOBSTOOL_BLOBSLISTPARSER_H
#define BLOBSTOOL_BLOBSLISTPARSER_H
#include <fstream>
#include <BlobsList.h>

class BlobsListParser {
private:
    std::ifstream ifs;
    BlobsList *blist;
public:
    explicit BlobsListParser(std::string &path) : ifs(path),blist(nullptr)
    {
        if (!ifs.is_open()) {
            throw std::invalid_argument("Unable to open blobs list file");
        }
    }
    explicit BlobsListParser(const char *path) : ifs(path),blist(nullptr)
    {
        if (!ifs.is_open()) {
            throw std::invalid_argument("Unable to open blobs list file");
        }
    }
    BlobsList parse();
    ~BlobsListParser()
    {
        ifs.close();
    }
};

#endif //BLOBSTOOL_BLOBSLISTPARSER_H
