//
// Created by Ciaran on 5/8/2020.
//

#ifndef LIBOMEXMETA_OMEXMETACAPI_H
#define LIBOMEXMETA_OMEXMETACAPI_H

#include "omexmeta/RDF.h"
#include "omexmeta/Editor.h"
#include "omexmeta/OmexMetaXmlAssistant.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalProcess.h"
#include "omexmeta/PhysicalForce.h"
#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta_capi_export.h"
#include <cstring>

namespace omexmeta {

#ifdef __cplusplus
    extern "C" {
#endif

    OMEXMETA_CAPI_EXPORT int free_c_char_star(char *c);

    OMEXMETA_CAPI_EXPORT int free_c_char_star_star(char **c, int size);

/***************************************************
 * librdf_world methods
 *
 * note: Really I do not want users to have to deal with this
 * todo take steps to ensure users do not need to interact with the librdf_world*
 *
 */

    OMEXMETA_CAPI_EXPORT [[maybe_unused]] int free_world(librdf_world *world);

/***************************************************
 * RDF class methods
 */

    OMEXMETA_CAPI_EXPORT RDF *RDF_new(const char *storage_type = "memory", const char *storage_name = "semsim_store",
                            const char *storage_options = nullptr, const char *model_options = nullptr);

    OMEXMETA_CAPI_EXPORT void RDF_delete(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT char *RDF_getBaseUri(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT int RDF_setBaseUri(RDF *rdf_ptr, const char *uri);

    OMEXMETA_CAPI_EXPORT char *RDF_toString(RDF *rdf_ptr, const char *format);

    OMEXMETA_CAPI_EXPORT int RDF_toFile(RDF *rdf_ptr, const char* format, const char *filename);

    /**
     * @brief read RDF formatted annotations a string.
     * @param pdf_ptr a pointer to an RDF object.
     * @param str the string to read annotations from
     * @param format the format that the string annotations are in (get it
     * wrong to be provided a list of supported syntaxes)
     * @param baseuri the uri used for the base. All relative uri's
     * in the RDF graph are relative to the base uri
     *
     * @example
     * RDF* rdf_ptr = RDF_fromString(string_annotations, "rdfxml", "string_annotations_base_uri");
     */
    OMEXMETA_CAPI_EXPORT RDF *RDF_fromString(const char *str, const char *format,
                                   const char *storage_type = "memory", const char *storage_name = "semsim_store",
                                   const char *storage_options = nullptr, const char *model_options = nullptr);

    OMEXMETA_CAPI_EXPORT int RDF_addFromString(RDF *rdf_ptr, const char *str, const char *format);

    OMEXMETA_CAPI_EXPORT RDF *RDF_fromUri(const char *uri_string, const char *format,
                                const char *storage_type = "memory", const char *storage_name = "semsim_store",
                                const char *storage_options = nullptr, const char *model_options = nullptr);

    OMEXMETA_CAPI_EXPORT int RDF_addFromUri(RDF *rdf_ptr, const char *uri_string, const char *format);

    OMEXMETA_CAPI_EXPORT RDF *RDF_fromFile(const char *filename, const char *format, const char *storage_type = "memory",
                                 const char *storage_name = "semsim_store",
                                 const char *storage_options = nullptr, const char *model_options = nullptr);

    OMEXMETA_CAPI_EXPORT int RDF_addFromFile(RDF *rdf_ptr, const char *uri_string, const char *format);

    OMEXMETA_CAPI_EXPORT char *RDF_query(RDF *rdf_ptr, const char *query_str, const char *results_format);

    OMEXMETA_CAPI_EXPORT int RDF_size(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT int RDF_setRepositoryUri(RDF *rdf_ptr, const char *repository_uri);

    OMEXMETA_CAPI_EXPORT int RDF_setArchiveUri(RDF *rdf_ptr, const char *archive_uri);

    OMEXMETA_CAPI_EXPORT int RDF_setModelUri(RDF *rdf_ptr, const char *model_uri);

    OMEXMETA_CAPI_EXPORT char *RDF_getRepositoryUri(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT char *RDF_getArchiveUri(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT char *RDF_getModelUri(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT char *RDF_getLocalUri(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT bool RDF_equals_rdf_vs_string(RDF* rdf_ptr, const char* serialized_rdf, const char* format = "turtle");

    OMEXMETA_CAPI_EXPORT bool RDF_equals_rdf_vs_rdf(RDF* rdf_ptr1, RDF* rdf_ptr2, const char* format = "turtle");

    OMEXMETA_CAPI_EXPORT bool RDF_equals_string_vs_string(const char* first_rdf_graph, const char* second_rdf_graph, const char* format = "turtle");

    OMEXMETA_CAPI_EXPORT Editor *
    RDF_toEditor(RDF *rdf_ptr, const char *xml, bool generate_new_metaids, bool sbml_semantic_extraction);

/*********************************************
 *  Editor class methods
 */

    OMEXMETA_CAPI_EXPORT int Editor_addNamespace(Editor *editor_ptr, const char *namespace_, const char *prefix);

    OMEXMETA_CAPI_EXPORT int Editor_addSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation);

    OMEXMETA_CAPI_EXPORT int Editor_addPhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity);

    OMEXMETA_CAPI_EXPORT int Editor_addPhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess);

    OMEXMETA_CAPI_EXPORT int Editor_addPhysicalForce(Editor *editor_ptr, PhysicalForce *physicalForce);

    OMEXMETA_CAPI_EXPORT int Editor_addPersonalInformation(Editor *editor_ptr, PersonalInformation *personalInformation);

    OMEXMETA_CAPI_EXPORT int Editor_removeSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation);

    OMEXMETA_CAPI_EXPORT int Editor_removePhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity);

    OMEXMETA_CAPI_EXPORT int Editor_removePhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess);

    OMEXMETA_CAPI_EXPORT int Editor_removePhysicalForce(Editor *editor_ptr, PhysicalForce *physicalForce);

    OMEXMETA_CAPI_EXPORT int Editor_removePersonalInformation(Editor *editor_ptr, PersonalInformation *information);

    OMEXMETA_CAPI_EXPORT int Editor_checkValidMetaid(Editor *editor_ptr, const char *id);

    OMEXMETA_CAPI_EXPORT char *Editor_getMetaId(Editor *editor_ptr, int index);

    OMEXMETA_CAPI_EXPORT char *Editor_getXml(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT int Editor_getNumMetaIds(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT int Editor_delete(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT char *Editor_getArchiveUri(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT char *Editor_getLocalUri(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT char *Editor_getModelUri(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT char *Editor_getRepositoryUri(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT Editor* Editor_addCreator(Editor *editor_ptr, const char *orcid_id);

    OMEXMETA_CAPI_EXPORT Editor* Editor_addCurator(Editor *editor_ptr, const char *orcid_id);

    OMEXMETA_CAPI_EXPORT Editor* Editor_addTaxon(Editor *editor_ptr, const char *taxon_id);

    OMEXMETA_CAPI_EXPORT Editor* Editor_addPubmed(Editor *editor_ptr, const char *pubmedid);

    OMEXMETA_CAPI_EXPORT Editor* Editor_addDescription(Editor *editor_ptr, const char *date);

    OMEXMETA_CAPI_EXPORT Editor* Editor_addDateCreated(Editor *editor_ptr, const char *date);

    OMEXMETA_CAPI_EXPORT Editor* Editor_addParentModel(Editor *editor_ptr, const char *biomod_id);

/*********************************************************************
 * SingularAnnotation class methods
 */
    OMEXMETA_CAPI_EXPORT SingularAnnotation *SingularAnnotation_new(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT int SingularAnnotation_delete(SingularAnnotation *singularAnnotation);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_about(SingularAnnotation *singular_annotation, const char *about);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_setPredicate(SingularAnnotation *singular_annotation, const char *namespace_, const char *term);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_predicate(SingularAnnotation *singular_annotation, const char *namespace_, const char *term);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *SingularAnnotation_setPredicateFromUri(
            SingularAnnotation *singular_annotation, const char *uri);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *SingularAnnotation_predicateFromUri(
            SingularAnnotation *singular_annotation, const char *uri);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *SingularAnnotation_setResourceLiteral(
            SingularAnnotation *singular_annotation, const char *literal);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *SingularAnnotation_resourceLiteral(
            SingularAnnotation *singular_annotation, const char *literal);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_setResourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_resourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_setResourceBlank(SingularAnnotation *singular_annotation, const char *blank_id);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_resourceBlank(SingularAnnotation *singular_annotation, const char *blank_id);

    OMEXMETA_CAPI_EXPORT char *SingularAnnotation_getAbout(SingularAnnotation *singular_annotation);

    OMEXMETA_CAPI_EXPORT char *
    SingularAnnotation_str(SingularAnnotation *singular_annotation, const char *format);

    OMEXMETA_CAPI_EXPORT char *SingularAnnotation_getPredicate(SingularAnnotation *singular_annotation);

    OMEXMETA_CAPI_EXPORT char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation);

/*********************************************************************
 * PhysicalEntity class methods
 */
    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_new(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT int PhysicalEntity_delete(PhysicalEntity *physical_entity_ptr);

    OMEXMETA_CAPI_EXPORT int PhysicalEntity_freeAll(PhysicalEntity *physical_entity_ptr);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_setPhysicalProperty(
            PhysicalEntity *physical_entity_ptr, const char *subject_metaid, const char *physical_property=nullptr);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_setIdentity(
            PhysicalEntity *physical_entity_ptr, const char *identity_resource);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_identity(
            PhysicalEntity *physical_entity_ptr, const char *identity_resource);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_addLocation(
            PhysicalEntity *physical_entity_ptr, const char *location_resource);

    OMEXMETA_CAPI_EXPORT char *PhysicalEntity_getAbout(PhysicalEntity *physical_entity_ptr);

    OMEXMETA_CAPI_EXPORT char *PhysicalEntity_getIdentity(PhysicalEntity *physical_entity_ptr);

    OMEXMETA_CAPI_EXPORT int PhysicalEntity_getNumLocations(PhysicalEntity *physicalEntity);

    OMEXMETA_CAPI_EXPORT char *PhysicalEntity_getLocation(PhysicalEntity *physical_entity_ptr, int index);

    OMEXMETA_CAPI_EXPORT char *PhysicalEntity_str(PhysicalEntity *physical_entity_ptr, const char *format, const char *base_uri);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_hasProperty(PhysicalEntity *physical_entity_ptr, const char *property);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_isPartOf(PhysicalEntity *physical_entity_ptr, const char *is_part_of);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_hasPart(PhysicalEntity *physical_entity_ptr, const char *part);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_about(PhysicalEntity *physical_entity_ptr, const char *about);

/*********************************************************************
 * PhysicalProcess class methods
 */
    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_new(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT int PhysicalProcess_delete(PhysicalProcess *physicalProcess);

    OMEXMETA_CAPI_EXPORT int PhysicalProcess_freeAll(PhysicalProcess *physicalProcess);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_setPhysicalProperty(
            PhysicalProcess *physical_process, const char *subject_metaid, const char *physical_property);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_addSource(
            PhysicalProcess *physical_process, int multiplier,
            const char *physical_entity_reference);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_addSink(
            PhysicalProcess *physical_process, int multiplier,
            const char *physical_entity_reference);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_addMediator(
            PhysicalProcess *physical_process, const char *physical_entity_reference);

    OMEXMETA_CAPI_EXPORT char *
    PhysicalProcess_str(PhysicalProcess *physical_process_ptr, const char *format, const char *base_uri);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_hasProperty(PhysicalProcess *physical_process_ptr, const char *property);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_about(PhysicalProcess *physical_process_ptr, const char *about);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_isVersionOf(PhysicalProcess *physical_process_ptr, const char *version);

/*********************************************************************
 * PhysicalForce class methods
 */
    OMEXMETA_CAPI_EXPORT PhysicalForce *PhysicalForce_new(Editor *editor_ptr);


    /**
         * @brief deletes physical force excluding all
     * nodes associated with it.
     */
    OMEXMETA_CAPI_EXPORT int PhysicalForce_delete(PhysicalForce *physicalForce);

    /**
         * @brief deletes physical force including all
     * nodes associated with it.
     */
    OMEXMETA_CAPI_EXPORT int PhysicalForce_freeAll(PhysicalForce *physical_force_ptr);

    OMEXMETA_CAPI_EXPORT PhysicalForce *PhysicalForce_addSource(
            PhysicalForce *physical_force_ptr, int multiplier,
            const char *physical_entity_reference);

    OMEXMETA_CAPI_EXPORT PhysicalForce *PhysicalForce_addSink(
            PhysicalForce *physical_force_ptr, int multiplier,
            const char *physical_entity_reference);

    OMEXMETA_CAPI_EXPORT PhysicalForce *PhysicalForce_setPhysicalProperty(
            PhysicalForce *physical_force_ptr, const char *subject_metaid, const char *physical_property);

    OMEXMETA_CAPI_EXPORT int PhysicalForce_getNumSources(PhysicalForce *physicalForce);

    OMEXMETA_CAPI_EXPORT int PhysicalForce_getNumSinks(PhysicalForce *physicalForce);

    OMEXMETA_CAPI_EXPORT char *PhysicalForce_str(PhysicalForce *physical_force_ptr, const char *format, const char *base_uri);

    OMEXMETA_CAPI_EXPORT char *PhysicalForce_getAbout(PhysicalForce *physical_force_ptr);

    OMEXMETA_CAPI_EXPORT PhysicalForce *PhysicalForce_hasProperty(PhysicalForce *physical_force_ptr, const char *is_version_of);

    OMEXMETA_CAPI_EXPORT PhysicalForce *PhysicalForce_about(PhysicalForce *physical_force_ptr, const char *about);

/*********************************************************************
 * PersonalInformation class methods
 */

    OMEXMETA_CAPI_EXPORT PersonalInformation *PersonalInformation_new(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT int PersonalInformation_delete(PersonalInformation *information);

    OMEXMETA_CAPI_EXPORT char *PersonalInformation_getLocalUri(PersonalInformation *information);

    OMEXMETA_CAPI_EXPORT int PersonalInformation_setLocalUri(PersonalInformation *information, const char *localUri);

    OMEXMETA_CAPI_EXPORT PersonalInformation *PersonalInformation_addCreator(PersonalInformation *information, const char *value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *PersonalInformation_addName(PersonalInformation *information, const char *value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *PersonalInformation_addMbox(PersonalInformation *information, const char *value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addAccountName(PersonalInformation *information, const char *value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addAccountServiceHomepage(PersonalInformation *information, const char *value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addFoafBlank(PersonalInformation *information, const char *predicate, const char *blank_value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addFoafUri(PersonalInformation *information, const char *predicate, const char *uri_value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addFoafLiteral(PersonalInformation *information, const char *predicate,
                                       const char *literal_value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addFoaf(PersonalInformation *information, const char *predicate, const LibrdfNode &value_node);

    OMEXMETA_CAPI_EXPORT char *PersonalInformation_getMetaid(PersonalInformation *information);

    OMEXMETA_CAPI_EXPORT int PersonalInformation_setMetaid(PersonalInformation *information, const char *metaid);

    OMEXMETA_CAPI_EXPORT char *PersonalInformation_getModelUri(PersonalInformation *information);

    OMEXMETA_CAPI_EXPORT int PersonalInformation_setModelUri(PersonalInformation *information, const char *modelUri);


#ifdef __cplusplus
    }
#endif
}

#endif //LIBOMEXMETA_OMEXMETACAPI_H
























