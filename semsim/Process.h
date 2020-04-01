# ifndef SEMSIM_PROCESS_H_
# define SEMSIM_PROCESS_H_


# include "semsim/Component.h"
# include "semsim/Participant.h"
# include "semsim/Source.h"
# include "semsim/Sink.h"
# include "semsim/Mediator.h"
# include "semsim/RaptorUtils.h"

# include <string>

namespace semsim {

    /**
     * A @ref Process is a component that represents a physical process.
     * It has sources and sinks, as well as its own annotation element.
     */
    class  Process : public Component {
    protected:
        /// Container for sources, treat as opaque
        typedef std::vector<Source> Sources;
        /// Container for sinks, treat as opaque
        typedef std::vector<Sink> Sinks;
        /// Container for mediators, treat as opaque
        typedef std::vector<Mediator> Mediators;

    public:
        /// Empty constructor
        Process() {}

        /// Construct from a singular annotation
        Process(SingularAnnotation &annotation)
                : Component(annotation) {}

        /// Move-construct from a singular annotation
        Process(SingularAnnotation &&annotation)
                : Component(std::move(annotation)) {}

        /// Construct from a composite annotation
        Process(const CompositeAnnotation &annotation)
                : Component(annotation) {}

        /// Move-construct from a composite annotation
        Process(CompositeAnnotation &&annotation)
                : Component(std::move(annotation)) {}

        Process(const Process &other)
                : Component(other) {
            for (Sources::const_iterator i = other.sources_.begin(); i != other.sources_.end(); ++i)
                sources_.push_back(*i);
            for (Sinks::const_iterator i = other.sinks_.begin(); i != other.sinks_.end(); ++i)
                sinks_.push_back(*i);
            for (Mediators::const_iterator i = other.mediators_.begin(); i != other.mediators_.end(); ++i)
                mediators_.push_back(*i);
        }

# if __cplusplus >= 201103L

        /// Move-construct from a component
        Process(Process &&other)
                : Component(std::move(other)), sources_(std::move(other.sources_)), sinks_(std::move(other.sinks_)) {}

# endif

        /// Create a copy of this physical process
        virtual Component *clone() const {
            return new Process(*this);
        }

        /**
         * Add a new @ref Source to the physical process.
         * @param source The @ref Source to add.
         */
        void addSource(const Source &source) {
            sources_.push_back(source);
        }

        /**
         * Add a new @ref Source to the physical process.
         * @param source The @ref Source to add.
         */
        void addSink(const Sink &sink) {
            sinks_.push_back(sink);
        }

        /**
         * Add a new @ref Mediator to the physical process.
         * @param source The @ref Source to add.
         */
        void addMediator(const Mediator &mediator) {
            mediators_.push_back(mediator);
        }


        /**
         * Serialize this process to RDF using the Raptor library.
         * @param sbml_base_uri   The base Url of the SBML document relative to this (e.g. a relative path in a COMBINE archive).
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         * @return the Url for this entity.
         */
        virtual void serializeToRDF(Url &sbml_base_uri, raptor_world *world, raptor_serializer *serializer) const {
            getAnnotation().serializeToRDF(sbml_base_uri, world, serializer);
            Url this_uri = getURI(sbml_base_uri);

            // serialize the participants
            for (Sources::const_iterator i = sources_.begin(); i != sources_.end(); ++i) {
                Url participant_uri = i->serializeToRDF(sbml_base_uri, world, serializer);

                SerializeURIStatement(this_uri.str(), semsim::hasSourceParticipant.getURI().str(),
                                      participant_uri.str(), world, serializer);
            }
            for (Sinks::const_iterator i = sinks_.begin(); i != sinks_.end(); ++i) {
                Url participant_uri = i->serializeToRDF(sbml_base_uri, world, serializer);

                SerializeURIStatement(this_uri.str(), semsim::hasSinkParticipant.getURI().str(),
                                      participant_uri.str(), world, serializer);
            }
            for (Mediators::const_iterator i = mediators_.begin(); i != mediators_.end(); ++i) {
                Url participant_uri = i->serializeToRDF(sbml_base_uri, world, serializer);

                SerializeURIStatement(this_uri.str(), semsim::hasMediatorParticipant.getURI().str(),
                                      participant_uri.str(), world, serializer);
            }
        }

        virtual bool isProcess() const {
            return true;
        }

        virtual bool containsMetaId(const std::string &metaid) const {
            if (metaid_ == metaid)
                return true;
            else {
                for (Sources::const_iterator i = sources_.begin(); i != sources_.end(); ++i)
                    if (i->containsMetaId(metaid))
                        return true;
                for (Sinks::const_iterator i = sinks_.begin(); i != sinks_.end(); ++i)
                    if (i->containsMetaId(metaid))
                        return true;
                for (Mediators::const_iterator i = mediators_.begin(); i != mediators_.end(); ++i)
                    if (i->containsMetaId(metaid))
                        return true;
            }
            return false;
        }

    protected:
        Sources sources_;
        Sinks sinks_;
        Mediators mediators_;
    };

}

# endif
