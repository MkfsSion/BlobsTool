/* BlobsSection.h
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
#ifndef BLOBSTOOL_BLOBSSECTION_H
#define BLOBSTOOL_BLOBSSECTION_H
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <fstream>
#include <Blob.h>

// Basic definition of a blobs section

class BlobsSection {
private:
    std::string section_name;
    std::string vendor_name;
    std::vector<std::shared_ptr<Blob>> v_b;
public:
    BlobsSection(std::string s_name, std::string v_name) : section_name(std::move(s_name)), vendor_name(std::move(v_name)) {}
    BlobsSection() = default;
    std::shared_ptr<Blob> getBlob(size_t index);
    void addBlob(Blob &b);
    void setSectionName(std::string s) { this->section_name = std::move(s); }
    void setVendorName(std::string s) { this->vendor_name = std::move(s); }
    size_t getSize() { return this->v_b.size(); }
    void sort(std::function<bool(std::shared_ptr<Blob> &a, std::shared_ptr<Blob> &b)> compare_fun);
    std::string getVendorName();
    std::string getSectionName();
    void reHash(std::string &top, bool source);
    void write(std::ofstream &ofs);
};

#endif //BLOBSTOOL_BLOBSSECTION_H
