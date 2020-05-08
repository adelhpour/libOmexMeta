//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_SEMSIM_H
#define LIBSEMGEN_SEMSIM_H

#define HERE()                              \
do {                                        \
  std::cout << __FILE__ << ":" << __LINE__ << std::endl; \
} while (0)

// these will be included in the finished product
#include "semsim/RDF.h"
#include "semsim/CurlGet.h"
#include "semsim/SemsimUtils.h"
#include "semsim/MetaID.h"
#include "semsim/XmlAssistant.h"
#include "semsim/Editor.h"

// these may be included in the finished product
#include "semsim/Subject.h"
#include "semsim/Resource.h"
#include "semsim/Predicate.h"
#include "semsim/Predicate.h"
#include "semsim/SemsimCombineArchive.h"

#endif //LIBSEMGEN_SEMSIM_H