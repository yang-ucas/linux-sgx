/*############################################################################
  # Copyright 2016-2017 Intel Corporation
  #
  # Licensed under the Apache License, Version 2.0 (the "License");
  # you may not use this file except in compliance with the License.
  # You may obtain a copy of the License at
  #
  #     http://www.apache.org/licenses/LICENSE-2.0
  #
  # Unless required by applicable law or agreed to in writing, software
  # distributed under the License is distributed on an "AS IS" BASIS,
  # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  # See the License for the specific language governing permissions and
  # limitations under the License.
  ############################################################################*/

/*!
 * \file
 * \brief native type validation unit tests.
 *
 * \warning to run the tests in this file you must build a non-shared mode.
 */

#ifndef SHARED

#include <cstring>
#include <vector>

#include "epid/common-testhelper/epid_gtest-testhelper.h"
#include "epid/member/tiny/unittests/member-testhelper.h"
#include "gtest/gtest.h"

extern "C" {
#include "epid/common/types.h"
#include "epid/member/tiny/math/pairing.h"
#include "epid/member/tiny/src/native_types.h"
#include "epid/member/tiny/src/validate.h"
}

namespace {
//////////////////////////////////////////////////////////////////////////
// GroupPubKeyIsInRange Tests
TEST_F(EpidMemberTest, GroupPubKeyIsInRangePasses) {
  NativeGroupPubKey const input = {
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x01},  // group id
      {{{{0xb580e099, 0x434c62fd, 0x64cee3ce, 0xd06d8f9d, 0x7e27b0cb,
          0x3d753d61, 0xe21b17eb, 0xb36fff81}}},
       {{{0x74f459ee, 0xd8693ea1, 0x82457e7f, 0xee3d6642, 0xe94dae9c,
          0xfdb5b79d, 0xe08859a4, 0x3a075680}}}},  // h1
      {{{{0xbcdd7fe1, 0x29666163, 0xd55ba704, 0xdc99ed42, 0x5474107b,
          0xd5dbca1c, 0x63c2518e, 0xd2742e9f}}},
       {{{0xe78e1084, 0x93a56ecc, 0xde4ceacb, 0xda3f517d, 0xe85b087b,
          0x48120aa6, 0xe314ac72, 0x765dc06e}}}},  // h2
      {{{{{0x0728e896, 0x8dcd3688, 0x6a95cac6, 0x788753f6, 0x401ba5b6,
           0x50719451, 0xe20fca1c, 0xbd195a95}}},
        {{{0xe2f4b3a1, 0x22d9fde0, 0x0f6c56f5, 0x2414cfd1, 0x15d775f8,
           0xa6657a68, 0xb86ae7e5, 0xca78115b}}}},
       {{{{0x57e4f33c, 0x0a3b5896, 0x89c2399c, 0x898846dd, 0x5deef56a,
           0xbc077230, 0xe8b3c725, 0x9021a7e0}}},
        {{{0xee1140a9, 0x837d3e31, 0x8e25c6ad, 0xba6bf0da, 0x1f3deaa2,
           0x5d0a88db, 0x1bb6f705, 0x79516936}}}}}};
  EXPECT_TRUE(GroupPubKeyIsInRange(&input));
}

TEST_F(EpidMemberTest, GroupPubKeyIsInRangeFails) {
  NativeGroupPubKey const input = {
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x01},  // group id
      {{{{0xAED33013, 0xD3292DDB, 0x12980A82, 0x0CDC65FB, 0xEE71A49F,
          0x46E5F25E, 0xFFFCF0CD, 0xFFFFFFFF}}},  //< q
       {{{0x74f459ee, 0xd8693ea1, 0x82457e7f, 0xee3d6642, 0xe94dae9c,
          0xfdb5b79d, 0xe08859a4, 0x3a075680}}}},  // h1
      {{{{0xbcdd7fe1, 0x29666163, 0xd55ba704, 0xdc99ed42, 0x5474107b,
          0xd5dbca1c, 0x63c2518e, 0xd2742e9f}}},
       {{{0xe78e1084, 0x93a56ecc, 0xde4ceacb, 0xda3f517d, 0xe85b087b,
          0x48120aa6, 0xe314ac72, 0x765dc06e}}}},  // h2
      {{{{{0x0728e896, 0x8dcd3688, 0x6a95cac6, 0x788753f6, 0x401ba5b6,
           0x50719451, 0xe20fca1c, 0xbd195a95}}},
        {{{0xe2f4b3a1, 0x22d9fde0, 0x0f6c56f5, 0x2414cfd1, 0x15d775f8,
           0xa6657a68, 0xb86ae7e5, 0xca78115b}}}},
       {{{{0x57e4f33c, 0x0a3b5896, 0x89c2399c, 0x898846dd, 0x5deef56a,
           0xbc077230, 0xe8b3c725, 0x9021a7e0}}},
        {{{0xee1140a9, 0x837d3e31, 0x8e25c6ad, 0xba6bf0da, 0x1f3deaa2,
           0x5d0a88db, 0x1bb6f705, 0x79516936}}}}}};
  EXPECT_FALSE(GroupPubKeyIsInRange(&input));
}

//////////////////////////////////////////////////////////////////////////
// MembershipCredentialIsInRange Tests
TEST_F(EpidMemberTest, MembershipCredentialIsInRangePasses) {
  NativeMembershipCredential const input = {
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x01},  // group id
      {{{{0x196254db, 0x570890e8, 0xdaf296ec, 0x87683f4e, 0xeb4caf8a,
          0xacbfdd77, 0xf468e15f, 0x46c969ee}}},
       {{{0x82803777, 0x16249880, 0xffa64ba8, 0xae43de62, 0x0acf364f,
          0x9a1b8aad, 0x91e4a81d, 0x1e522316}}}},  // A
      {0x1372c377, 0x00147c6b, 0x46ddb71b, 0xd09db9e4, 0x5a611086, 0x105eafd8,
       0xa1e0d7df, 0x0a30ae43}  // x
  };
  EXPECT_TRUE(MembershipCredentialIsInRange(&input));
}

TEST_F(EpidMemberTest, MembershipCredentialIsInRangeFails) {
  NativeMembershipCredential const input = {
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x01},  // group id
      {{{{0xAED33013, 0xD3292DDB, 0x12980A82, 0x0CDC65FB, 0xEE71A49F,
          0x46E5F25E, 0xFFFCF0CD, 0xFFFFFFFF}}},  //< q
       {{{0x82803777, 0x16249880, 0xffa64ba8, 0xae43de62, 0x0acf364f,
          0x9a1b8aad, 0x91e4a81d, 0x1e522316}}}},  // A
      {0x1372c377, 0x00147c6b, 0x46ddb71b, 0xd09db9e4, 0x5a611086, 0x105eafd8,
       0xa1e0d7df, 0x0a30ae43}  // x
  };
  EXPECT_FALSE(MembershipCredentialIsInRange(&input));
}

//////////////////////////////////////////////////////////////////////////
// MembershipCredentialIsInGroup Tests
TEST_F(EpidMemberTest, MembershipCredentialIsInGroupPasses) {
  PairingState pairing_state;
  PairingInit(&pairing_state);
  NativeMembershipCredential const input = {
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x01},  // group id
      {{{{0x196254db, 0x570890e8, 0xdaf296ec, 0x87683f4e, 0xeb4caf8a,
          0xacbfdd77, 0xf468e15f, 0x46c969ee}}},
       {{{0x82803777, 0x16249880, 0xffa64ba8, 0xae43de62, 0x0acf364f,
          0x9a1b8aad, 0x91e4a81d, 0x1e522316}}}},  // A
      {0x1372c377, 0x00147c6b, 0x46ddb71b, 0xd09db9e4, 0x5a611086, 0x105eafd8,
       0xa1e0d7df, 0x0a30ae43}  // x
  };
  FpElem const f = {0x636131c7, 0x362d4135, 0xa707879b, 0xa16567fd,
                    0xe07cc68e, 0x05d64356, 0x6d47090b, 0x4840b56c};  // f
  NativeGroupPubKey const pubkey = {
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x01},  // group id
      {{{{0xb580e099, 0x434c62fd, 0x64cee3ce, 0xd06d8f9d, 0x7e27b0cb,
          0x3d753d61, 0xe21b17eb, 0xb36fff81}}},
       {{{0x74f459ee, 0xd8693ea1, 0x82457e7f, 0xee3d6642, 0xe94dae9c,
          0xfdb5b79d, 0xe08859a4, 0x3a075680}}}},  // h1
      {{{{0xbcdd7fe1, 0x29666163, 0xd55ba704, 0xdc99ed42, 0x5474107b,
          0xd5dbca1c, 0x63c2518e, 0xd2742e9f}}},
       {{{0xe78e1084, 0x93a56ecc, 0xde4ceacb, 0xda3f517d, 0xe85b087b,
          0x48120aa6, 0xe314ac72, 0x765dc06e}}}},  // h2
      {{{{{0x0728e896, 0x8dcd3688, 0x6a95cac6, 0x788753f6, 0x401ba5b6,
           0x50719451, 0xe20fca1c, 0xbd195a95}}},
        {{{0xe2f4b3a1, 0x22d9fde0, 0x0f6c56f5, 0x2414cfd1, 0x15d775f8,
           0xa6657a68, 0xb86ae7e5, 0xca78115b}}}},
       {{{{0x57e4f33c, 0x0a3b5896, 0x89c2399c, 0x898846dd, 0x5deef56a,
           0xbc077230, 0xe8b3c725, 0x9021a7e0}}},
        {{{0xee1140a9, 0x837d3e31, 0x8e25c6ad, 0xba6bf0da, 0x1f3deaa2,
           0x5d0a88db, 0x1bb6f705, 0x79516936}}}}}};
  EXPECT_TRUE(
      MembershipCredentialIsInGroup(&input, &f, &pubkey, &pairing_state));
}

TEST_F(EpidMemberTest, MembershipCredentialIsInGroupFails) {
  PairingState pairing_state;
  PairingInit(&pairing_state);
  NativeMembershipCredential const input = {
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x02},  // group id
      {{{{0x196254db, 0x570890e8, 0xdaf296ec, 0x87683f4e, 0xeb4caf8a,
          0xacbfdd77, 0xf468e15f, 0x46c969ee}}},
       {{{0x82803777, 0x16249880, 0xffa64ba8, 0xae43de62, 0x0acf364f,
          0x9a1b8aad, 0x91e4a81d, 0x1e522316}}}},  // A
      {0x1372c377, 0x00147c6b, 0x46ddb71b, 0xd09db9e4, 0x5a611086, 0x105eafd8,
       0xa1e0d7df, 0x0a30ae43}  // x
  };
  FpElem const f = {0x636131c7, 0x362d4135, 0xa707879b, 0xa16567fd,
                    0xe07cc68e, 0x05d64356, 0x6d47090b, 0x4840b56c};  // f
  NativeGroupPubKey const pubkey = {
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x01},  // group id
      {{{{0xb580e099, 0x434c62fd, 0x64cee3ce, 0xd06d8f9d, 0x7e27b0cb,
          0x3d753d61, 0xe21b17eb, 0xb36fff81}}},
       {{{0x74f459ee, 0xd8693ea1, 0x82457e7f, 0xee3d6642, 0xe94dae9c,
          0xfdb5b79d, 0xe08859a4, 0x3a075680}}}},  // h1
      {{{{0xbcdd7fe1, 0x29666163, 0xd55ba704, 0xdc99ed42, 0x5474107b,
          0xd5dbca1c, 0x63c2518e, 0xd2742e9f}}},
       {{{0xe78e1084, 0x93a56ecc, 0xde4ceacb, 0xda3f517d, 0xe85b087b,
          0x48120aa6, 0xe314ac72, 0x765dc06e}}}},  // h2
      {{{{{0x0728e896, 0x8dcd3688, 0x6a95cac6, 0x788753f6, 0x401ba5b6,
           0x50719451, 0xe20fca1c, 0xbd195a95}}},
        {{{0xe2f4b3a1, 0x22d9fde0, 0x0f6c56f5, 0x2414cfd1, 0x15d775f8,
           0xa6657a68, 0xb86ae7e5, 0xca78115b}}}},
       {{{{0x57e4f33c, 0x0a3b5896, 0x89c2399c, 0x898846dd, 0x5deef56a,
           0xbc077230, 0xe8b3c725, 0x9021a7e0}}},
        {{{0xee1140a9, 0x837d3e31, 0x8e25c6ad, 0xba6bf0da, 0x1f3deaa2,
           0x5d0a88db, 0x1bb6f705, 0x79516936}}}}}};
  EXPECT_FALSE(
      MembershipCredentialIsInGroup(&input, &f, &pubkey, &pairing_state));
}

//////////////////////////////////////////////////////////////////////////
// PrivKeyIsInRange Tests
TEST_F(EpidMemberTest, PrivKeyIsInRangePasses) {
  NativePrivKey const input = {
      {
          {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x01},  // group id
          {{{{0x196254db, 0x570890e8, 0xdaf296ec, 0x87683f4e, 0xeb4caf8a,
              0xacbfdd77, 0xf468e15f, 0x46c969ee}}},
           {{{0x82803777, 0x16249880, 0xffa64ba8, 0xae43de62, 0x0acf364f,
              0x9a1b8aad, 0x91e4a81d, 0x1e522316}}}},  // A
          {0x1372c377, 0x00147c6b, 0x46ddb71b, 0xd09db9e4, 0x5a611086,
           0x105eafd8, 0xa1e0d7df, 0x0a30ae43}  // x
      },
      {0x636131c7, 0x362d4135, 0xa707879b, 0xa16567fd, 0xe07cc68e, 0x05d64356,
       0x6d47090b, 0x4840b56c}  // f
  };
  EXPECT_TRUE(PrivKeyIsInRange(&input));
}

TEST_F(EpidMemberTest, PrivKeyIsInRangeRangeFails) {
  NativePrivKey const input = {
      {
          {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x01},  // group id
          {{{{0xAED33013, 0xD3292DDB, 0x12980A82, 0x0CDC65FB, 0xEE71A49F,
              0x46E5F25E, 0xFFFCF0CD, 0xFFFFFFFF}}},  //< q
           {{{0x82803777, 0x16249880, 0xffa64ba8, 0xae43de62, 0x0acf364f,
              0x9a1b8aad, 0x91e4a81d, 0x1e522316}}}},  // A
          {0x1372c377, 0x00147c6b, 0x46ddb71b, 0xd09db9e4, 0x5a611086,
           0x105eafd8, 0xa1e0d7df, 0x0a30ae43}  // x
      },
      {0x636131c7, 0x362d4135, 0xa707879b, 0xa16567fd, 0xe07cc68e, 0x05d64356,
       0x6d47090b, 0x4840b56c}  // f
  };
  EXPECT_FALSE(PrivKeyIsInRange(&input));
}

//////////////////////////////////////////////////////////////////////////
// PrivKeyIsInGroup Tests
TEST_F(EpidMemberTest, PrivKeyIsInGroupPasses) {
  PairingState pairing_state;
  PairingInit(&pairing_state);
  NativePrivKey const input = {
      {
          {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x01},  // group id
          {{{{0x196254db, 0x570890e8, 0xdaf296ec, 0x87683f4e, 0xeb4caf8a,
              0xacbfdd77, 0xf468e15f, 0x46c969ee}}},
           {{{0x82803777, 0x16249880, 0xffa64ba8, 0xae43de62, 0x0acf364f,
              0x9a1b8aad, 0x91e4a81d, 0x1e522316}}}},  // A
          {0x1372c377, 0x00147c6b, 0x46ddb71b, 0xd09db9e4, 0x5a611086,
           0x105eafd8, 0xa1e0d7df, 0x0a30ae43}  // x
      },
      {0x636131c7, 0x362d4135, 0xa707879b, 0xa16567fd, 0xe07cc68e, 0x05d64356,
       0x6d47090b, 0x4840b56c}  // f
  };
  NativeGroupPubKey const pubkey = {
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x01},  // group id
      {{{{0xb580e099, 0x434c62fd, 0x64cee3ce, 0xd06d8f9d, 0x7e27b0cb,
          0x3d753d61, 0xe21b17eb, 0xb36fff81}}},
       {{{0x74f459ee, 0xd8693ea1, 0x82457e7f, 0xee3d6642, 0xe94dae9c,
          0xfdb5b79d, 0xe08859a4, 0x3a075680}}}},  // h1
      {{{{0xbcdd7fe1, 0x29666163, 0xd55ba704, 0xdc99ed42, 0x5474107b,
          0xd5dbca1c, 0x63c2518e, 0xd2742e9f}}},
       {{{0xe78e1084, 0x93a56ecc, 0xde4ceacb, 0xda3f517d, 0xe85b087b,
          0x48120aa6, 0xe314ac72, 0x765dc06e}}}},  // h2
      {{{{{0x0728e896, 0x8dcd3688, 0x6a95cac6, 0x788753f6, 0x401ba5b6,
           0x50719451, 0xe20fca1c, 0xbd195a95}}},
        {{{0xe2f4b3a1, 0x22d9fde0, 0x0f6c56f5, 0x2414cfd1, 0x15d775f8,
           0xa6657a68, 0xb86ae7e5, 0xca78115b}}}},
       {{{{0x57e4f33c, 0x0a3b5896, 0x89c2399c, 0x898846dd, 0x5deef56a,
           0xbc077230, 0xe8b3c725, 0x9021a7e0}}},
        {{{0xee1140a9, 0x837d3e31, 0x8e25c6ad, 0xba6bf0da, 0x1f3deaa2,
           0x5d0a88db, 0x1bb6f705, 0x79516936}}}}}};
  EXPECT_TRUE(PrivKeyIsInGroup(&input, &pubkey, &pairing_state));
}

TEST_F(EpidMemberTest, PrivKeyIsInGroupFails) {
  PairingState pairing_state;
  PairingInit(&pairing_state);
  NativePrivKey const input = {
      {
          {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x02},  // group id
          {{{{0x196254db, 0x570890e8, 0xdaf296ec, 0x87683f4e, 0xeb4caf8a,
              0xacbfdd77, 0xf468e15f, 0x46c969ee}}},
           {{{0x82803777, 0x16249880, 0xffa64ba8, 0xae43de62, 0x0acf364f,
              0x9a1b8aad, 0x91e4a81d, 0x1e522316}}}},  // A
          {0x1372c377, 0x00147c6b, 0x46ddb71b, 0xd09db9e4, 0x5a611086,
           0x105eafd8, 0xa1e0d7df, 0x0a30ae43}  // x
      },
      {0x636131c7, 0x362d4135, 0xa707879b, 0xa16567fd, 0xe07cc68e, 0x05d64356,
       0x6d47090b, 0x4840b56c}  // f
  };
  NativeGroupPubKey const pubkey = {
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x01},  // group id
      {{{{0xb580e099, 0x434c62fd, 0x64cee3ce, 0xd06d8f9d, 0x7e27b0cb,
          0x3d753d61, 0xe21b17eb, 0xb36fff81}}},
       {{{0x74f459ee, 0xd8693ea1, 0x82457e7f, 0xee3d6642, 0xe94dae9c,
          0xfdb5b79d, 0xe08859a4, 0x3a075680}}}},  // h1
      {{{{0xbcdd7fe1, 0x29666163, 0xd55ba704, 0xdc99ed42, 0x5474107b,
          0xd5dbca1c, 0x63c2518e, 0xd2742e9f}}},
       {{{0xe78e1084, 0x93a56ecc, 0xde4ceacb, 0xda3f517d, 0xe85b087b,
          0x48120aa6, 0xe314ac72, 0x765dc06e}}}},  // h2
      {{{{{0x0728e896, 0x8dcd3688, 0x6a95cac6, 0x788753f6, 0x401ba5b6,
           0x50719451, 0xe20fca1c, 0xbd195a95}}},
        {{{0xe2f4b3a1, 0x22d9fde0, 0x0f6c56f5, 0x2414cfd1, 0x15d775f8,
           0xa6657a68, 0xb86ae7e5, 0xca78115b}}}},
       {{{{0x57e4f33c, 0x0a3b5896, 0x89c2399c, 0x898846dd, 0x5deef56a,
           0xbc077230, 0xe8b3c725, 0x9021a7e0}}},
        {{{0xee1140a9, 0x837d3e31, 0x8e25c6ad, 0xba6bf0da, 0x1f3deaa2,
           0x5d0a88db, 0x1bb6f705, 0x79516936}}}}}};
  EXPECT_FALSE(PrivKeyIsInGroup(&input, &pubkey, &pairing_state));
}

}  // namespace

#endif  // SHARED
