//
// Created by Ciaran on 4/23/2020.
//


#include "omexmeta/RDF.h"
#include <vector>
#include "gtest/gtest.h"
#include "librdf.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalProcess.h"
#include "omexmeta/Participant.h"
#include "omexmeta/OmexMetaUtils.h"

using namespace omexmeta;

class PhysicalProcessTests : public ::testing::Test {

public:

    LibrdfStorage storage;
    LibrdfModel model;
    std::string model_uri = "http://omex-library.org/NewOmex.omex/NewModel.xml#";
    std::string local_uri = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";

    PhysicalProperty physical_property;

    PhysicalProcessTests() {
        model = LibrdfModel(storage.get());

        physical_property = PhysicalProperty("metaid", "OPB:OPB_00340", model_uri);
    };

    ~PhysicalProcessTests() override {
        model.freeModel();
        storage.freeStorage();
    };
};

TEST_F(PhysicalProcessTests, TestPhysicalProcessSubjectMetaidNode) {
    Subject subject_metaid = Subject::fromRawPtr(LibrdfNode::fromUriString("MetaId004").get());
    std::vector <SourceParticipant> source_participants(
            {SourceParticipant(
                    model.get(),
                    1.0,
                    "#PhysicalEntityReference1", model_uri, local_uri
            )}
    );
    std::vector <SinkParticipant> sink_participants(
            {SinkParticipant(
                    model.get(),
                    1.0,
                    "PhysicalEntityReference2", model_uri, local_uri
            )}
    );
    std::vector <MediatorParticipant> mediator_participants(
            {MediatorParticipant(
                    model.get(),
                    "PhysicalEntityReference3", model_uri, local_uri
            )}
    );

    PhysicalProcess process(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            source_participants,
            sink_participants,
            mediator_participants
    );

    std::string actual = process.getSubjectStr();
    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#metaid";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Without Triple we need to free stuff manually
    //physical_property.free();
    subject_metaid.free();
    source_participants[0].free();
    sink_participants[0].free();
    mediator_participants[0].free();
}


TEST_F(PhysicalProcessTests, TestPhysicalProcessSource) {
    std::vector <SourceParticipant> source_participants(
            {SourceParticipant(
                    model.get(),
                    1.0,
                    "#PhysicalEntityReference1", model_uri, local_uri
            )}
    );
    std::vector <SinkParticipant> sink_participants(
            {SinkParticipant(
                    model.get(),
                    1.0,
                    "PhysicalEntityReference2", model_uri, local_uri
            )}
    );
    std::vector <MediatorParticipant> mediator_participants(
            {MediatorParticipant(
                    model.get(),
                    "PhysicalEntityReference3", model_uri, local_uri
            )}
    );

    PhysicalProcess process(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            source_participants,
            sink_participants,
            mediator_participants
    );

    std::string actual = process.getSources()[0].getSubject();
    std::string expected = "SourceParticipant";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Without Triple we need to free stuff manually
    //physical_property.free();
    source_participants[0].free();
    sink_participants[0].free();
    mediator_participants[0].free();
}


TEST_F(PhysicalProcessTests, TestPhysicalProcessNumTriples) {
    PhysicalProcess process(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            1.0,
                            "#PhysicalEntityReference1", model_uri, local_uri
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(

                            model.get(),
                            1.0,
                            "PhysicalEntityReference2", model_uri, local_uri
                    )}
            ),
            std::vector<MediatorParticipant>(
                    {MediatorParticipant(

                            model.get(),
                            "PhysicalEntityReference3", model_uri, local_uri
                    )}
            )
    );

    Triples triples = process.toTriples();
    std::cout << triples.str() << std::endl;
    int expected = 10;
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
    triples.freeTriples();

}


TEST_F(PhysicalProcessTests, TestPhysicalProcessTrips) {
    PhysicalProcess process(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            1.0,
                            "#PhysicalEntityReference1", model_uri, local_uri
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(
                            model.get(),
                            1.0,
                            "PhysicalEntityReference2", model_uri, local_uri
                    )}
            ),
            std::vector<MediatorParticipant>(
                    {MediatorParticipant(

                            model.get(),
                            "PhysicalEntityReference3", model_uri, local_uri
                    )}
            )
    );
    Triples triples = process.toTriples();

    int expected = 10;
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
    triples.freeTriples();
}

TEST_F(PhysicalProcessTests, TestPhysicalProcessToTriplesStr) {
    LOG_INFO("model uri: %s", model_uri.c_str());
    PhysicalProcess process(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            1.0,
                            "#PhysicalEntityReference1", model_uri, local_uri
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(
                            model.get(),
                            1.0,
                            "PhysicalEntityReference2", model_uri, local_uri
                    )}
            ),
            std::vector<MediatorParticipant>(
                    {MediatorParticipant(
                            model.get(),
                            "PhysicalEntityReference3", model_uri, local_uri
                    )}
            )
    );
    Triples triples = process.toTriples();

    std::string actual = triples.str("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/NewModel.xml#> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "myOMEX:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference myOMEX:PhysicalEntityReference3 .\n"
                           "\n"
                           "myOMEX:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference myOMEX:PhysicalEntityReference2 .\n"
                           "\n"
                           "myOMEX:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference myOMEX:PhysicalEntityReference1 .\n"
                           "\n"
                           "myOMEX:metaid\n"
                           "    bqbiol:isPropertyOf myOMEX:metaid ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> ;\n"
                           "    semsim:hasMediatorParticipant myOMEX:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant myOMEX:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant myOMEX:SourceParticipant0000 .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalProcessTests, TestPhysicalProcessBuilder1) {
    PhysicalProcess process(model.get());
    process.setModelUri(model_uri);
    process.setLocalUri(local_uri);
    process.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2")
            .addMediator("species_metaid2");

    Triples triples = process.toTriples();

    std::string actual = triples.str("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/NewModel.xml#> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "myOMEX:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference myOMEX:species_metaid2 .\n"
                           "\n"
                           "myOMEX:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference myOMEX:species_metaid2 .\n"
                           "\n"
                           "myOMEX:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double, \"2\"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;\n"
                           "    semsim:hasPhysicalEntityReference myOMEX:species_metaid0, myOMEX:species_metaid1 .\n"
                           "\n"
                           "myOMEX:property_metaid_0\n"
                           "    bqbiol:isPropertyOf myOMEX:property_metaid_0 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> ;\n"
                           "    semsim:hasMediatorParticipant myOMEX:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant myOMEX:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant myOMEX:SourceParticipant0000 .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // remember to free the unused physical property from test fixture
    triples.freeTriples();
}

TEST_F(PhysicalProcessTests, TestEquality) {
    PhysicalProcess process1(model.get());
    process1.setModelUri(model_uri);
    process1.setLocalUri(local_uri);
    process1.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2")
            .addMediator( "species_metaid2");

    PhysicalProcess process2(model.get());
    process2.setModelUri(model_uri);
    process2.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2")
            .addMediator( "species_metaid2");
    ASSERT_EQ(process1, process2);
    process1.free();
    process2.free();
}

TEST_F(PhysicalProcessTests, TestInequality) {
    PhysicalProcess process1(model.get());
    process1.setModelUri(model_uri);
    process1.setLocalUri(local_uri);
    process1.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2")
            .addMediator( "species_metaid2");

    PhysicalProcess process2(model.get());
    process2.setModelUri(model_uri);
    process2.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2")
            .addMediator( "species_metaid2");
    ASSERT_NE(process1, process2);

    process1.free();
    process2.free();
}




















