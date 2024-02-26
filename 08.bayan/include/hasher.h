#pragma once 

#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

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


    static std::string get_hash(std::string s) {

        md5 hash;
        md5::digest_type digest;

        hash.process_bytes(s.data(), s.size());
        hash.get_digest(digest);

        // std::cout << "md5(" << s << ") = " << toString(digest) << '\n';
    
        return toString(digest);
    }

private:
    // md5 hash;

};


