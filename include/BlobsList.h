/* BlobsList.h
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
#ifndef BLOBSTOOL_BLOBSLIST_H
#define BLOBSTOOL_BLOBSLIST_H
#include <vector>
#include <BlobsSection.h>

class BlobsList {
private:
    std::vector<std::shared_ptr<BlobsSection>> v_bs;
public:
    std::shared_ptr<BlobsSection> getBlobsSection(size_t index);
    size_t getSize() { return this->v_bs.size(); }
    void addBlobsSection(BlobsSection &bs);
    void sort(std::function<bool(std::shared_ptr<BlobsSection> &a, std::shared_ptr<BlobsSection> &b)>,
              std::function<bool(std::shared_ptr<Blob> &a, std::shared_ptr<Blob> &b)>);
    void reHash(std::string &top, std::function<bool(std::shared_ptr<BlobsSection> &a, std::string &device)> bs_except_fun, bool source, std::string &device);
    void write(std::ofstream &ofs);
};

#endif //BLOBSTOOL_BLOBSLIST_H
