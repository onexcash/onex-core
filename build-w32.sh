#!/bin/sh

# apt-get -y install build-essential g++-mingw-w64-i686 mingw-w64-i686-dev g++-mingw-w64-x86-64 mingw-w64-x86-64-dev make automake pkg-config
# apt-get -y install software-properties-common
# add-apt-repository ppa:bitcoin/bitcoin
# apt-get update
# apt-get -y install libdb4.8-dev libdb4.8++-dev

sed -i 's/version=2.6.1/version=2.5.0/g' depends/packages/native_protobuf.mk
sed -i 's/sha256_hash=ee445612d544d885ae240ffbcbf9267faa9f593b7b101f21d58beceb92661910/sha256_hash=13bfc5ae543cf3aa180ac2485c0bc89495e3ae711fc6fab4f8ffe90dfb4bb677/g' depends/packages/native_protobuf.mk

#
for patch in pidlist_absolute.patch mingw-uuidof.patch fix-xcb-include-order.patch; do
  wget -o ./depends/patches/qt/$patch  "https://raw.githubusercontent.com/dashpay/dash/master/depends/patches/qt/$patch"
done
#

cd depends
make HOST=i686-w64-mingw32 -j$(nproc)
cd ..
./configure --prefix=`pwd`/depends/i686-w64-mingw32
make -j$(nproc)
#
