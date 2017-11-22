// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Onex Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"
#include <stdio.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}


static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Onex Cash Genesis Block mined by Onex Cash Team";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 394200; // one year
        consensus.nMasternodePaymentsStartBlock = 10080; // tow week /1.5
        consensus.nMasternodePaymentsIncreaseBlock = 158000; // not used
        consensus.nMasternodePaymentsIncreasePeriod = 576*30; // not used
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 2100000000; // year 10000+
        consensus.nBudgetPaymentsCycleBlocks = 16616;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 2100000000; // year 10000+
        consensus.nSuperblockCycle = 16616;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 227931; // FIX
        consensus.BIP34Hash = uint256S("0x000000000000024b89b42a942fe0d9fea3bb44ab7bd1b19115dd6a759c0808b8"); // FIX
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan =  40 * 1.5 * 60; // Onex: 1 hour, 45 blocks
        consensus.nPowTargetSpacing =  1.5 * 60;      // Onex: 90 seconds
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1502280000; // Aug 9th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1533816000; // Aug 9th, 2018

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x1b;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0x4b;
        vAlertPubKey = ParseHex("040dffb6f5de41d01b2f6da8d5048d57c63cdf91051b6204f30b75f7183b88bca4746b754ce8e3573ce30a2c54ff9e7d318b1807249f8dd781d1ec470c800ad42b");
        nDefaultPort = 18291;
        nMaxTipAge = 6 * 60 * 60; // ~270 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1510444800, 240798, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //printf("block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x00000ee3a55532114881619e15da9dac3bb73f2875b2dc775106d2d37478cdeb"));
        assert(genesis.hashMerkleRoot     == uint256S("0x991548dbdcf66408146039b1309cd39b439e54ddfccd4008556944397a8803e6"));

        vSeeds.push_back(CDNSSeedData("onex.cash", "seed1.onex.cash"));
        vSeeds.push_back(CDNSSeedData("onex.cash", "seed2.onex.cash"));
        vSeeds.push_back(CDNSSeedData("onex.cash", "seed3.onex.cash"));
        vSeeds.push_back(CDNSSeedData("onex.cash", "seed4.onex.cash"));

        // Onex addresses start with 'X'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,75);
        // Onex script addresses start with '5'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,0);
        // Onex private keys start with '5' or 'X' (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,75);
        // Onex BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Onex BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Onex BIP44 coin type is '5'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "0481869ed71446c6ce9036dab7b7375501e61a45c884723e81e7fb8fdd1b730b6dbf4fe764442c38fdd8ea1c2f1a8581478db59783219a3a873b0a9a954889e951";
        strMasternodePaymentsPubKey = "048615e041d52773052482df9bd081192234f1fba583e4d4781a85ee9f0f5af0a606fd6990f6edbdb0cb149673a7197d7e758282ffe901189677ba68134810ca0f";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (    0, uint256S("0x00000ee3a55532114881619e15da9dac3bb73f2875b2dc775106d2d37478cdeb"))
            (   33, uint256S("0x00000b4792fdd8f5e7435984fb0f9fbd31f3284ba6d182ff0fb226c1b0c14d1c"))
            (  198, uint256S("0x000000378db684ba7ed54ea9442192877e265a533cdf87bc6094e98021aa000f"))
            (  897, uint256S("0x0000000004dda89ffa5dc6bc50478a12db416b054c9040101a3182294c7835e8"))
            ( 1018, uint256S("0x0000000006b794f31ffb74e1ba593050f82c040839107fe37ef1016f51d8916b"))
            ( 1541, uint256S("0x0000000001864de05d6ef3ec744fdb008b2072b5122ddcefd72db16af3fb872b"))
            ( 1756, uint256S("0x0000000005559d698cc173c5a46684888ecb90ce9d2b8b591e76cc8fb19508b1"))
            ( 1989, uint256S("0x00000000027fd98e6761ef76ca5312272304d6882c9b1f82a2edd5be3ba66472")),
            1510643344, // * UNIX timestamp of last checkpoint block
            0,          // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            2800        // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 262800;
        consensus.nMasternodePaymentsStartBlock = 10000; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 46000;
        consensus.nMasternodePaymentsIncreasePeriod = 576;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 2100000000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 2100000000; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 21111; // FIX
        consensus.BIP34Hash = uint256S("0x0000000023b3a96d3484e5abb3755c413e7d41500f8e2a5c3f0dd01299cd8ef8"); // FIX
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 60 * 60; // Onex: 1 hour
        consensus.nPowTargetSpacing = 2 * 60;   // Onex: 1 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1502280000; // Aug 9th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1533816000; // Aug 9th, 2018

        pchMessageStart[0] = 0x1c;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0x4b;
        vAlertPubKey = ParseHex("04560e810aa354c07e84467095ea58fb1838e754bd63fdc078774184833e0d8f2834a709602a4b49655fc54668454b61c2e59ea5b4f43f3615fcf74f95b7baf7cc");

        nDefaultPort = 28291;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1510444800, 240798, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //printf("block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x00000ee3a55532114881619e15da9dac3bb73f2875b2dc775106d2d37478cdeb"));
        assert(genesis.hashMerkleRoot     == uint256S("0x991548dbdcf66408146039b1309cd39b439e54ddfccd4008556944397a8803e6"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("onex.cash",  "testnet.onex.cash"));

        // Testnet Onex addresses start with 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
        // Testnet Onex script addresses start with '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,20);
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults) (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        // Testnet Onex BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Onex BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet Onex BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "0481869ed71446c6ce9036dab7b7375501e61a45c884723e81e7fb8fdd1b730b6dbf4fe764442c38fdd8ea1c2f1a8581478db59783219a3a873b0a9a954889e951";
        strMasternodePaymentsPubKey = "048615e041d52773052482df9bd081192234f1fba583e4d4781a85ee9f0f5af0a606fd6990f6edbdb0cb149673a7197d7e758282ffe901189677ba68134810ca0f";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x00000ee3a55532114881619e15da9dac3bb73f2875b2dc775106d2d37478cdeb")),
            1510444800, // * UNIX timestamp of last checkpoint block
            0,          // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            500         // * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMasternodePaymentsStartBlock = 240;
        consensus.nMasternodePaymentsIncreaseBlock = 350;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1500;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 60 * 60; // Onex: 1 hour
        consensus.nPowTargetSpacing = 2 * 60; // Onex: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;

        pchMessageStart[0] = 0x1d;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0x4b;
        nMaxTipAge = 12 * 60 * 60;
        nDefaultPort = 38291;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1510444800, 240798, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //printf("block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x00000ee3a55532114881619e15da9dac3bb73f2875b2dc775106d2d37478cdeb"));
        assert(genesis.hashMerkleRoot     == uint256S("0x991548dbdcf66408146039b1309cd39b439e54ddfccd4008556944397a8803e6"));


        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x00000ee3a55532114881619e15da9dac3bb73f2875b2dc775106d2d37478cdeb")),
            0,
            0,
            0
        };
        // Regtest Onex addresses start with 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
        // Regtest Onex script addresses start with '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,20);
        // Regtest private keys start with '9' or 'c' (Bitcoin defaults) (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        // Regtest Onex BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Onex BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Regtest Onex BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
