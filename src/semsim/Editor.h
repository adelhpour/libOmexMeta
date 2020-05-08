//
// Created by Ciaran on 4/15/2020.
//

#ifndef LIBSEMGEN_EDITOR_H
#define LIBSEMGEN_EDITOR_H


class XmlAssistant;

#include "semsim/XmlAssistant.h"
#include "semsim/Predicate.h"
#include "semsim/Resource.h"
#include "semsim/Triple.h"
#include "semsim/Participant.h"
#include "semsim/RDF.h"
#include "PhysicalPhenomenon.h"


// todo implement this logic from Maxes email
/*
 * Here's the basic logic that we use in SemGen to determine which OPB physical property is represented by a <species> in an SBML model:
 *
 * Using libSBML, we first look up the substance base units for the model and also whether the species's "hasOnlySubstanceUnits" attribute is true...
 *
 * if the substance base unit is mole
 *      if hasOnlySubstanceUnits for species is TRUE, then use OPB:Chemical_molar_amount (OPB_00425)
 *      else use OPB:Chemical_concentration (OPB_00340)
 *
 * else if the substance base unit is item
 *      if hasOnlySubstanceUnits for species is TRUE, then use OPB:Particle_count (OPB_01001)
 *      else use OPB:Particle_concentration (OPB_01000)
 *
 * else if the base unit is kilogram or gram
 *      if hasOnlySubstanceUnits is TRUE, then use OPB:Mass_of_solid_entity (OPB_01226)
 *      else
 *           if the spatial dimensions of the compartment containing the species = 1, use OPB:Mass_lineal_density (OPB_00190)
 *           else, if the spatial dimensions of the compartment containing the species = 2, use OPB:Mass_areal_density (OPB_00258)
 *           else, if the spatial dimensions of the compartment containing the species = 3, use OPB:Mass_volumetric_density (OPB_00101)
 *
 * Hope that's helpful for determining which OPB property to use in composite annotations for SBML <species>.
 *
 * Any questions, just lemme know.
 */

namespace semsim {

    typedef std::unordered_map<std::string, std::string> NamespaceMap;

    class RDF; // forward declaration

    class Editor {
    private:
        std::string xml_;
        std::vector<std::string> metaids_;
        NestedTriples triple_list_;
        librdf_world *world_;
        librdf_model *model_;
        std::unordered_map<std::string, std::string> &namespaces_;

        void extractNamespacesFromTriplesVector(Triples triples);
    public:
        const NamespaceMap &getNamespaces() const;

        void setNamespaces(const NamespaceMap &namespaces);

        // probably need to send our librdf model etc to the editor
        const NestedTriples &getTripleList() const;

        explicit Editor(const std::string &xml, XmlAssistantType type,
                        librdf_world *world,
                        librdf_model *model, NamespaceMap &ns_map);

        const std::string &getXml() const;

        const std::vector<std::string> &getMetaids() const;

        void addSingleAnnotation(Subject subject, PredicatePtr predicate_ptr, Resource resource);

        void addNamespace(std::string ns, std::string prefix);

        void addSingleAnnotation(Triple triple);

        void addCompositeAnnotation(PhysicalPhenomenonPtr phenomenonPtr);

        void addAnnotationFromNestedTriples(NestedTriples tripleList);
        //overloaded

        // physical entity
        void addPhysicalEntityAnnotation(const std::string &subject, std::string isVersionOf,
                                         const std::string &isPropertyOf, Resource is, Resource isPartOf);

        // physical process
        void addPhysicalProcessAnnotation(
                std::string subject, std::string isVersionOf, std::string isPropertyOf,
                std::vector<ParticipantPtr> participants);

        // physical force
        void addPhysicalForceAnnotation(
                std::string subject, std::string isVersionOf, std::string isPropertyOf);

        void removeAnnotation();

        void toRDF();

        void checkValidMetaid(const std::string &metaid);

        void addAnnotationFromTriples(Triples triples);

    };

}

#endif //LIBSEMGEN_EDITOR_H