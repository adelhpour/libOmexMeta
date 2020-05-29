//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFSTORAGE_H
#define LIBSEMSIM_LIBRDFSTORAGE_H

#include <librdf.h>
#include <string>
#include <memory>
#include "World.h"

namespace semsim {

    class LibrdfStorage {

        std::vector<std::string> valid_stores_ = {
                "hashes",
                "memory",
                "file",
                "mysql",
                "postgresql",
                "sqlite",
                "tstore",
                "uri",
                "virtuoso",
        };

        struct deleter {
            void operator()(librdf_storage *storage);
        };

        std::unique_ptr<librdf_storage, deleter> storage_;

    public:
        explicit LibrdfStorage(librdf_storage *storage);

        explicit LibrdfStorage(const std::string &storage_name = "memory", const std::string &name = "SemsimStore",
                               const char *options = nullptr);

        [[nodiscard]] librdf_storage *get() const;

    };
}


#endif //LIBSEMSIM_LIBRDFSTORAGE_H