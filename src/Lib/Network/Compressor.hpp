#ifndef CLIENT_COMPRESSOR_HPP
#define CLIENT_COMPRESSOR_HPP

#include <zstd.h>

#include <vector>

std::vector<char> Compress(const std::string_view &data) {
    auto maxCompressSize = ZSTD_compressBound(data.size());

    std::vector<char> compressed(maxCompressSize, 0);

    auto compressSize = ZSTD_compress(compressed.data(), maxCompressSize, data.data(), data.size(), 22);

    compressed.resize(compressSize);

    return compressed;
}

std::string Decompress(const std::string &data) {
    auto maxDecompressedSize = ZSTD_getDecompressedSize(data.c_str(), data.size());

    std::string decompressed(maxDecompressedSize, 0);

    const auto decompressedSize = ZSTD_decompress(decompressed.data(), maxDecompressedSize, data.data(), data.size());

    decompressed.resize(decompressedSize);

    return decompressed;
}

#endif  // CLIENT_COMPRESSOR_HPP
