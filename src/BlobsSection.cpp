/* BlobSection.cpp
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

#include <BlobsSection.h>
#include <BlobHash.h>

static bool BlobCompare(std::shared_ptr<Blob> &a, std::shared_ptr<Blob> &b)
{
    return b->source > a->source;
}

std::shared_ptr<Blob> BlobsSection::getBlob(size_t index)
{
    if (this->v_b.empty())
    {
        return nullptr;
    }
    return this->v_b.at(index);
}

void BlobsSection::addBlob(Blob &b)
{
    Blob *nb = new Blob;
    *nb = b;
    this->v_b.push_back(std::shared_ptr<Blob>(nb));
}

void BlobsSection::sort(std::function<bool(std::shared_ptr<Blob> &a, std::shared_ptr<Blob> &b)> compare_fun)
{
    if (!compare_fun)
    {
        std::sort(this->v_b.begin(), this->v_b.end(), BlobCompare);
    }
    else
    {
        std::sort(this->v_b.begin(), this->v_b.end(), compare_fun);
    }
}

std::string BlobsSection::getSectionName()
{
    return this->section_name;
}

std::string BlobsSection::getVendorName()
{
    return this->vendor_name;
}
void BlobsSection::reHash(std::string &top, bool source)
{
    if (top.empty())
        return;
    for (auto &x : this->v_b)
    {
        x->sha1sum = getBlobHexSHA1(top, *x, source);
    }
}

void BlobsSection::write(std::ofstream &ofs)
{
    if (!ofs.is_open())
        return;
    ofs << "# " << this->section_name;
    if (!this->vendor_name.empty())
    {
        ofs << " - from" << " " << this->vendor_name;
    }
    ofs << std::endl;
    for (auto &x : this->v_b)
    {
        ofs << (x->modularized ? "-" : "");
        ofs << x->source;
        ofs << (x->source == x->destination ? "" : ":");
        ofs << (x->source == x->destination ? "" : x->destination);
        ofs << (x->sha1sum.empty() ? "" : "|");
        ofs << (x->sha1sum.empty() ? "" : x->sha1sum);
        ofs << std::endl;
    }
}
