#!/usr/bin/bash
cd ./src/sfmlGraphicsPipeline/build/
rm -rf ./*
cmake ..
make -j6
cd ../../sampleProject/build/
rm -rf ./*
cmake ..
make -j6
./star_warz
cd ../../..
