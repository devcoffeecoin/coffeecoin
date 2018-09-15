// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2015-2017 The ALQO developers
// Copyright (c) 2018 The COFFEECOIN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>


using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"
#include "test/bignum.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
	(0, uint256("0x"))
        (0, uint256("0x"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    0, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    0        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    0,
    0,
    0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0,
    0,
    0};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xba;
        pchMessageStart[1] = 0xcb;
        pchMessageStart[2] = 0xf7;
        pchMessageStart[3] = 0xb9;
        vAlertPubKey = ParseHex("04baf13c6e32fad837647750c8de6a2a097b0d683c345fd0e43fe1f11da8dd530f6df0cdbe3406477bb9bf84bdc3c90c29d44ec51d3f9eb8ab42a96e2a51e40ab3");
        nDefaultPort = 6366;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // COFFEECOIN starting difficulty is 1 / 2^12  //20
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // COFFEECOIN: 1 day
        nTargetSpacing = 2 * 60;  // COFFEECOIN: 2 minute
        nLastPOWBlock = 262800;
        nMaturity = 100;
        nMasternodeCountDrift = 20;
	    nMasternodeColleteralLimxDev = 1000; //Params().MasternodeColleteralLimxDev()
        nModifierUpdateBlock = 1; // we use the version 2 for dmd
        nMaxMoneyOut = MAX_MONEY;

        const char* pszTimestamp = "This is genesis block for CoffeeCoin network";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0472d331be8b1028a38297e62298a618095d19529f17617ab39c63c39c8a1761838d422ec12e52b976a8668794b82127b6aff491b656b5798bf7d1c75d54fda4c8") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1537038000;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 13263844;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000005ab84a70088d38980288d0f3d5ba8a540c7de30a0526c8889fedfce7e43"));
        assert(genesis.hashMerkleRoot == uint256("0x28f97cf4a7c3ffdd1d76f514d09b822c99eb5bd0e45ac37684eddba46c3bb6d6"));

        vSeeds.push_back(CDNSSeedData("seed1", "seed1.coffeecoin.store"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.coffeecoin.store"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.coffeecoin.store"));

        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "045bf6c9b2e4ef90ebe1fc3a4ac5749ee410dacbbe7e98c4f45f65f01b5af50c8d3b66c9178f8eaa346d0f58c1961fd6f37c77388d5a9f79f07209b2987effd3e4";
        strDarksendPoolDummyAddress = "GNEZjVTQHjff8BoWvUhGMSg9KZA7QNEwUm";
        nStartMasternodePayments = 1536996200; //
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0xf4;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xe4;
        vAlertPubKey = ParseHex("04e4164fd806bb712c2a2dde464be3b1e8edee7a4f4d08319b147d162c7f3ed6df346cc276047da90de44f24539f076c30c4f550d625e98874137ce1aeb1a728cd");
        nDefaultPort = 6367;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // COFFEECOIN: 1 day
        nTargetSpacing = 2 * 60;  // COFFEECOIN: 1 minute
        nLastPOWBlock = 262800;
        nMaturity = 15;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = MAX_MONEY;

        genesis.nTime = 1537038200;
        genesis.nNonce = 11185861;

        hashGenesisBlock = genesis.GetHash();


        assert(hashGenesisBlock == uint256("0x000009c0bb5ac9f41fb70af857b7726664152162020fd5b85029f8df88505196"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.coffeecoin.store"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.coffeecoin.store"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.coffeecoin.store"));
		
	    base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 87);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 195);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x81)(0x62)(0xa1).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x81)(0x59)(0x38).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x01)(0x01)(0x02).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));


        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "044a139678fc890a247aa5fe560f83a35a6688d3723c541d9b686626b7efb55a14ed497d47dba14457159fc4386406a9006a95f9dfb5b46ae3fb11ede77696396f";
        strDarksendPoolDummyAddress = "";
        nStartMasternodePayments = 1562531573;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0xd4;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x64;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // COFFEECOIN: 1 day
        nTargetSpacing = 1 * 60;        // COFFEECOIN: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1537038400;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 7617416;
		
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 6368;

        assert(hashGenesisBlock == uint256("0x000005ab84a70088d38980288d0f3d5ba8a540c7de30a0526c8889fedfce7e43"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
