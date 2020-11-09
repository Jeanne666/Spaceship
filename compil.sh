#!/usr/bin/bash
cd ./src/sfmlGraphicsPipeline/build/
make -j6
cd ../../sampleProject/build/
make -j6
./star_warz
cd ../../..
