mkdir asm_build
cd asm_build
emconfigure cmake .. -DCOMPILE_ASM=ON -DJS_ONLY=ON
make
cd ..
