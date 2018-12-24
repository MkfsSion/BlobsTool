/* BlobsList.cpp
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

#include <BlobsList.h>

static bool BlobsSectionCompare(std::shared_ptr<BlobsSection> &a, std::shared_ptr<BlobsSection> &b)
{
    return b->getSectionName() > a->getSectionName();
}

std::shared_ptr<BlobsSection> BlobsList::getBlobsSection(size_t index)
{
    if (this->v_bs.empty())
    {
        return nullptr;
    }
    return this->v_bs.at(index);
}

void BlobsList::addBlobsSection(BlobsSection &bs)
{
    auto nbs = new BlobsSection();
    *nbs = bs;
    this->v_bs.push_back(std::shared_ptr<BlobsSection>(nbs));
}

void BlobsList::sort(std::function<bool(std::shared_ptr<BlobsSection> &a, std::shared_ptr<BlobsSection> &b)> bs_compare_fun,
                     std::function<bool(std::shared_ptr<Blob> &a, std::shared_ptr<Blob> &b)> b_compare_fun)
{
    if (!bs_compare_fun)
    {
        std::sort(this->v_bs.begin(), this->v_bs.end(), BlobsSectionCompare);
    }
    else
    {
        std::sort(this->v_bs.begin(), this->v_bs.end(), bs_compare_fun);
    }
    for (auto &x : this->v_bs)
    {
        if (!b_compare_fun)
        {
            x->sort(nullptr);
        }
        else
        {
            x->sort(b_compare_fun);
        }
    }
}

void BlobsList::reHash(std::string &top, std::function<bool(std::shared_ptr<BlobsSection> &a, std::string &device)> bs_except_fun ,bool source, std::string &device)
{
    if (top.empty())
        return;
    for (auto &x : this->v_bs)
    {
        if (!bs_except_fun)
        {
            auto f = [&device](std::shared_ptr<BlobsSection> &pbs) -> bool {
                if (pbs->getVendorName().empty())
                    return false;
                return !(device == pbs->getVendorName());
            };
            if (f(x))
            {
                x->reHash(top, source);
            }
        }
        else
        {
            if (bs_except_fun(x, device))
            {
                x->reHash(top,source);
            }
        }
    }
}

void BlobsList::write(std::ofstream &ofs)
{
    if (!ofs.is_open())
        return;
    for (auto &x : this->v_bs)
    {
        x->write(ofs);
        if (x != *(this->v_bs.end()-1))
            ofs << std::endl;
    }
}
