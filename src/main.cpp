/* main.cpp
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
#include <cstring>
#include <stdexcept>
#include <BlobsListParser.h>
#include <BlobHash.h>
#include <BlobsToolVersion.h>

struct BlobsToolCmdline
{
    std::string input_path;
    bool sort;
    std::string top_path;
    bool hash;
    std::string output_file;
};


static void blobstool_help()
{
    std::cout << "BlobsTool v" << getBlobsToolVersionStr() << std::endl;
    std::cout << "Usage: blobstool -i list_file [ -s ] [ -p top_path ] [ -u ] -o write_out_file [-v]" << std::endl;
    std::cout << "\t -i: Input file" << std::endl;
    std::cout << "\t -s: Sort blob by order" << std::endl;
    std::cout << "\t -p: Path for abstracting blobs" << std::endl;
    std::cout << "\t -u: Update hash" << std::endl;
    std::cout << "\t -o: Output file" << std::endl;
    std::cout << "\t -v: Show help" << std::endl;
}

static void blobstool_cmdline_process(BlobsToolCmdline cmdline)
{
    if (cmdline.input_path.empty()||cmdline.output_file.empty())
    {
        throw std::invalid_argument("No input file or output file specified");
    }
    BlobsListParser parser(cmdline.input_path);
    std::ofstream ofs;
	ofs.open(cmdline.output_file, std::ios::out | std::ios::trunc);
    BlobsList blist = parser.parse();
    if (cmdline.sort)
    {
        blist.sort(nullptr, nullptr);
    }
    if (cmdline.hash)
    {
        blist.reHash(cmdline.top_path, nullptr, true);
    }
    blist.write(ofs);
}

static BlobsToolCmdline blobstool_cmdline_parser(int argc, char **argv)
{

    BlobsToolCmdline cmdline {};
    int expect_value = 0;
    for (int i = 1; i < argc; i++)
    {
        if (!expect_value)
        {
            if (!strcmp(argv[i], "-i")) {
                expect_value = 1;
            }
            if (!strcmp(argv[i], "-s")) {
                cmdline.sort = true;
            }
            if (!strcmp(argv[i], "-p")) {
                expect_value = 3;
            }
            if (!strcmp(argv[i], "-u")) {
                cmdline.hash = true;
            }
            if (!strcmp(argv[i], "-o")) {
                expect_value = 5;
            }
            if (!strcmp(argv[i], "-h")) {
                blobstool_help();
            }
        }
        else
        {
            switch (expect_value)
            {
                case 1:
                    cmdline.input_path = argv[i];
                    break;
                case 3:
                    cmdline.top_path = argv[i];
                    break;
                case 5:
                    cmdline.output_file = argv[i];
                    break;
                default:
                    break;
            }
            expect_value = 0;
        }
    }
    return cmdline;
}

int main(int argc, char *argv[])
{
   if (argc == 1)
   {
       std::cout << "No args specified" << std::endl;
       blobstool_help();
       return 1;
   }
   BlobsToolCmdline cmdline = blobstool_cmdline_parser(argc, argv);
   blobstool_cmdline_process(std::move(cmdline));
   return 0;
}
