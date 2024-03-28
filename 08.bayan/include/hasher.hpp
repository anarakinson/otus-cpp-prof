#pragma once 

#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/crc.hpp>

#include <iostream>
#include <string>



using boost::uuids::detail::md5;


class Hasher {

public:

    static std::string toString(const md5::digest_type &digest)
    {
        const auto intDigest = reinterpret_cast<const int*>(&digest);
        std::string result;
        boost::algorithm::hex(intDigest, intDigest + (sizeof(md5::digest_type)/sizeof(int)), std::back_inserter(result));
        return result;
    }


    static uint32_t GetCrc32(const std::string &my_string) {
        boost::crc_32_type result;
        result.process_bytes(my_string.data(), my_string.length());
        return result.checksum();
    }

    static std::string GetMd5(const std::string &str) {
        md5 hash;
        md5::digest_type digest;

        hash.process_bytes(str.data(), str.size());
        hash.get_digest(digest);

        // std::cout << "md5(" << s << ") = " << toString(digest) << '\n';

        return toString(digest);
    }


    static std::string get_hash(const std::string &str, const std::string &hash_method) {

        if (hash_method == "md5") {
            
            return GetMd5(str);
            
        }
        else if (hash_method == "crc32") {

            return std::to_string(GetCrc32(str));

        }
        else {

            return GetMd5(str);
       
        }


    }

private:
    // md5 hash;

};




