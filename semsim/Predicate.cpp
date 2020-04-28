//
// Created by Ciaran on 4/17/2020.
//

#include "Predicate.h"

#include <utility>
#include <iostream>
#include "librdf.h"

namespace semsim {

    Predicate::Predicate(librdf_world *world, const std::string &namespace_,
                         std::string term, std::string prefix)
            : world_(world), namespace_(namespace_), term_(std::move(term)),
              prefix_(std::move(prefix)) {
        if (namespace_.back() == '/') {
            this->uri_ = namespace_ + term_;
        } else {
            this->uri_ = namespace_ + "/" + term_;
        }
        verify(valid_terms_, term);
        this->uri_node_ = std::make_shared<RDFURINode>(RDFURINode(world_, uri_));
    }

    std::string Predicate::str() {
        return uri_;
    }

    librdf_node *Predicate::toRdfNode() {
        return uri_node_->toRdfNode();
    }

    int Predicate::verify(std::vector<std::string> valid_terms, const std::string& term) {
        // when valled from the base Predicate class, accept anything
        if (valid_terms.size() == 1)
            if (valid_terms[0] == "All")
                return 0;
        // when called from any other class (which should have overridden valid_terms), we do validatation
        if (!(std::find(valid_terms.begin(), valid_terms.end(), term) != valid_terms.end())) {
            std::ostringstream os;
            os << __FILE__ << ":" << __LINE__ << ": Invalid term \"" << term << "\"given. Terms available for "
               << " include: ";
            for (auto &i : valid_terms) {
                os << i << ", ";
            }
            throw std::invalid_argument(os.str());
        }
        return 0;
    }

    const std::string &Predicate::getNamespace() const {
        return namespace_;
    }

    const std::string &Predicate::getTerm() const {
        return term_;
    }

    const std::string &Predicate::getPrefix() const {
        return prefix_;
    }

    const std::string &Predicate::getUri() const {
        return uri_;
    }

    void Predicate::setPrefix(const std::string &prefix) {
        prefix_ = prefix;
    }
    void Predicate::setNamespace(const std::string &ns) {
        namespace_ = ns;
    }

    BiomodelsBiologyQualifier::BiomodelsBiologyQualifier(librdf_world *world, const std::string &term) :
            Predicate(world, "http://biomodels.net/biology-qualifiers/", term, "bqbiol"){
        verify(valid_terms_, term_);

    }
    BiomodelsModelQualifier::BiomodelsModelQualifier(librdf_world *world, const std::string &term) :
            Predicate(world, "http://biomodels.net/model-qualifiers/", term, "bqmodel"){
        verify(valid_terms_, term_);

    }

    DCTerm::DCTerm(librdf_world *world, const std::string &term) :
            Predicate(world, "http://purl.org/dc/terms/", term, "dcterms"){
        verify(valid_terms_, term_);
    }

    SemSim::SemSim(librdf_world *world, const std::string &term) :
            Predicate(world, "http://www.bhi.washington.edu/semsim/", term, "semsim") {
        verify(valid_terms_, term_);
    }


}
