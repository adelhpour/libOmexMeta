# ifndef SEMSIM_COMPOSITE_ANNOTATION_H_
# define SEMSIM_COMPOSITE_ANNOTATION_H_


# include "semsim/AnnotationBase.h"
# include "semsim/PhysicalPropertyResource.h"
# include "semsim/Entity.h"
# include "semsim/SingularAnnotation.h"


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
    /**
     * Composite annotations allow more precise descriptions of model
     * elements than singular ("plain") @ref Annotation "Annotation".
     * Whereas singular annotations specify the *chemical identity* of an SBML
     * species or the *physiological identity* of a CellML variable,
     * composite annotations also provide two additional pieces of information:
     * the @ref PhysicalProperty of an element, which specifies the physical
     * quantity the element represents (e.g. *concentration* or *amount* of an
     * SBML species; *liquid volume* or *electric current* of a CellML variable),
     * and a linear chain of terms (the @ref EntityDescriptor) that describes
     * *what* the element is (e.g. the chemical identity of an SBML species)
     * and *where* it is in the physical world.
     *
     * For example, to describe an SBML species representing the
     * *cytosolic glucose concentration in a pancreatic beta cell*,
     * one would need to specify that the species represents
     * glucose (<a href="https://identifiers.org/CHEBI:17234">CHEBI:17234</a>)
     * inside the cytosolic compartment (<a href="https://identifiers.org/GO:0005829">GO:0005829</a>)
     * of a pancreatic beta cell (<a href="https://identifiers.org/CL:0000169">CL:0000169</a>).
     * The following code snippet illustrates how to construct a @ref CompositeAnnotation
     * for this example:
     *
     * @code{.cpp}
     * // this example assumes you are using C++11 mode
     * // (controlled by the SEMSIM_CXX_STANDARD CMake variable)
     * @endcode
     */
    class  CompositeAnnotation : public AnnotationBase {
    public:
        /**
         * Construct a @ref CompositeAnnotation given a physical property (what is the quantity being represented - chemical concentration, fluid volume, etc.?)
         * and a domain descriptor ("what" is the chemical identity and "where" does the entity reside in physical space?)
         * @param property The physical property of this composite annotation. Always provided.
         * @param entity The entity contains all information outside of the physical property. This tells you "what" the element is (e.g. by specifying chemical identity) and "where". For example, if the annotation describes "cytosolic glucose concentration in a pancreatic beta cell", the entity would contain a definition (glycose) and two *structural relations* specifying the entity is *occurs in* the cytosol, which in turn *is part of* a pancreatic beta cell.
         */
        CompositeAnnotation(std::string &metaid, PhysicalProperty &property, Entity &entity)
                : metaid_(metaid), property_(property), entity_(entity) {}

        /**
         * Construct a @ref CompositeAnnotation given a physical property (what is the quantity being represented - chemical concentration, fluid volume, etc.?)
         * and a domain descriptor ("what" is the chemical identity and "where" does the entity reside in physical space?)
         * @param property The physical property of this composite annotation. Always provided.
         * @param entity The entity contains all information outside of the physical property. This tells you "what" the element is (e.g. by specifying chemical identity) and "where". For example, if the annotation describes "cytosolic glucose concentration in a pancreatic beta cell", the entity would contain a definition (glycose) and two *structural relations* specifying the entity is *occurs in* the cytosol, which in turn *is part of* a pancreatic beta cell.
         */
        CompositeAnnotation(std::string &metaid, PhysicalProperty &&property, Entity &&entity)
                : metaid_(metaid), property_(std::move(property)), entity_(std::move(entity)) {}

        /// Copy constructor
        CompositeAnnotation(CompositeAnnotation &other)
                : metaid_(other.metaid_), property_(other.property_), entity_(other.entity_) {}

        /// Move constructor
        CompositeAnnotation(CompositeAnnotation &&other)
                : metaid_(std::move(other.metaid_)), property_(std::move(other.property_)),
                  entity_(std::move(other.entity_)) {}

        /**
         * Construct from a singular annotation.
         * Copy all definitions and terms.
         * @param other The singular annotation to copy.
         * @param property The physical property to assign to the composite annotation.
         * @param
         */
        CompositeAnnotation(SingularAnnotation &other, PhysicalProperty &property)
                : metaid_(other.getMetaId()), property_(property), entity_(other) {
            entity_.setMetaId(metaid_);
        }

        /**
         * This function returns @p true if the @ref Entity element of this composite annotation is empty.
         * The entity describes "what" the model element is and "where"
         * the it is located.
         * IGNORE:
         * It is typically empty for
         * annotations read in from SBML models, since SBML has
         * no way of expressing the "where" part of a composite annotation.
         * However, if the SBML entity is a **species** that resides in
         * a **compartment**, SemSim may automatically insert a domain
         * descriptor encoding the species/compartment relationship (
         * and this function will return false).
         * @return Whether the physical domain descriptor is empty.
         */
        bool isEntityEmpty()  {
            return entity_.isEmpty();
        }

        /**
         * @return The @ref EntityDescriptor describing the physical entity of this annotation.
         */
         Entity &getEntity()  {
            return entity_;
        }

        /**
         * @return The @ref EntityDescriptor describing the physical entity of this annotation.
         */
        Entity &getEntity() {
            return entity_;
        }

        /**
         * Shortcut for adding a descriptor term to the last entity descriptor
         * (often, there is just one entity descriptor).
         * Create a new @ref EntityDescriptor if none exist.
         * @param relation The relation that the new term should use.
         * @param resource The resource that the term should point to.
         */
        void addTerm(Relation &relation, Resource &resource) {
            if (getEntity().getNumDescriptors() < 1)
                getEntity().addDescriptor(EntityDescriptor());
            getEntity().getDescriptors().back().addTerm(relation, resource);
        }


        /// Create a copy of this object using the correct derived class's type.
        AnnotationBase *clone() override {
            return new CompositeAnnotation(*this);
        }

        /**
         * Serialize this annotation to RDF using the Raptor library.
         * The RDF serialization format is chosen when initializing the
         * @c raptor_serializer, and must be done before calling this function.
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         */
        void serializeToRDF(Url &sbml_base_uri, raptor_world *world, raptor_serializer *serializer)   {
            entity_.serializeToRDF(sbml_base_uri, world, serializer);
            serializePhysicalPropertyToRDF(sbml_base_uri, world, serializer);
        }

        std::string getRDF(Url &sbml_base_uri,  std::string &format = "rdfxml")  {
            raptor_world *world = raptor_new_world();
            raptor_serializer *serializer = raptor_new_serializer(world, format.c_str());
            if (!serializer)
                throw std::runtime_error("Could not create Raptor serializer for format " + format);

            raptor_uri *base_uri = raptor_new_uri(world, ( unsigned char *) "");

            raptor_serializer_set_namespace(serializer,
                                            raptor_new_uri(world, ( unsigned char *) bqb::root.c_str()),
                                            ( unsigned char *) "bqb");
            raptor_serializer_set_namespace(serializer,
                                            raptor_new_uri(world, ( unsigned char *) semsim::root.c_str()),
                                            ( unsigned char *) "semsim");

            void *output;
            size_t length;
            raptor_serializer_start_to_string(serializer, base_uri, &output, &length);

            serializeToRDF(sbml_base_uri, world, serializer);

            raptor_serializer_serialize_end(serializer);

            raptor_free_serializer(serializer);
            raptor_free_world(world);

            std::string result((char *) output);
            free(output);
            return result;
        }

        /**
         * @return the Url for this element (usually a local identifier).
         */
         std::string &getMetaId()  override {
            return metaid_;
        }

        /**
         * Set the meta id for this annotation.
         * @param metaid The meta id.
         */
        void setMetaId( std::string &metaid) {
            metaid_ = metaid;
        }

        /**
         * Convert singular annotations to composite annotations
         * by copying their definitions and terms.
         * Effect when called on an instance of @ref CompositeAnnotation
         * is to create a clone.
         * @return A new composite annotation
         */
         // todo why does this function have unused parameter?
        AnnotationPtr makeComposite(PhysicalProperty &prop) override {
            return AnnotationPtr(clone());
        }
        //todo Why on earth would this function take a parameter that is unused???
        // Is this a result of inappropriate inheritance?

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        std::string humanize()  override {
            return property_.humanize() + " -> (isPropertyOf) -> " + "#" + metaid_ + entity_.humanize();
        }

        bool isComposite()  override {
            return true;
        }

    protected:
        virtual void serializePhysicalPropertyToRDF(Url &sbml_base_uri, raptor_world *world,
                                                    raptor_serializer *serializer)  {
             Url &phys_prop_uri = sbml_base_uri.fragment(metaid_ + "_property");
             Url &phys_prop_def = property_.getResource().getURI();
            Url entity_uri = entity_.getURI(sbml_base_uri);

            // serialize physical property definition
            SerializeURIStatement(phys_prop_uri.str(), bqb::isVersionOf.getURI().str(), phys_prop_def.str(),
                                  world, serializer);

            // serialize physical property to entity linkage
            SerializeURIStatement(phys_prop_uri.str(), bqb::isPropertyOf.getURI().str(), entity_uri.str(),
                                  world, serializer);
        }

        /// Stores the Url of this element (usu. a local identifier)
        std::string metaid_;
        /// Stores the physical property for this annotation
        PhysicalProperty property_;
        /// Stores the physical domain descriptor for this annotation
        Entity entity_;
    };
}

# endif