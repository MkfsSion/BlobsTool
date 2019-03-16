/* hashtest.cpp
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

#include <iostream>
#include <filesystem>
#include <BlobHash.h>

int main()
{
    std::string path(std::filesystem::current_path().u8string());
    Blob b;
#ifdef _WIN32
    b.source = "hashtest.exe";
    b.destination = "hashtest.exe";
#else
    b.source = "hashtest";
    b.destination = "hashtest";
#endif // _WIN32
    std::string hash = getBlobHexSHA1(path, b, true);
    std::cout << "Self hash is " << hash << std::endl;
    return 0;
}