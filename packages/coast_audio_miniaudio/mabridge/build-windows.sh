cd src

ABIS=(x86_64)

for ABI in "${ABIS[@]}"
do
  mkdir -p build/windows
  cd build/windows

  cmake ../../.. -DCMAKE_TOOLCHAIN_FILE=../../../toolchain/mingw-w64-x86_64.toolchain.cmake -DCMAKE_INSTALL_PREFIX="../../../build/windows/x86_64" -DOS=WIN32
  cmake ../.. -DCMAKE_TOOLCHAIN_FILE=../../toolchain/mingw-w64-x86_64.toolchain.cmake -DCMAKE_INSTALL_PREFIX="../../build/windows/x86_64" -DOS=WIN32 -D CMAKE_CFLAGS='-DMAB_WIN32'
  cmake --build . --config Release
  cmake --install . --config Release
  cd ../..
  rm -rf build/windows
done

# move to src/build
cd ../build

mkdir -p ../prebuilt/
cp -r windows ../prebuilt/
