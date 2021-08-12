#include "redland/LibrdfQuery.h"
#include "redland/LibrdfQueryResults.h"
#include <redland/LibrdfException.h>
#include <redland/LibrdfModel.h>

#include <utility>
#include "redland/Logger.h"

namespace redland {

    bool LibrdfQuery::operator==(const LibrdfQuery &rhs) const {
        return obj_ == rhs.obj_;
    }

    bool LibrdfQuery::operator!=(const LibrdfQuery &rhs) const {
        return !(rhs == *this);
    };

    LibrdfQuery::LibrdfQuery(librdf_query *query, const LibrdfModel &model)
        : RedlandType_librdf_query(query, librdf_free_query), model_(const_cast<LibrdfModel &>(model)) {
        REDLAND_DEBUG("Instantiated a LibrdfQuery instance");
    }

    LibrdfQuery::LibrdfQuery(std::string query, const LibrdfModel &model)
        : query_(std::move(query)), model_(const_cast<LibrdfModel &>(model)) {
        obj_ = newQuery();
        freeFunc_ = librdf_free_query;
    }

    librdf_query *LibrdfQuery::newQuery() {
        return librdf_new_query(
                LibrdfWorld::getWorld(),
                "sparql",
                nullptr,
                (const unsigned char *) query_.c_str(),
                nullptr);
    }

    LibrdfQueryResults LibrdfQuery::execute() {
        //        if (!queryResults_.isNull()) {
        //            freeFunc_(obj_);
        //            obj_ = nullptr;
        //        }

        return LibrdfQueryResults(librdf_query_execute(obj_, model_.getWithoutIncrement()));
    }


    //
    //    void LibrdfQuery::runQuery() {
    //        // When we runQuery twice, we have memory leak if we do
    //        //  not free previous query results.
    ////        if (queryResults_.isNull() ) {
    ////            librdf_free_query_results(queryResults_.get());
    ////            queryResults_ = nullptr;
    ////        }
    //
    //        queryResults_ = LibrdfQueryResults(librdf_query_execute(q_, model_));
    //        if (queryResults_.isNull()) {
    //            throw NullPointerException("NullPointerException: LibrdfQuery::runQuery(): queryResults_");
    //        }
    //    }
    //
}// namespace redland
