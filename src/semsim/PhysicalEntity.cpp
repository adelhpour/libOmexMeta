//
// Created by Ciaran on 4/22/2020.
//

#include "semsim/PhysicalEntity.h"

#include <utility>

namespace semsim {

    PhysicalEntity::PhysicalEntity(librdf_model *model,
                                   Subject about,
                                   PhysicalPropertyResource physicalProperty,
                                   Resource is,
                                   Resources is_part_of)
            : PhysicalPhenomenon(model, about, std::move(physicalProperty), PHYSICAL_ENTITY),
              identity_resource_(std::move(is)), location_resources(std::move(is_part_of)) {}


    void PhysicalEntity::free() {
        if (about.getNode() != nullptr) {
            about.free();
            about.setNode(nullptr);
        }

        if (physical_property_.getNode() != nullptr) {
            physical_property_.free();
            physical_property_.setNode(nullptr);
        }
        if (identity_resource_.getNode() != nullptr) {
            identity_resource_.free();
            identity_resource_.setNode(nullptr);
        }

        for (auto &i : location_resources) {
            if (i.getNode() != nullptr) {
                i.free();
                i.setNode(nullptr);
            }
        }
    }

    PhysicalEntity::PhysicalEntity(librdf_model *model) : PhysicalPhenomenon(model) {
    }


    PhysicalEntity &PhysicalEntity::setAbout(std::string metaid) {
        this->about = Subject::fromRawPtr(LibrdfNode::fromUriString(std::move(metaid)));
        return *this;

    }

    PhysicalEntity &PhysicalEntity::setPhysicalProperty(PhysicalPropertyResource physicalProperty) {
        PhysicalPhenomenon::physical_property_ = physicalProperty;
        return *this;
    }

    PhysicalEntity &PhysicalEntity::setPhysicalProperty(const std::string &physicalProperty) {
        physical_property_ = PhysicalPropertyResource(physicalProperty);
        return *this;
    }


    PhysicalEntity &PhysicalEntity::setIdentity(std::string resource) {
        // todo implement second argument which defaults to RDFUriNode
        //  and controls whether we use literal/blank/uri node
        identity_resource_ = Resource::fromRawPtr(LibrdfNode::fromUriString(std::move(resource)));
        return *this;
    }

    PhysicalEntity &PhysicalEntity::addLocation(std::string where) {
        location_resources.push_back(
                Resource::fromRawPtr(LibrdfNode::fromUriString(where))
        );
        return *this;
    }

    const Resource &PhysicalEntity::getIdentityResource() const {
        return identity_resource_;
    }

    const Resources &PhysicalEntity::getLocationResources() const {
        return location_resources;
    }

    Triples PhysicalEntity::toTriples() {

        if (getAbout().getNode() == nullptr) {
            throw AnnotationBuilderException(
                    "PhysicalEntity::toTriples(): Cannot create"
                    " triples because the \"about\" information is not set. "
                    "Use the setAbout() method."
            );
        }
        if (getPhysicalProperty().getNode() == nullptr) {
            throw AnnotationBuilderException(
                    "PhysicalEntity::toTriples(): Cannot create"
                    " triples because the \"physical_property\" information is not set. "
                    "Use the setPhysicalProperty() method."
            );
        }
        if (getLocationResources().empty()) {
            throw AnnotationBuilderException(
                    "PhysicalEntity::toTriples(): cannot create "
                    "triples object because the\"location\" information "
                    "is empty. Use the addLocation() method."
            );
        }
        int count = 0;
        for (auto &i : getLocationResources()) {
            if (i.getNode() == nullptr) {
                std::ostringstream err;
                err << "PhysicalEntity::toTriples(): Cannot create"
                       " triples because item ";
                err << count << "of the \"location\" information is not set. ";
                err << "Use the addLocation() method.";
                throw AnnotationBuilderException(
                        err.str()
                );
            }
        }
        // no exclusions needed here - we only generate 1 process metaid before comiting the triples
        // to the model.
        std::string property_metaid = SemsimUtils::generateUniqueMetaid(
                model_, "PhysicalEntity",
                std::vector<std::string>());
//        Triples triples;


        Triples triples = physical_property_.toTriples(about.str(), property_metaid);
        /*
         * todo note: We are passing a Subject as argument to PhysicalPhenomena types
         *  but when we get to generation of the triples themselves, we are only pulling out
         *  the string. The easiest thing to do is to change the code to only accept string arguments.
         *  I have resisted this so far because this would make the assumption that Subjects are URI nodes,
         *  where they can actually be blank nodes as well. If we want to implement a string parameter
         *  for the subject argument we may need an additional parameter to maintain the ability to
         *  also create a Blank subject node. This is a note for potential future improvement. Right now,
         *  I handle the memory leak by freeing the subject node (about) here;
         */
        about.free();

        // the "what" part of physical entity triple
        triples.emplace_back(
                Subject::fromRawPtr(LibrdfNode::fromUriString(property_metaid)).getNode(),
                BiomodelsBiologyQualifier("is").getNode(),
                getIdentityResource().getNode()
        );
        // the "where" part of the physical entity
        for (auto &locationResource : getLocationResources()) {
            triples.emplace_back(
                    Subject::fromRawPtr(LibrdfNode::fromUriString(property_metaid)).getNode(),
                    BiomodelsBiologyQualifier("isPartOf").getNode(),
                    locationResource.getNode()
            );
        }

        return triples;
    }

    [[maybe_unused]] int PhysicalEntity::getNumLocations() const {
        return getLocationResources().size();
    }


}
















