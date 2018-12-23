# BlobsTool

## Contents
- Introduction
- Build
- Usage
- Contribution

## Introduction
A simple tool written in C++ for processing proprietary blobs list(**Still on development**).

## Build
The tool is using cmake as its build system for generating makefiles and depends on openssl library for generating SHA1.
### ArchLinux
```
sudo pacman -S git openssl cmake make gcc
git clone https://github.com/MkfsSion/BlobsTool.git BlobsTool
cd BlobsTool
mkdir out
cd out
cmake -G ..
make
```

## Usage
### Reorder blobs
`blobstools -s -i path_to_list_file -o output_file`
### Generate SHA1 for blobs
`blobstools -u -p path_to_top_directory -i path_to_list -o output_file`
### Show help
`blobstools -h`
### Show version
`blobstool -v`

Note: `path_to_top_directory` means the path that can access a blob with its realitive path

## Contribution
Issues and pull requests are welcomed.
